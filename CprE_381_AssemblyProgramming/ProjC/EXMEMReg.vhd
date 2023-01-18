library IEEE;
use IEEE.std_logic_1164.all;

entity EXMEMReg is
    port(i_CLK          :in std_logic;
         i_stall        :in std_logic;
         i_flush        :in std_logic;
         i_DMemWr       :in std_logic;
         i_RegWr        :in std_logic;
         i_MemToReg     :in std_logic;
         i_RegWrMem     :in std_logic;
         i_Rd           :in std_logic_vector(4 downto 0);
         i_Reg1         :in std_logic_vector(31 downto 0);
         i_imm          :in std_logic_vector(31 downto 0);
         i_ALUOut       :in std_logic_vector(31 downto 0);
		 i_OpCode		:in std_logic_vector(5 downto 0);
		 i_Funct		:in std_logic_vector(5 downto 0);
		 o_OpCode		:out std_logic_vector(5 downto 0);
		 o_Funct		:out std_logic_vector(5 downto 0);
         o_DMemWr       :out std_logic;
         o_RegWr        :out std_logic;
         o_MemToReg     :out std_logic;
         o_RegWrMem     :out std_logic;
         o_Rd           :out std_logic_vector(4 downto 0);
         o_Reg1         :out std_logic_vector(31 downto 0);
         o_imm          :out std_logic_vector(31 downto 0);
         o_ALUOut       :out std_logic_vector(31 downto 0));

end EXMEMReg;

architecture s_EXMEMReg of EXMEMReg is

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
DMemWr : reg_n
        generic map(N => 1)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D(0)   => i_DMemWr,
                 o_Q(0)   => s_DMemWr);

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

                 
Reg1 : reg_n
        generic map(N => 32)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D   => i_Reg1,
                 o_Q   => o_Reg1);
                 
imm : reg_n
        generic map(N => 32)
        port map(i_CLK => i_CLK,
                 i_RST => i_flush,
                 i_WE  => s_stallNot,
                 i_D   => i_imm,
                 o_Q   => o_imm);

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
true_DMemWr : mux_21
        port map(i_0 => s_DMemWr,
                 i_1 => '0',
                 i_S => i_stall,
                 o_R => o_DMemWr);

true_RegWr : mux_21
        port map(i_0 => s_RegWr,
                 i_1 => '0',
                 i_S => i_stall,
                 o_R => o_RegWr);                 

end s_EXMEMReg;