library IEEE;
use IEEE.std_logic_1164.all;
use work.reg_file_regs.all;

entity ALU_SIMD is
	port(i_Rs 	: in std_logic_vector(31 downto 0);
	     i_Rt 	: in std_logic_vector(31 downto 0);
		 i_Imm	: in std_logic_vector(7 downto 0);
		 i_CTL	: in std_logic_vector(2 downto 0);
		 o_F 	: out std_logic_vector(31 downto 0);
		 o_A	: out std_logic_vector(31 downto 0);
		 o_B	: out std_logic_vector(31 downto 0)
	);
end ALU_SIMD;

-- 000 Rs + Rt
-- 001 Unsigned Rs + Rt w/ Saturation
-- 010 Unsigned subtraction w/o Saturation
-- 011 Output i_Rs
-- 100 |Rs| Absolute Value
-- 101 Add Bytes 
-- 110 Output i_Imm
-- 111 Returns 0

architecture s_ALU_SIMD of ALU_SIMD is

component mux_N2to1_struct
  generic(N : integer);
  port(i_S  : in std_logic;
       i_0  : in std_logic_vector(N-1 downto 0);
       i_1  : in std_logic_vector(N-1 downto 0);
       o_F  : out std_logic_vector(N-1 downto 0));
end component;

component ALU_BYTE
	port(i_Rs 	: in std_logic_vector(7 downto 0);
	     i_Rt 	: in std_logic_vector(7 downto 0);
		 i_Imm	: in std_logic_vector(7 downto 0);
		 i_CTL	: in std_logic_vector(2 downto 0);
		 o_F 	: out std_logic_vector(7 downto 0)
	);
end component;

component nBitAdder
  generic(N : integer);
  port (i_A		: in std_logic_vector(N-1 downto 0);
		i_B		: in std_logic_vector(N-1 downto 0);
       	i_Cin		: in std_logic;
       	o_Sum		: out std_logic_vector(N-1 downto 0);
       	o_Cout		: out std_logic);

end component;

component extender
	generic (N : integer);
	port(i_value 	: in std_logic_vector(N-1 downto 0);
	     i_sign	: in std_logic;
	     o_output 	: out std_logic_vector(31 downto 0));
end component;

signal s_Rs_into_BYTE_ALUs, s_BYTE_ALUs_output : std_logic_vector(31 downto 0);
signal s_ExtendA1, s_ExtendA2, s_ExtendB1, s_ExtendB2 : std_logic_vector(31 downto 0);
signal s_CoutA, s_CoutB, s_dupRs : std_logic;

begin

-- 3 Muxes off the start to choose Rs input

s_Rs_into_BYTE_ALUs(7 downto 0) <= i_Rs(7 downto 0);
s_dupRs <= (not i_CTL(2)) and i_CTL(1) and i_CTL(0);

mux8_to_15: mux_N2to1_struct
  generic map(N => 8)
  port map(i_S => s_dupRs,
		 i_0 => i_Rs(15 downto 8),
		 i_1 => i_Rs(7 downto 0),
		 o_F => s_Rs_into_BYTE_ALUs(15 downto 8));
		 
mux16_to_23: mux_N2to1_struct
  generic map(N => 8)
  port map(i_S => s_dupRs,
		 i_0 => i_Rs(23 downto 16),
		 i_1 => i_Rs(7 downto 0),
		 o_F => s_Rs_into_BYTE_ALUs(23 downto 16));
		 
mux24_to_31: mux_N2to1_struct
  generic map(N => 8)
  port map(i_S => s_dupRs,
		 i_0 => i_Rs(31 downto 24),
		 i_1 => i_Rs(7 downto 0),
		 o_F => s_Rs_into_BYTE_ALUs(31 downto 24));


BYTE_ALU_0 :  ALU_BYTE
	port map(i_Rs	=> s_Rs_into_BYTE_ALUs(7 downto 0),
		 i_Rt 	=> i_Rt(7 downto 0),
		 i_Imm	=> i_Imm,
		 i_CTL	=> i_CTL,
		 o_F 	=> s_BYTE_ALUs_output(7 downto 0));


BYTE_ALU_1 :  ALU_BYTE
		port map(i_Rs	=> s_Rs_into_BYTE_ALUs(15 downto 8),
			 i_Rt 	=> i_Rt(15 downto 8),
			 i_Imm	=> i_Imm,
			 i_CTL	=> i_CTL,
			 o_F 	=> s_BYTE_ALUs_output(15 downto 8));
			 
 BYTE_ALU_2 :  ALU_BYTE
		port map(i_Rs	=> s_Rs_into_BYTE_ALUs(23 downto 16),
			 i_Rt 	=> i_Rt(23 downto 16),
			 i_Imm	=> i_Imm,
			 i_CTL	=> i_CTL,
			 o_F 	=> s_BYTE_ALUs_output(23 downto 16));
			 
 BYTE_ALU_3 :  ALU_BYTE
		port map(i_Rs	=> s_Rs_into_BYTE_ALUs(31 downto 24),
			 i_Rt 	=> i_Rt(31 downto 24),
			 i_Imm	=> i_Imm,
			 i_CTL	=> i_CTL,
			 o_F 	=> s_BYTE_ALUs_output(31 downto 24));
			 

extenderA1 : extender
	generic map (N => 8)
	port map(i_value => s_BYTE_ALUs_output(7 downto 0),
		 i_sign => '0',
		 o_output => s_ExtendA1);
		 
extenderA2 : extender
	generic map (N => 8)
	port map(i_value => s_BYTE_ALUs_output(15 downto 8),
		 i_sign => '0',
		 o_output => s_ExtendA2);
		 
extenderB1 : extender
	generic map (N => 8)
	port map(i_value => s_BYTE_ALUs_output(23 downto 16),
		 i_sign => '0',
		 o_output => s_ExtendB1);
		 
extenderB2 : extender
	generic map (N => 8)
	port map(i_value => s_BYTE_ALUs_output(31 downto 24),
		 i_sign => '0',
		 o_output => s_ExtendB2);


adderA: nBitAdder
	generic map(N => 32)
	port map(
		i_A => s_ExtendA1,
		i_B => s_ExtendA2,
		i_Cin => '0',
		o_Sum => o_A,
		o_Cout => s_CoutA);
		
adderB: nBitAdder
	generic map(N => 32)
	port map(
		i_A => s_ExtendB1,
		i_B => s_ExtendB2,
		i_Cin => '0',
		o_Sum => o_B,
		o_Cout => s_CoutB);
		
o_F <= s_BYTE_ALUs_output;


end s_ALU_SIMD;