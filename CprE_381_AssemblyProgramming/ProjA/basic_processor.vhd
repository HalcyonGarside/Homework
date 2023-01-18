library IEEE;
use IEEE.std_logic_1164.all;

entity basic_processor is
	port( imm 		: in std_logic_vector(15 downto 0);
	      rs, rt, rd	: in std_logic_vector(4  downto 0);
	      funct		: in std_logic_vector(2 downto 0);
	      shamt		: in std_logic_vector(4 downto 0);
	      reset, we, mw	: in std_logic;
	      I_t, lr, la, SIMD    	: in std_logic;
	      read_mem, read_sft, CLK	: in std_logic);
end basic_processor;

architecture s_basic_processor of basic_processor is

component reg_file_32_32 is
  port(	CLK		: in std_logic;
	rs, rt, rd 	: in std_logic_vector(4 downto 0);
	w_dat		: in std_logic_vector(31 downto 0);
	w_reg		: in std_logic;
	reset		: in std_logic;
	r_0, r_1	: out std_logic_vector(31 downto 0));
end component;

component ALU_shifter is
	port(	i_A 		: in std_logic_vector(31 downto 0);
	     	i_B 		: in std_logic_vector(31 downto 0);
		i_Control 	: in std_logic_vector(2 downto 0);
		i_Shamt		: in std_logic_vector(4 downto 0);
		i_nLeft_Right	: in std_logic;
		i_nLog_Arith	: in std_logic;
		i_ByteImm	: in std_logic_vector(7 downto 0);
		i_SIMD		: in std_logic;
		o_F 		: out std_logic_vector(31 downto 0);
		o_Cout 		: out std_logic;
		o_overflow 	: out std_logic;
		o_zero 		: out std_logic;
		o_ShiftedVal	: out std_logic_vector(31 downto 0)
	);
end component;

component extender_16_32 is
	port(i_I 	: in std_logic_vector(15 downto 0);
	     i_signed	: in std_logic;
	     o_O 	: out std_logic_vector(31 downto 0));
end component;

component mem is
	generic 
	(DATA_WIDTH : natural := 32;
	 ADDR_WIDTH : natural := 10);
	port 
	(clk		: in std_logic;
	 addr	        : in std_logic_vector((ADDR_WIDTH-1) downto 0);
	 data	        : in std_logic_vector((DATA_WIDTH-1) downto 0);
	 we		: in std_logic := '1';
	 q		: out std_logic_vector((DATA_WIDTH -1) downto 0));
end component;

component mux_N2to1_struct is
  generic(N : integer);
  port(i_s  : in std_logic;
       i_0  : in std_logic_vector(N-1 downto 0);
       i_1  : in std_logic_vector(N-1 downto 0);
       o_F  : out std_logic_vector(N-1 downto 0));
end component;

signal reg_0, reg_1, reg_1_act, ALU_res, imm32, S_q, rd0, rd1, s_shifted : std_logic_vector(31 downto 0);
signal cout, overflow, zero : std_logic;

begin

-- Extender for immediate
extender : extender_16_32
	port map(i_I => imm,
		 i_signed => '1',
		 o_O => imm32);

-- Memory interface
dmem : mem
	port map(clk => CLK,
		 addr => ALU_res(9 downto 0),
		 data => reg_1,
		 we => mw,
		 q => S_q);

-- Mux for what data to write into registers
mux_reg_dat : mux_N2to1_struct
	generic map(N => 32)
	port map(i_s => read_mem,
		 i_0 => rd0,
		 i_1 => S_q,
		 o_F => rd1);

-- NEW test this, picks between ALU and Shifted value
mux_reg_shf : mux_N2to1_struct
	generic map(N => 32)
	port map(i_s => read_sft,
		 i_0 => ALU_res,
		 i_1 => s_shifted,
		 o_F => rd0);

-- NEWish? Determines wether we use two registers or an immediate
mux_immediate : mux_N2to1_struct
	generic map (N => 32)
	port map(i_s => I_t,
		 i_0 => reg_1,
		 i_1 => imm32,
		 o_F => reg_1_act);

-- Register File
reg_file : reg_file_32_32
	port map(CLK => CLK,
		 rs  => rs,
		 rt  => rt,
		 rd  => rd,
		 w_dat => rd1,
		 w_reg => we,
		 reset => reset,
		 r_0 => reg_0,
		 r_1 => reg_1);

-- NEW alu and shifter
adder : ALU_shifter
	port map(i_A => reg_0,
		 i_B => reg_1_act,
		 i_Control => funct,
		 i_shamt => shamt,
		 i_nLeft_Right => lr,
		 i_nLog_Arith => la,
		 i_ByteImm => imm(7 downto 0),
		 i_SIMD	=> SIMD,
		 o_F => ALU_res,
		 o_Cout => cout,
		 o_overflow => overflow,
		 o_zero => zero,
		 o_ShiftedVal => s_shifted);

end s_basic_processor;