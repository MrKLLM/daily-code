"""
训练入口脚本
------------
运行方法（项目根目录下）:
    python train.py --episodes 500

训练完成后:
    - 模型权重保存到 models/snake_dqn.pth
    - 训练曲线保存到 logs/training_curve.png
    - 训练统计保存到 logs/training_log.csv
"""
import os
import sys
import time
import argparse
import csv
from collections import deque

# 允许从项目根目录运行
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import numpy as np
import matplotlib
matplotlib.use("Agg")  # 无显示器环境也能保存图片
import matplotlib.pyplot as plt

from game.snake_game import SnakeGame
from agent.dqn_agent import DQNAgent


def train(
    episodes: int = 500,
    grid_size: int = 10,
    render_every: int = 0,
    save_path: str = "models/snake_dqn.pth",
    log_dir: str = "logs",
    seed: int = 42,
):
    """主训练流程"""
    np.random.seed(seed)

    # ---- 1) 创建环境和智能体 ----
    env = SnakeGame(grid_size=grid_size, render_mode=False)
    agent = DQNAgent(
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
        device="cpu",  # 玩这个游戏 CPU 足够，GPU 反而慢
    )

    os.makedirs(os.path.dirname(save_path) or ".", exist_ok=True)
    os.makedirs(log_dir, exist_ok=True)

    # ---- 2) 训练统计 ----
    scores, mean_scores, losses, epsilons = [], [], [], []
    best_score = 0
    recent_scores = deque(maxlen=20)  # 滑动窗口算平均

    start = time.time()
    print("=" * 60)
    print("开始训练 RL Snake")
    print(f"  episodes      = {episodes}")
    print(f"  grid_size     = {grid_size}")
    print(f"  state_size    = {env.STATE_SIZE}")
    print(f"  action_size   = {env.ACTION_SPACE_SIZE}")
    print(f"  device        = cpu")
    print("=" * 60)

    # ---- 3) 训练循环 ----
    for i_episode in range(1, episodes + 1):
        state = env.reset()
        total_reward = 0.0
        episode_loss = []
        steps = 0

        # 是否在当前回合渲染（通常只在最后验证时打开）
        env.render_mode = (render_every > 0 and i_episode % render_every == 0)

        while True:
            action = agent.act(state, training=True)
            next_state, reward, done, info = env.step(action)
            agent.remember(state, action, reward, next_state, done)
            loss = agent.learn()
            if loss is not None:
                episode_loss.append(loss)

            state = next_state
            total_reward += reward
            steps += 1
            if done:
                break

        score = info["score"]
        scores.append(score)
        recent_scores.append(score)
        mean_score = np.mean(recent_scores) if recent_scores else 0
        mean_scores.append(mean_score)
        epsilons.append(agent.epsilon)
        avg_loss = np.mean(episode_loss) if episode_loss else 0.0
        losses.append(avg_loss)

        # 保存最优模型
        if score > best_score:
            best_score = score
            agent.save(save_path)

        # 打印训练进度
        if i_episode % 10 == 0 or i_episode == 1:
            elapsed = time.time() - start
            print(
                f"回合 {i_episode:>4d}/{episodes} | "
                f"得分 {score:>2d} | "
                f"近20均分 {mean_score:>5.2f} | "
                f"最高 {best_score:>2d} | "
                f"ε {agent.epsilon:.3f} | "
                f"loss {avg_loss:.4f} | "
                f"步数 {steps:>3d} | "
                f"用时 {elapsed:.1f}s"
            )

    total_time = time.time() - start
    print("=" * 60)
    print(f"训练结束！总用时 {total_time:.1f} 秒，平均每回合 {total_time/episodes:.2f} 秒")
    print(f"最高分: {best_score}")

    # ---- 4) 保存最终模型 ----
    final_path = save_path.replace(".pth", "_final.pth")
    agent.save(final_path)

    # ---- 5) 保存训练曲线 ----
    _plot_training_curve(scores, mean_scores, losses, epsilons, os.path.join(log_dir, "training_curve.png"))

    # ---- 6) 保存 CSV 日志 ----
    csv_path = os.path.join(log_dir, "training_log.csv")
    with open(csv_path, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)
        writer.writerow(["episode", "score", "mean_score_20", "loss", "epsilon"])
        for i, (s, m, l, e) in enumerate(zip(scores, mean_scores, losses, epsilons), start=1):
            writer.writerow([i, s, m, l, e])
    print(f"[INFO] 训练日志已保存到 {csv_path}")
    print(f"[INFO] 训练曲线已保存到 {os.path.join(log_dir, 'training_curve.png')}")

    env.close()
    return agent


def _plot_training_curve(scores, mean_scores, losses, epsilons, save_path):
    """绘制训练曲线"""
    fig, axes = plt.subplots(1, 3, figsize=(18, 4))

    axes[0].plot(scores, alpha=0.4, label="score")
    axes[0].plot(mean_scores, linewidth=2, label="mean(20)")
    axes[0].set_title("Training Score")
    axes[0].set_xlabel("Episode")
    axes[0].set_ylabel("Score")
    axes[0].legend()
    axes[0].grid(True, alpha=0.3)

    axes[1].plot(losses, color="orange")
    axes[1].set_title("Training Loss (Huber)")
    axes[1].set_xlabel("Episode")
    axes[1].set_ylabel("Loss")
    axes[1].grid(True, alpha=0.3)

    axes[2].plot(epsilons, color="green")
    axes[2].set_title("Epsilon Decay")
    axes[2].set_xlabel("Episode")
    axes[2].set_ylabel("Epsilon")
    axes[2].grid(True, alpha=0.3)

    plt.tight_layout()
    plt.savefig(save_path, dpi=120)
    plt.close()
    print(f"[INFO] Training curve saved to {save_path}")


# ----------------- CLI 入口 -----------------
def parse_args():
    parser = argparse.ArgumentParser(description="强化学习贪吃蛇训练脚本")
    parser.add_argument("--episodes", type=int, default=500, help="训练回合数")
    parser.add_argument("--grid-size", type=int, default=10, help="地图大小 NxN")
    parser.add_argument("--render-every", type=int, default=0, help="每 N 回合渲染一次（0=不渲染）")
    parser.add_argument("--save-path", type=str, default="models/snake_dqn.pth", help="模型保存路径")
    return parser.parse_args()


if __name__ == "__main__":
    args = parse_args()
    train(
        episodes=args.episodes,
        grid_size=args.grid_size,
        render_every=args.render_every,
        save_path=args.save_path,
    )
