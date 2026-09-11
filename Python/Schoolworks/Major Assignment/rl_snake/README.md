# RL Snake - Reinforcement Learning Snake

> A teaching project that trains a Snake AI using **DQN (Deep Q-Network)**.
> Goal: Let the AI learn to **automatically eat food while avoiding walls and itself**.

---

## 1. Project Overview

### 1.1 Introduction
Snake is a classic game: control a snake on a grid, eat food to grow, and avoid walls or yourself.

This project turns Snake into a **Reinforcement Learning (RL) environment**, letting an AI agent learn through trial-and-error. The AI only needs to know:
- What **state** it's in;
- What **actions** it can take;
- What **reward** it receives after each action.

### 1.2 Project Goals
1. Understand core RL concepts: state, action, reward, policy, value function.
2. Master the DQN algorithm: experience replay, target network, epsilon-greedy exploration.
3. Engineering practice: complete an RL project from environment to training to visualization.
4. Extensible: clean code structure for further improvements (Double DQN, Dueling DQN, PPO, etc.).

---

## 2. Environment & Installation

### 2.1 Python Version
- Recommended: **Python 3.8 ~ 3.11**

### 2.2 Dependencies

| Library | Purpose |
|---------|---------|
| `pygame` | Game graphics rendering |
| `numpy` | Numerical computation, state vectorization |
| `torch` | PyTorch deep learning framework (Q-Network) |
| `matplotlib` | Training curve visualization |

### 2.3 Installation
```bash
# 1) Create virtual environment (optional but recommended)
python -m venv venv
venv\Scripts\activate  # Windows
source venv/bin/activate  # Linux/macOS

# 2) Install dependencies
pip install -r requirements.txt
```

---

## 3. Project Structure

```
rl_snake/
├── game/
│   └── snake_game.py        # Snake game environment (Gym-style API)
├── agent/
│   └── dqn_agent.py         # DQN agent (Q-Network + Experience Replay)
├── train.py                 # Training entry point
├── play.py                  # Load model and visualize
├── menu.py                  # Main menu (Manual Play / RL Auto Play)
├── Train.bat                # One-click headless training
├── RL_Snake.bat             # One-click launch menu
├── models/                  # Saved model weights
├── logs/                    # Training curves and logs
├── requirements.txt         # Dependencies
└── README.md                # This file
```

---

## 4. Usage

### 4.1 Launch Game Menu
```bash
python menu.py
```
Or double-click `RL_Snake.bat`.

Menu options:
- **MANUAL PLAY** - Control the snake with arrow keys
- **RL AUTO PLAY** - AI plays using the trained model

### 4.2 Headless Training
```bash
python train.py --episodes 500
```
Or double-click `Train.bat`.

Common parameters:
- `--episodes` - Number of training episodes (500+, 1000+ for better results)
- `--grid-size` - Map size, default 10x10
- `--render-every` - Render every N episodes (0 = never, faster training)
- `--save-path` - Model save path, default `models/snake_dqn.pth`

Training output:
1. Console prints stats every 10 episodes
2. Best model saved to `models/snake_dqn.pth`
3. Final model saved to `models/snake_dqn_final.pth`
4. Training curve saved to `logs/training_curve.png`
5. Episode stats saved to `logs/training_log.csv`

### 4.3 Visualize Trained Model
```bash
python play.py --model models/snake_dqn.pth --episodes 5
```

### 4.4 Game Controls

| Key | Action |
|-----|--------|
| Arrow Keys | Control snake direction |
| Space | Pause/Resume |
| ESC | Quit |

---

## 5. Game Mechanics

### 5.1 Speed System
- **Start speed**: 3 (configurable)
- **Max speed**: 25
- **Speed increase**: `speed = base_speed + sqrt(score) * 0.8`
- Speed increases gradually as score increases

### 5.2 Snake Growth
- Snake grows by 1 segment every **2 food items** eaten
- This provides a smoother gameplay experience

