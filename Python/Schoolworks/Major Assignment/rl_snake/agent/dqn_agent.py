"""
DQN (Deep Q-Network) 智能体实现
--------------------------------
核心要点:
1. 经验回放 (Experience Replay): 把 (s, a, r, s', done) 存进 buffer，
   训练时随机采样小批量样本，打破样本时间相关性。
2. 目标网络 (Target Network): 用一个更新较慢的网络估计 Q 目标值，
   稳定训练过程。
3. ε-贪心策略 (Epsilon-Greedy): 以 ε 概率随机探索，否则选择 Q 值最大的动作。
4. Q-Learning 更新公式:
       Q(s, a) ← Q(s, a) + α [ r + γ · max_a' Q_target(s', a') - Q(s, a) ]
   在 DQN 中用神经网络拟合 Q 函数，用 MSE 损失反向传播。
"""
import random
import collections
from typing import Optional, Tuple

import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim


# -------------------------------------------------
# 1) Q 网络结构：简单的 MLP
# -------------------------------------------------
class QNetwork(nn.Module):
    """将 11 维状态映射到 3 个动作的 Q 值"""

    def __init__(self, state_size: int, action_size: int, hidden_size: int = 256):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(state_size, hidden_size),
            nn.ReLU(),
            nn.Linear(hidden_size, hidden_size),
            nn.ReLU(),
            nn.Linear(hidden_size, action_size),
        )

    def forward(self, x: torch.Tensor) -> torch.Tensor:
        return self.net(x)


# -------------------------------------------------
# 2) 经验回放池
# -------------------------------------------------
class ReplayBuffer:
    """固定容量的循环队列 (deque)，超过容量则丢弃最旧样本"""

    def __init__(self, capacity: int):
        self.buffer = collections.deque(maxlen=capacity)

    def push(self, transition: Tuple):
        """transition: (state, action, reward, next_state, done)"""
        self.buffer.append(transition)

    def sample(self, batch_size: int):
        """随机采样 batch_size 条样本"""
        batch = random.sample(self.buffer, batch_size)
        # 解包到对应列表
        states, actions, rewards, next_states, dones = zip(*batch)
        return (
            np.array(states,  dtype=np.float32),
            np.array(actions, dtype=np.int64),
            np.array(rewards, dtype=np.float32),
            np.array(next_states, dtype=np.float32),
            np.array(dones, dtype=np.float32),
        )

    def __len__(self):
        return len(self.buffer)


