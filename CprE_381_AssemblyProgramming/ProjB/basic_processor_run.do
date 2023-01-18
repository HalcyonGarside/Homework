exit -sim
vlib work

vcom -reportprogress 300 -work work barrelShifter.vhd
vcom -reportprogress 300 -work work full_adder.vhd
vcom -reportprogress 300 -work work bitwise_functs.vhd
vcom -reportprogress 300 -work work mux_21.vhd
vcom -reportprogress 300 -work work mux_81.vhd
vcom -reportprogress 300 -work work ALU_1.vhd
vcom -reportprogress 300 -work work MSB_ALU.vhd
vcom -reportprogress 300 -work work norg32.vhd
vcom -reportprogress 300 -work work xnorg2.vhd
vcom -reportprogress 300 -work work xorg2.vhd
vcom -reportprogress 300 -work work and2.vhd
vcom -reportprogress 300 -work work ALU_32.vhd
vcom -reportprogress 300 -work work ALU_shifter.vhd
vcom -reportprogress 300 -work work invg.vhd
vcom -reportprogress 300 -work work xorg2.vhd
vcom -reportprogress 300 -work work andg2.vhd
vcom -reportprogress 300 -work work org2.vhd
vcom -reportprogress 300 -work work Nfull_adder_struct.vhd
vcom -reportprogress 300 -work work mux_N2to1_struct.vhd
vcom -reportprogress 300 -work work ones_complimenter.vhd
vcom -reportprogress 300 -work work reg_file_regs.vhd
vcom -reportprogress 300 -work work mux_32_32.vhd
vcom -reportprogress 300 -work work decoder_32.vhd
vcom -reportprogress 300 -work work reg_n.vhd
vcom -reportprogress 300 -work work reg_file_32_32.vhd
vcom -reportprogress 300 -work work mem.vhd
vcom -reportprogress 300 -work work extender_16_32.vhd
vcom -reportprogress 300 -work work basic_processor.vhd

