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
vcom -reportprogress 300 -work work IFIDReg.vhd
vcom -reportprogress 300 -work work IDEXReg.vhd
vcom -reportprogress 300 -work work EXMEMReg.vhd
vcom -reportprogress 300 -work work MEMWBReg.vhd
vcom -reportprogress 300 -work work PipelineRegTestbench.vhd



vsim work.basic_processor
add wave sim:/basic_processor/*

run 400