exit -sim
vlib work

vcom -reportprogress 300 -work work mux_21.vhd

vsim work.mux_21
add wave sim:/mux_21/*

force -freeze sim:/mux_21/i_S 0 0
force -freeze sim:/mux_21/i_0 0 0
force -freeze sim:/mux_21/i_1 0 0
run 200

force -freeze sim:/mux_21/i_S 0 0
force -freeze sim:/mux_21/i_0 1 0
force -freeze sim:/mux_21/i_1 0 0
run 200

force -freeze sim:/mux_21/i_S 0 0
force -freeze sim:/mux_21/i_0 0 0
force -freeze sim:/mux_21/i_1 1 0
run 200

force -freeze sim:/mux_21/i_S 0 0
force -freeze sim:/mux_21/i_0 1 0
force -freeze sim:/mux_21/i_1 1 0
run 200

force -freeze sim:/mux_21/i_S 1 0
force -freeze sim:/mux_21/i_0 0 0
force -freeze sim:/mux_21/i_1 0 0
run 200

force -freeze sim:/mux_21/i_S 1 0
force -freeze sim:/mux_21/i_0 1 0
force -freeze sim:/mux_21/i_1 0 0
run 200

force -freeze sim:/mux_21/i_S 1 0
force -freeze sim:/mux_21/i_0 0 0
force -freeze sim:/mux_21/i_1 1 0
run 200

force -freeze sim:/mux_21/i_S 1 0
force -freeze sim:/mux_21/i_0 1 0
force -freeze sim:/mux_21/i_1 1 0
run 200