### 5.3 State Design (13 dimensions)
```python
state = [
    # Danger in three directions
    int(danger_straight), int(danger_right), int(danger_left),
    # Current direction (one-hot)
    int(dir_left), int(dir_right), int(dir_up), int(dir_down),
    # Food relative position
    int(food_left), int(food_right), int(food_up), int(food_down),
    # Food distance (normalized)
    food_dx,  # x distance (-1 to 1)
    food_dy,  # y distance (-1 to 1)
]
```

### 5.4 Action Space (3 actions)
- `0`: Go straight
- `1`: Turn right 90°
- `2`: Turn left 90°

### 5.5 Reward Shaping

| Event | Reward | Purpose |
|-------|--------|---------|
| Eat food | **+10** | Strong encouragement to score |
| Hit wall/self | **-10** | Strong penalty for death |
| Move without food | **-0.01** | Encourage efficient pathfinding |
| Timeout | **-10** | Prevent snake from circling |

---

## 6. Core Concepts

### 6.1 DQN (Deep Q-Network)
- Uses neural network to approximate Q-function
- Network: 13 → 256 → 256 → 3 (MLP)

### 6.2 Key Techniques
1. **Experience Replay**: Store (s, a, r, s', done) in buffer, sample random batches
2. **Target Network**: Separate network for stable TD target calculation
3. **Epsilon-Greedy**: Random exploration decays from 1.0 → 0.01

### 6.3 Training Pseudocode
```
1. Initialize env, agent (policy_net = target_net)
2. For episode = 1 to N:
3.   s = env.reset()
4.   While not done:
5.     a = agent.act(s)  # epsilon-greedy
6.     s', r, done, _ = env.step(a)
7.     agent.remember(s, a, r, s', done)
8.     agent.learn()  # sample batch, update policy_net
9.     Every K steps: target_net ← policy_net
10.    s = s'
```

---

## 7. Extensible Features

### 7.1 Algorithm Improvements
- **Double DQN**: Solve Q-value overestimation
- **Dueling DQN**: Split Q into V(s) + A(s,a)
- **Prioritized Experience Replay**: Weighted sampling for important samples
- **PPO / A2C**: Policy gradient algorithms

### 7.2 State Representation
- CNN input directly from game frames
- Stack last N frames for motion information

### 7.3 Training Visualization
- TensorBoard integration
- Real-time Q-value overlay

### 7.4 Environment Improvements
- Larger maps (20x20)
- Multiple food types
- Multi-snake competition

---

## 8. FAQ

### Q1: Training loss doesn't decrease?
- Check learning rate (lr=1e-3 is safe)
- Increase batch_size (64 → 128/256)
- Lower gamma (gamma=0.9 is stable)

### Q2: AI keeps circling without progress?
- Reduce `max_steps_without_food`
- Increase `epsilon_decay` for more exploration

### Q3: Can't open visualization window?
- Training runs without rendering
- On remote servers, use headless training only
- Try `set SDL_VIDEODRIVER=windib` on Windows

### Q4: How long to see results?
- 200-500 episodes for noticeable improvement
- 1000+ episodes for stable performance
- 500 episodes takes ~5-10 minutes on laptop

### Q5: CPU or GPU training?
- CPU is faster for this project (small network, low dimensionality)
- Default `device="cpu"`

### Q6: How to verify the model learned?
- Run `play.py` with `agent.epsilon = 0`
- Compare with random baseline (avg score ~0.5)

---

## 9. References

- [Playing Atari with Deep Reinforcement Learning](https://arxiv.org/abs/1312.5602) - DQN original paper
- [Human-level control through deep reinforcement learning](https://www.nature.com/articles/nature14236) - Nature 2015
- [Sutton & Barto "Reinforcement Learning: An Introduction"](http://incompleteideas.net/book/RLbook2020.pdf)
- [PyTorch Documentation](https://pytorch.org/docs/stable/index.html)
- [Pygame Documentation](https://www.pygame.org/docs/)

---

> **Learning tip**: Run `train.py`, observe the training curve, then read the code.
> Modify rewards, state design, and watch how AI behavior changes.
> This is the fastest way to master RL — **"modify code + observe"**.
