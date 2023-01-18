.data
N: .word 10
Array: .word 1, 5, 2, 7, 4, 16, 485, -2, -33, 0

.text
main:
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	# lw 	$s1, N($zero)	#Store size of array
	lui $1,4097		# These lines are the psuedoinstruction's equivalent
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addu $1,$1,$0
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	lw $17,0($1)
	
	addi 	$t1, $zero, 2
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	slt 	$t0, $s1, $t1
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	bne	$t0, $zero, End	# End program if size is less than 0
	
BSort:
	addi	$s0, $zero, 0	#Switched = false
	addi 	$t0, $zero, 1	#i = 1
Loop:
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi 	$t1, $t0, -1	#i - 1
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	sll	$t2, $t1, 2	#First Number Addr ((i - 1) * 4)
	sll	$t3, $t0, 2	#Second Number Addr (i * 4)
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	
	# lw	$t4, Array($t2)	#$t4 = Array[i - 1]
	lui $1,4097
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addu $1,$1,$10
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	lw $12,4($1)
	
	# Pseudo instruction  lw	$t5, Array($t3)	#$t5 = Array[i]
	lui $1,4097
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addu $1,$1,$11
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	lw $13,4($1)
	
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	slt	$t6, $t4, $t5	#$t6 = $t4 < $t5
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0 # NOP
	bne	$t6, $zero, Skip
	add	$t6, $zero, $t4	#Swap $t4 and $t5 if $t4 > $t5
	addi	$zero, $zero, 0 # NOP
	addi	$zero, $zero, 0 # NOP
	addi	$zero, $zero, 0 # NOP
	add	$t4, $zero, $t5
	add	$t5, $zero, $t6
	addi	$s0, $zero, 1	#Switched = true
Skip:	
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP	
	#Pseudoinstruction in sw $t4, Array($t2)
	lui $1,4097
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addu $1,$1,$10
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	sw	$12, 4($1)	#Store elements in switched order into array

	#Pseudoinstruction in 	sw	$t5, Array($t3)
	lui $1,4097
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addu $1,$1,$11
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	sw	$13, 4($1)

	addi	$t0, $t0, 1	#Increment i
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	slt	$t6, $t0, $s1	#If i < N
	addi	$zero, $zero, 0	# NOP
	addi	$zero, $zero, 0	# NOP
	bne	$t6, $zero, Loop #loop
	bne	$s0, $zero, BSort#If a switch happened, loop BSort again
End:
	add	$v0, $zero, 10
	syscall			#Terminate execution
