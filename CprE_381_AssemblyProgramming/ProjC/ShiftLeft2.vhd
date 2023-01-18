library IEEE;
use IEEE.std_logic_1164.all;

entity ShiftLeft2 is
	generic(N : integer := 32);
	port(i_Input 	: in std_logic_vector(N-1 downto 0);
	     o_Output 	: out std_logic_vector(N-1 downto 0)
	);
end ShiftLeft2;

architecture d_ShiftLeft2 of ShiftLeft2 is

begin

o_Output(1 downto 0) <= "00";
o_Output(N-1 downto 2) <= i_Input(N-3 downto 0);

end d_ShiftLeft2;