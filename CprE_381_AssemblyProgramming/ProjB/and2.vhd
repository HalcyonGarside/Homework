library IEEE;
use IEEE.std_logic_1164.all;

entity and2 is
	port(	i_A : in std_logic;
		i_B : in std_logic;
		o_R : out std_logic
	);
end and2;

architecture s_and2 of and2 is
begin

o_R <= i_A and i_B;

end s_and2;