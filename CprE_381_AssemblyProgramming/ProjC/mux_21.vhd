library IEEE;
use IEEE.std_logic_1164.all;

entity mux_21 is
	port(	i_0 : in std_logic;
		i_1 : in std_logic;
		i_S : in std_logic;
		o_R : out std_logic
	);
end mux_21;

architecture s_mux_21 of mux_21 is
begin

G1: process(i_S, i_0, i_1) begin

	case i_S is
		when '0' =>
			o_R <= i_0;
		when '1' =>
			o_R <= i_1;
		when others => 
			o_R <= i_0;
	end case;
end process;

end s_mux_21;