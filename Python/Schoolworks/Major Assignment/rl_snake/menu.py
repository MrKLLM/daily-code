"""
主菜单 — 赛博朋克风格
选择: 一般模式 / 强化训练后模式
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import pygame
import math

# ── 配色 ──
BG           = (5, 5, 15)
NEON_CYAN    = (0, 255, 255)
NEON_MAGENTA = (255, 0, 128)
NEON_YELLOW  = (255, 255, 0)
NEON_GREEN   = (0, 255, 128)
DIM_CYAN     = (0, 80, 100)
DIM_MAGENTA  = (100, 0, 50)
TEXT_WHITE    = (220, 230, 240)
TEXT_DIM      = (60, 70, 90)
GRID_COLOR   = (15, 15, 38)
SCANLINE     = (0, 0, 0, 18)

# ── 按钮定义 ──
BUTTONS = [
    {"label": "MANUAL PLAY",   "desc": "Arrow keys to control",   "action": "manual",  "color": NEON_CYAN},
    {"label": "RL AUTO PLAY",  "desc": "AI plays with trained model", "action": "rl",  "color": NEON_GREEN},
]


def draw_menu(screen, w, h, frame, selected):
    """绘制赛博朋克菜单"""
    screen.fill(BG)

    # ── 背景网格 ──
    for x in range(0, w, 40):
        pygame.draw.line(screen, GRID_COLOR, (x, 0), (x, h), 1)
    for y in range(0, h, 40):
        pygame.draw.line(screen, GRID_COLOR, (0, y), (w, y), 1)

    # ── 扫描线 ──
    scan = pygame.Surface((w, h), pygame.SRCALPHA)
    for sy in range(0, h, 3):
        pygame.draw.line(scan, SCANLINE, (0, sy), (w, sy), 1)
    screen.blit(scan, (0, 0))

    # ── 标题 ──
    try:
        font_title = pygame.font.SysFont("consolas", 48, bold=True)
        font_sub   = pygame.font.SysFont("consolas", 14)
        font_btn   = pygame.font.SysFont("consolas", 22, bold=True)
        font_desc  = pygame.font.SysFont("consolas", 12)
        font_hint  = pygame.font.SysFont("consolas", 11)
        if font_title is None:
            raise RuntimeError
    except Exception:
        font_title = pygame.font.Font(None, 72)
        font_sub   = pygame.font.Font(None, 20)
        font_btn   = pygame.font.Font(None, 36)
        font_desc  = pygame.font.Font(None, 18)
        font_hint  = pygame.font.Font(None, 16)

    # 标题闪烁效果
    blink = 0.6 + 0.4 * math.sin(frame * 0.05)
    title_color = (int(NEON_CYAN[0] * blink), int(NEON_CYAN[1] * blink), int(NEON_CYAN[2] * blink))
    title = font_title.render("RL  SNAKE", True, title_color)
    title_x = w // 2 - title.get_width() // 2
    screen.blit(title, (title_x, 60))

    # 副标题
    sub = font_sub.render("// REINFORCEMENT LEARNING Snake //", True, TEXT_DIM)
    screen.blit(sub, (w // 2 - sub.get_width() // 2, 120))

    # 标题下横线
    line_y = 148
    pygame.draw.line(screen, NEON_CYAN, (w // 2 - 160, line_y), (w // 2 + 160, line_y), 1)

    # ── 按钮 ──
    btn_w = 320
    btn_h = 70
    start_y = 190
    gap = 20

    for i, btn in enumerate(BUTTONS):
        bx = w // 2 - btn_w // 2
        by = start_y + i * (btn_h + gap)
        rect = pygame.Rect(bx, by, btn_w, btn_h)

        is_hover = (i == selected)

        if is_hover:
            # 选中状态 — 霓虹发光
            glow = pygame.Surface((btn_w + 12, btn_h + 12), pygame.SRCALPHA)
            glow_c = btn["color"]
            pygame.draw.rect(glow, (*glow_c, 30), (0, 0, btn_w + 12, btn_h + 12), border_radius=8)
            screen.blit(glow, (bx - 6, by - 6))
            pygame.draw.rect(screen, btn["color"], rect, 2, border_radius=6)
            # 内部填充 — 低透明度，不遮挡文字
            inner = pygame.Surface((btn_w - 8, btn_h - 8), pygame.SRCALPHA)
            inner.fill((*btn["color"], 15))
            screen.blit(inner, (bx + 4, by + 4))
        else:
            pygame.draw.rect(screen, DIM_CYAN, rect, 1, border_radius=6)

        # 按钮文字
        label = font_btn.render(btn["label"], True, btn["color"] if is_hover else TEXT_DIM)
        lx = bx + btn_w // 2 - label.get_width() // 2
        ly = by + 14
        screen.blit(label, (lx, ly))

        # 描述
        desc = font_desc.render(btn["desc"], True, TEXT_DIM if is_hover else (40, 50, 70))
        dx = bx + btn_w // 2 - desc.get_width() // 2
        dy = by + 44
        screen.blit(desc, (dx, dy))

    # ── 底部提示 ──
    hint = font_hint.render("[UP/DOWN] Select    [ENTER] Confirm    [ESC] Quit", True, TEXT_DIM)
    screen.blit(hint, (w // 2 - hint.get_width() // 2, h - 40))

    # ── 右下角装饰 ──
    ver = font_hint.render("v1.0", True, (30, 40, 60))
    screen.blit(ver, (w - 50, h - 25))

    pygame.display.flip()


def main():
    pygame.init()
    w, h = 520, 500
    screen = pygame.display.set_mode((w, h))
    pygame.display.set_caption("RL Snake - Main Menu")
    clock = pygame.time.Clock()

    selected = 0
    frame = 0
    running = True

    while running:
        frame += 1
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    running = False
                elif event.key == pygame.K_UP:
                    selected = (selected - 1) % len(BUTTONS)
                elif event.key == pygame.K_DOWN:
                    selected = (selected + 1) % len(BUTTONS)
                elif event.key in (pygame.K_RETURN, pygame.K_SPACE):
                    action = BUTTONS[selected]["action"]
                    pygame.quit()
                    if action == "manual":
                        from game.snake_game import human_play
                        human_play()
                    elif action == "rl":
                        from game.snake_game import rl_play
                        rl_play()
                    return

        draw_menu(screen, w, h, frame, selected)
        clock.tick(30)

    pygame.quit()


if __name__ == "__main__":
    main()
