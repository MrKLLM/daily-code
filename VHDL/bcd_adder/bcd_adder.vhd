-- ============================================================
-- 8421 BCD 码十进制加法器
-- 功能: 计算两个 1 位十进制数 (0~9, 用 8421BCD 编码) 相加
-- 输入: A(3:0), B(3:0) —— 两个BCD加数
--       Cin —— 来自低位十进制的进位
-- 输出: Sum(3:0) —— BCD 和
--       Dout —— 向高位十进制的进位
-- 原理: 先用二进制加法器相加, 然后判断是否需要加 6 修正
--       (因为 BCD 中 1010~1111 是无效状态, 遇到时加 0110 修正)
-- ============================================================

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity bcd_adder is
    Port ( A     : in  STD_LOGIC_VECTOR (3 downto 0);
           B     : in  STD_LOGIC_VECTOR (3 downto 0);
           Cin   : in  STD_LOGIC;
           Sum   : out STD_LOGIC_VECTOR (3 downto 0);
           Dout  : out STD_LOGIC);     -- Decimal output carry, 十进制进位
end bcd_adder;

architecture structure of bcd_adder is

    -- 声明要用到的子模块: 4 位二进制加法器
    component four_bit_adder is
        Port ( A   : in  STD_LOGIC_VECTOR (3 downto 0);
               B   : in  STD_LOGIC_VECTOR (3 downto 0);
               Cin : in  STD_LOGIC;
               S   : out STD_LOGIC_VECTOR (3 downto 0);
               Cout: out STD_LOGIC);
    end component;

    -- ===== 内部信号定义 =====

    -- 第一次加法的结果: 二进制和 + 进位
    signal bin_sum    : STD_LOGIC_VECTOR (3 downto 0);   -- 二进制相加得到的和
    signal bin_cout   : STD_LOGIC;                       -- 二进制相加得到的进位

    -- 是否需要修正的判断信号
    -- 当 (1) 有进位 或 (2) 和 > 9 (即 1010~1111) 时需要修正
    signal corr_need  : STD_LOGIC;

    -- 如果需要修正, 要给 bin_sum 加上的数 (无进位时为 0000, 有修正时为 0110)
    signal zero_plus6 : STD_LOGIC_VECTOR (3 downto 0);
    signal zero_cin   : STD_LOGIC;   -- 第二次加法的 Cin, 固定为 0

begin

    -- ===== 第一步: 先做二进制加法 =====
    -- 把两个 BCD 数当作普通 4 位二进制数相加
    u_bin_adder: four_bit_adder
        port map(A => A, B => B, Cin => Cin, S => bin_sum, Cout => bin_cout);

    -- ===== 第二步: 判断是否需要加 6 修正 =====
    -- BCD 修正条件 = 有进位 OR 结果在 1010~1111 之间
    -- 结果 > 9 的条件写成布尔式:
    --   bit3=1 且 (bit2=1 或 bit1=1)
    corr_need <= bin_cout or (bin_sum(3) and (bin_sum(2) or bin_sum(1)));

    -- ===== 第三步: 构造修正值 =====
    -- corr_need = 0 时, zero_plus6 = 0000 (不加)
    -- corr_need = 1 时, zero_plus6 = 0110 (加6)
    -- 0110 的 4 位分别是: bit3=0, bit2=corr_need, bit1=corr_need, bit0=0
    zero_plus6(0) <= '0';
    zero_plus6(1) <= corr_need;
    zero_plus6(2) <= corr_need;
    zero_plus6(3) <= '0';

    zero_cin <= '0';   -- 第二次加法没有额外的进位输入

    -- ===== 第四步: 做修正加法 =====
    -- 把二进制和 bin_sum 加上修正值 zero_plus6, 得到最终 BCD 和
    u_corr_adder: four_bit_adder
        port map(A => bin_sum, B => zero_plus6, Cin => zero_cin,
                 S => Sum, Cout => open);   -- open 表示不关心这个输出

    -- 最终的十进制进位 = 是否需要修正 (因为 bin_cout 已经被包含在 corr_need 里)
    Dout <= corr_need;

end structure;