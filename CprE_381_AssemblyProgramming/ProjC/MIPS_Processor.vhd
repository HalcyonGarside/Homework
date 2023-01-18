-------------------------------------------------------------------------
-- Henry Duwe
-- Department of Electrical and Computer Engineering
-- Iowa State University
-------------------------------------------------------------------------


-- MIPS_Processor.vhd
-------------------------------------------------------------------------
-- DESCRIPTION: This file contains a skeleton of a MIPS_Processor  
-- implementation.

-- 01/29/2019 by H3::Design created.
-------------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.all;

entity MIPS_Processor is
  generic(N : integer := 32);
  port(iCLK            : in std_logic;
       iRST            : in std_logic;
       iInstLd         : in std_logic;
       iInstAddr       : in std_logic_vector(N-1 downto 0);
       iInstExt        : in std_logic_vector(N-1 downto 0);
       oALUOut         : out std_logic_vector(N-1 downto 0)); -- TODO: Hook this up to the output of the ALU. It is important for synthesis that you have this output that can effectively be impacted by all other components so they are not optimized away.

end  MIPS_Processor;

architecture structure of MIPS_Processor is

	component reg_file_32_32 is
	  port(	CLK		: in std_logic;
		rs, rt, rd 	: in std_logic_vector(4 downto 0);
		w_dat		: in std_logic_vector(31 downto 0);
		w_reg		: in std_logic;
		reset		: in std_logic;
		r_0, r_1, o_Reg2	: out std_logic_vector(31 downto 0));
	end component;

	component ALU_shifter is
		port(	i_A 		: in std_logic_vector(31 downto 0);
				i_B 		: in std_logic_vector(31 downto 0);
			i_Control 		: in std_logic_vector(2 downto 0);
			i_Shamt			: in std_logic_vector(4 downto 0);
			i_nLeft_Right	: in std_logic;
			i_nLog_Arith	: in std_logic;
			i_ByteImm		: in std_logic_vector(7 downto 0);
			i_SIMD			: in std_logic;
			i_Signed	: in std_logic;
			o_F 			: out std_logic_vector(31 downto 0);
			o_Cout 			: out std_logic;
			o_overflow 		: out std_logic;
			o_zero 			: out std_logic;
			o_ShiftedVal	: out std_logic_vector(31 downto 0)
		);
	end component;

	component extender_16_32 is
		port(i_I 		: in std_logic_vector(15 downto 0);
			 i_signed	: in std_logic;
			 o_O 		: out std_logic_vector(31 downto 0));
	end component;

	component reg_n is
	  generic(N : integer);
	  port(i_CLK        : in std_logic;     
		   i_RST        : in std_logic;     
		   i_WE         : in std_logic;     
		   i_D          : in std_logic_vector(N-1 downto 0);
		   o_Q          : out std_logic_vector(N-1 downto 0));
	end component;

	component mux_N2to1_struct is
	  generic(N : integer);
	  port(i_s  : in std_logic;
		   i_0  : in std_logic_vector(N-1 downto 0);
		   i_1  : in std_logic_vector(N-1 downto 0);
		   o_F  : out std_logic_vector(N-1 downto 0));
	end component;

	component ctl_logic is
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
	end component;
	
	component nBitAdder is
		generic(N : integer);
		port(i_A		: in std_logic_vector(N-1 downto 0);
			 i_B		: in std_logic_vector(N-1 downto 0);
			 i_Cin		: in std_logic;
			 o_Sum		: out std_logic_vector(N-1 downto 0);
			 o_Cout		: out std_logic);
	end component;
	
	component ShiftLeft2 is
		generic(N : integer := 32);
		port(i_Input 	: in std_logic_vector(N-1 downto 0);
			 o_Output 	: out std_logic_vector(N-1 downto 0)
		);
	end component;

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
			 i_flush        :in std_logic;
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
			 i_Rs           :in std_logic_vector(4 downto 0);
			 i_Rt           :in std_logic_vector(4 downto 0);
			 i_Rd           :in std_logic_vector(4 downto 0);
			 i_Shamt        :in std_logic_vector(4 downto 0);
			 i_Reg1         :in std_logic_vector(31 downto 0);
			 i_Reg2         :in std_logic_vector(31 downto 0);
			 i_imm          :in std_logic_vector(31 downto 0);
			 i_OpCode		:in std_logic_vector(5 downto 0);
			 i_Funct		:in std_logic_vector(5 downto 0);
			 i_SftV			:in std_logic;
			 o_OpCode		:out std_logic_vector(5 downto 0);
			 o_Funct		:out std_logic_vector(5 downto 0);
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
			 o_Rs           :out std_logic_vector(4 downto 0);
			 o_Rt           :out std_logic_vector(4 downto 0);
			 o_Rd           :out std_logic_vector(4 downto 0);
			 o_Shamt        :out std_logic_vector(4 downto 0);
			 o_Reg1         :out std_logic_vector(31 downto 0);
			 o_Reg2         :out std_logic_vector(31 downto 0);
			 o_imm          :out std_logic_vector(31 downto 0);
			 o_SftV			:out std_logic);
	end component;

	component EXMEMReg is
		port(i_CLK          :in std_logic;
			 i_stall        :in std_logic;
			 i_flush		:in std_logic;
			 i_DMemWr       :in std_logic;
			 i_RegWr        :in std_logic;
			 i_MemToReg     :in std_logic;
			 i_RegWrMem     :in std_logic;
			 i_Rd           :in std_logic_vector(4 downto 0);
			 i_Reg1         :in std_logic_vector(31 downto 0);
			 i_imm          :in std_logic_vector(31 downto 0);
			 i_ALUOut		:in std_logic_vector(31 downto 0);
			 i_OpCode		:in std_logic_vector(5 downto 0);
			 i_Funct		:in std_logic_vector(5 downto 0);
			 o_OpCode		:out std_logic_vector(5 downto 0);
			 o_Funct		:out std_logic_vector(5 downto 0);
			 o_DMemWr       :out std_logic;
			 o_RegWr        :out std_logic;
			 o_MemToReg     :out std_logic;
			 o_RegWrMem     :out std_logic;
			 o_Rd           :out std_logic_vector(4 downto 0);
			 o_Reg1         :out std_logic_vector(31 downto 0);
			 o_imm          :out std_logic_vector(31 downto 0);
			 o_ALUOut		:out std_logic_vector(31 downto 0));
	end component;

	component MEMWBReg is
		port(i_CLK          :in std_logic;
			 i_stall        :in std_logic;
			 i_flush		:in std_logic;
			 i_RegWr        :in std_logic;
			 i_MemToReg     :in std_logic;
			 i_RegWrMem     :in std_logic;
			 i_Rd           :in std_logic_vector(4 downto 0);
			 i_MemOut       :in std_logic_vector(31 downto 0);
			 i_ALUOut		:in std_logic_vector(31 downto 0);
			 i_OpCode		:in std_logic_vector(5 downto 0);
			 i_Funct		:in std_logic_vector(5 downto 0);
			 o_OpCode		:out std_logic_vector(5 downto 0);
			 o_Funct		:out std_logic_vector(5 downto 0);
			 o_RegWr        :out std_logic;
			 o_MemToReg     :out std_logic;
			 o_RegWrMem     :out std_logic;
			 o_Rd           :out std_logic_vector(4 downto 0);
			 o_MemOut       :out std_logic_vector(31 downto 0);
			 o_ALUOut		:out std_logic_vector(31 downto 0));
	
	end component;

	component comparator is
		generic(N : integer);
		port(i_A : in std_logic_vector(N-1 downto 0);
			 i_B : in std_logic_vector(N-1 downto 0);
			 o_F : out std_logic);
	end component;

  -- Required data memory signals
  signal s_DMemWr       : std_logic; -- TODO: use this signal as the final active high data memory write enable signal
  signal s_DMemAddr     : std_logic_vector(N-1 downto 0); -- TODO: use this signal as the final data memory address input
  signal s_DMemData     : std_logic_vector(N-1 downto 0); -- TODO: use this signal as the final data memory data input
  signal s_DMemOut      : std_logic_vector(N-1 downto 0); -- TODO: use this signal as the data memory output
 
  -- Required register file signals 
  signal s_RegWr        : std_logic; -- TODO: use this signal as the final active high write enable input to the register file
  signal s_RegWrAddr    : std_logic_vector(4 downto 0); -- TODO: use this signal as the final destination register address input
  signal s_RegWrData    : std_logic_vector(N-1 downto 0); -- TODO: use this signal as the final data memory data input

  -- Required instruction memory signals
  signal s_IMemAddr     : std_logic_vector(N-1 downto 0); -- Do not assign this signal, assign to s_NextInstAddr instead
  signal s_NextInstAddr : std_logic_vector(N-1 downto 0); -- TODO: use this signal as your intended final instruction memory address input.
  signal s_Inst         : std_logic_vector(N-1 downto 0); -- TODO: use this signal as the instruction signal 

  -- Required halt signal -- for simulation
  signal v0             : std_logic_vector(N-1 downto 0); -- TODO: should be assigned to the output of register 2, used to implement the halt SYSCALL
  signal s_Halt         : std_logic;  -- TODO: this signal indicates to the simulation that intended program execution has completed. This case happens when the syscall instruction is observed and the V0 register is at 0x0000000A. This signal is active high and should only be asserted after the last register and memory writes before the syscall are guaranteed to be completed.

  component mem is
    generic(ADDR_WIDTH : integer;
            DATA_WIDTH : integer);
    port(
          clk          : in std_logic;
          addr         : in std_logic_vector((ADDR_WIDTH-1) downto 0);
          data         : in std_logic_vector((DATA_WIDTH-1) downto 0);
          we           : in std_logic := '1';
          q            : out std_logic_vector((DATA_WIDTH -1) downto 0));
    end component;

  -- TODO: You may add any additional signals or components your implementation 
  --       requires below this comment
  
  signal s_PCinput, s_ExtendedImm, s_RegFileOut0, s_RegFileOut1, s_ALUInputB, s_ALUOutput, s_ShifterOutput, s_RegInputALU, s_PCAdderOut : std_logic_vector(N-1 downto 0);
  signal s_RegWriteDataMuxes, s_ExtendedAddress, s_ExtendedVal, s_ExtendedBranchOffset, s_PCBranchMuxInputB : std_logic_vector(N-1 downto 0);
  signal s_BranchMuxOutput, s_PCAdderInputB, s_PCJumpMuxOut, s_JumpAddress : std_logic_vector(N-1 downto 0);
  signal s_PCAdderCout, s_Zero, s_ALUCout, s_ALUOverflow : std_logic;
  signal s_ALUShamt, s_ShiftV_MuxOut, s_RegWriteAdressMuxes : std_logic_vector(4 downto 0);
  
  -- Additional Control Signals
  signal s_ALUsrc, s_MemtoReg, s_RegDest, s_RegWrMem, s_RegWrSft, s_ShiftRight, s_ShiftArith, s_ControlRegWr, s_Signed, s_LUI, s_SftV : std_logic;
  signal s_Branch, s_BNE, s_Jump, s_JAL, regEquals : std_logic;
  signal s_ALUFunct : std_logic_vector(2 downto 0);

  --ID signals
  signal ID_inst	: std_logic_vector(31 downto 0);
  signal ID_rd		: std_logic_vector(4 downto 0);
  signal ID_DMemWr	: std_logic;

  --EX signals
  signal EX_ALUsrc, EX_MemtoReg, EX_RegDest, EX_RegWrMem, EX_RegWrSft, EX_ShiftRight, EX_ShiftArith, EX_ControlRegWr, EX_Signed, EX_LUI, EX_SftV : std_logic;
  signal EX_DMemWr, EX_Branch, EX_BNE, EX_Jump, EX_JAL : std_logic;
  signal EX_ALUFunct : std_logic_vector(2 downto 0);
  signal EX_Shamt, EX_rs, EX_rt, EX_rd : std_logic_vector(4 downto 0);
  signal EX_RegFileOut0, EX_RegFileOut1, EX_ExtendedImm : std_logic_vector(N-1 downto 0);
  signal EX_ExtendedVal, EX_ALURes : std_logic_vector(31 downto 0);
  signal EX_OpCode, EX_Funct : std_logic_vector(5 downto 0);

  --MEM signals
  signal MEM_DMemWr, MEM_RegWr, MEM_MemToReg, MEM_RegWrMem : std_logic;
  signal MEM_rd : std_logic_vector(4 downto 0);
  signal MEM_Reg1, MEM_ExtendedImm, MEM_ALURes : std_logic_vector(N-1 downto 0);
  signal MEM_OpCode, MEM_Funct : std_logic_vector(5 downto 0);

  --WB Signals
  signal WB_RegWr, WB_MemToReg, WB_RegWrMem : std_logic;
  signal WB_rd : std_logic_vector(4 downto 0);
  signal WB_MemOut, WB_ALURes : std_logic_vector(31 downto 0);
  signal WB_OpCode, WB_Funct : std_logic_vector(5 downto 0);

