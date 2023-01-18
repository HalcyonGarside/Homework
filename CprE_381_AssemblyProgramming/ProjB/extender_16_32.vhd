library IEEE;
use IEEE.std_logic_1164.all;

entity extender_16_32 is
	port(	i_I 	: in std_logic_vector(15 downto 0);
		i_signed: in std_logic;
		o_O 	: out std_logic_vector(31 downto 0));
end extender_16_32;

architecture s_extender_16_32 of extender_16_32 is

signal out_temp : std_logic;

begin

with i_signed select
	out_temp <= i_I(15) when '1',
			'0' when others;

G1: for i in 0 to 15 generate
	o_O(i) <= i_I(i);
end generate;

G2: for i in 16 to 31 generate
	o_O(i) <= out_temp;
end generate;

end s_extender_16_32;