library IEEE;
use IEEE.std_logic_1164.all;

entity ALU_shifter is
	port(	i_A 		: in std_logic_vector(31 downto 0);
	     	i_B 		: in std_logic_vector(31 downto 0);
		i_Control 	: in std_logic_vector(2 downto 0);
		i_Shamt		: in std_logic_vector(4 downto 0);
		i_nLeft_Right	: in std_logic;
		i_nLog_Arith	: in std_logic;
		i_ByteImm	: in std_logic_vector(7 downto 0);
		i_SIMD		: in std_logic;
		i_Signed	: in std_logic;
		o_F 		: out std_logic_vector(31 downto 0);
		o_Cout 		: out std_logic;
		o_overflow 	: out std_logic;
		o_zero 		: out std_logic;
		o_ShiftedVal	: out std_logic_vector(31 downto 0)
	);
end ALU_shifter;

architecture s_ALU_shifter of ALU_shifter is

component mux_N2to1_struct
  generic(N : integer);
  port(i_S  : in std_logic;
       i_0  : in std_logic_vector(N-1 downto 0);
       i_1  : in std_logic_vector(N-1 downto 0);
       o_F  : out std_logic_vector(N-1 downto 0));
end component;

component ALU_32 is
	port(	i_A 		: in std_logic_vector(31 downto 0);
	     	i_B 		: in std_logic_vector(31 downto 0);
		i_Control	: in std_logic_vector(2 downto 0);
		i_Signed	: in std_logic;
		o_F 		: out std_logic_vector(31 downto 0);
		o_Cout		: out std_logic;
		o_Zero		: out std_logic;
		o_Overflow	: out std_logic
	);
end component;

component ALU_SIMD is
	port(i_Rs 	: in std_logic_vector(31 downto 0);
	     i_Rt 	: in std_logic_vector(31 downto 0);
		 i_Imm	: in std_logic_vector(7 downto 0);
		 i_CTL	: in std_logic_vector(2 downto 0);
		 o_F 	: out std_logic_vector(31 downto 0);
		 o_A	: out std_logic_vector(31 downto 0);
		 o_B	: out std_logic_vector(31 downto 0)
	);
end component;

component barrelShifter is 
  generic(N : integer := 32);
  port( i_ShiftingVal	: in std_logic_vector(N-1 downto 0); 
	i_Shamt		: in std_logic_vector(4 downto 0);
	i_nLeft_Right	: in std_logic;
	i_nLog_Arith	: in std_logic;
	o_ShiftedVal	: out std_logic_vector(N-1 downto 0));
end component;

signal s_raddu, output_Mux : std_logic;
signal s_ALU_Control : std_logic_vector(2 downto 0);
signal s_ALU_to_Mux, s_SIMD_to_Mux, s_SIMD_A, s_SIMD_B, s_ALU_InputA, s_ALU_InputB : std_logic_vector(31 downto 0);

begin

s_ALU_Control(0) <= i_Control(0) and not i_SIMD;
s_ALU_Control(1) <= i_Control(1) and not i_SIMD;
s_ALU_Control(2) <= i_Control(2) and not i_SIMD;

SIMD: ALU_SIMD
	port map(i_Rs	=> i_A,
	     i_Rt 	=> i_B,
		 i_Imm	=> i_ByteImm,
		 i_CTL	=> i_Control,
		 o_F 	=> s_SIMD_to_Mux,
		 o_A	=> s_SIMD_A,
		 o_B	=> s_SIMD_B
	);

mux_ALUInputA : mux_N2to1_struct
	generic map (N => 32)
	port map(i_s => i_SIMD,
		 i_0 => i_A,
		 i_1 => s_SIMD_A,
		 o_F => s_ALU_InputA);
		 
mux_ALUInputB : mux_N2to1_struct
	generic map (N => 32)
	port map(i_s => i_SIMD,
		 i_0 => i_B,
		 i_1 => s_SIMD_B,
		 o_F => s_ALU_InputB);

ALU : ALU_32
	port map(i_A => s_ALU_InputA,
		 i_B => s_ALU_InputB,
		 i_Control => s_ALU_Control,
		 i_Signed => i_Signed,
		 o_F => s_ALU_to_Mux,
		 o_Cout => o_Cout,
		 o_Zero => o_zero,
		 o_Overflow => o_overflow);
		 
s_raddu <= i_Control(2) and not i_Control(1) and i_Control(0);
output_Mux <= i_SIMD and not s_raddu;
		 
mux_nALU_SIMD : mux_N2to1_struct
	generic map (N => 32)
	port map(i_s => output_Mux,
		 i_0 => s_ALU_to_Mux,
		 i_1 => s_SIMD_to_Mux,
		 o_F => o_F);

shifter : barrelShifter
	port map(i_ShiftingVal => i_B,
		 i_Shamt => i_Shamt,
		 i_nLeft_Right => i_nLeft_Right,
		 i_nLog_Arith => i_nLog_Arith,
		 o_ShiftedVal => o_ShiftedVal);
		 
		 


end s_ALU_shifter;
		  