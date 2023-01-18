library IEEE;
use IEEE.std_logic_1164.all;

entity bitwise_functs is
	port( 	i_A 				: in std_logic;
		i_B 				: in std_logic;
		o_A, o_O, o_X, o_NO, o_NA	: out std_logic
	);
end bitwise_functs;

architecture s_bitwise_functs of bitwise_functs is
begin

o_A <= i_A and i_B;
o_O <= i_A or i_B;
o_X <= i_A xor i_B;
o_NO <= i_A nor i_B;
o_NA <= i_A nand i_B;

end s_bitwise_functs;