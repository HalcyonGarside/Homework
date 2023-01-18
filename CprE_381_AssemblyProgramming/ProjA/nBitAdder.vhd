library IEEE;
use IEEE.std_logic_1164.all;

entity nBitAdder is
  generic(N : integer);
  port (i_A		: in std_logic_vector(N-1 downto 0);
	i_B		: in std_logic_vector(N-1 downto 0);
       	i_Cin		: in std_logic;
       	o_Sum		: out std_logic_vector(N-1 downto 0);
       	o_Cout		: out std_logic);

end nBitAdder;

architecture structure of nBitAdder is


component struct_single_adder
  port (i_A		: in std_logic;
	i_B		: in std_logic;
       	i_Cin		: in std_logic;
       	o_Sum		: out std_logic;
       	o_Cout		: out std_logic);

end component;

signal carryOver : std_logic_vector(N-1 downto 1);
signal first_Cin : std_logic;

--------------------------------------------------------------------

begin

adder_0: struct_single_adder
	port map(
		i_A => i_A(0),
		i_B => i_B(0),
		i_Cin => i_Cin,
		o_Sum => o_Sum(0),
		o_Cout => carryOver(1));

G1: for i in 1 to N-2 generate
	adder_i: struct_single_adder
		port map(
			i_A => i_A(i),
			i_B => i_B(i),
			i_Cin => carryOver(i),
			o_Sum => o_Sum(i),
			o_Cout => carryOver(i + 1));
end generate;

adder_31: struct_single_adder
	port map(
		i_A => i_A(31),
		i_B => i_B(31),
		i_Cin => carryOver(31),
		o_Sum => o_Sum(31),
		o_Cout => o_Cout);


end structure;