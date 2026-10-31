-- ============================================================
-- 全加器 (Full Adder)
-- 功能: 计算 1 位二进制加法, 考虑来自低位的进位 Cin
-- 输入: A, B (两个1位加数), Cin (来自低位的进位)
-- 输出: S (和), Cout (向高位的进位)
-- 结构描述: 用 2 个半加器 + 1 个或门组成
-- ============================================================

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity full_adder is
    Port ( A   : in  STD_LOGIC;
           B   : in  STD_LOGIC;
           Cin : in  STD_LOGIC;   -- 新增: 来自低位的进位
           S   : out STD_LOGIC;
           Cout: out STD_LOGIC);  -- 向高位的进位
end full_adder;

architecture structure of full_adder is

    -- component (元件声明): 告诉编译器我们要用到 half_adder 这个子模块
    -- 写法和 entity 的 Port 一模一样, 但关键字是 component/end component
    component half_adder is
        Port ( A : in  STD_LOGIC;
               B : in  STD_LOGIC;
               S : out STD_LOGIC;
               C : out STD_LOGIC);
    end component;

    -- signal (信号声明): 定义模块内部的连接线
    -- s1, c1 是第一个半加器的输出; c2 是第二个半加器的进位输出
    signal s1, c1, c2 : STD_LOGIC;

begin
    -- port map (端口映射): 把元件的端口连接到实际信号上
    -- u1, u2 是元件实例名, 随便起
    -- 箭头 A => A 意思是: 元件端口 A 连接到当前模块的信号 A

    -- 第一个半加器: 先算 A + B, 得到中间和 s1 和中间进位 c1
    u1: half_adder port map(A => A,  B => B,  S => s1, C => c1);

    -- 第二个半加器: 再把中间和 s1 加上 Cin, 得到最终和 S 和另一个进位 c2
    u2: half_adder port map(A => s1, B => Cin, S => S,  C => c2);

    -- 最终进位 = 两个半加器进位的或 (只要任意一个产生进位就进位)
    Cout <= c1 or c2;

end structure;