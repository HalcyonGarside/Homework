library IEEE;
use IEEE.std_logic_1164.all;

entity full_adder is
  port(i_Cin: in std_logic;
       i_A  : in std_logic;
       i_B  : in std_logic;
       o_R  : out std_logic;
       o_Cout : out std_logic);

end full_adder;

architecture s_full_adder of full_adder is

signal AxorB, AandB, CinandAxorB, subB : std_logic;

begin

  AxorB <= i_A xor i_B;
  AandB <= i_A and i_B;

  o_R <= AxorB xor i_Cin;
  CinandAxorB <= i_Cin and AxorB;

  o_Cout <= CinandAxorB or AandB;

end s_full_adder;