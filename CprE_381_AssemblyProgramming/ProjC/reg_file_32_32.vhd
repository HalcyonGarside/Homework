library IEEE;
use IEEE.std_logic_1164.all;
use work.AAAA_reg_file_regs.all;

entity reg_file_32_32 is

  port(	CLK				: in std_logic;
	rs, rt, rd 			: in std_logic_vector(4 downto 0);
	w_dat				: in std_logic_vector(31 downto 0);
	w_reg				: in std_logic;
	reset				: in std_logic;
	r_0, r_1, o_Reg2	: out std_logic_vector(31 downto 0));

end reg_file_32_32;

architecture s_reg_file_32_32 of reg_file_32_32 is

component decoder_32 is
  port(	i_I 	: in std_logic_vector(4 downto 0);
	o_O 	: out std_logic_vector(31 downto 0));
end component;

component reg_n is
  generic(N : integer);
  port(i_CLK        : in std_logic;     
       i_RST        : in std_logic;     
       i_WE         : in std_logic;     
       i_D          : in std_logic_vector(N-1 downto 0);
       o_Q          : out std_logic_vector(N-1 downto 0));
end component;

component mux_32_32 is
  port(	sel	: in std_logic_vector(4 downto 0);
	i	: in REG_FILE_REGISTERS;
       	o_O     : out std_logic_vector(31 downto 0));
end component;

--Register files
signal reg : REG_FILE_REGISTERS;

signal reg_sel : std_logic_vector(31 downto 0);

begin
decoder:decoder_32
	port map( i_I => rd,
		  o_O => reg_sel);


rzero:reg_n
	generic map (N => 32)
	port map (i_CLK => CLK,
		  i_RST => '1',
		  i_WE  => '0',
		  i_D	=> w_dat,
		  o_Q	=> reg(0));

G1: for i in 1 to 31 generate
	rrest:reg_n
		generic map (N => 32)
		port map(i_CLK => CLK,
		  i_RST => reset,
		  i_WE  => reg_sel(i) and w_reg,
		  i_D	=> w_dat,
		  o_Q	=> reg(i));
end generate G1;
		  
o_Reg2 <= reg(2);
		  
mux0:mux_32_32
	port map( sel => rs,
		  i   => reg,
		  o_O => r_0);

mux1:mux_32_32
	port map( sel => rt,
		  i   => reg,
		  o_O => r_1);

end s_reg_file_32_32;