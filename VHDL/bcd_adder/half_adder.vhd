-- ============================================================
-- 半加器 (Half Adder)
-- 功能: 计算 1 位二进制加法, 不考虑来自低位的进位
-- 输入: A, B (两个1位加数)
-- 输出: S (和), C (向高位的进位)
-- 逻辑: S = A XOR B,  C = A AND B
-- ============================================================

-- library 声明: 告诉编译器我们要用哪个库
-- IEEE 是标准库, STD_LOGIC_1164 里定义了 std_logic 类型
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- entity (实体): 定义电路的"外接口"——有哪些输入输出端口
-- 就像画芯片的引脚图, entity 只规定接口, 不规定内部怎么做
entity half_adder is
    Port ( A  : in  STD_LOGIC;   -- in 表示输入; STD_LOGIC 是标准逻辑类型(0/1/X/Z)
           B  : in  STD_LOGIC;
           S  : out STD_LOGIC;   -- out 表示输出
           C  : out STD_LOGIC);
end half_adder;                  -- entity 结束

-- architecture (结构体): 定义电路的"内部实现"
-- 一个 entity 可以对应多个 architecture, 这里我们用结构描述
architecture structure of half_adder is
begin
    -- begin ... end 之间是真正的电路行为描述

    -- <= 是信号赋值符号 (区别于变量赋值 :=)
    -- 这里直接用布尔运算描述: 异或得到和, 与得到进位
    S <= A xor B;   -- xor = 异或门
    C <= A and B;   -- and = 与门

end structure;                  -- architecture 结束