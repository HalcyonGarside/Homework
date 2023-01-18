library IEEE;
use IEEE.std_logic_1164.all;

entity MSB_ALU is
	port(i_A 	: in std_logic;
	    i_B 	: in std_logic;
		i_LT	: in std_logic;
		i_Cin	: in std_logic;
	    i_funct : in std_logic_vector(2 downto 0);
		i_Signed: in std_logic;
		o_Set	: out std_logic;
		o_Over	: out std_logic;
		o_R 	: out std_logic;
		o_Cout  : out std_logic
	);
end MSB_ALU;

architecture s_MSB_ALU of MSB_ALU is

component full_adder is
  	port(	i_Cin: in std_logic;
       		i_A  : in std_logic;
       		i_B  : in std_logic;
       		o_R  : out std_logic;
       		o_Cout : out std_logic
	);
end component;

component bitwise_functs is
	port( 	i_A 				: in std_logic;
		i_B 				: in std_logic;
		o_A, o_O, o_X, o_NO, o_NA	: out std_logic
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

component xorg2 is
	port(i_A : in std_logic;
	     i_B : in std_logic;
	     o_F : out std_logic);
end component;

signal o_adder, s_invB, invertedB_to_mux, smallMux_select, norgate_to_smallMux, carryOut, SLT_overflow, s_SLT : std_logic;
signal o_bus : std_logic_vector(7 downto 0);

begin

-- Logic to know to invert B
norgate_to_smallMux <= i_funct(2) xnor i_funct(1);

smallMux_select <= norgate_to_smallMux and i_funct(0);

invertedB_to_mux <= not i_B;
		
--Invert B in case of subtraction
invB : mux_21
	port map(i_0 => i_B,
		 i_1 => invertedB_to_mux,
		 i_S => smallMux_select,
		 o_R => s_invB);

--Adder/subtractor module
adder : full_adder
	port map(i_Cin => i_Cin,
		 i_A => i_A,
		 i_B => s_invB,
		 o_R => o_adder,
		 o_Cout => carryOut);

--Constitutes both add and subtract
o_bus(0) <= o_adder;
o_bus(1) <= o_adder;



--Bitwise functions module
bitwise : bitwise_functs
	port map(i_A => i_A,
		i_B => i_B,
		o_A => o_bus(2), 
		o_O => o_bus(3), 
		o_X => o_bus(4), 
		o_NO => o_bus(5), 
		o_NA => o_bus(6));

--SLT determined either by last 1-bit ALU.
o_bus(7) <= i_LT;


--Final MUX
-- 0->1, Add/Sub
-- 2, AND
-- 3, OR
-- 4, XOR
-- 5, NOR
-- 6, NAND
-- 7, SLT
mux1 : mux_81
	port map(i_I => o_bus,
		 i_S => i_funct,
		 o_R => o_R);

-- Logic to know if A < B
overflow : xorg2
	port map(i_A => i_Cin,
		i_B => carryOut,
		o_F => SLT_overflow);


SLT : xorg2
	port map(i_A => SLT_overflow,
		i_B => o_adder,
		o_F => s_SLT);

-- Setting outputs
o_Over <= SLT_overflow;
o_Cout <= carryOut;

SLT_Mux : mux_21
	port map(i_0 => not carryOut,
		 i_1 => s_SLT,
		 i_S => i_Signed,
		 o_R => o_Set);

end s_MSB_ALU;