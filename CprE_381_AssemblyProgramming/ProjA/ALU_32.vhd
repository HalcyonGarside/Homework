library IEEE;
use IEEE.std_logic_1164.all;

entity ALU_32 is
	port(	i_A 		: in std_logic_vector(31 downto 0);
	     	i_B 		: in std_logic_vector(31 downto 0);
		i_Control	: in std_logic_vector(2 downto 0);
		o_F 		: out std_logic_vector(31 downto 0);
		o_Cout		: out std_logic;
		o_Zero		: out std_logic;
		o_Overflow	: out std_logic
	);
end ALU_32;

architecture s_ALU_32 of ALU_32 is

component MSB_ALU is
	port(	i_A 	: in std_logic;
	     	i_B 	: in std_logic;
		i_LT	: in std_logic;
		i_Cin	: in std_logic;
	     	i_funct : in std_logic_vector(2 downto 0);
		o_Set	: out std_logic;
		o_Over	: out std_logic;
		o_R 	: out std_logic;
		o_Cout  : out std_logic
	);
end component;

component ALU_1 is
	port(	i_A 	: in std_logic;
	     	i_B 	: in std_logic;
		i_LT	: in std_logic;
		i_Cin	: in std_logic;
	     	i_funct : in std_logic_vector(2 downto 0);
		o_R 	: out std_logic;
		o_Cout	: out std_logic
	);
end component;

component norg32 is
	port(	i_In		: in std_logic_vector(31 downto 0);
		o_F 		: out std_logic
	);
end component;

component xnorg2 is
	port(	i_A		: in std_logic;
		i_B		: in std_logic;
		o_R 		: out std_logic
	);
end component;

component and2 is
	port(	i_A		: in std_logic;
		i_B		: in std_logic;
		o_R 		: out std_logic
	);
end component;

signal carry_between, outputSignal : std_logic_vector(31 downto 0);
signal setSignal, xnor_to_and : std_logic;

begin

-- Logic for when to add in a carry bit
xnorg : xnorg2
	port map(i_A => i_Control(2),
		i_B => i_Control(1),
		o_R => xnor_to_and);

andg : and2
	port map(i_A => xnor_to_and,
		i_B => i_Control(0),
		o_R => carry_between(0));


-- First 1 bit ALU that is a little bit different because of the i_LT input
single_bit_ALU_0 : ALU_1
		port map(i_A 	=> i_A(0),
	     		i_B 	=> i_B(0),
			i_LT	=> setSignal,
			i_Cin	=> carry_between(0),
	     		i_funct => i_Control,
			o_R 	=> outputSignal(0),
			o_Cout	=> carry_between(1));

-- 1 bit ALUs 1-30
GenALUs : for i in 30 downto 1 generate
	single_bit_ALU_i : ALU_1
		port map(i_A 	=> i_A(i),
	     		i_B 	=> i_B(i),
			i_LT	=> '0',
			i_Cin	=> carry_between(i),
	     		i_funct => i_Control,
			o_R 	=> outputSignal(i),
			o_Cout	=> carry_between(i + 1));
end generate;

-- Special 1 bit ALU that I had to create to handle the SLT instruction and overflow
single_bit_ALU_i : MSB_ALU
		port map(i_A 	=> i_A(31),
	     		i_B 	=> i_B(31),
			i_LT	=> '0',
			i_Cin	=> carry_between(31),
	     		i_funct => i_Control,
			o_R 	=> outputSignal(31),
			o_Set	=> setSignal,
			o_Over	=> o_Overflow,
			o_Cout	=> o_Cout);

-- Zero gate is used to know if the output is equal to zero
zeroGate : norg32
	port map(i_In	=> outputSignal,
		o_F => o_Zero);

o_F <= outputSignal;

end s_ALU_32;