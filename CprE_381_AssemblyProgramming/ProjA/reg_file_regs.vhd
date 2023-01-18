library IEEE;
use IEEE.std_logic_1164.all;

package reg_file_regs is
	type REG_FILE_REGISTERS is array (31 downto 0) of std_logic_vector(31 downto 0);
	type SIMD_MUX_INPUTS is array (7 downto 0) of std_logic_vector(7 downto 0);
end package reg_file_regs;