# -------------------------------------------------
# 3) DQN 智能体
# -------------------------------------------------
class DQNAgent:
    """
    DQN 智能体，封装了:
      - 策略网络 (policy_net)
      - 目标网络 (target_net)
      - 经验回放
      - ε-贪心选择动作
      - 学习更新
    """

    def __init__(
        self,
        state_size: int,
        action_size: int,
        hidden_size: int = 256,
        lr: float = 1e-3,
        gamma: float = 0.9,
        epsilon_start: float = 1.0,
        epsilon_end: float = 0.01,
        epsilon_decay: float = 0.995,
        buffer_size: int = 100_000,
        batch_size: int = 64,
        target_update_every: int = 100,
        device: str = "cpu",
    ):
        self.state_size = state_size
        self.action_size = action_size
        self.gamma = gamma
        self.batch_size = batch_size
        self.target_update_every = target_update_every
        self.device = torch.device(device)

        # ε 参数
        self.epsilon = epsilon_start
        self.epsilon_end = epsilon_end
        self.epsilon_decay = epsilon_decay

        # 网络
        self.policy_net = QNetwork(state_size, action_size, hidden_size).to(self.device)
        self.target_net = QNetwork(state_size, action_size, hidden_size).to(self.device)
        self.target_net.load_state_dict(self.policy_net.state_dict())
        # 目标网络不直接参与梯度更新
        for p in self.target_net.parameters():
            p.requires_grad = False

        # 优化器（用 Adam 即可）
        self.optimizer = optim.Adam(self.policy_net.parameters(), lr=lr)

        # 经验回放
        self.memory = ReplayBuffer(buffer_size)

        # 训练步数（用于决定何时同步 target 网络）
        self.learn_step_counter = 0

    # ---------- 动作选择 ----------
    def act(self, state: np.ndarray, training: bool = True) -> int:
        """
        ε-贪心策略:
        - 训练时: 以 ε 概率随机探索
        - 评估时: 直接选 Q 值最大的动作
        """
        if training and random.random() < self.epsilon:
            return random.randint(0, self.action_size - 1)

        state_t = torch.from_numpy(state).float().unsqueeze(0).to(self.device)
        with torch.no_grad():
            q_values = self.policy_net(state_t)
        return int(q_values.argmax(dim=1).item())

    # ---------- 经验存储 ----------
    def remember(self, state, action, reward, next_state, done):
        self.memory.push((state, action, reward, next_state, done))

    # ---------- 学习更新 ----------
    def learn(self) -> Optional[float]:
        """从 buffer 中采样一批样本做一次梯度更新，返回 loss（如果有更新）"""
        if len(self.memory) < self.batch_size:
            return None

        states, actions, rewards, next_states, dones = self.memory.sample(self.batch_size)

        states      = torch.from_numpy(states).to(self.device)
        actions     = torch.from_numpy(actions).to(self.device)
        rewards     = torch.from_numpy(rewards).to(self.device)
        next_states = torch.from_numpy(next_states).to(self.device)
        dones       = torch.from_numpy(dones).to(self.device)

        # 当前状态-动作对的 Q 值: Q(s, a)
        q_pred = self.policy_net(states).gather(1, actions.unsqueeze(1)).squeeze(1)

        # TD 目标: r + γ * max_a' Q_target(s', a')，done 终止时不再加未来奖励
        with torch.no_grad():
            q_next = self.target_net(next_states).max(dim=1)[0]
            q_target = rewards + self.gamma * q_next * (1.0 - dones)

        # 均方误差损失
        loss = nn.functional.smooth_l1_loss(q_pred, q_target)  # Huber loss 比 MSE 更稳健
        # 梯度下降
        self.optimizer.zero_grad()
        loss.backward()
        # 梯度裁剪，防止梯度爆炸
        torch.nn.utils.clip_grad_norm_(self.policy_net.parameters(), max_norm=10.0)
        self.optimizer.step()

        # 定期同步 target 网络
        self.learn_step_counter += 1
        if self.learn_step_counter % self.target_update_every == 0:
            self.target_net.load_state_dict(self.policy_net.state_dict())

        # 衰减 ε
        self.epsilon = max(self.epsilon_end, self.epsilon * self.epsilon_decay)

        return float(loss.item())

    # ---------- 模型保存 / 加载 ----------
    def save(self, path: str):
        """保存模型权重"""
        torch.save({
            "policy_net": self.policy_net.state_dict(),
            "target_net": self.target_net.state_dict(),
            "optimizer":  self.optimizer.state_dict(),
            "epsilon":    self.epsilon,
        }, path)
        print(f"[INFO] 模型已保存到 {path}")

    def load(self, path: str, load_optimizer: bool = True):
        """
        加载模型权重
        参数:
            load_optimizer: 是否同时加载 optimizer 状态。评估/可视化时建议设为 False，
                            避免优化器超参数不一致时 PyTorch 报警告。
        """
        ckpt = torch.load(path, map_location=self.device)
        self.policy_net.load_state_dict(ckpt["policy_net"])
        self.target_net.load_state_dict(ckpt["target_net"])
        if load_optimizer and "optimizer" in ckpt:
            try:
                self.optimizer.load_state_dict(ckpt["optimizer"])
            except Exception as e:
                print(f"[WARN] optimizer 状态加载失败（不影响评估）: {e}")
        self.epsilon = ckpt.get("epsilon", self.epsilon_end)
        print(f"[INFO] 已从 {path} 加载模型，当前 epsilon={self.epsilon:.3f}")
