library IEEE;
use IEEE.std_logic_1164.all;

entity norg32 is
	port(	i_In		: in std_logic_vector(31 downto 0);
		o_F 		: out std_logic
	);
end norg32;

architecture dataflow of norg32 is
begin

o_F <= not(i_In(0) or i_In(1) or i_In(2) or i_In(3) or i_In(4) or i_In(5) or i_In(6) or i_In(7) or i_In(8) or i_In(9) or i_In(10) or i_In(11) or i_In(12) or i_In(13) or i_In(14) or i_In(15) or i_In(16) or i_In(17) or i_In(18) or i_In(19) or i_In(20) or i_In(21) or i_In(22) or i_In(23) or i_In(24) or i_In(25) or i_In(26) or i_In(27) or i_In(28) or i_In(29) or i_In(30) or i_In(31));

end dataflow;