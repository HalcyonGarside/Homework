.data
N: .word 10
Array: .word 1, 5, 2, 7, 4, 16, 485, -2, -33, 0

.text
main:
	lw 	$s1, N($zero)	#Store size of array
	addi 	$t1, $zero, 2
	slt 	$t0, $s1, $t1
	bne	$t0, $zero, End	#End program if size is less than 0
	
BSort:
	addi	$s0, $zero, 0	#Switched = false
	addi 	$t0, $zero, 1	#i = 1
Loop:
	addi 	$t1, $t0, -1	#i - 1
	sll	$t2, $t1, 2	#First Number Addr ((i - 1) * 4)
	sll	$t3, $t0, 2	#Second Number Addr (i * 4)
	lw	$t4, Array($t2)	#$t4 = Array[i - 1]
	lw	$t5, Array($t3)	#$t5 = Array[i]
	slt	$t6, $t4, $t5	#$t6 = $t4 < $t5
	bne	$t6, $zero, Skip
	add	$t6, $zero, $t4	#Swap $t4 and $t5 if $t4 > $t5
	add	$t4, $zero, $t5
	add	$t5, $zero, $t6
	addi	$s0, $zero, 1	#Switched = true
Skip:	sw	$t4, Array($t2)	#Store elements in switched order into array
	sw	$t5, Array($t3)
	addi	$t0, $t0, 1	#Increment i
	slt	$t6, $t0, $s1	#If i < N
	bne	$t6, $zero, Loop #loop
	bne	$s0, $zero, BSort#If a switch happened, loop BSort again
End:
	add	$v0, $zero, 10
	syscall			#Terminate execution