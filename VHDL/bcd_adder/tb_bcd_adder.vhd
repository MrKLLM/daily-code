-- ============================================================
-- 测试平台 (Testbench) —— 给 BCD 加法器喂测试数据
-- 功能: 自动生成输入信号, 观察输出是否正确
-- 注意: Testbench 没有端口 (不需要被别的模块调用)
--       Testbench 也不需要 library/use 之外的外部文件
-- ============================================================

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Testbench 的 entity 是空的, 因为它只是用来给 DUT (被测设备) 提供激励
entity tb_bcd_adder is
end tb_bcd_adder;

architecture behavior of tb_bcd_adder is

    -- 声明要测试的 DUT (Design Under Test) 组件
    component bcd_adder is
        Port ( A    : in  STD_LOGIC_VECTOR (3 downto 0);
               B    : in  STD_LOGIC_VECTOR (3 downto 0);
               Cin  : in  STD_LOGIC;
               Sum  : out STD_LOGIC_VECTOR (3 downto 0);
               Dout : out STD_LOGIC);
    end component;

    -- 内部信号: 用来连接到 DUT 的端口
    -- 这些信号会驱动 DUT 的输入, 也会接收 DUT 的输出
    signal A, B, Sum : STD_LOGIC_VECTOR (3 downto 0);
    signal Cin, Dout : STD_LOGIC;

begin

    -- port map: 把 DUT 连接到内部信号上
    -- 这样我们通过改变内部信号的值来"驱动"DUT
    uut: bcd_adder port map(A => A, B => B, Cin => Cin, Sum => Sum, Dout => Dout);

    -- ===== 激励进程 =====
    -- process (进程) 是 VHDL 中用来描述时序行为的基本单元
    -- 这个进程会从上往下顺序执行, 然后停在 wait 处
    stim_proc: process
    begin
        Cin <= '0';   -- 本次测试都没有来自低位的进位

        -- 每一组测试数据: 设置 A, B 的值, 等待一段时间让电路稳定
        -- 然后再看下一组

        A <= "0000"; B <= "0000"; wait for 100 ns;   -- 0 + 0 = 0
        -- report "A=0000 B=0000 | Dout=" & std_logic'image(Dout) & " Sum=" & to_string(Sum) & " | expected: Dout=0 Sum=0000";
        A <= "0011"; B <= "0100"; wait for 100 ns;   -- 3 + 4 = 7
        -- report "A=0011 B=0100 | Dout=" & std_logic'image(Dout) & " Sum=" & to_string(Sum) & " | expected: Dout=0 Sum=0111";
        A <= "0101"; B <= "0011"; wait for 100 ns;   -- 5 + 3 = 8
        -- report "A=0101 B=0011 | Dout=" & std_logic'image(Dout) & " Sum=" & to_string(Sum) & " | expected: Dout=0 Sum=1000";
        A <= "0111"; B <= "0010"; wait for 100 ns;   -- 7 + 2 = 9  (不进位, 无需修正)
        -- report "A=0111 B=0010 | Dout=" & std_logic'image(Dout) & " Sum=" & to_string(Sum) & " | expected: Dout=0 Sum=1001";
        A <= "1000"; B <= "0011"; wait for 100 ns;   -- 8 + 3 = 11 (应得到 Sum=1, Dout=1, 即十进制 11)
        -- report "A=1000 B=0011 | Dout=" & std_logic'image(Dout) & " Sum=" & to_string(Sum) & " | expected: Dout=1 Sum=0001";
        A <= "0110"; B <= "0101"; wait for 100 ns;   -- 6 + 5 = 11 (同上)
        -- report "A=0110 B=0101 | Dout=" & std_logic'image(Dout) & " Sum=" & to_string(Sum) & " | expected: Dout=1 Sum=0001";
        A <= "1001"; B <= "1001"; wait for 100 ns;   -- 9 + 9 = 18 (应得到 Sum=8, Dout=1)
        -- report "A=1001 B=1001 | Dout=" & std_logic'image(Dout) & " Sum=" & to_string(Sum) & " | expected: Dout=1 Sum=1000";
        A <= "1001"; B <= "0001"; wait for 100 ns;   -- 9 + 1 = 10 (应得到 Sum=0, Dout=1)
        -- report "A=1001 B=0001 | Dout=" & std_logic'image(Dout) & " Sum=" & to_string(Sum) & " | expected: Dout=1 Sum=0000";

        wait;   -- 永远等待, 让仿真停在这里 (进程结束)
    end process;

end behavior;