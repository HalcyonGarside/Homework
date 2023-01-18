library IEEE;
use IEEE.std_logic_1164.all;

entity mux_N2to1_struct is
  generic(N : integer);
  port(i_s  : in std_logic;
       i_0  : in std_logic_vector(N-1 downto 0);
       i_1  : in std_logic_vector(N-1 downto 0);
       o_F  : out std_logic_vector(N-1 downto 0));
end mux_N2to1_struct;

architecture s_mux_N2to1_struct of mux_N2to1_struct is

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

component invg
  port(i_A  : in std_logic;
       o_F  : out std_logic);
end component;

signal invs : std_logic;
signal sandi1, sandi0 : std_logic_vector(N-1 downto 0);

begin

  inv_0: invg
    port map(i_A  => i_s,
  	          o_F  => invs);

G1: for i in 0 to N-1 generate
  and_0: andg2
    port map(i_A => i_s,
	     i_B => i_1(i),
	     o_F => sandi1(i));

  and_1: andg2
    port map(i_A => invs,
	     i_B => i_0(i),
	     o_F => sandi0(i));



  or_0: org2
    port map(i_A => sandi1(i),
	     i_B => sandi0(i),
	     o_F => o_F(i));

end generate;
end s_mux_N2to1_struct;