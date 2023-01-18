library IEEE;
use IEEE.std_logic_1164.all;

entity barrelShifter is
  generic(N : integer := 32);
  port(i_ShiftingVal	: in std_logic_vector(N-1 downto 0); 
	i_Shamt		: in std_logic_vector(4 downto 0);
	i_nLeft_Right	: in std_logic;
	i_nLog_Arith	: in std_logic;
	o_ShiftedVal	: out std_logic_vector(N-1 downto 0));

end barrelShifter;

architecture structure of barrelShifter is

component mux_21
	port(	i_0 : in std_logic;
		i_1 : in std_logic;
		i_S : in std_logic;
		o_R : out std_logic
	);
end component;

component and2
	port(	i_A : in std_logic;
		i_B : in std_logic;
		o_R : out std_logic
	);
end component;

signal inFlip_to_row1, row1_to_row2, row2_to_row3  : std_logic_vector(N-1 downto 0);
signal row3_to_row4, row4_to_row5, row5_to_outFlip : std_logic_vector(N-1 downto 0);
signal control_and_to_mux, shift_in  : std_logic;

begin

-------------- Input flipper -----------------------

inputFlipper: for i in 0 to N-1 generate
  mux_flipper1_i: mux_21
    port map(i_0  => i_ShiftingVal(31 - i),
             i_1  => i_ShiftingVal(i),
	     i_S  => i_nLeft_Right,
  	     o_R  => inFlip_to_row1(i));
end generate;

-------------- Control Logic -----------------------

controlAnd: and2
	port map(i_A => i_nLeft_Right,
		 i_B => i_nLog_Arith,
		 o_R => control_and_to_mux);

controlMux: mux_21
	port map(i_0 => '0',
		 i_1 => i_ShiftingVal(31),
		 i_S => control_and_to_mux,
		 o_R => shift_in);

--------------- Shifting Mux Rows --------------------

		--- Row 1 ---
muxRow1: for i in 0 to 30 generate
  mux_row1_i: mux_21
    port map(i_0  => inFlip_to_row1(i),
             i_1  => inFlip_to_row1(i + 1),
	     i_S  => i_shamt(0),
  	     o_R  => row1_to_row2(i));
end generate;

mux_row1_31: mux_21
  port map(i_0  => inFlip_to_row1(31),
           i_1  => shift_in,
	   i_S  => i_shamt(0),
  	   o_R  => row1_to_row2(31));


		--- Row 2 ---
muxRow2a: for i in 0 to 29 generate
  mux_row2_i: mux_21
    port map(i_0  => row1_to_row2(i),
             i_1  => row1_to_row2(i + 2),
	     i_S  => i_shamt(1),
  	     o_R  => row2_to_row3(i));
end generate;

muxRow2b: for i in 30 to 31 generate
  mux_row2_i: mux_21
    port map(i_0  => row1_to_row2(i),
             i_1  => shift_in,
	     i_S  => i_shamt(1),
  	     o_R  => row2_to_row3(i));
end generate;

		--- Row 3 ---
muxRow3a: for i in 0 to 27 generate
  mux_row3_i: mux_21
    port map(i_0  => row2_to_row3(i),
             i_1  => row2_to_row3(i + 4),
	     i_S  => i_shamt(2),
  	     o_R  => row3_to_row4(i));
end generate;

muxRow3b: for i in 28 to 31 generate
  mux_row3_i: mux_21
    port map(i_0  => row2_to_row3(i),
             i_1  => shift_in,
	     i_S  => i_shamt(2),
  	     o_R  => row3_to_row4(i));
end generate;

		--- Row 4 ---
muxRow4a: for i in 0 to 23 generate
  mux_row4_i: mux_21
    port map(i_0  => row3_to_row4(i),
             i_1  => row3_to_row4(i + 8),
	     i_S  => i_shamt(3),
  	     o_R  => row4_to_row5(i));
end generate;

muxRow4b: for i in 24 to 31 generate
  mux_row4_i: mux_21
    port map(i_0  => row3_to_row4(i),
             i_1  => shift_in,
	     i_S  => i_shamt(3),
  	     o_R  => row4_to_row5(i));
end generate;

		--- Row 5 ---
muxRow5a: for i in 0 to 15 generate
  mux_row5_i: mux_21
    port map(i_0  => row4_to_row5(i),
             i_1  => row4_to_row5(i + 16),
	     i_S  => i_shamt(4),
  	     o_R  => row5_to_outFlip(i));
end generate;

muxRow5b: for i in 16 to 31 generate
  mux_row5_i: mux_21
    port map(i_0  => row4_to_row5(i),
             i_1  => shift_in,
	     i_S  => i_shamt(4),
  	     o_R  => row5_to_outFlip(i));
end generate;


---------------- Output flipper ----------------------

outputFlipper: for i in 0 to N-1 generate
  mux_flipper2_i: mux_21
    port map(i_0  => row5_to_outFlip(31 - i),
             i_1  => row5_to_outFlip(i),
	     i_S  => i_nLeft_Right,
  	     o_R  => o_ShiftedVal(i));
end generate;

end structure;