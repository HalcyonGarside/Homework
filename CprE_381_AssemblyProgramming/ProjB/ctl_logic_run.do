exit -sim
vlib work

#Required VHD comps
vcom -reportprogress 300 -work work ctl_logic.vhd

#Begin simulation
vsim work.ctl_logic
add wave sim:/ctl_logic/*

#Init
force -freeze sim:/ctl_logic/i_op 000000 0
force -freeze sim:/ctl_logic/i_funct 000000 0
run 100

#Begin test, use spreadsheet for reference.
#Test R-types
#add
force -freeze sim:/ctl_logic/i_op 000000 0
force -freeze sim:/ctl_logic/i_funct 100000 0
run 100

#addu
force -freeze sim:/ctl_logic/i_funct 100001 0
run 100

#and
force -freeze sim:/ctl_logic/i_funct 100100 0
run 100

#nor
force -freeze sim:/ctl_logic/i_funct 100111 0
run 100

#xor
force -freeze sim:/ctl_logic/i_funct 100110 0
run 100

#or
force -freeze sim:/ctl_logic/i_funct 100101 0
run 100

#slt
force -freeze sim:/ctl_logic/i_funct 101010 0
run 100

#sltu
force -freeze sim:/ctl_logic/i_funct 101011 0
run 100

#sll
force -freeze sim:/ctl_logic/i_funct 000000 0
run 100

#srl
force -freeze sim:/ctl_logic/i_funct 000010 0
run 100

#sra
force -freeze sim:/ctl_logic/i_funct 000011 0
run 100

#sllv
force -freeze sim:/ctl_logic/i_funct 000100 0
run 100

#srlv
force -freeze sim:/ctl_logic/i_funct 000110 0
run 100

#srav
force -freeze sim:/ctl_logic/i_funct 000111 0
run 100

#sub
force -freeze sim:/ctl_logic/i_funct 100010 0
run 100

#subu
force -freeze sim:/ctl_logic/i_funct 100011 0
run 100

#Test I-types (Here, the i_function field doesn't exist, so the i_funct inputs shouldn't matter)
#addi
force -freeze sim:/ctl_logic/i_op 001000 0
run 50
run 50

#addiu
force -freeze sim:/ctl_logic/i_op 001001 0
run 100

#andi
force -freeze sim:/ctl_logic/i_op 001100 0
run 100

#lui
force -freeze sim:/ctl_logic/i_op 001111 0
run 100

#lw
force -freeze sim:/ctl_logic/i_op 100011 0
run 100

#xori
force -freeze sim:/ctl_logic/i_op 001110 0
run 100

#ori
force -freeze sim:/ctl_logic/i_op 001101 0
run 100

#slti
force -freeze sim:/ctl_logic/i_op 001010 0
run 100

#sltiu
force -freeze sim:/ctl_logic/i_op 001011 0
run 100

#sw
force -freeze sim:/ctl_logic/i_op 101011 0
run 100