library IEEE;
use IEEE.std_logic_1164.all;
use work.reg_file_regs.all;

entity ALU_BYTE is
	port(i_Rs 	: in std_logic_vector(7 downto 0);
	     i_Rt 	: in std_logic_vector(7 downto 0);
		 i_Imm	: in std_logic_vector(7 downto 0);
		 i_CTL	: in std_logic_vector(2 downto 0);
		 o_F 	: out std_logic_vector(7 downto 0)
	);
end ALU_BYTE;

-- 000 Rs + Rt
-- 001 Unsigned Rs + Rt w/ Saturation
-- 010 Unsigned subtraction w/o Saturation
-- 011 Output i_Rs
-- 100 |Rs| Absolute Value
-- 101 Output i_Rs 
-- 110 Output i_Imm
-- 111 Returns 0

architecture s_ALU_BYTE of ALU_BYTE is

component full_adder is
  	port(	i_Cin: in std_logic;
       		i_A  : in std_logic;
       		i_B  : in std_logic;
       		o_R  : out std_logic;
       		o_Cout : out std_logic
	);
end component;

component mux_21 is
	port(	i_0 : in std_logic;
		i_1 : in std_logic;
		i_S : in std_logic;
		o_R : out std_logic
	);
end component;

component mux_81 is
	port(	i_I : in std_logic_vector(7 downto 0);
		i_S : in std_logic_vector(2 downto 0);
		o_R : out std_logic
	);
end component;

signal s_nAdd_Subtract : std_logic;
signal s_invRt, s_FullAdder_InputB, s_carryOver, s_absCarry, s_adderOut : std_logic_vector(7 downto 0);
signal s_absAdder_out : std_logic_vector(6 downto 0);
signal s_muxInputs : SIMD_MUX_INPUTS;

begin

-- Setup to be used for the entire BYTE
s_nAdd_Subtract <= not i_CTL(2) and i_CTL(1) and not i_CTL(0);
s_invRt <= not i_Rt;
s_absCarry(0) <= '0';


--Adder/subtractor module
adder_0 : full_adder
	port map(i_Cin => s_nAdd_Subtract,
		 i_A => i_Rs(0),
		 i_B => s_FullAdder_InputB(0),
		 o_R => s_adderOut(0),
		 o_Cout => s_carryOver(0));
		
middleBitSections: for i in 0 to 6 generate
	-- LSB of the BYTE
	invRt_i : mux_21
		port map(i_0 => i_Rt(i),
			 i_1 => s_invRt(i),
			 i_S => s_nAdd_Subtract,
			 o_R => s_FullAdder_InputB(i));
			 
	-- Adder for the absolute value operation
	abs_adder_i : full_adder
		port map(i_Cin => s_absCarry(i),
			 i_A => i_Rs(i),
			 i_B => i_Rs(7),
			 o_R => s_absAdder_out(i),
			 o_Cout => s_absCarry(i+1));
			 
	s_muxInputs(i)(0) <= s_adderOut(i);
	s_muxInputs(i)(1) <= s_carryOver(7) or s_adderOut(i);	
	s_muxInputs(i)(2) <= s_adderOut(i);	
	s_muxInputs(i)(3) <= i_Rs(i);	
	s_muxInputs(i)(4) <= i_Rs(7) xor s_absAdder_out(i);	
	s_muxInputs(i)(5) <= i_Rs(i);	
	s_muxInputs(i)(6) <= i_Imm(i);	
	s_muxInputs(i)(7) <= '0';	 
			 
	mux_i : mux_81
		port map(i_I => s_muxInputs(i),
			i_S => i_CTL,
			o_R => o_F(i));
end generate;
		
middleBitAdders: for i in 1 to 7 generate
	--Adder/subtractor module
	adder_i : full_adder
		port map(i_Cin => s_carryOver(i-1),
			 i_A => i_Rs(i),
			 i_B => s_FullAdder_InputB(i),
			 o_R => s_adderOut(i),
			 o_Cout => s_carryOver(i));
 end generate;

-- LSB of the BYTE
	invRt_7 : mux_21
		port map(i_0 => i_Rt(7),
			 i_1 => s_invRt(7),
			 i_S => s_nAdd_Subtract,
			 o_R => s_FullAdder_InputB(7));
			 
			 
	s_muxInputs(7)(0) <= s_adderOut(7);
	s_muxInputs(7)(1) <= s_carryOver(7) or s_adderOut(7);	
	s_muxInputs(7)(2) <= s_adderOut(7);	
	s_muxInputs(7)(3) <= i_Rs(7);	
	s_muxInputs(7)(4) <= '0';	
	s_muxInputs(7)(5) <= i_Rs(7);	
	s_muxInputs(7)(6) <= i_Imm(7);	
	s_muxInputs(7)(7) <= '0';	 
			 
	mux_7 : mux_81
		port map(i_I => s_muxInputs(7),
			i_S => i_CTL,
			o_R => o_F(7));
		 
end s_ALU_BYTE;