library IEEE;
use IEEE.std_logic_1164.all;

entity Nfull_adder_struct is
  generic(N : integer);
  port(i_Cin: in std_logic;
       i_A  : in std_logic_vector(N-1 downto 0);
       i_B  : in std_logic_vector(N-1 downto 0);
       o_R  : out std_logic_vector(N-1 downto 0);
       o_Cout : out std_logic);

end Nfull_adder_struct;

architecture s_Nfull_adder_struct of Nfull_adder_struct is

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

component xorg2 is
  port(i_A  : in std_logic;
       i_B  : in std_logic;
       o_F  : out std_logic);
end component;

signal carry : std_logic_vector(N downto 0);
signal AxorB, AandB, CinandAxorB : std_logic_vector(N-1 downto 0);

begin

  carry(0) <= i_Cin;

G1: for i in 0 to N-1 generate
  xor_0: xorg2
    port map(i_A => i_A(i),
	     i_B => i_B(i),
	     o_F => AxorB(i));

  and_0: andg2
    port map(i_A => i_A(i),
	     i_B => i_B(i),
	     o_F => AandB(i));



  xor_1: xorg2
    port map(i_A => AxorB(i),
	     i_B => carry(i),
	     o_F => o_R(i));

  and_1: andg2
    port map(i_A => carry(i),
	     i_B => AxorB(i),
	     o_F => CinandAxorB(i));



  or_0: org2
    port map(i_A => CinandAxorB(i),
	     i_B => AandB(i),
	     o_F => carry(i+1));
end generate;

  o_Cout <= carry(N);
end s_Nfull_adder_struct;