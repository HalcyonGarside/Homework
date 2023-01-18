library IEEE;
use IEEE.std_logic_1164.all;
use work.AAAA_reg_file_regs.all;

entity mux_32_32 is

  port(	sel	: in std_logic_vector(4 downto 0);
	i	: in REG_FILE_REGISTERS;
       	o_O     : out std_logic_vector(31 downto 0)); 

end mux_32_32;

architecture s_mux_32_32 of mux_32_32 is

begin
  
  -- This process handles the asyncrhonous reset and
  -- synchronous write. We want to be able to reset 
  -- our processor's registers so that we minimize
  -- glitchy behavior on startup.
    with sel select
	o_O <= 	i(0) when "00000",
 		i(1) when "00001",
 		i(2) when "00010",
 		i(3) when "00011",
 		i(4) when "00100",
 		i(5) when "00101",
 		i(6) when "00110",
 		i(7) when "00111",
 		i(8) when "01000",
 		i(9) when "01001",
 		i(10) when "01010",
 		i(11) when "01011",
 		i(12) when "01100",
 		i(13) when "01101",
 		i(14) when "01110",
 		i(15) when "01111",
 		i(16) when "10000",
 		i(17) when "10001",
 		i(18) when "10010",
 		i(19) when "10011",
 		i(20) when "10100",
 		i(21) when "10101",
 		i(22) when "10110",
 		i(23) when "10111",
 		i(24) when "11000",
 		i(25) when "11001",
 		i(26) when "11010",
 		i(27) when "11011", 		i(28) when "11100",
 		i(29) when "11101",
 		i(30) when "11110",
 		i(31) when "11111",
 		"11111111111111111111111111111111" when others;
  
end s_mux_32_32;