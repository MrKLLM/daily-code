# 组合逻辑电路 VHDL 设计报告
## —— 8421BCD 码十进制加法电路

| 项目 | 内容 |
|------|------|
| 学生姓名 | XXX |
| 学号 | XXXXXX |
| 课程 | 数字逻辑电路 |
| 提交日期 | 2026-11-15 |

---

## 一、设计任务

设计实现带十进制进位的 **8421BCD 码十进制加法电路**。具体要求：

1. 采用**结构描述法**实现；
2. 先描述 2 个四位二进制数加法电路；
3. 在此基础上，描述十进制加法电路；
4. 仿真验证正确性。

---

## 二、设计原理

### 2.1 8421BCD 码基础

8421BCD 码使用 4 位二进制数表示 0–9 的十进制数码，每位二进制的权值分别为 8、4、2、1。BCD 码与十进制数的对应关系如下：

| 十进制 | BCD 码 | 十进制 | BCD 码 |
|--------|--------|--------|--------|
| 0      | 0000   | 5      | 0101   |
| 1      | 0001   | 6      | 0110   |
| 2      | 0010   | 7      | 0111   |
| 3      | 0011   | 8      | 1000   |
| 4      | 0100   | 9      | 1001   |

> 注意：**1010~1111 在 BCD 码中是非法状态**。

### 2.2 BCD 加法修正规则

两个 1 位 BCD 数相加时，先按普通二进制数进行运算，然后根据结果判断是否需要**加 6（0110₂）修正**。修正规则如下：

| 二进制和范围 | 进位 Cout | 操作 | 说明 |
|-------------|-----------|------|------|
| 0000 – 1001 | 0 | 不需要修正 | 结果本身就是合法 BCD |
| 1010 – 1111 | 0 | **加 6**，产生十进制进位 Dout=1 | 十进制和为 10–15 |
| 0000 – 1001 | 1 | **加 6**，Dout=1 | 十进制和为 16–18 |

**示例**：

| 运算 | 二进制加法结果 | 修正 | BCD 结果 |
|------|---------------|------|---------|
| 3 + 4 | 0111 (7) | 不加 | Dout=0, Sum=0111 |
| 8 + 3 | 1011 (11) | +0110 → 0001 | Dout=1, Sum=0001 |
| 9 + 9 | 10010 (18) | +0110 → 1000 | Dout=1, Sum=1000 |

### 2.3 修正条件的布尔表达

观察二进制和 1010–1111（十进制 10–15）的特征：
- 最高位 bit3 必定为 1
- bit2 和 bit1 至少有一个为 1

因此**修正触发信号**可写为：

$$ \text{corr\_need} = \text{Cout} \lor (\text{Sum}[3] \land (\text{Sum}[2] \lor \text{Sum}[1])) $$

同时，十进制进位输出 Dout 就等于 corr_need。

---

## 三、系统层次与模块划分

本设计采用**自底向上的层次化结构描述法**，共 4 个层次、5 个源文件：

```
┌─────────────────────────────────────┐
│        bcd_adder.vhd (顶层)         │  8421BCD 加法器 + 修正电路
│   A[3:0], B[3:0], Cin → Sum, Dout  │
└─────────────────────────────────────┘
        ┌──────────┐        ┌──────────┐
        │  u_bin_   │        │  u_corr_ │
        │  adder    │        │  adder   │
        └──────────┘        └──────────┘
┌───────────────────────────────────────┐
│    four_bit_adder.vhd (中间层)        │  四位串行进位二进制加法器
│  A[3:0], B[3:0], Cin → S[3:0], Cout  │
└───────────────────────────────────────┘
  FA3 ── FA2 ── FA1 ── FA0
┌───────────────────────────────────────┐
│      full_adder.vhd (基础层)          │  1 位全加器
│      A, B, Cin → S, Cout              │
└───────────────────────────────────────┘
  ┌───────┐  ┌───────┐
  │  HA1  │  │  HA2  │
┌───────────────────────────────────────┐
│     half_adder.vhd (最底层)           │  1 位半加器
│       A, B → S, C                     │
└───────────────────────────────────────┘
```

---

## 四、各模块详细设计

### 4.1 半加器 half_adder

**功能**：完成两个 1 位二进制数的本位加，不考虑低位进位。

| 输入 |  | 输出 |  |
|------|---|------|---|
| A | B | S | C |
| 0 | 0 | 0 | 0 |
| 0 | 1 | 1 | 0 |
| 1 | 0 | 1 | 0 |
| 1 | 1 | 0 | 1 |