vsim work.basic_processor
add wave sim:/basic_processor/*

#initialize
force -freeze sim:/basic_processor/mw 0 0
mem load -infile dmem.hex -format hex /basic_processor/dmem/ram
force -freeze sim:/basic_processor/CLK 1 0, 0 {50 ps} -r 100
force -freeze sim:/basic_processor/reset 1 0
force -freeze sim:/basic_processor/SIMD 0 0
run 100

#addi $25, $0, 0
force -freeze sim:/basic_processor/shamt 00010 0
force -freeze sim:/basic_processor/funct 000 0
force -freeze sim:/basic_processor/reset 0 0
force -freeze sim:/basic_processor/I_t 1 0
force -freeze sim:/basic_processor/lr 0 0
force -freeze sim:/basic_processor/la 0 0
force -freeze sim:/basic_processor/read_mem 0 0
force -freeze sim:/basic_processor/read_sft 0 0
force -freeze sim:/basic_processor/imm 0000000000000000 0
force -freeze sim:/basic_processor/rs 00000 0
force -freeze sim:/basic_processor/rd 11001 0
force -freeze sim:/basic_processor/we 1 0
run 100

#addi $26, $0, 256
force -freeze sim:/basic_processor/rd 11010 0
force -freeze sim:/basic_processor/imm 0000000100000000 0
run 100

#lw $1, 0($25)
force -freeze sim:/basic_processor/rs 11001 0
force -freeze sim:/basic_processor/rd 00001 0
force -freeze sim:/basic_processor/imm 0000000000000000 0
force -freeze sim:/basic_processor/read_mem 1 0
run 100

#lw $2, 4($25)
force -freeze sim:/basic_processor/rd 00010 0
force -freeze sim:/basic_processor/imm 0000000000000001 0
run 100

#add $1, $1, $2
force -freeze sim:/basic_processor/rs 00001 0
force -freeze sim:/basic_processor/rt 00010 0
force -freeze sim:/basic_processor/rd 00001 0
force -freeze sim:/basic_processor/I_t 0 0
force -freeze sim:/basic_processor/read_mem 0 0
run 100

#sw $1, 0($26)
force -freeze sim:/basic_processor/imm 0000000000000000 0
force -freeze sim:/basic_processor/I_t 1 0
force -freeze sim:/basic_processor/we 0 0
force -freeze sim:/basic_processor/mw 1 0
force -freeze sim:/basic_processor/rs 11010 0
force -freeze sim:/basic_processor/rd 11010 0
force -freeze sim:/basic_processor/rt 00001 0
run 100

#lw $2, 8($25)
force -freeze sim:/basic_processor/read_mem 1 0
force -freeze sim:/basic_processor/we 1 0
force -freeze sim:/basic_processor/mw 0 0
force -freeze sim:/basic_processor/rs 11001 0
force -freeze sim:/basic_processor/rd 00010 0
force -freeze sim:/basic_processor/imm 0000000000000010 0
run 100

#add $1, $1, $2
force -freeze sim:/basic_processor/rs 00001 0
force -freeze sim:/basic_processor/rt 00010 0
force -freeze sim:/basic_processor/rd 00001 0
force -freeze sim:/basic_processor/I_t 0 0
force -freeze sim:/basic_processor/read_mem 0 0
run 100

#sw $1, 4($26)
force -freeze sim:/basic_processor/I_t 1 0
force -freeze sim:/basic_processor/we 0 0
force -freeze sim:/basic_processor/mw 1 0
force -freeze sim:/basic_processor/rs 11010 0
force -freeze sim:/basic_processor/rt 00001 0
force -freeze sim:/basic_processor/rd 11010 0
force -freeze sim:/basic_processor/imm 0000000000000001 0
run 100

#lw $2, 12($25)
force -freeze sim:/basic_processor/read_mem 1 0
force -freeze sim:/basic_processor/we 1 0
force -freeze sim:/basic_processor/mw 0 0
force -freeze sim:/basic_processor/rs 11001 0
force -freeze sim:/basic_processor/rd 00010 0
force -freeze sim:/basic_processor/imm 0000000000000011 0
run 100

#add $1, $1, $2
force -freeze sim:/basic_processor/rs 00001 0
force -freeze sim:/basic_processor/rt 00010 0
force -freeze sim:/basic_processor/rd 00001 0
force -freeze sim:/basic_processor/I_t 0 0
force -freeze sim:/basic_processor/read_mem 0 0
run 100

#sw $1, 8($26)
force -freeze sim:/basic_processor/I_t 1 0
force -freeze sim:/basic_processor/we 0 0
force -freeze sim:/basic_processor/mw 1 0
force -freeze sim:/basic_processor/rs 11010 0
force -freeze sim:/basic_processor/rt 00001 0
force -freeze sim:/basic_processor/rd 11010 0
force -freeze sim:/basic_processor/imm 0000000000000010 0
run 100

#lw $2, 16($25)
force -freeze sim:/basic_processor/read_mem 1 0
force -freeze sim:/basic_processor/we 1 0
force -freeze sim:/basic_processor/mw 0 0
force -freeze sim:/basic_processor/rs 11001 0
force -freeze sim:/basic_processor/rd 00010 0
force -freeze sim:/basic_processor/imm 0000000000000100 0
run 100

#add $1, $1, $2
force -freeze sim:/basic_processor/rs 00001 0
force -freeze sim:/basic_processor/rt 00010 0
force -freeze sim:/basic_processor/rd 00001 0
force -freeze sim:/basic_processor/I_t 0 0
force -freeze sim:/basic_processor/read_mem 0 0
run 100

#sw $1, 12($26)
force -freeze sim:/basic_processor/I_t 1 0
force -freeze sim:/basic_processor/we 0 0
force -freeze sim:/basic_processor/mw 1 0
force -freeze sim:/basic_processor/rs 11010 0
force -freeze sim:/basic_processor/rt 00001 0
force -freeze sim:/basic_processor/rd 11010 0
force -freeze sim:/basic_processor/imm 0000000000000011 0
run 100

#lw $2, 20($25)
force -freeze sim:/basic_processor/read_mem 1 0
force -freeze sim:/basic_processor/we 1 0
force -freeze sim:/basic_processor/mw 0 0
force -freeze sim:/basic_processor/rs 11001 0
force -freeze sim:/basic_processor/rd 00010 0
force -freeze sim:/basic_processor/imm 0000000000000101 0
run 100

#add $1, $1, $2
force -freeze sim:/basic_processor/rs 00001 0
force -freeze sim:/basic_processor/rt 00010 0
force -freeze sim:/basic_processor/rd 00001 0
force -freeze sim:/basic_processor/I_t 0 0
force -freeze sim:/basic_processor/read_mem 0 0
run 100

#sw $1, 16($26)
force -freeze sim:/basic_processor/I_t 1 0
force -freeze sim:/basic_processor/we 0 0
force -freeze sim:/basic_processor/mw 1 0
force -freeze sim:/basic_processor/rs 11010 0
force -freeze sim:/basic_processor/rt 00001 0
force -freeze sim:/basic_processor/rd 11010 0
force -freeze sim:/basic_processor/imm 0000000000000011 0
run 100

#lw $2, 24($25)
force -freeze sim:/basic_processor/read_mem 1 0
force -freeze sim:/basic_processor/we 1 0
force -freeze sim:/basic_processor/mw 0 0
force -freeze sim:/basic_processor/rs 11001 0
force -freeze sim:/basic_processor/rd 00010 0
force -freeze sim:/basic_processor/imm 0000000000000110 0
run 100

#add $1, $1, $2
force -freeze sim:/basic_processor/rs 00001 0
force -freeze sim:/basic_processor/rt 00010 0
force -freeze sim:/basic_processor/rd 00001 0
force -freeze sim:/basic_processor/I_t 0 0
force -freeze sim:/basic_processor/read_mem 0 0
run 100

#addi $27, $26, 512
force -freeze sim:/basic_processor/I_t 1 0
force -freeze sim:/basic_processor/rs 11010 0
force -freeze sim:/basic_processor/rd 11011 0
force -freeze sim:/basic_processor/imm 0000000010000000 0
run 100

#sw $1, -4($27)
force -freeze sim:/basic_processor/I_t 1 0
force -freeze sim:/basic_processor/we 0 0
force -freeze sim:/basic_processor/mw 1 0
force -freeze sim:/basic_processor/rs 11011 0
force -freeze sim:/basic_processor/rt 00001 0
force -freeze sim:/basic_processor/rd 11011 0
force -freeze sim:/basic_processor/imm 1111111111111111 0
run 100

force -freeze sim:/basic_processor/mw 0 0
force -freeze sim:/basic_processor/rs 00001 0
run 100

force -freeze sim:/basic_processor/read_mem 0 0
force -freeze sim:/basic_processor/read_sft 1 0
run 100

# Set register 1 to 15
force -freeze sim:/basic_processor/shamt 00000 0
force -freeze sim:/basic_processor/we 1 0
force -freeze sim:/basic_processor/imm 0000000000011111 0
force -freeze sim:/basic_processor/rs 00000 0
force -freeze sim:/basic_processor/rd 00001 0
force -freeze sim:/basic_processor/read_sft 0 0
run 100

# To see value of registers
add wave -position insertpoint sim:/basic_processor/reg_file/*

# Shift register 1 3 to the right
force -freeze sim:/basic_processor/read_sft 1 0
force -freeze sim:/basic_processor/rs 00001 0
force -freeze sim:/basic_processor/shamt 00011 0
force -freeze sim:/basic_processor/lr 1 0
run 100

#Shift register 1 left 3 times
force -freeze sim:/basic_processor/lr 0 0
run 100

# Bring 1 to MSB in reg 1
force -freeze sim:/basic_processor/la 1 0
force -freeze sim:/basic_processor/shamt 11011 0
run 100

# Fill with all 1 with arithmetic right shift 31
force -freeze sim:/basic_processor/shamt 11111 0
force -freeze sim:/basic_processor/lr 1 0
run 100

# Set register 1 to value of 1 by shifting right 31 logically
force -freeze sim:/basic_processor/la 0 0
run 100

# Add Rs + 1 through the ALU with funct 000 addi $1, $1, 1
force -freeze sim:/basic_processor/imm 0000000000000001 0
force -freeze sim:/basic_processor/read_sft 0 0
run 100

# add $1, $1, $1
force -freeze sim:/basic_processor/I_t 0 0
run 100

# sub $1, $1, $1
force -freeze sim:/basic_processor/funct 001 0
run 100

# andi
force -freeze sim:/basic_processor/I_t 1 0
force -freeze sim:/basic_processor/imm 0000000000011111 0
force -freeze sim:/basic_processor/funct 010 0
run 100

# ori
force -freeze sim:/basic_processor/funct 011 0
run 100

# xori
force -freeze sim:/basic_processor/funct 100 0
run 100

# nori
force -freeze sim:/basic_processor/funct 101 0
run 100

# nandi
force -freeze sim:/basic_processor/funct 110 0
run 100

# slti
force -freeze sim:/basic_processor/funct 111 0
run 100

### SIMD ###

# Addu.qb $1, $1, $2 
force -freeze sim:/basic_processor/SIMD 1 0
force -freeze sim:/basic_processor/funct 000 0
force -freeze sim:/basic_processor/rt 00010 0
force -freeze sim:/basic_processor/I_t 0 0
run 100

# Addu_s.qb
force -freeze sim:/basic_processor/funct 001 0
run 100

# Subu.qb
force -freeze sim:/basic_processor/funct 010 0
run 100

# replv.qb
force -freeze sim:/basic_processor/funct 011 0
run 100

# Add all 4 together
force -freeze sim:/basic_processor/funct 101 0
run 100

# Absolute Value
force -freeze sim:/basic_processor/funct 100 0
run 100

# Immediate Value
force -freeze sim:/basic_processor/funct 110 0
run 100

