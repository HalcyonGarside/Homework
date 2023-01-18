library IEEE;
use IEEE.std_logic_1164.all;

entity comparator is
    generic(N : integer);
    port(i_A : in std_logic_vector(N-1 downto 0);
         i_B : in std_logic_vector(N-1 downto 0);
         o_F : out std_logic);
end comparator;

architecture s_comparator of comparator is
    
    component xnorg2 is

        port(i_A          : in std_logic;
             i_B          : in std_logic;
             o_R          : out std_logic);
      
    end component;

    component andg2 is

        port(i_A          : in std_logic;
             i_B          : in std_logic;
             o_F          : out std_logic);
      
    end component;

    signal axnorb, compared : std_logic_vector(N-1 downto 0);

begin

o_F <= (i_A(0) xnor i_B(0)) and (i_A(1) xnor i_B(1)) and (i_A(2) xnor i_B(2)) and (i_A(3) xnor i_B(3)) and (i_A(4) xnor i_B(4)) and (i_A(5) xnor i_B(5)) and (i_A(6) xnor i_B(6)) and (i_A(7) xnor i_B(7)) and (i_A(8) xnor i_B(8)) and (i_A(9) xnor i_B(9)) and (i_A(10) xnor i_B(10)) and (i_A(11) xnor i_B(11)) and (i_A(12) xnor i_B(12)) and (i_A(13) xnor i_B(13)) and (i_A(14) xnor i_B(14)) and (i_A(15) xnor i_B(15)) and (i_A(16) xnor i_B(16)) and (i_A(17) xnor i_B(17)) and (i_A(18) xnor i_B(18)) and (i_A(19) xnor i_B(19)) and (i_A(20) xnor i_B(20)) and (i_A(21) xnor i_B(21)) and (i_A(22) xnor i_B(22)) and (i_A(23) xnor i_B(23)) and (i_A(24) xnor i_B(24)) and (i_A(25) xnor i_B(25)) and (i_A(26) xnor i_B(26)) and (i_A(27) xnor i_B(27)) and (i_A(28) xnor i_B(28)) and (i_A(29) xnor i_B(29)) and (i_A(30) xnor i_B(30)) and (i_A(31) xnor i_B(31));

--G1: for i in N-1 downto 0 generate
--    compare : xnorg2
--        port map(i_A => i_A(i),
--                 i_B => i_B(i),
--                 o_R => axnorb(i));
--end generate;

--compared(N-1) <= axnorb(N-1);

--G2: for i in N-2 downto 0 generate 
--    findComp : andg2
--        port map(i_A => compared(i+1),
--                 i_B => axnorb(i),
--                 o_F => compared(i));
--end generate;

--o_F <= compared(0);

end s_comparator;