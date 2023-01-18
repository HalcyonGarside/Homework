exit -sim
vlib work

vcom -reportprogress 300 -work work bitwise_functs.vhd

vsim work.bitwise_functs
add wave sim:/bitwise_functs/*

force -freeze sim:/bitwise_functs/i_funct 0100 0
force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_funct 0101 0
force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_funct 0110 0
force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_funct 0111 0
force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_funct 1000 0
force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_funct 1001 0
force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 0 0
run 100

force -freeze sim:/bitwise_functs/i_A 0 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100

force -freeze sim:/bitwise_functs/i_A 1 0
force -freeze sim:/bitwise_functs/i_B 1 0
run 100