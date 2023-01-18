exit -sim
vlib work

vcom -reportprogress 300 -work work full_adder.vhd

vsim work.full_adder
add wave sim:/full_adder/*

force -freeze sim:/full_adder/i_Cin 0 0
force -freeze sim:/full_adder/i_A 0 0
force -freeze sim:/full_adder/i_B 0 0
run 100

force -freeze sim:/full_adder/i_Cin 0 0
force -freeze sim:/full_adder/i_A 1 0
force -freeze sim:/full_adder/i_B 0 0
run 100

force -freeze sim:/full_adder/i_Cin 0 0
force -freeze sim:/full_adder/i_A 0 0
force -freeze sim:/full_adder/i_B 1 0
run 100

force -freeze sim:/full_adder/i_Cin 0 0
force -freeze sim:/full_adder/i_A 1 0
force -freeze sim:/full_adder/i_B 1 0
run 100

force -freeze sim:/full_adder/i_Cin 1 0
force -freeze sim:/full_adder/i_A 0 0
force -freeze sim:/full_adder/i_B 0 0
run 100

force -freeze sim:/full_adder/i_Cin 1 0
force -freeze sim:/full_adder/i_A 1 0
force -freeze sim:/full_adder/i_B 0 0
run 100

force -freeze sim:/full_adder/i_Cin 1 0
force -freeze sim:/full_adder/i_A 0 0
force -freeze sim:/full_adder/i_B 1 0
run 100

force -freeze sim:/full_adder/i_Cin 1 0
force -freeze sim:/full_adder/i_A 1 0
force -freeze sim:/full_adder/i_B 1 0
run 100