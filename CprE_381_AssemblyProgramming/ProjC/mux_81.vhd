library IEEE;
use IEEE.std_logic_1164.all;

entity mux_81 is
	port(	i_I : in std_logic_vector(7 downto 0);
		i_S : in std_logic_vector(2 downto 0);
		o_R : out std_logic
	);
end mux_81;

architecture s_mux_81 of mux_81 is
begin

G1: process(i_I, i_S) begin

	case i_S is
		when "000" =>
			o_R <= i_I(0);
		when "001" =>
			o_R <= i_I(1);
		when "010" =>
			o_R <= i_I(2);
		when "011" =>
			o_R <= i_I(3);
		when "100" =>
			o_R <= i_I(4);
		when "101" =>
			o_R <= i_I(5);
		when "110" =>
			o_R <= i_I(6);
		when "111" =>
			o_R <= i_I(7);
		when others =>
			o_R <= i_I(0);
	end case;
end process;

end s_mux_81;