library IEEE;
use IEEE.std_logic_1164.all;

entity xnorg2 is
	port(	i_A		: in std_logic;
		i_B		: in std_logic;
		o_R 		: out std_logic
	);
end xnorg2;

architecture s_xnor2 of xnorg2 is
begin

o_R <= i_A xnor i_B;

end s_xnor2;