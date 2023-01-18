library IEEE;
use IEEE.std_logic_1164.all;

entity extender is
  generic(N : integer := 16);
  port(i_value	: in std_logic_vector(N-1 downto 0);
       i_sign	: in std_logic;
       o_output : out std_logic_vector(31 downto 0));

end extender;

architecture behavior of extender is

----------------------------------------------------------------

begin

Gen_zero0 : for i in 0 to N-1 generate
	o_output(i) <= i_value(i);
end generate;

Gen_sign1 : for i in N to 31 generate
	o_output(i) <= i_value(N-1) and i_sign;
end generate;


end behavior;