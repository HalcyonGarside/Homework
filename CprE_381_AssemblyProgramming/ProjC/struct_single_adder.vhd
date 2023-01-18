library IEEE;
use IEEE.std_logic_1164.all;

entity struct_single_adder is
  port (i_A		: in std_logic;
	i_B		: in std_logic;
       	i_Cin		: in std_logic;
       	o_Sum		: out std_logic;
       	o_Cout		: out std_logic);

end struct_single_adder;

architecture structure of struct_single_adder is

component andg2
  port(i_A  : in std_logic;
       i_B  : in std_logic;
       o_F  : out std_logic);
end component;

component org2
  port(i_A  : in std_logic;
       i_B  : in std_logic;
       o_F  : out std_logic);
end component;

component xorg2
  port(i_A  : in std_logic;
       i_B  : in std_logic;
       o_F  : out std_logic);
end component;

signal xor_output, and1_output, and2_output : std_logic :='0';

-----------------------------

begin

level1_xor: xorg2
  port map(
	i_A => i_A,
	i_B => i_B,
	o_F => xor_output);

level2_xor: xorg2
  port map(
	i_A => xor_output,
	i_B => i_Cin,
	o_F => o_Sum);

and_gate1: andg2
  port map(
	i_A => xor_output,
	i_B => i_Cin,
	o_F => and1_output);

and_gate2: andg2
  port map(
	i_A => i_A,
	i_B => i_B,
	o_F => and2_output);

or_gate: org2
  port map(
	i_A => and1_output,
	i_B => and2_output,
	o_F => o_Cout);

end structure;