**逻辑表达式**：
- $S = A \oplus B$
- $C = A \cdot B$

```vhdl
entity half_adder is
    Port ( A : in  STD_LOGIC;
           B : in  STD_LOGIC;
           S : out STD_LOGIC;
           C : out STD_LOGIC);
end half_adder;

architecture structure of half_adder is
begin
    S <= A xor B;
    C <= A and B;
end structure;
```

### 4.2 全加器 full_adder

**功能**：考虑低位进位 Cin 的 1 位加法器。

**实现方法**：使用 2 个半加器 + 1 个或门组合实现。

```
     A ──┬──▶ HA1 ──┬──▶ HA2 ──▶ S
         │          │
     B ──┘          └──▶ Cin
                    HA1.C ──▶ C1 ──┐
                                   ├──▶ Cout
                    HA2.C ──▶ C2 ──┘
```

```vhdl
architecture structure of full_adder is
    component half_adder is
        Port ( A, B : in  STD_LOGIC;
               S, C : out STD_LOGIC);
    end component;
    signal s1, c1, c2 : STD_LOGIC;
begin
    u1: half_adder port map(A => A,  B => B,  S => s1, C => c1);
    u2: half_adder port map(A => s1, B => Cin, S => S,  C => c2);
    Cout <= c1 or c2;
end structure;
```

### 4.3 四位二进制加法器 four_bit_adder

**功能**：两个 4 位二进制数的加法，采用**串行进位**结构。

**结构**：4 个 full_adder 级联，进位自低位向高位逐级传播：

```
Cin → FA0(c0) → FA1(c1) → FA2(c2) → FA3 → Cout
      A[0]+B[0]  A[1]+B[1]  A[2]+B[2]  A[3]+B[3]
         S[0]       S[1]       S[2]       S[3]
```

```vhdl
architecture structure of four_bit_adder is
    component full_adder is
        Port ( A, B, Cin : in  STD_LOGIC;
               S, Cout   : out STD_LOGIC);
    end component;
    signal c : STD_LOGIC_VECTOR (3 downto 0);
begin
    u0: full_adder port map(A=>A(0), B=>B(0), Cin=>Cin,  S=>S(0), Cout=>c(0));
    u1: full_adder port map(A=>A(1), B=>B(1), Cin=>c(0), S=>S(1), Cout=>c(1));
    u2: full_adder port map(A=>A(2), B=>B(2), Cin=>c(1), S=>S(2), Cout=>c(2));
    u3: full_adder port map(A=>A(3), B=>B(3), Cin=>c(2), S=>S(3), Cout=>Cout);
end structure;
```

### 4.4 BCD 加法器 bcd_adder（顶层）

**功能**：完成两个 1 位 BCD 数的加法，输出修正后的 BCD 结果和十进制进位。

**实现步骤**：

1. **二进制求和**：使用第一个 `four_bit_adder` 将 A、B 连同 Cin 按普通二进制相加，得到 `bin_sum` 和 `bin_cout`；
2. **修正判断**：根据公式 $\text{corr\_need} = \text{bin\_cout} \lor (\text{bin\_sum}[3] \land (\text{bin\_sum}[2] \lor \text{bin\_sum}[1]))$ 判断是否需要加 6；
3. **加 6 修正**：当 `corr_need = 1` 时，向 `bin_sum` 加上 `0110`（十进制 6），得到正确的 BCD Sum；
4. **十进制进位**：`Dout = corr_need`。

```vhdl
architecture structure of bcd_adder is
    component four_bit_adder is
        Port ( A, B   : in  STD_LOGIC_VECTOR (3 downto 0);
               Cin    : in  STD_LOGIC;
               S      : out STD_LOGIC_VECTOR (3 downto 0);
               Cout   : out STD_LOGIC);
    end component;
    signal bin_sum, zero_plus6 : STD_LOGIC_VECTOR (3 downto 0);
    signal bin_cout, corr_need : STD_LOGIC;
begin
    u_bin_adder: four_bit_adder
        port map(A=>A, B=>B, Cin=>Cin, S=>bin_sum, Cout=>bin_cout);

    corr_need <= bin_cout or (bin_sum(3) and (bin_sum(2) or bin_sum(1)));

    zero_plus6(0) <= corr_need;
    zero_plus6(1) <= corr_need;
    zero_plus6(2) <= '0';
    zero_plus6(3) <= '0';

    u_corr_adder: four_bit_adder
        port map(A=>bin_sum, B=>zero_plus6, Cin=>'0', S=>Sum, Cout=>open);

    Dout <= corr_need;
end structure;
```

