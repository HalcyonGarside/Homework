library IEEE;
use IEEE.std_logic_1164.all;

entity tb_ALU_1 is

end tb_ALU_1;

architecture tb of tb_ALU_1 is

component ALU_1
	port(	i_A 	: in std_logic;
	     	i_B 	: in std_logic;
		i_LT	: in std_logic;
		i_Cin	: in std_logic; -- Carry in bit
	     	i_funct : in std_logic_vector(2 downto 0);
		o_R 	: out std_logic;
		o_Cout	: out std_logic);
end component;

signal tbi_A, tbi_B, tbi_LT, tbi_Cin, tbo_Cout, tbo_R : std_logic;
signal tbi_funct : std_logic_vector(2 downto 0);

-------------------------------------

begin

TB_1bitALU: ALU_1
	port map(i_A	=> tbi_A,
	     	i_B 	=> tbi_B,
		i_LT	=> tbi_LT,
		i_Cin	=> tbi_Cin,
	     	i_funct => tbi_funct,
		o_R 	=> tbo_R,
		o_Cout	=> tbo_Cout);

process
	begin
		-- Setting up inputs to zero
		tbi_LT <= '0';
		tbi_Cin <= '0';

		----------------------

		-- A + B
		tbi_funct <= "000";
		tbi_A <= '0';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '0';
		tbi_B <= '1';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '1';
		wait for 100 ns;
		
		-- A - B
		tbi_funct <= "001";
		tbi_Cin <= '1';
		tbi_A <= '0';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '0';
		tbi_B <= '1';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '1';
		wait for 100 ns;

		-- A & B
		tbi_funct <= "010";
		tbi_A <= '0';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '1';
		wait for 100 ns;

		-- A | B
		tbi_funct <= "011";
		tbi_A <= '0';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '1';
		wait for 100 ns;


		-- A xor B
		tbi_funct <= "100";
		tbi_A <= '0';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '1';
		wait for 100 ns;

		-- A nor B
		tbi_funct <= "101";
		tbi_A <= '0';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '1';
		wait for 100 ns;

		-- A nand B
		tbi_funct <= "110";
		tbi_A <= '0';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '0';
		wait for 100 ns;

		tbi_A <= '1';
		tbi_B <= '1';
		wait for 100 ns;

		-- SLT
		tbi_funct <= "111";
		tbi_LT <= '0';
		wait for 100 ns;

		tbi_LT <= '1';
		wait for 100 ns;
	end process;

end tb;