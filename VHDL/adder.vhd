library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- 一个 4 位加法器：s = a + b
entity adder is
  port (
    a : in std_logic_vector(3 downto 0); -- 4 位输入 a
    b : in std_logic_vector(3 downto 0); -- 4 位输入 b
    s : out std_logic_vector(4 downto 0) -- 5 位输出和（多一位防溢出）
  );
end entity adder;

architecture rtl of adder is
begin
  s <= std_logic_vector(resize(unsigned(a), 5) + resize(unsigned(b), 5));
end architecture rtl;