---

## 五、仿真与结果分析

### 5.1 仿真工具

- **编译器**：GHDL v1.0（GNU VHDL 分析器）
- **波形查看器**：GTKWave v3.3

### 5.2 测试平台

测试平台 `tb_bcd_adder.vhd` 采用 `process` 语句产生 8 组测试激励，每组持续 100ns，覆盖以下场景：

| # | A[3:0] | B[3:0] | 十进制 | 二进制和 | 修正 | Dout | Sum[3:0] | 预期十进制结果 |
|---|--------|--------|--------|---------|------|------|----------|---------------|
| 1 | 0000   | 0000   | 0 + 0  | 0000    | ❌   | 0    | 0000     | 0             |
| 2 | 0011   | 0100   | 3 + 4  | 0111    | ❌   | 0    | 0111     | 7             |
| 3 | 0101   | 0011   | 5 + 3  | 1000    | ❌   | 0    | 1000     | 8             |
| 4 | 0111   | 0010   | 7 + 2  | 1001    | ❌   | 0    | 1001     | 9             |
| 5 | 1000   | 0011   | 8 + 3  | 1011    | ✅+6 | 1    | 0001     | 11            |
| 6 | 0110   | 0101   | 6 + 5  | 1011    | ✅+6 | 1    | 0001     | 11            |
| 7 | 1001   | 1001   | 9 + 9  | 10010   | ✅+6 | 1    | 1000     | 18            |
| 8 | 1001   | 0001   | 9 + 1  | 1010    | ✅+6 | 1    | 0000     | 10            |

### 5.3 仿真验证命令

```bash
ghdl -a half_adder.vhd
ghdl -a full_adder.vhd
ghdl -a four_bit_adder.vhd
ghdl -a bcd_adder.vhd
ghdl -a tb_bcd_adder.vhd
ghdl -e tb_bcd_adder
ghdl -r tb_bcd_adder --vcd=wave.vcd
gtkwave wave.vcd
```

### 5.4 仿真结果

所有 8 组测试向量仿真结果与预期一致：

| 时间段 (ns) | Dout | Sum[3:0] | 判定 |
|-------------|------|----------|------|
| 0 – 100     | 0    | 0000     | ✅   |
| 100 – 200   | 0    | 0111     | ✅   |
| 200 – 300   | 0    | 1000     | ✅   |
| 300 – 400   | 0    | 1001     | ✅   |
| 400 – 500   | 1    | 0001     | ✅   |
| 500 – 600   | 1    | 0001     | ✅   |
| 600 – 700   | 1    | 1000     | ✅   |
| 700 – 800   | 1    | 0000     | ✅   |

---

## 六、设计总结

### 6.1 结构描述法的特点

本作业要求采用**结构描述法**，核心是通过 `component` 声明和 `port map` 语句将已有模块实例化并互连。与行为描述法（用 `process` + 时序/条件语句直接描述功能）相比：

| 方面 | 结构描述法 | 行为描述法 |
|------|-----------|-----------|
| 风格 | 像画电路原理图 | 像写程序算法 |
| 层次 | 支持分层、便于复用 | 通常单层次 |
| 可移植 | 好，子模块可独立使用 | 差，与具体功能耦合 |
| 代码量 | 较多（component 声明 + 实例化） | 较少 |

### 6.2 心得体会

1. **层次化设计**将复杂问题分解为多个简单子问题，每层只关注自己的接口和功能，降低了调试难度；
2. **串行进位加法器**虽然延迟较大（每级 FA 延迟叠加），但结构规整、易于扩展；
3. BCD 修正逻辑的关键在于**找出非法状态的共同特征**，用布尔代数化简得到最简表达式 `S[3]·(S[2]∨S[1])`，比直接枚举所有非法状态更简洁；
4. 用同一个加法器做修正加（复用硬件），体现了"让同一个电路做两次加法"的设计思想。

---

## 附录：源文件清单

| 文件名 | 实体名 | 层次 |
|--------|--------|------|
| `half_adder.vhd` | half_adder | 1（最底层） |
| `full_adder.vhd` | full_adder | 2 |
| `four_bit_adder.vhd` | four_bit_adder | 3 |
| `bcd_adder.vhd` | bcd_adder | 4（顶层） |
| `tb_bcd_adder.vhd` | tb_bcd_adder | 测试平台 |