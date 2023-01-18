exit -sim
vlib work

vcom -reportprogress 300 -work work barrelShifter.vhd

vsim work.barrelShifter
add wave sim:/barrelShifter/*

force -freeze sim:/barrelShifter/i_ShiftingVal 00000000000000001010110011110000 0
force -freeze sim:/barrelShifter/i_Shamt 00000 0
force -freeze sim:/barrelShifter/i_nLeft_Right 0 0
force -freeze sim:/barrelShifter/i_nLog_Arith 0 0

run 100

#shift left 1
force -freeze sim:/barrelShifter/i_Shamt 00001 0

run 100

#shift left 16
force -freeze sim:/barrelShifter/i_Shamt 10000 0

run 100

#shift left 15
force -freeze sim:/barrelShifter/i_Shamt 01111 0

run 100

#shift right logical
#1
force -freeze sim:/barrelShifter/i_Shamt 00001 0
force -freeze sim:/barrelShifter/i_nLeft_Right 1 0

run 100

#16
force -freeze sim:/barrelShifter/i_Shamt 10000 0

run 100

#15
force -freeze sim:/barrelShifter/i_Shamt 01111 0

run 100

#shift right arithmatic
#1
force -freeze sim:/barrelShifter/i_Shamt 00001 0
force -freeze sim:/barrelShifter/i_nLog_Arith 1 0

run 100

#16
force -freeze sim:/barrelShifter/i_Shamt 10000 0

run 100

#15
force -freeze sim:/barrelShifter/i_Shamt 01111 0

run 100