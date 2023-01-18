library IEEE;
use IEEE.std_logic_1164.all;

entity PipelineRegTestbench is
end PipelineRegTestbench;


architecture s_PipelineRegTestbench of PipelineRegTestbench is

	component IFIDReg is
		port(i_CLK          :in std_logic;
			 i_stall        :in std_logic;
			 i_flush        :in std_logic;
			 i_instr        :in std_logic_vector(31 downto 0);
			 o_instr        :out std_logic_vector(31 downto 0));
	end component;

	component IDEXReg is
		port(i_CLK          :in std_logic;
			 i_stall        :in std_logic;
			 i_ALUSrc       :in std_logic;
			 i_ALUCtl       :in std_logic_vector(2 downto 0);
			 i_SftR         :in std_logic;
			 i_lui          :in std_logic;
			 i_SftArith     :in std_logic;
			 i_Signed       :in std_logic;
			 i_DMemWr       :in std_logic;
			 i_RegWr        :in std_logic;
			 i_MemToReg     :in std_logic;
			 i_RegWrMem     :in std_logic;
			 i_RegWrSft     :in std_logic;
			 i_Rs           :in std_logic_vector(5 downto 0);
			 i_Rt           :in std_logic_vector(5 downto 0);
			 i_Rd           :in std_logic_vector(5 downto 0);
			 i_Reg1         :in std_logic_vector(31 downto 0);
			 i_Reg2         :in std_logic_vector(31 downto 0);
			 i_imm          :in std_logic_vector(15 downto 0);
			 o_ALUSrc       :out std_logic;
			 o_ALUCtl       :out std_logic_vector(2 downto 0);
			 o_SftR         :out std_logic;
			 o_lui          :out std_logic;
			 o_SftArith     :out std_logic;
			 o_Signed       :out std_logic;
			 o_DMemWr       :out std_logic;
			 o_RegWr        :out std_logic;
			 o_MemToReg     :out std_logic;
			 o_RegWrMem     :out std_logic;
			 o_RegWrSft     :out std_logic;
			 o_Rs           :out std_logic_vector(5 downto 0);
			 o_Rt           :out std_logic_vector(5 downto 0);
			 o_Rd           :out std_logic_vector(5 downto 0);
			 o_Reg1         :out std_logic_vector(31 downto 0);
			 o_Reg2         :out std_logic_vector(31 downto 0);
			 o_imm          :out std_logic_vector(15 downto 0));
    end component;

    component EXMEMReg is
        port(i_CLK          :in std_logic;
             i_stall        :in std_logic;
             i_DMemWr       :in std_logic;
             i_RegWr        :in std_logic;
             i_MemToReg     :in std_logic;
             i_RegWrMem     :in std_logic;
             i_Rd           :in std_logic_vector(5 downto 0);
             i_Reg1         :in std_logic_vector(31 downto 0);
             i_imm          :in std_logic_vector(15 downto 0);
             o_DMemWr       :out std_logic;
             o_RegWr        :out std_logic;
             o_MemToReg     :out std_logic;
             o_RegWrMem     :out std_logic;
             o_Rd           :out std_logic_vector(5 downto 0);
             o_Reg1         :out std_logic_vector(31 downto 0);
             o_imm          :out std_logic_vector(15 downto 0));
    end component;
    
    component MEMWBReg is
        port(i_CLK          :in std_logic;
             i_stall        :in std_logic;
             i_RegWr        :in std_logic;
             i_MemToReg     :in std_logic;
             i_RegWrMem     :in std_logic;
             i_Rd           :in std_logic_vector(5 downto 0);
             i_MemOut       :in std_logic_vector(31 downto 0);
             o_RegWr        :out std_logic;
             o_MemToReg     :out std_logic;
             o_RegWrMem     :out std_logic;
             o_Rd           :out std_logic_vector(5 downto 0);
             o_MemOut       :out std_logic_vector(31 downto 0));
    end component;

	signal s_stall, s_flush, s_CLK : std_logic;
	signal EX_rd, MEM_rd, WB_rd : std_logic_vector(5 downto 0);
	signal s_Inst, ID_Inst : std_logic_vector(31 downto 0);

begin

    IFID : IFIDReg 
        port map(i_CLK   => s_CLK,
                i_stall => s_stall,
                i_flush => s_flush,
                i_instr => s_Inst,
                o_instr => ID_Inst);

    IDEX : IDEXReg
		port map(i_CLK      => s_CLK,
			     i_stall    => s_stall,
			     i_ALUSrc   => '0',
			     i_ALUCtl   => "000",
			     i_SftR     => '0',
			     i_lui      => '0',
			     i_SftArith => '0',
			     i_Signed   => '0',
			     i_DMemWr   => '0',
			     i_RegWr    => '0',
			     i_MemToReg => '0',
			     i_RegWrMem => '0',
			     i_RegWrSft => '0',
			     i_Rs       => "000000",
			     i_Rt       => "000000",
			     i_Rd       => ID_Inst(5 downto 0),
			     i_Reg1     => "00000000000000000000000000000000",
			     i_Reg2     => "00000000000000000000000000000000",
			     i_imm      => "0000000000000000",
			     o_ALUSrc   => open,
			     o_ALUCtl   => open,
			     o_SftR     => open,
			     o_lui      => open,
			     o_SftArith => open,
			     o_Signed   => open,
			     o_DMemWr   => open,
			     o_RegWr    => open,
			     o_MemToReg => open,
			     o_RegWrMem => open,
			     o_RegWrSft => open,
			     o_Rs       => open,
			     o_Rt       => open,
			     o_Rd       => EX_rd,
			     o_Reg1     => open,
			     o_Reg2     => open,
                 o_imm      => open);
             
    EXMEM : EXMEMReg
        port map(i_CLK      => s_CLK,
                 i_stall    => s_stall,
                 i_DMemWr   => '0',
                 i_RegWr    => '0',
                 i_MemToReg => '0',
                 i_RegWrMem => '0',
                 i_Rd       => EX_rd,
                 i_Reg1     => "00000000000000000000000000000000",
                 i_imm      => "0000000000000000",
                 o_DMemWr   => open,
                 o_RegWr    => open,
                 o_MemToReg => open,
                 o_RegWrMem => open,
                 o_Rd       => MEM_rd,
                 o_Reg1     => open,
                 o_imm      => open);

    MEMWB : MEMWBReg
        port map(i_CLK      => s_CLK,
                 i_stall    => s_stall,
                 i_RegWr    => '0',
                 i_MemToReg => '0',
                 i_RegWrMem => '0',
                 i_Rd       => MEM_rd,
                 i_MemOut   => "00000000000000000000000000000000",
                 o_RegWr    => open,
                 o_MemToReg => open,
                 o_RegWrMem => open,
                 o_Rd       => WB_rd,
				 o_MemOut   => open);
				 
	test : process begin
		s_stall <= '0';
		s_flush <= '0';
		s_Inst <= "11111111111111111111111111111111";
		wait for 400ps;
	end process;

end s_PipelineRegTestbench;