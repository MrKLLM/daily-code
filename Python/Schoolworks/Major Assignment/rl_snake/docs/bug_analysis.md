# Bug 分析与修复记录

## Bug 1：RL Snake 复选框按下 R 键后无反应

### 问题现象
在游戏界面侧边栏按下 R 键后，复选框没有勾选，没有任何视觉反馈。

### 根本原因
在 `human_play()` 的游戏循环中，模式执行部分存在致命逻辑错误：

```python
# 修复前（错误代码）
if env.use_rl_snake:
    if env.agent is None:
        running = False   # ← 问题所在！模型不存在时直接退出游戏
        break
```

当用户按下 R 键时，`use_rl_snake` 被设为 `True`，但模型文件不存在时 `_load_rl_agent()` 会将 `use_rl_snake` 重置为 `False`。即使如此，下一帧执行到上述代码时，由于 `agent is None`，游戏直接 `running = False` 退出。用户看到的现象就是：按了 R 键后游戏没有任何反应（实际上游戏在退出边缘）。

### 修复方案
将 `running = False` 改为显示错误提示并重置复选框状态：

```python
# 修复后（正确代码）
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
```

同时在 `_load_rl_agent()` 中，模型不存在时也设置提示信息：

```python
if not os.path.exists(model_path):
    env.use_rl_snake = False
    env.no_model_msg = "No model found! Train first."
    env.no_model_timer = 120
    return
```

### 教训
- 不要用 `running = False` 处理非致命错误，会导致整个游戏退出
- 应当区分"游戏结束"和"操作失败"两种情况

---

## Bug 2：界面卡顿、按键延迟严重

### 问题现象
整个游戏界面响应迟钝，按下方向键有明显延迟，操作手感极差。

### 根本原因
`_render()` 方法末尾的 `clock.tick(self.speed)` 控制的是**整个主循环**的帧率，而不仅仅是渲染速度：

```python
# 修复前（错误设计）
def _render(self):
    # ... 绘制所有内容 ...
    pygame.display.flip()
    if self.clock is not None:
        self.clock.tick(self.speed)  # ← 问题所在！
```

当 `speed=5` 时，`clock.tick(5)` 让整个循环每秒只运行 5 次。这意味着：
- 事件处理（键盘、鼠标）每秒只检查 5 次
- 渲染每秒只更新 5 次
- 按键最多需要 200ms 才能被检测到

### 修复方案
将 `clock.tick()` 从 `_render()` 中移除，改为在 `human_play()` 中分别控制：

1. **输入和渲染**：始终以 30 FPS 运行（`env.clock.tick(30)`）
2. **游戏步进**：按 speed 间隔执行（`step_interval = 1000 // speed` ms）

```python
# 修复后
# _render() 中不再调用 clock.tick()

# human_play() 主循环
while running:
    # 1. 事件处理（始终运行）
    for event in pygame.event.get():
        ...

    # 2. 渲染（始终 30 FPS）
    env._render()

    # 3. 游戏步进（按 speed 间隔）
    if now - last_step_time < step_interval:
        env.clock.tick(30)
        continue
    last_step_time = now

    # 执行一步游戏逻辑
    if env.mode == MODE_MANUAL:
        ...
    env.clock.tick(30)
```

### 教训
- `clock.tick()` 的位置决定了它控制的范围，放在渲染函数里会限制整个循环
- 输入响应和游戏逻辑应该分离处理

---

## Bug 3：侧边栏过于拥挤

### 问题现象
侧边栏信息太多、间距过大，视觉上非常拥挤。

### 原因
每个信息项都独占一行，间距过大（`py += 22~38`），字体偏大。

### 修复方案
1. 将 LENGTH/STEPS 合并为一行
2. 将 EPISODE/SPEED 合并为一行
3. 减小所有间距（`py += 12~16`）
4. 减小字体大小
5. 移除冗余的分隔线和装饰文字

---

## Bug 4：速度递增不合理

### 问题现象
速度线性增长，后期蛇移动过快，无法控制。

### 修复方案
使用平方根函数实现非线性增长：

```python
def _update_speed(self):
    self.speed = min(self.max_speed, int(self.base_speed + math.sqrt(self.score) * 2))
```

速度变化表（base_speed=5, max_speed=25）：

| 分数 | 速度 |
|------|------|
| 0    | 5    |
| 1    | 7    |
| 4    | 9    |
| 9    | 11   |
| 16   | 13   |
| 25   | 15   |
| 64   | 21   |
| 100  | 25   |

每局开始时速度重置为 `base_speed`。
