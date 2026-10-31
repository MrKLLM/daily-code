-- ============================================================
-- 4 位二进制加法器 (Four-Bit Binary Adder)
-- 功能: 计算两个 4 位二进制数相加
-- 输入: A(3:0), B(3:0), Cin (来自低位的进位)
-- 输出: S(3:0) (和), Cout (向高位的进位)
-- 结构描述: 级联 4 个全加器, 低位进位输出连到高位进位输入
-- ============================================================

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity four_bit_adder is
    Port ( A   : in  STD_LOGIC_VECTOR (3 downto 0);   -- 4 位向量, 从高位(3)到低位(0)
           B   : in  STD_LOGIC_VECTOR (3 downto 0);
           Cin : in  STD_LOGIC;
           S   : out STD_LOGIC_VECTOR (3 downto 0);
           Cout: out STD_LOGIC);
end four_bit_adder;

architecture structure of four_bit_adder is

    -- 声明要用到的子模块: full_adder
    component full_adder is
        Port ( A   : in  STD_LOGIC;
               B   : in  STD_LOGIC;
               Cin : in  STD_LOGIC;
               S   : out STD_LOGIC;
               Cout: out STD_LOGIC);
    end component;

    -- 内部进位信号 c(0)~c(2): 相邻全加器之间的进位连接线
    signal c : STD_LOGIC_VECTOR (3 downto 0);

begin
    -- 实例化 4 个全加器, 串联起来组成 4 位加法器
    -- u0 是最低位, u3 是最高位

    -- 第0位: 直接用外部 Cin
    u0: full_adder port map(A => A(0), B => B(0), Cin => Cin,    S => S(0), Cout => c(0));

    -- 第1位: 进位来自第0位的 c(0)
    u1: full_adder port map(A => A(1), B => B(1), Cin => c(0),   S => S(1), Cout => c(1));

    -- 第2位: 进位来自第1位的 c(1)
    u2: full_adder port map(A => A(2), B => B(2), Cin => c(1),   S => S(2), Cout => c(2));

    -- 第3位: 进位来自第2位的 c(2); 其 Cout 直接作为整个加法器的进位输出
    u3: full_adder port map(A => A(3), B => B(3), Cin => c(2),   S => S(3), Cout => Cout);

end structure;