begin

  -- TODO: This is required to be your final input to your instruction memory. This provides a feasible method to externally load the memory module which means that the synthesis tool must assume it knows nothing about the values stored in the instruction memory. If this is not included, much, if not all of the design is optimized out because the synthesis tool will believe the memory to be all zeros.
  with iInstLd select
    s_IMemAddr <= s_NextInstAddr when '0',
      iInstAddr when others;

  IMem: mem
    generic map(ADDR_WIDTH => 10,
                DATA_WIDTH => N)
    port map(clk  => iCLK,
             addr => s_IMemAddr(11 downto 2),
             data => iInstExt,
             we   => iInstLd,
             q    => s_Inst);
  
  DMem: mem
    generic map(ADDR_WIDTH => 10,
                DATA_WIDTH => N)
    port map(clk  => iCLK,
             addr => s_DMemAddr(11 downto 2),
             data => s_DMemData,
             we   => s_DMemWr,
             q    => s_DMemOut);

  s_Halt <='1' when (WB_OpCode = "000000") and (WB_Funct = "001100") and (v0 = "00000000000000000000000000001010") else '0';

  -- TODO: Implement the rest of your processor below this comment! 

  --IF/ID Pipeline Reg
  IFID : IFIDReg
    port map(i_CLK => iCLK,
         	 i_stall => '0',
         	 i_flush => (s_Branch and (regEquals xor s_BNE)) or s_Jump or iRST,
         	 i_instr => s_Inst,
         	 o_instr => ID_Inst);
  
  -- Control Logic
  
	Control_Logic : ctl_logic
		port map( i_op			=> ID_Inst(31 downto 26),
			  i_funct		=> ID_Inst(5 downto 0),
			  o_ALUsrc		=> s_ALUsrc,
			  o_MemtoReg	=> s_MemtoReg,
			  o_DMemWr		=> ID_DMemWr,
			  o_RegWr		=> s_ControlRegWr,
			  o_RegDst		=> s_RegDest,
			  o_RegWrMem	=> s_RegWrMem,
			  o_RegWrSft	=> s_RegWrSft,
			  o_lui			=> s_LUI,
			  o_SftR		=> s_ShiftRight,
			  o_SftArith	=> s_ShiftArith,
			  o_Signed		=> s_Signed,
			  o_SftV		=> s_SftV,
			  o_Branch		=> s_Branch,
			  o_BNE			=> s_BNE,
			  o_Jump		=> s_Jump,
			  o_JAL			=> s_JAL,
			  o_ALUControl	=> s_ALUFunct);

  -- PC Counter and Adder
  
	s_RegWr <= WB_RegWr and not iRST;
  
	PC : reg_n
		generic map(N => N)
		port map(i_CLK  => iCLK,
				i_RST	=> '0',
				i_WE  	=> '1',     
				i_D  	=> s_PCinput,
				o_Q  	=> s_NextInstAddr);
	
	PC_Adder : nBitAdder
		generic map(N => N)
		port map(i_A		=> s_NextInstAddr,
				i_B			=> x"00000004",
				i_Cin		=> '0',
				o_Sum		=> s_PCAdderOut,
				o_Cout		=> s_PCAdderCout);
				
	PC_Reset_Mux : mux_N2to1_struct
		generic map (N => 32)
		port map(i_s => iRST,
				 i_0 => s_BranchMuxOutput,
				 i_1 => x"00400000",
				 o_F => s_PCinput);
				 
	-- Branching and Jumping
	
	JAL_WriteAddtress_Mux : mux_N2to1_struct
		generic map (N => 5)
		port map(i_s => s_JAL,
				 i_0 => s_RegWriteAdressMuxes,
				 i_1 => "11111",
				 o_F => ID_rd);
				 
	JAL_WriteData_Mux : mux_N2to1_struct
		generic map (N => 32)
		port map(i_s => s_JAL,
				 i_0 => s_RegWriteDataMuxes,
				 i_1 => s_PCAdderOut,
				 o_F => s_RegWrData);
				 
	Jump_Mux : mux_N2to1_struct
		generic map (N => 32)
		port map(i_s => s_Jump,
				 i_0 => s_PCAdderOut,
				 i_1 => s_JumpAddress,
				 o_F => s_PCJumpMuxOut);
				 
	Branch_Mux : mux_N2to1_struct
		generic map (N => 32)
		port map(i_s => s_Branch and (regEquals xor s_BNE),
				 i_0 => s_PCJumpMuxOut,
				 i_1 => s_PCBranchMuxInputB,
				 o_F => s_BranchMuxOutput);
				 
	JR_Mux : mux_N2to1_struct
		generic map (N => 32)
		port map(i_s => s_Jump and not s_ALUSrc,
				 i_0 => s_ExtendedVal,
				 i_1 => s_RegFileOut0,
				 o_F => s_JumpAddress);
					 
	Branch_Adder : nBitAdder
		generic map(N => N)
		port map(i_A		=> s_PCJumpMuxOut,
				i_B			=> s_ExtendedBranchOffset,
				i_Cin		=> '0',
				o_Sum		=> s_PCBranchMuxInputB,
				o_Cout		=> open);
	
	-- Register File
	Write_Dest_Mux : mux_N2to1_struct
		generic map (N => 5)
		port map(i_s => s_RegDest,
				 i_0 => ID_Inst(20 downto 16),
				 i_1 => ID_Inst(15 downto 11),
				 o_F => s_RegWriteAdressMuxes);

	Branch_Shifter : ShiftLeft2
		generic map(N => 32)
		port map(i_Input => s_ExtendedImm,
				o_Output => s_ExtendedBranchOffset);
	
	Register_File : reg_file_32_32
		port map(CLK => iCLK,
				rs  => ID_Inst(25 downto 21),
				rt  => ID_Inst(20 downto 16),
				rd  => s_RegWrAddr,
				w_dat => s_RegWrData,
				w_reg => WB_RegWr and not iRST,
				reset => iRST,
				r_0 => s_RegFileOut0,
				r_1 => s_RegFileOut1,
				o_Reg2 => v0);

	compares : comparator
		generic map(N => 32)
		port map(i_A => s_RegFileOut0,
			 i_B => s_RegFileOut1,
			 o_F => regEquals);

	--ID/EX Pipeline Register
	IDEX : IDEXReg
		port map(i_CLK      => iCLK,
			 i_stall    => regEquals and s_Branch,
			 i_flush	=> iRST,
			 i_ALUSrc   => s_ALUsrc,
			 i_ALUCtl   => s_ALUFunct,
			 i_SftR     => s_ShiftRight,
			 i_lui      => s_LUI,
			 i_SftArith => s_ShiftArith,
			 i_Signed   => s_Signed,
			 i_DMemWr   => ID_DMemWr,
			 i_RegWr    => s_ControlRegWr,
			 i_MemToReg => s_MemToReg,
			 i_RegWrMem => s_RegWrMem,
			 i_RegWrSft => s_RegWrSft,
			 i_Rs       => ID_Inst(25 downto 21),
			 i_Rt       => ID_Inst(20 downto 16),
			 i_Rd       => ID_rd,
			 i_Shamt	=> ID_Inst(10 downto 6),
			 i_Reg1     => s_RegFileOut0,
			 i_Reg2     => s_RegFileOut1,
			 i_imm      => s_ExtendedVal,
			 i_OpCode	=> ID_Inst(31 downto 26), 
			 i_Funct	=> ID_Inst(5 downto 0),
			 i_SftV		=> s_SftV,
			 o_ALUSrc   => EX_ALUsrc,
			 o_ALUCtl   => EX_ALUFunct,
			 o_SftR     => EX_ShiftRight,
			 o_lui      => EX_LUI,
			 o_SftArith => EX_ShiftArith,
			 o_Signed   => EX_Signed,
			 o_DMemWr   => EX_DMemWr,
			 o_RegWr    => EX_ControlRegWr,
			 o_MemToReg => EX_MemToReg,
			 o_RegWrMem => EX_RegWrMem,
			 o_RegWrSft => EX_RegWrSft,
			 o_Rs       => EX_rs,
			 o_Rt       => EX_rt,
			 o_Rd       => EX_rd,
			 o_Shamt	=> EX_Shamt,
			 o_Reg1     => EX_RegFileOut0,
			 o_Reg2     => EX_RegFileOut1,
			 o_imm      => EX_ExtendedImm,
			 o_OpCode	=> EX_OpCode,
			 o_Funct	=> EX_Funct,
			 o_SftV		=> EX_SftV);
	
	-- ALU
	
	LUI_Mux : mux_N2to1_struct
		generic map (N => 5)
		port map(i_s => EX_LUI,
				 i_0 => s_ShiftV_MuxOut,
				 i_1 => "10000",
				 o_F => s_ALUShamt);
	
	ShiftV_Mux : mux_N2to1_struct
		generic map (N => 5)
		port map(i_s => EX_SftV,
				 i_0 => EX_Shamt,
				 i_1 => EX_RegFileOut0(4 downto 0),
				 o_F => s_ShiftV_MuxOut);
	
	Immediate_Extender : extender_16_32
	port map(i_I => ID_Inst(15 downto 0),
		 i_signed => s_Signed,
		 o_O => s_ExtendedImm);
		 
	Address_Shifter : ShiftLeft2
		generic map(N => 28)
		port map(i_Input => ID_Inst(27 downto 0),
				o_Output => s_ExtendedAddress(27 downto 0));
				s_ExtendedAddress(31 downto 28) <= "0000";
	
	Extender_Mux : mux_N2to1_struct
		generic map (N => N)
		port map(i_s => s_Jump,
			 i_0 => s_ExtendedImm,
			 i_1 => s_ExtendedAddress,
			 o_F => s_ExtendedVal);
	
	nReg_Imm_Mux : mux_N2to1_struct
		generic map (N => N)
		port map(i_s => EX_ALUSrc,
			 i_0 => EX_RegFileOut1,
			 i_1 => EX_ExtendedImm,
			 o_F => s_ALUInputB);
			 
	-- alu and shifter
	MIPS_ALU : ALU_shifter
		port map(i_A => EX_RegFileOut0,
				i_B => s_ALUInputB,
				i_Control => EX_ALUFunct,
				i_shamt => s_ALUShamt,
				i_nLeft_Right => EX_ShiftRight,
				i_nLog_Arith => EX_ShiftArith,
				i_ByteImm => EX_ExtendedVal(7 downto 0),
				i_SIMD	=> '0',
				i_Signed => EX_Signed,
				o_F => s_ALUOutput,
				o_Cout => s_ALUCout,
				o_overflow => s_ALUOverflow,
				o_zero => s_Zero,
				o_ShiftedVal => s_ShifterOutput);
				
	nALU_Shift_Mux : mux_N2to1_struct
		generic map(N => 32)
		port map(i_s => EX_RegWrSft,
				 i_0 => s_ALUOutput,
				 i_1 => s_ShifterOutput,
				 o_F => EX_ALURes);

	EXMEM : EXMEMReg
		port map(i_CLK      => iCLK,
				 i_stall    => '0',
				 i_flush	=> iRST,
				 i_DMemWr   => EX_DMemWr,
				 i_RegWr    => EX_ControlRegWr,
				 i_MemToReg => EX_MemToReg,
				 i_RegWrMem => EX_RegWrMem,
				 i_Rd       => EX_rd,
				 i_Reg1     => EX_RegFileOut1,
				 i_imm      => EX_ExtendedImm,
				 i_ALUOut	=> EX_ALURes,
				 i_OpCode	=> EX_OpCode, 
				 i_Funct	=> EX_Funct,
				 o_OpCode	=> MEM_OpCode,
				 o_Funct	=> MEM_Funct,
				 o_DMemWr   => MEM_DMemWr,
				 o_RegWr    => MEM_RegWr,
				 o_MemToReg => MEM_MemToReg,
				 o_RegWrMem => MEM_RegWrMem,
				 o_Rd       => MEM_rd,
				 o_Reg1     => MEM_Reg1,
				 o_imm      => MEM_ExtendedImm,
				 o_ALUOut	=> MEM_ALURes);
				 
	s_DMemAddr <= MEM_ALURes;
	s_DMemData <= MEM_Reg1;
	s_DMemWr   <= MEM_DMemWr;
	
	Register_Write_Data_Mux : mux_N2to1_struct
		generic map (N => 32)
		port map(i_s => WB_MemtoReg,
				 i_0 => WB_ALURes,
				 i_1 => WB_MemOut,
				 o_F => s_RegWriteDataMuxes);

	MEMWB : MEMWBReg
		port map(i_CLK      => iCLK,
				 i_stall    => '0',
				 i_flush	=> iRST,
				 i_RegWr    => MEM_RegWr,
				 i_MemToReg => MEM_MemToReg,
				 i_RegWrMem => MEM_RegWrMem,
				 i_Rd       => MEM_rd,
				 i_MemOut   => s_DMemOut,
				 i_ALUOut	=> MEM_ALURes,
				 i_OpCode	=> MEM_OpCode, 
				 i_Funct	=> MEM_Funct,
				 o_OpCode	=> WB_OpCode,
				 o_Funct	=> WB_Funct,
				 o_RegWr    => WB_RegWr,
				 o_MemToReg => WB_MemToReg,
				 o_RegWrMem => WB_RegWrMem,
				 o_Rd       => s_RegWrAddr,
				 o_MemOut   => WB_MemOut,
				 o_ALUOut	=> WB_ALURes);

				 
	oALUOut <= MEM_ALURes;

end structure;
