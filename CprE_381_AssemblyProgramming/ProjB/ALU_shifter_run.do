exit -sim
vlib work

#Required VHD comps
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

#Waveform
vsim work.ALU_shifter
add wave sim:/ALU_shifter/*

#Process

#Add/subtract
#i_A = 10
force -freeze sim:/ALU_shifter/i_A 00000000000000000000000000001010 0
#i_B = 12
force -freeze sim:/ALU_shifter/i_B 00000000000000000000000000001100 0

#Adding (output from o_F, should be 22)
force -freeze sim:/ALU_shifter/i_Control 000 0
run 100

#Subtracting (Should be -2) (Overflow should be set)
force -freeze sim:/ALU_shifter/i_Control 001 0
run 100

#SLT (Should be 1)
force -freeze sim:/ALU_shifter/i_Control 111 0
run 100

#i_A = -1
force -freeze sim:/ALU_shifter/i_A 11111111111111111111111111111111 0
#i_B = -1
force -freeze sim:/ALU_shifter/i_B 11111111111111111111111111111111 0

#Adding (output from o_F, should be -2) (Overflow shouldn't be set)
force -freeze sim:/ALU_shifter/i_Control 000 0
run 100

#Subtracting (Should be 0) (Overflow shouldn't be set)
force -freeze sim:/ALU_shifter/i_Control 001 0
run 100

#SLT (Should be 0)
force -freeze sim:/ALU_shifter/i_Control 111 0
run 100


#Init vals
force -freeze sim:/ALU_shifter/i_Control 000 0
force -freeze sim:/ALU_shifter/i_nLeft_Right 1 0
force -freeze sim:/ALU_shifter/i_nLog_Arith 1 0
force -freeze sim:/ALU_shifter/i_Shamt 00010 0

#Overflow Test
#A and B = MAX
#Result should come out to be -2, overflow should be SET
force -freeze sim:/ALU_shifter/i_A 01111111111111111111111111111111 0
force -freeze sim:/ALU_shifter/i_B 01111111111111111111111111111111 0

run 100

#Shift RA
force -freeze sim:/ALU_shifter/i_A 11110000000000000000000000001111 0

run 100

#Shift RL
force -freeze sim:/ALU_shifter/i_nLeft_Right 1 0
force -freeze sim:/ALU_shifter/i_nLog_Arith 0 0

run 100

#Shift LA
force -freeze sim:/ALU_shifter/i_nLeft_Right 0 0
force -freeze sim:/ALU_shifter/i_nLog_Arith 1 0

run 100

#shift LL
force -freeze sim:/ALU_shifter/i_nLeft_Right 0 0
force -freeze sim:/ALU_shifter/i_nLog_Arith 0 0

run 100

#Same w/ Max Shamt
force -freeze sim:/ALU_shifter/i_Shamt 11111 0

#Shift RA
force -freeze sim:/ALU_shifter/i_nLeft_Right 1 0
force -freeze sim:/ALU_shifter/i_nLog_Arith 1 0

run 100

#Shift RL
force -freeze sim:/ALU_shifter/i_nLeft_Right 1 0
force -freeze sim:/ALU_shifter/i_nLog_Arith 0 0

run 100

#Shift LA
force -freeze sim:/ALU_shifter/i_nLeft_Right 0 0
force -freeze sim:/ALU_shifter/i_nLog_Arith 1 0

run 100

#shift LL
force -freeze sim:/ALU_shifter/i_nLeft_Right 0 0
force -freeze sim:/ALU_shifter/i_nLog_Arith 0 0

run 100

#Test bitwise for all bits
#For 1 (BITWISE) 1
force -freeze sim:/ALU_shifter/i_A 11111111111111111111111111111111 0
force -freeze sim:/ALU_shifter/i_B 11111111111111111111111111111111 0

#AND
force -freeze sim:/ALU_shifter/i_Control 010 0
run 100
#OR
force -freeze sim:/ALU_shifter/i_Control 011 0
run 100
#XOR
force -freeze sim:/ALU_shifter/i_Control 100 0
run 100
#NOR
force -freeze sim:/ALU_shifter/i_Control 101 0
run 100
#NAND
force -freeze sim:/ALU_shifter/i_Control 110 0
run 100

#For 1 (BITWISE) 0
force -freeze sim:/ALU_shifter/i_A 11111111111111111111111111111111 0
force -freeze sim:/ALU_shifter/i_B 00000000000000000000000000000000 0

#AND
force -freeze sim:/ALU_shifter/i_Control 010 0
run 100
#OR
force -freeze sim:/ALU_shifter/i_Control 011 0
run 100
#XOR
force -freeze sim:/ALU_shifter/i_Control 100 0
run 100
#NOR
force -freeze sim:/ALU_shifter/i_Control 101 0
run 100
#NAND
force -freeze sim:/ALU_shifter/i_Control 110 0
run 100

#For 0 (BITWISE) 1
force -freeze sim:/ALU_shifter/i_A 00000000000000000000000000000000 0
force -freeze sim:/ALU_shifter/i_B 11111111111111111111111111111111 0

#AND
force -freeze sim:/ALU_shifter/i_Control 010 0
run 100
#OR
force -freeze sim:/ALU_shifter/i_Control 011 0
run 100
#XOR
force -freeze sim:/ALU_shifter/i_Control 100 0
run 100
#NOR
force -freeze sim:/ALU_shifter/i_Control 101 0
run 100
#NAND
force -freeze sim:/ALU_shifter/i_Control 110 0
run 100

#For 0 (BITWISE) 0
force -freeze sim:/ALU_shifter/i_A 00000000000000000000000000000000 0
force -freeze sim:/ALU_shifter/i_B 00000000000000000000000000000000 0

#AND
force -freeze sim:/ALU_shifter/i_Control 010 0
run 100
#OR
force -freeze sim:/ALU_shifter/i_Control 011 0
run 100
#XOR
force -freeze sim:/ALU_shifter/i_Control 100 0
run 100
#NOR
force -freeze sim:/ALU_shifter/i_Control 101 0
run 100
#NAND
force -freeze sim:/ALU_shifter/i_Control 110 0
run 100

#SLT Edge Case (-1 and 0, should be set)
force -freeze sim:/ALU_shifter/i_Control 111 0
force -freeze sim:/ALU_shifter/i_A 11111111111111111111111111111111 0
force -freeze sim:/ALU_shifter/i_B 00000000000000000000000000000000 0

run 100

#Should not be set
force -freeze sim:/ALU_shifter/i_A 00000000000000000000000000000000 0
force -freeze sim:/ALU_shifter/i_B 11111111111111111111111111111111 0

run 100