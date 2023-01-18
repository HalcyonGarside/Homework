library IEEE;
use IEEE.std_logic_1164.all;

entity MEMWBReg is
    port(i_CLK          :in std_logic;
         i_stall        :in std_logic;
         i_flush        :in std_logic;
         i_RegWr        :in std_logic;
         i_MemToReg     :in std_logic;
         i_RegWrMem     :in std_logic;
         i_Rd           :in std_logic_vector(4 downto 0);
         i_MemOut       :in std_logic_vector(31 downto 0);
         i_ALUOut       :in std_logic_vector(31 downto 0);
		 i_OpCode		:in std_logic_vector(5 downto 0);
		 i_Funct		:in std_logic_vector(5 downto 0);
		 o_OpCode		:out std_logic_vector(5 downto 0);
		 o_Funct		:out std_logic_vector(5 downto 0);
         o_RegWr        :out std_logic;
         o_MemToReg     :out std_logic;
         o_RegWrMem     :out std_logic;
         o_Rd           :out std_logic_vector(4 downto 0);
         o_MemOut       :out std_logic_vector(31 downto 0);
         o_ALUOut       :out std_logic_vector(31 downto 0));

end MEMWBReg;

architecture s_MEMWBReg of MEMWBReg is

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

   component mux_21 is
        port(i_0 : in std_logic;
             i_1 : in std_logic;
             i_S : in std_logic;
             o_R : out std_logic
        );
    end component;

    signal s_stallNot, s_DMemWr, s_RegWr   :   std_logic;

    begin

-- Create signal used for halting write enable
stallNot: invg
        port map(i_A => i_stall,
                 o_F => s_stallNot);

-- Registers to store stage values
RegWr : reg_n
        generic map(N => 1)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D(0)   => i_RegWr,
                 o_Q(0)   => s_RegWr);
                 
MemToReg : reg_n
        generic map(N => 1)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D(0)   => i_MemToReg,
                 o_Q(0)   => o_MemToReg);

                 
RegWrMem : reg_n
        generic map(N => 1)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D(0)   => i_RegWrMem,
                 o_Q(0)   => o_RegWrMem);
                 
Rd : reg_n
        generic map(N => 5)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D   => i_Rd,
                 o_Q   => o_Rd);

                 
MemOut : reg_n
        generic map(N => 32)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D   => i_MemOut,
                 o_Q   => o_MemOut);

ALUOut : reg_n
        generic map(N => 32)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D   => i_ALUOut,
                 o_Q   => o_ALUOut);
				 
OpCode : reg_n
        generic map(N => 6)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D   => i_OpCode,
                 o_Q   => o_OpCode);
				 
Funct : reg_n
        generic map(N => 6)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D   => i_Funct,
                 o_Q   => o_Funct);
				 

-- If stalling, nothing gets written to DMem or Register File
true_RegWr : mux_21
        port map(i_0 => s_RegWr,
                 i_1 => '0',
                 i_S => i_stall,
                 o_R => o_RegWr);                 

end s_MEMWBReg;