"""
贪吃蛇游戏环境模块
基于 Pygame 实现，同时提供 Gym 风格的 API（reset/step/render）
便于与强化学习算法对接。
"""
import os
import pygame
import math
import random
import numpy as np
from collections import deque
from typing import Tuple, List, Optional

# ---------- 赛博朋克配色 ----------
# 背景
BG_DARK       = (5, 5, 15)
BG_PANEL      = (8, 8, 20)
GRID_LINE     = (18, 18, 42)
BORDER_CYAN   = (0, 255, 255)
BORDER_DIM    = (0, 80, 80)

# 侧边栏
SIDEBAR_BG    = (6, 6, 18)
SIDEBAR_LINE  = (0, 100, 120)

# 食物 — 品红/洋红脉冲
FOOD_NEON     = (255, 0, 128)
FOOD_GLOW     = (255, 40, 160)
FOOD_CORE     = (255, 100, 180)
FOOD_HL       = (255, 200, 230)

# 蛇 — 霓虹青色
HEAD_CYAN     = (0, 255, 255)
HEAD_DARK     = (0, 160, 180)
BODY_CYAN_1   = (0, 220, 240)
BODY_CYAN_2   = (0, 120, 160)
BODY_GLOW     = (0, 255, 255, 60)

# 霓虹网格
NEON_CYAN     = (0, 200, 220)
NEON_MAGENTA  = (255, 0, 128)
NEON_YELLOW   = (255, 255, 0)

# 文字
TEXT_WHITE    = (220, 230, 240)
TEXT_DIM      = (80, 90, 110)
TEXT_CYAN     = (0, 255, 255)
TEXT_MAGENTA  = (255, 0, 128)
TEXT_GOLD     = (255, 255, 0)
TEXT_GREEN    = (0, 255, 128)
TEXT_RED      = (255, 50, 80)
PANEL_BG      = (0, 0, 0, 200)


class Direction:
    """方向枚举，使用 one-hot 编码便于网络学习"""
    RIGHT = 0
    UP    = 1
    LEFT  = 2
    DOWN  = 3


MODE_MANUAL = 0
MODE_TRAIN  = 1
MODE_LABELS = ["MANUAL PLAY", "TRAIN"]
MODE_DESCS  = ["Arrow keys to control", "Train neural network"]
MODE_COLORS = [TEXT_CYAN, TEXT_GOLD]


