library IEEE;
use IEEE.std_logic_1164.all;

entity IFIDReg is
    port(i_CLK          :in std_logic;
         i_stall        :in std_logic;
         i_flush        :in std_logic;
         i_instr        :in std_logic_vector(31 downto 0);
         o_instr        :out std_logic_vector(31 downto 0));
end IFIDReg;

architecture s_IFIDReg of IFIDReg is

    component reg_n is
        generic(N : integer);
        port(i_CLK        : in std_logic;     -- Clock input
             i_RST        : in std_logic;     -- Reset input
             i_WE         : in std_logic;     -- Write enable input
             i_D          : in std_logic_vector(N-1 downto 0);     -- Data value input
             o_Q          : out std_logic_vector(N-1 downto 0));   -- Data value output
    end component;
    
    component invg is
        port(i_A          : in std_logic;
             o_F          : out std_logic);
    end component;

    component mux_N2to1_struct is
        generic(N : integer);
        port(i_s  : in std_logic;
             i_0  : in std_logic_vector(N-1 downto 0);
             i_1  : in std_logic_vector(N-1 downto 0);
             o_F  : out std_logic_vector(N-1 downto 0));
    end component;

    signal s_stallNot   :   std_logic;
    signal in_act       :   std_logic_vector(31 downto 0);

begin

    flush : mux_N2to1_struct
        generic map(N => 32)
        port map(i_s => i_flush,
                 i_0 => i_instr,
                 i_1 => "00000000000000000000000000000000",
                 o_F => in_act);

    snot : invg
        port map(i_A => i_stall,
                 o_F => s_stallNot);

    instr : reg_n
        generic map(N => 32)
        port map(i_CLK => i_CLK,
                 i_RST => '0',
                 i_WE => s_stallNot,
                 i_D => in_act,
                 o_Q => o_instr);
end s_IFIDReg;