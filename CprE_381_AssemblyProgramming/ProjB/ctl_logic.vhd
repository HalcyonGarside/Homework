library IEEE;
use IEEE.std_logic_1164.all;

entity ctl_logic is
    port( i_op, i_funct : in std_logic_vector(5 downto 0);
          o_ALUsrc      : out std_logic;
          o_MemtoReg    : out std_logic;
          o_DMemWr      : out std_logic;
          o_RegWr       : out std_logic;
          o_RegDst      : out std_logic;
          o_RegWrMem    : out std_logic;
          o_RegWrSft    : out std_logic;
          o_lui         : out std_logic;
          o_SftR        : out std_logic;
          o_SftArith    : out std_logic;
		  o_Signed		: out std_logic;
          o_SftV		: out std_logic;
          o_Branch      : out std_logic;
          o_BNE       	: out std_logic;
          o_Jump        : out std_logic;
		  o_JAL			: out std_logic;
          o_ALUControl  : out std_logic_vector(2 downto 0));
end ctl_logic;

architecture s_ctl_logic of ctl_logic is
    begin

MainProc: process (i_op, i_funct) begin
            if(i_op = "000000") then
                o_ALUsrc <= '0';
                o_MemtoReg <= '0';
                o_DMemWr <= '0';
                o_RegDst <= '1';
                o_RegWrMem <= '0';
                o_lui <= '0';
                o_Branch <= '0';
                o_BNE <= '0';
				o_JAL <= '0';

                case i_funct is
                    when "001000" => o_RegWr <= '0';
                    when others => o_RegWr <= '1';
                end case;

                case i_funct is
                    when "001000" => o_Jump <= '1';
                    when others => o_Jump <= '0';
                end case;

                case i_funct is
                    when "100000" => o_RegWrSft <= '0';
                    when "100001" => o_RegWrSft <= '0';
                    when "100100" => o_RegWrSft <= '0';
                    when "100111" => o_RegWrSft <= '0';
                    when "100110" => o_RegWrSft <= '0';
                    when "100101" => o_RegWrSft <= '0';
                    when "100010" => o_RegWrSft <= '0';
                    when "100011" => o_RegWrSft <= '0';
                    when "101010" => o_RegWrSft <= '0';
                    when "101011" => o_RegWrSft <= '0';
                    when "001000" => o_RegWrSft <= '0';
                    when others => o_RegWrSft <= '1';
                end case;

                case i_funct is
                    when "100010" =>  o_ALUControl <= "001";
                    when "100011" =>  o_ALUControl <= "001";
                    when "100100" =>  o_ALUControl <= "010";
                    when "100101" =>  o_ALUControl <= "011";
                    when "100110" =>  o_ALUControl <= "100";
                    when "100111" =>  o_ALUControl <= "101";
                    when "101010" =>  o_ALUControl <= "111";
                    when "101011" =>  o_ALUControl <= "111";
                    when "000100" =>  o_ALUControl <= "001";
                    when "000101" =>  o_ALUControl <= "001";
                    when others =>  o_ALUControl <= "000";
                end case;

                case i_funct is
                    when "000000" => o_SftR <= '0';
                    when "000100" => o_SftR <= '0';
                    when others => o_SftR <= '1';
                end case;

                case i_funct is
                    when "000011" => o_SftArith <= '1';
                    when "000111" => o_SftArith <= '1';
                    when others => o_SftArith <= '0';
                end case;
				
				case i_funct is
                    when "000100" => o_SftV <= '1';
                    when "000110" => o_SftV <= '1';
					when "000111" => o_SftV <= '1';
                    when others => o_SftV <= '0';
                end case;
				
				case i_funct is
                    when "101011" => o_Signed <= '0';
					when "100011" => o_Signed <= '0';
                    when others => o_Signed <= '1';
                end case;

            else
                o_SftR <= '0';
                o_SftArith <= '0';
				
				case i_op is 
                    when "000100" => o_ALUsrc <= '0';
					when "000101" => o_ALUsrc <= '0';
                    when others => o_ALUsrc <= '1';
                end case;
				
                case i_op is 
                    when "100011" => o_MemtoReg <= '1';
                    when others => o_MemtoReg <= '0';
                end case;
				
				case i_op is 
                    when "000011" => o_JAL <= '1';
                    when others => o_JAL <= '0';
                end case;

                case i_op is
                    when "000100" => o_Branch <= '1';
					when "000101" => o_Branch <= '1';
                    when others => o_Branch <= '0';
                end case;

                case i_op is
                    when "000101" => o_BNE <= '1';
                    when others => o_BNE <= '0';
                end case;

                case i_op is
                    when "000010" => o_Jump <= '1';
                    when "000011" => o_Jump <= '1';
                    when others => o_Jump <= '0';
                end case;

                case i_op is
                    when "101011" => o_DMemWr <= '1';
                    when others => o_DMemWr <= '0';
                end case;
                case i_op is
                    when "101011" => o_RegWr <= '0';
                    when "000100" => o_RegWr <= '0';
                    when "000101" => o_RegWr <= '0';
                    when "000010" => o_RegWr <= '0';
                    when others => o_RegWr <= '1';
                end case;
                o_RegDst <= '0';
                case i_op is 
                    when "100011" => o_RegWrMem <= '1';
                    when others => o_RegWrMem <= '0';
                end case;
                case i_op is
                    when "001111" =>  o_RegWrSft <= '1';
                    when others =>  o_RegWrSft <= '0';
                end case;
				case i_op is
					when "001111" => o_Signed <= '0';
					when "100011" => o_Signed <= '0';
					when "001011" => o_Signed <= '0';
					when "001101" => o_Signed <= '0';
					when "001110" => o_Signed <= '0';
					when "001100" => o_Signed <= '0';
					when others => o_Signed <= '1';
				end case;
                case i_op is
                    when "001100" => o_ALUControl <= "010";
                    when "001101" => o_ALUControl <= "011";
                    when "001110" => o_ALUControl <= "100";
                    when "001010" => o_ALUControl <= "111";
                    when "001011" => o_ALUControl <= "111";
					when "000100" => o_ALUControl <= "001";
                    when "000101" => o_ALUControl <= "001";
                    when others => o_ALUControl <= "000";
                end case;
				case i_op is
					when "001111" => o_lui <= '1';
					when others => o_lui <= '0';
				end case;
            end if;
    end process;
end s_ctl_logic;