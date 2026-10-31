library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Testbench：给 adder 喂几组数据，看输出对不对
entity tb_adder is
end entity tb_adder;

architecture sim of tb_adder is
    signal a : std_logic_vector(3 downto 0) := (others => '0');
    signal b : std_logic_vector(3 downto 0) := (others => '0');
    signal s : std_logic_vector(4 downto 0);
begin
    -- 例化待测试的 adder
    uut: entity work.adder
        port map(a => a, b => b, s => s);

    -- 每隔 10ns 换一组输入
    process
    begin
        a <= x"3"; b <= x"5"; wait for 10 ns;   -- 3 + 5 = 8
        a <= x"A"; b <= x"7"; wait for 10 ns;   -- 10 + 7 = 17
        a <= x"F"; b <= x"1"; wait for 10 ns;   -- 15 + 1 = 16
        a <= x"0"; b <= x"0"; wait for 10 ns;   -- 0 + 0 = 0
        wait;                                    -- 停住
    end process;
end architecture sim;
