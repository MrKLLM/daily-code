"""
加载训练好的模型，可视化测试智能体表现
用法:
    python play.py --model models/snake_dqn.pth
    python play.py --model models/snake_dqn.pth --episodes 5 --speed 15
"""
import os
import sys
import argparse

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

import numpy as np
from game.snake_game import SnakeGame
from agent.dqn_agent import DQNAgent


def play(model_path: str, episodes: int = 3, grid_size: int = 10,
         speed: int = 5, cell_size: int = 40):
    """加载模型并可视化运行 N 回合"""
    if not os.path.exists(model_path):
        print(f"[ERROR] 模型文件不存在: {model_path}")
        print("请先运行: python train.py --episodes 500")
        return

    env = SnakeGame(
        grid_size=grid_size,
        cell_size=cell_size,
        speed=speed,
        render_mode=True,  # 开启可视化
    )

    # 创建 agent 并加载权重（注意：评估时不需要 optimizer）
    agent = DQNAgent(
        state_size=env.STATE_SIZE,
        action_size=env.ACTION_SPACE_SIZE,
        hidden_size=256,
        device="cpu",
    )
    # 评估模式：不加载 optimizer，避免 lr/动量等不匹配产生警告
    agent.load(model_path, load_optimizer=False)
    agent.epsilon = 0.0  # 评估模式，纯贪心，不再随机探索

    scores = []
    print("=" * 60)
    print(f"开始可视化测试，共 {episodes} 回合")
    print("按 Ctrl+C 或关闭窗口可提前结束")
    print("=" * 60)

    try:
        for ep in range(1, episodes + 1):
            state = env.reset()
            score = 0
            steps = 0
            while True:
                action = agent.act(state, training=False)
                state, reward, done, info = env.step(action)
                steps += 1
                if done:
                    score = info["score"]
                    break
            scores.append(score)
            print(f"回合 {ep:>2d}: 得分 = {score}, 步数 = {steps}")

        print("=" * 60)
        print(f"平均得分: {np.mean(scores):.2f}, 最高分: {np.max(scores)}, 最低分: {np.min(scores)}")
    except KeyboardInterrupt:
        print("\n[INFO] 用户中断，可视化结束。")
    finally:
        env.close()


def main():
    parser = argparse.ArgumentParser(description="可视化测试训练好的贪吃蛇 AI")
    parser.add_argument("--model", type=str, default="models/snake_dqn.pth", help="模型文件路径")
    parser.add_argument("--episodes", type=int, default=3, help="测试回合数")
    parser.add_argument("--grid-size", type=int, default=10, help="Map size")
    parser.add_argument("--speed", type=int, default=5, help="Animation speed (FPS)")
    parser.add_argument("--cell-size", type=int, default=40, help="Pixel size per cell")
    args = parser.parse_args()
    play(args.model, args.episodes, args.grid_size, args.speed, args.cell_size)


if __name__ == "__main__":
    main()