class SnakeGame:
    """
    贪吃蛇游戏环境
    网格大小: GRID_SIZE x GRID_SIZE
    每个格子大小: CELL_SIZE 像素
    """

    # 动作空间: 直行 / 右转 / 左转（共 3 个动作，避免直接 4 方向冗余）
    ACTION_SPACE_SIZE = 3
    SIDEBAR_WIDTH = 200

    def __init__(self, grid_size: int = 10, cell_size: int = 40,
                 speed: int = 3, render_mode: bool = False,
                 max_steps_without_food: int = 100):
        self.grid_size = grid_size
        self.cell_size = cell_size
        self.base_speed = speed
        self.speed = speed
        self.max_speed = 25
        self.render_mode = render_mode
        self.max_steps_without_food = max_steps_without_food

        self.game_width = grid_size * cell_size
        self.game_height = grid_size * cell_size
        self.width = self.game_width + self.SIDEBAR_WIDTH
        self.height = self.game_height

        self.STATE_SIZE = 13

        self.screen: Optional[pygame.Surface] = None
        self.clock: Optional[pygame.time.Clock] = None
        self.frame_count = 0
        self.best_score = 0
        self.best_score_session = 0
        self.episode_count = 0
        self.food_pulse = 0.0
        self.paused = False
        self.show_mode_select = True
        self.selected_mode = 0
        self.mode = MODE_MANUAL
        self.mode_count = 2
        self.agent = None
        self.use_rl_snake = False
        self.rl_checkbox_rect = None
        self.no_model_msg = ""
        self.no_model_timer = 0
        self.training_scores = []
        self.training_mean_scores = []
        self.train_episode = 0
        self.train_total = 0
        self.food_counter = 0

        self._scanline_surf: Optional[pygame.Surface] = None
        self._font_cache: dict = {}

        if self.render_mode:
            pygame.init()
            pygame.display.set_caption("RL Snake  -  Reinforcement Learning Snake")
            self.screen = pygame.display.set_mode((self.width, self.height))
            self.clock = pygame.time.Clock()
            self._init_cached_surfaces()

        self.snake: Optional[deque] = None
        self.food: Optional[Tuple[int, int]] = None
        self.direction: int = Direction.RIGHT
        self.score: int = 0
        self.frame_iteration: int = 0
        self.steps_without_food: int = 0

    # ----------------- 核心 API -----------------

    def _init_cached_surfaces(self):
        gw = self.game_width
        gh = self.game_height
        self._scanline_surf = pygame.Surface((gw, gh), pygame.SRCALPHA)
        for sy in range(0, gh, 3):
            pygame.draw.line(self._scanline_surf, (0, 0, 0, 25), (0, sy), (gw, sy), 1)

    def _get_font(self, name: str, size: int, bold: bool = False):
        key = (name, size, bold)
        if key not in self._font_cache:
            try:
                f = pygame.font.SysFont(name, size, bold=bold)
                if f is None:
                    raise RuntimeError
                self._font_cache[key] = f
            except Exception:
                self._font_cache[key] = pygame.font.Font(None, size + 10)
        return self._font_cache[key]

    def _update_speed(self):
        self.speed = min(self.max_speed, int(self.base_speed + math.sqrt(self.score) * 0.8))

    def reset(self) -> np.ndarray:
        """重置环境到初始状态，返回初始观察"""
        self.episode_count += 1
        if self.score > self.best_score:
            self.best_score = self.score
        if self.score > self.best_score_session:
            self.best_score_session = self.score
        center = (self.grid_size // 2, self.grid_size // 2)
        self.snake = deque([
            (center[0], center[1]),
            (center[0] - 1, center[1]),
            (center[0] - 2, center[1]),
        ])
        self.direction = Direction.RIGHT
        self.score = 0
        self.frame_iteration = 0
        self.steps_without_food = 0
        self.speed = self.base_speed
        self.food_counter = 0
        self._place_food()
        return self.get_state()

    def step(self, action: int) -> Tuple[np.ndarray, float, bool, dict]:
        """
        执行一步动作
        参数:
            action: 0=直行, 1=右转, 2=左转
        返回:
            state: 新的状态
            reward: 奖励
            done: 是否结束
            info: 附加信息（分数等）
        """
        self.frame_iteration += 1
        self.steps_without_food += 1

        # 1) 根据动作更新方向
        self._update_direction(action)

        # 2) 计算新的蛇头位置
        head_x, head_y = self.snake[0]
        dx, dy = self._dir_to_delta(self.direction)
        new_head = (head_x + dx, head_y + dy)

        # 3) 判断游戏是否结束
        #    - 撞墙
        #    - 撞自己
        #    - 长时间没吃到食物（防止死循环）
        game_over = False
        if self._is_collision(new_head):
            game_over = True
            reward = -10.0     # 撞墙/撞自己，大惩罚
            return self.get_state(), reward, game_over, {"score": self.score}

        if self.steps_without_food > self.max_steps_without_food * len(self.snake):
            game_over = True
            reward = -10.0
            return self.get_state(), reward, game_over, {"score": self.score}

        # 4) 移动蛇身
        self.snake.appendleft(new_head)

        # 5) 判定是否吃到食物
        reward = 0.0
        if new_head == self.food:
            self.score += 1
            self.food_counter += 1
            reward = 10.0              # 吃到食物，大奖励
            self.steps_without_food = 0
            self._place_food()
            self._update_speed()
            # 每吃2个豆才增长1节
            if self.food_counter % 2 == 0:
                pass  # 不pop尾巴，蛇增长
            else:
                self.snake.pop()  # 吃1个豆不增长
        else:
            self.snake.pop()           # 没吃到就去掉尾巴
            reward = -0.01             # 每走一步小惩罚，鼓励尽快吃到食物

        # 6) 可选：渲染
        if self.render_mode:
            self._render()

        # 7) 限制最大步数
        if self.frame_iteration > 100 * len(self.snake):
            game_over = True

        return self.get_state(), reward, game_over, {"score": self.score}

    def get_state(self) -> np.ndarray:
        """
        返回当前状态的特征向量（13 维）:
        [0]  是否有障碍物在直行方向
        [1]  是否有障碍物在右转方向
        [2]  是否有障碍物在左转方向
        [3]  当前方向是否向左
        [4]  当前方向是否向右
        [5]  当前方向是否向上
        [6]  当前方向是否向下
        [7]  食物是否在蛇头左侧
        [8]  食物是否在蛇头右侧
        [9]  食物是否在蛇头上方
        [10] 食物是否在蛇头下方
        [11] 食物x方向距离（归一化 [-1,1]）
        [12] 食物y方向距离（归一化 [-1,1]）
        """
        head_x, head_y = self.snake[0]
        dir_left  = self.direction == Direction.LEFT
        dir_right = self.direction == Direction.RIGHT
        dir_up    = self.direction == Direction.UP
        dir_down  = self.direction == Direction.DOWN

        # 计算三个相对方向上的位置点
        point_straight = self._next_point(head_x, head_y, self.direction)
        point_right    = self._next_point(head_x, head_y, (self.direction + 1) % 4)
        point_left     = self._next_point(head_x, head_y, (self.direction - 1) % 4)

        # 食物距离归一化
        food_dx = (self.food[0] - head_x) / self.grid_size
        food_dy = (self.food[1] - head_y) / self.grid_size

        state = [
            # 障碍物检测
            int(self._is_collision(point_straight)),
            int(self._is_collision(point_right)),
            int(self._is_collision(point_left)),
            # 自身方向（one-hot）
            int(dir_left),
            int(dir_right),
            int(dir_up),
            int(dir_down),
            # 食物相对位置
            int(self.food[0] < head_x),  # 食物在左
            int(self.food[0] > head_x),  # 食物在右
            int(self.food[1] < head_y),  # 食物在上
            int(self.food[1] > head_y),  # 食物在下
            # 食物距离（新增）
            food_dx,
            food_dy,
        ]
        return np.array(state, dtype=np.float32)

    def close(self):
        """关闭 Pygame 窗口"""
        if self.screen is not None:
            pygame.quit()
            self.screen = None
            self.clock = None

    # ----------------- 覆盖层绘制 -----------------

    def _draw_mode_overlay(self):
        """绘制模式选择覆盖层"""
        gw = self.game_width
        gh = self.game_height
        overlay = pygame.Surface((gw, gh), pygame.SRCALPHA)
        overlay.fill((0, 0, 0, 160))
        self.screen.blit(overlay, (0, 0))

        font_title = self._get_font("consolas", 24, bold=True)
        font_opt   = self._get_font("consolas", 16, bold=True)
        font_desc  = self._get_font("consolas", 11)
        font_hint  = self._get_font("consolas", 10)

        cx = gw // 2
        cy = gh // 2 - 30

        title = font_title.render("SELECT MODE", True, TEXT_CYAN)
        self.screen.blit(title, (cx - title.get_width() // 2, cy - 80))

        pygame.draw.line(self.screen, TEXT_CYAN, (cx - 120, cy - 55), (cx + 120, cy - 55), 1)

        opt_h = 50
        for i in range(self.mode_count):
            oy = cy - 20 + i * opt_h
            is_sel = (i == self.selected_mode)
            color = MODE_COLORS[i] if is_sel else TEXT_DIM

            if is_sel:
                pygame.draw.rect(self.screen, (color[0], color[1], color[2]),
                                 (cx - 130, oy - 4, 260, 40), 2, border_radius=4)
                inner = pygame.Surface((252, 32), pygame.SRCALPHA)
                inner.fill((*color, 20))
                self.screen.blit(inner, (cx - 126, oy))

            label = font_opt.render(MODE_LABELS[i], True, color)
            self.screen.blit(label, (cx - label.get_width() // 2, oy + 2))

            desc = font_desc.render(MODE_DESCS[i], True, TEXT_DIM if is_sel else (40, 50, 70))
            self.screen.blit(desc, (cx - desc.get_width() // 2, oy + 24))

        hint = font_hint.render("[UP/DOWN] Select   [ENTER] Confirm", True, TEXT_DIM)
        self.screen.blit(hint, (cx - hint.get_width() // 2, cy + 140))

    def _draw_pause_overlay(self):
        """绘制暂停覆盖层"""
        gw = self.game_width
        gh = self.game_height
        overlay = pygame.Surface((gw, gh), pygame.SRCALPHA)
        overlay.fill((0, 0, 0, 140))
        self.screen.blit(overlay, (0, 0))

        font_big = self._get_font("consolas", 32, bold=True)
        font_hint = self._get_font("consolas", 12)

        cx = gw // 2
        cy = gh // 2

        blink = 0.7 + 0.3 * math.sin(self.frame_count * 0.08)
        pc = (int(TEXT_CYAN[0] * blink), int(TEXT_CYAN[1] * blink), int(TEXT_CYAN[2] * blink))
        title = font_big.render("PAUSED", True, pc)
        self.screen.blit(title, (cx - title.get_width() // 2, cy - 20))

        hint = font_hint.render("[SPACE] Resume   [ESC] Quit", True, TEXT_DIM)
        self.screen.blit(hint, (cx - hint.get_width() // 2, cy + 25))

    # ----------------- 内部辅助方法 -----------------

    def _place_food(self):
        """在空白格子上随机放置一个食物"""
        while True:
            x = random.randint(0, self.grid_size - 1)
            y = random.randint(0, self.grid_size - 1)
            if (x, y) not in self.snake:
                self.food = (x, y)
                return

    def _update_direction(self, action: int):
        """
        根据动作更新朝向
        action: 0=直行, 1=右转, 2=左转
        """
        # 方向顺序: 右(0) -> 上(1) -> 左(2) -> 下(3) -> 右(0)...
        clockwise = [Direction.RIGHT, Direction.UP, Direction.LEFT, Direction.DOWN]
        idx = clockwise.index(self.direction)
        if action == 1:    # 右转
            idx = (idx + 1) % 4
        elif action == 2:  # 左转
            idx = (idx - 1) % 4
        # action == 0: 直行，方向不变
        self.direction = clockwise[idx]

    @staticmethod
    def _dir_to_delta(direction: int) -> Tuple[int, int]:
        """方向 -> (dx, dy) 位移"""
        if direction == Direction.RIGHT: return (1, 0)
        if direction == Direction.LEFT:  return (-1, 0)
        if direction == Direction.UP:    return (0, -1)
        if direction == Direction.DOWN:  return (0, 1)
        return (0, 0)

    def _next_point(self, x: int, y: int, direction: int) -> Tuple[int, int]:
        """根据方向计算 (x,y) 前面一格的位置（可能出界）"""
        dx, dy = self._dir_to_delta(direction)
        return (x + dx, y + dy)

    def _is_collision(self, point: Optional[Tuple[int, int]] = None) -> bool:
        """
        判断 point 是否发生碰撞
        碰撞条件: 越界 或 撞到蛇身
        """
        if point is None:
            point = self.snake[0]
        x, y = point
        # 撞墙
        if not (0 <= x < self.grid_size and 0 <= y < self.grid_size):
            return True
        # 撞自己（注意：蛇尾下一步会移动，所以蛇尾位置不算碰撞）
        body = list(self.snake)[:-1] if len(self.snake) > 1 else list(self.snake)
        return point in body

    def _render(self):
        """绘制游戏画面 — 赛博朋克霓虹主题（性能优化版）"""
        assert self.screen is not None, "请先开启 render_mode"
        self.frame_count += 1
        self.food_pulse += 0.15

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                raise SystemExit(0)

        c = self.cell_size
        gw = self.game_width
        gh = self.game_height

        # ── 背景 ──
        self.screen.fill(BG_DARK)

        # 暗色棋盘格
        for gx in range(self.grid_size):
            for gy in range(self.grid_size):
                if (gx + gy) % 2 == 1:
                    pygame.draw.rect(self.screen, (10, 10, 25),
                                     (gx * c, gy * c, c, c))

        # 霓虹网格线
        for i, x in enumerate(range(0, gw + 1, c)):
            color = NEON_CYAN if i % 4 == 0 else GRID_LINE
            pygame.draw.line(self.screen, color, (x, 0), (x, gh), 1)
        for i, y in enumerate(range(0, gh + 1, c)):
            color = NEON_MAGENTA if i % 4 == 0 else GRID_LINE
            pygame.draw.line(self.screen, color, (0, y), (gw, y), 1)

        # ── 食物 ──
        fx, fy = self.food
        food_cx = fx * c + c // 2
        food_cy = fy * c + c // 2
        pulse = 1.0 + 0.15 * math.sin(self.food_pulse)
        r_mid = int(c * 0.38 * pulse)
        pygame.draw.circle(self.screen, FOOD_GLOW, (food_cx, food_cy), r_mid)
        r_in = int(c * 0.25 * pulse)
        pygame.draw.circle(self.screen, FOOD_CORE, (food_cx, food_cy), r_in)

        # ── 蛇 ──
        margin = max(1, c // 8)
        radius = max(2, c // 5)

        for i, (sx, sy) in enumerate(self.snake):
            rx = sx * c + margin
            ry = sy * c + margin
            rw = c - 2 * margin
            rh = c - 2 * margin
            rect = pygame.Rect(rx, ry, rw, rh)

            if i == 0:
                head_margin = margin // 2
                hr = pygame.Rect(sx * c + head_margin, sy * c + head_margin,
                                 c - 2 * head_margin, c - 2 * head_margin)
                hr_r = max(2, c // 4)
                pygame.draw.rect(self.screen, HEAD_CYAN, hr, border_radius=hr_r)
                pygame.draw.rect(self.screen, HEAD_DARK, hr, 2, border_radius=hr_r)
                eye_r = max(2, c // 10)
                if self.direction == Direction.RIGHT:
                    eye_positions = [(sx * c + c - c // 3, sy * c + c // 4),
                                     (sx * c + c - c // 3, sy * c + c - c // 4)]
                elif self.direction == Direction.LEFT:
                    eye_positions = [(sx * c + c // 3, sy * c + c // 4),
                                     (sx * c + c // 3, sy * c + c - c // 4)]
                elif self.direction == Direction.UP:
                    eye_positions = [(sx * c + c // 4, sy * c + c // 3),
                                     (sx * c + c - c // 4, sy * c + c // 3)]
                else:
                    eye_positions = [(sx * c + c // 4, sy * c + c - c // 3),
                                     (sx * c + c - c // 4, sy * c + c - c // 3)]
                for ep in eye_positions:
                    pygame.draw.circle(self.screen, (255, 255, 255), ep, eye_r)
                    pygame.draw.circle(self.screen, (0, 20, 30), ep, max(1, eye_r // 2))
            else:
                t = i / max(len(self.snake) - 1, 1)
                rv = int(BODY_CYAN_1[0] * (1 - t) + BODY_CYAN_2[0] * t)
                gv = int(BODY_CYAN_1[1] * (1 - t) + BODY_CYAN_2[1] * t)
                bv = int(BODY_CYAN_1[2] * (1 - t) + BODY_CYAN_2[2] * t)
                pygame.draw.rect(self.screen, (rv, gv, bv), rect, border_radius=radius)
                pygame.draw.rect(self.screen, (0, 255, 255), rect, 1, border_radius=radius)

        # ── 游戏区域边框 ──
        pygame.draw.rect(self.screen, BORDER_CYAN, (0, 0, gw, gh), 2)

        # ── 侧边栏 ──
        sx = gw
        pygame.draw.rect(self.screen, SIDEBAR_BG, (sx, 0, self.SIDEBAR_WIDTH, gh))
        pygame.draw.line(self.screen, SIDEBAR_LINE, (sx, 0), (sx, gh), 2)

        font_title = self._get_font("consolas", 14, bold=True)
        font_big   = self._get_font("consolas", 24, bold=True)
        font_med   = self._get_font("consolas", 11, bold=True)
        font_small = self._get_font("consolas", 10)

        px = sx + 10
        py = 10

        # ── 标题 ──
        title = font_title.render("// RL SNAKE", True, TEXT_MAGENTA)
        self.screen.blit(title, (px, py))
        py += 18
        pygame.draw.line(self.screen, TEXT_MAGENTA, (px, py), (sx + self.SIDEBAR_WIDTH - 10, py), 1)
        py += 8

        # ── SCORE ──
        lbl = font_med.render("SCORE", True, TEXT_CYAN)
        self.screen.blit(lbl, (px, py))
        py += 14
        val = font_big.render(str(self.score), True, TEXT_GOLD)
        self.screen.blit(val, (px + 2, py))
        py += 30

        # ── BEST ──
        lbl = font_med.render("BEST", True, TEXT_CYAN)
        self.screen.blit(lbl, (px, py))
        py += 14
        best_val = max(self.best_score, self.best_score_session)
        val = font_big.render(str(best_val), True, TEXT_GREEN)
        self.screen.blit(val, (px + 2, py))
        py += 30

        pygame.draw.line(self.screen, SIDEBAR_LINE, (px, py), (sx + self.SIDEBAR_WIDTH - 10, py), 1)
        py += 6

        # ── LENGTH / STEPS 一行两个 ──
        mid = sx + self.SIDEBAR_WIDTH // 2
        lbl = font_med.render("LEN", True, TEXT_DIM)
        self.screen.blit(lbl, (px, py))
        val = font_med.render(str(len(self.snake)), True, TEXT_WHITE)
        self.screen.blit(val, (px + 30, py))
        lbl2 = font_med.render("STEP", True, TEXT_DIM)
        self.screen.blit(lbl2, (mid, py))
        val2 = font_med.render(str(self.frame_iteration), True, TEXT_WHITE)
        self.screen.blit(val2, (mid + 32, py))
        py += 16

        # ── EPISODE / SPEED 一行两个 ──
        lbl = font_med.render("EP", True, TEXT_DIM)
        self.screen.blit(lbl, (px, py))
        if self.mode == MODE_TRAIN and hasattr(self, 'train_episode'):
            val = font_med.render(f"{self.train_episode}/{self.train_total}", True, TEXT_WHITE)
        else:
            val = font_med.render(str(self.episode_count), True, TEXT_WHITE)
        self.screen.blit(val, (px + 22, py))
        lbl2 = font_med.render("SPD", True, TEXT_DIM)
        self.screen.blit(lbl2, (mid, py))
        val2 = font_med.render(f"{self.speed}", True, TEXT_WHITE)
        self.screen.blit(val2, (mid + 28, py))
        py += 16

        pygame.draw.line(self.screen, SIDEBAR_LINE, (px, py), (sx + self.SIDEBAR_WIDTH - 10, py), 1)
        py += 6

        # ── DIRECTION ──
        dir_names = {Direction.RIGHT: "RIGHT", Direction.LEFT: "LEFT",
                     Direction.UP: "UP", Direction.DOWN: "DOWN"}
        lbl = font_med.render("DIR", True, TEXT_DIM)
        self.screen.blit(lbl, (px, py))
        name_surf = font_med.render(dir_names[self.direction], True, TEXT_CYAN)
        self.screen.blit(name_surf, (px + 28, py))
        py += 16

        pygame.draw.line(self.screen, SIDEBAR_LINE, (px, py), (sx + self.SIDEBAR_WIDTH - 10, py), 1)
        py += 6

        # ── TRAIN PROGRESS ──
        if self.mode == MODE_TRAIN and self.training_scores:
            lbl = font_med.render("TRAIN", True, TEXT_MAGENTA)
            self.screen.blit(lbl, (px, py))
            py += 14
            recent = self.training_scores[-20:]
            mean_s = sum(recent) / len(recent)
            lbl = font_small.render(f"Avg20: {mean_s:.1f}", True, TEXT_GREEN)
            self.screen.blit(lbl, (px, py))
            py += 12
            lbl = font_small.render(f"Best: {self.best_score}", True, TEXT_GOLD)
            self.screen.blit(lbl, (px, py))
            py += 14
            pygame.draw.line(self.screen, SIDEBAR_LINE, (px, py), (sx + self.SIDEBAR_WIDTH - 10, py), 1)
            py += 6

        # ── RL Snake 复选框 ──
        cb_size = 16
        cb_x = px
        cb_y = py
        self.rl_checkbox_rect = pygame.Rect(cb_x - 4, cb_y - 4, cb_size + 100, cb_size + 8)
        if self.use_rl_snake:
            pygame.draw.rect(self.screen, TEXT_GREEN, (cb_x, cb_y, cb_size, cb_size), border_radius=3)
            pygame.draw.rect(self.screen, (0, 40, 20), (cb_x, cb_y, cb_size, cb_size), 2, border_radius=3)
            check_pts = [(cb_x + 3, cb_y + cb_size // 2), (cb_x + 6, cb_y + cb_size - 4), (cb_x + cb_size - 3, cb_y + 4)]
            pygame.draw.lines(self.screen, (0, 20, 10), False, check_pts, 3)
        else:
            pygame.draw.rect(self.screen, TEXT_DIM, (cb_x, cb_y, cb_size, cb_size), 2, border_radius=3)
        lbl_rl = font_med.render("RL SNAKE", True, TEXT_GREEN if self.use_rl_snake else TEXT_DIM)
        self.screen.blit(lbl_rl, (cb_x + cb_size + 6, cb_y + 1))
        py += 22

        # ── 状态文字 ──
        if self.use_rl_snake and self.agent is not None:
            status = font_small.render(">> AUTO PLAY", True, TEXT_GREEN)
            self.screen.blit(status, (px, py))
            py += 14
        elif self.no_model_timer > 0:
            self.no_model_timer -= 1
            msg_surf = font_small.render(self.no_model_msg, True, TEXT_RED)
            self.screen.blit(msg_surf, (px, py))
            py += 14
        py += 4

        pygame.draw.line(self.screen, SIDEBAR_LINE, (px, py), (sx + self.SIDEBAR_WIDTH - 10, py), 1)
        py += 6

        pause_txt = "PAUSED" if self.paused else "[SPACE] PAUSE"
        lbl = font_small.render(pause_txt, True, TEXT_GOLD if self.paused else TEXT_DIM)
        self.screen.blit(lbl, (px, py))
        py += 12
        lbl = font_small.render("[ESC] QUIT", True, TEXT_DIM)
        self.screen.blit(lbl, (px, py))

        # ── 扫描线（使用缓存） ──
        if self._scanline_surf:
            self.screen.blit(self._scanline_surf, (0, 0))

        # ── 覆盖层 ──
        if self.show_mode_select:
            self._draw_mode_overlay()
        elif self.paused:
            self._draw_pause_overlay()

        pygame.display.flip()


def human_play():
    """
    手动模式入口 — 直接进入手动控制，跳过模式选择
    """
    env = SnakeGame(grid_size=10, cell_size=40, speed=3, render_mode=True)
    env.show_mode_select = False
    env.mode = MODE_MANUAL
    state = env.reset()

    clockwise = [Direction.RIGHT, Direction.UP, Direction.LEFT, Direction.DOWN]
    key_to_dir = {
        pygame.K_UP: Direction.UP,
        pygame.K_DOWN: Direction.DOWN,
        pygame.K_LEFT: Direction.LEFT,
        pygame.K_RIGHT: Direction.RIGHT,
    }
    pending_dir = env.direction
    running = True

    last_step_time = 0
    step_interval = 1000 // env.speed

    while running:
        now = pygame.time.get_ticks()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                break

            if event.type != pygame.KEYDOWN:
                continue

            if event.key == pygame.K_ESCAPE:
                running = False
                continue

            # 暂停切换
            if event.key == pygame.K_SPACE:
                env.paused = not env.paused
                continue

            if env.mode == MODE_MANUAL and not env.use_rl_snake:
                if event.key in key_to_dir:
                    new_dir = key_to_dir[event.key]
                    # 检查是否是反方向，如果是则忽略
                    opposite = {
                        Direction.UP: Direction.DOWN,
                        Direction.DOWN: Direction.UP,
                        Direction.LEFT: Direction.RIGHT,
                        Direction.RIGHT: Direction.LEFT,
                    }
                    if new_dir != opposite.get(env.direction):
                        pending_dir = new_dir

        if not running:
            break

        env._render()

        if env.show_mode_select or env.paused:
            env.clock.tick(30)
            continue

        if now - last_step_time < step_interval:
            env.clock.tick(30)
            continue
        last_step_time = now

        if env.mode == MODE_MANUAL:
            if env.use_rl_snake:
                if env.agent is not None:
                    action = env.agent.act(state, training=False)
                    state, reward, done, info = env.step(action)
                    if done:
                        pygame.time.wait(400)
                        state = env.reset()
                else:
                    env.use_rl_snake = False
                    env.no_model_msg = "No model! Train first."
                    env.no_model_timer = 120
            else:
                # 直接根据pending_dir计算action，更灵敏
                direction_map = {
                    (Direction.RIGHT, Direction.RIGHT): 0,
                    (Direction.RIGHT, Direction.UP): 1,
                    (Direction.RIGHT, Direction.LEFT): 0,
                    (Direction.RIGHT, Direction.DOWN): 2,
                    (Direction.UP, Direction.RIGHT): 2,
                    (Direction.UP, Direction.UP): 0,
                    (Direction.UP, Direction.LEFT): 1,
                    (Direction.UP, Direction.DOWN): 0,
                    (Direction.LEFT, Direction.RIGHT): 0,
                    (Direction.LEFT, Direction.UP): 2,
                    (Direction.LEFT, Direction.LEFT): 0,
                    (Direction.LEFT, Direction.DOWN): 1,
                    (Direction.DOWN, Direction.RIGHT): 1,
                    (Direction.DOWN, Direction.UP): 0,
                    (Direction.DOWN, Direction.LEFT): 2,
                    (Direction.DOWN, Direction.DOWN): 0,
                }
                action = direction_map.get((env.direction, pending_dir), 0)
                state, reward, done, info = env.step(action)
                step_interval = 1000 // env.speed
                if done:
                    pygame.time.wait(800)
                    state = env.reset()
                    pending_dir = env.direction

        env.clock.tick(30)

    env.close()


def rl_play():
    """
    强化训练后模式入口 — 加载训练好的模型，AI自动玩
    """
    env = SnakeGame(grid_size=10, cell_size=40, speed=3, render_mode=True)
    env.show_mode_select = False
    env.mode = MODE_MANUAL
    env.use_rl_snake = True
    _load_rl_agent(env)
    state = env.reset()

    running = True
    last_step_time = 0
    step_interval = 1000 // env.speed

    while running:
        now = pygame.time.get_ticks()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                break

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False

        if not running:
            break

        env._render()

        if now - last_step_time < step_interval:
            env.clock.tick(30)
            continue
        last_step_time = now

        if env.agent is not None:
            action = env.agent.act(state, training=False)
            state, reward, done, info = env.step(action)
            if done:
                pygame.time.wait(400)
                state = env.reset()

        step_interval = 1000 // env.speed
        env.clock.tick(30)

    env.close()


def _load_rl_agent(env):
    """加载训练好的 RL 模型用于自动游玩"""
    import os
    import sys
    sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    from agent.dqn_agent import DQNAgent

    model_path = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                              "models", "snake_dqn.pth")
    if not os.path.exists(model_path):
        env.use_rl_snake = False
        env.no_model_msg = "No model found! Train first."
        env.no_model_timer = 120
        return

    agent = DQNAgent(
        state_size=env.STATE_SIZE,
        action_size=env.ACTION_SPACE_SIZE,
        hidden_size=256,
        device="cpu",
    )
    agent.load(model_path, load_optimizer=False)
    agent.epsilon = 0.0
    env.agent = agent


def _start_train_mode(env):
    """初始化训练模式"""
    import os
    import sys
    sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    from agent.dqn_agent import DQNAgent

    env.agent = DQNAgent(
        state_size=env.STATE_SIZE,
        action_size=env.ACTION_SPACE_SIZE,
        hidden_size=256,
        lr=1e-3,
        gamma=0.9,
        epsilon_start=1.0,
        epsilon_end=0.01,
        epsilon_decay=0.999,
        buffer_size=100_000,
        batch_size=64,
        target_update_every=100,
        device="cpu",
    )
    env.train_episode = 0
    env.train_total = 500
    env.training_scores = []
    env.training_mean_scores = []
    env.best_score = 0
    env.render_mode = False


def _step_train(env):
    """训练模式：执行一步训练（不渲染，每回合结束后刷新画面）"""
    import numpy as np

    state = env.get_state()
    action = env.agent.act(state, training=True)
    next_state, reward, done, info = env.step(action)
    env.agent.remember(state, action, reward, next_state, done)
    env.agent.learn()

    if done:
        env.train_episode += 1
        score = info["score"]
        env.training_scores.append(score)
        recent = env.training_scores[-20:]
        mean_s = np.mean(recent)
        env.training_mean_scores.append(mean_s)
        if score > env.best_score:
            env.best_score = score
        state = env.reset()

        if env.train_episode >= env.train_total:
            save_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "models")
            os.makedirs(save_dir, exist_ok=True)
            save_path = os.path.join(save_dir, "snake_dqn.pth")
            env.agent.save(save_path)
            env.show_mode_select = True
            env.selected_mode = 0
            env.agent = None
            env.render_mode = True
            env._render()
            return

        env._render()


if __name__ == "__main__":
    # 手动玩小游戏，方便体验
    human_play()
