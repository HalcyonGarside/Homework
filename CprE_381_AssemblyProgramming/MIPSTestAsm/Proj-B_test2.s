#Loading a word, adding 4 * 2^16 to it, and storing it in the next memory address.
addi $t0, $zero, 0
addiu $t0, $zero, 0 #for semantics' sake
lw $t1, 0($t0)
lui $t2, 4
add $t0, $t1, $t2
addu $t0, $t1, $t2 #for semantics' sake
sw $t0, 0($t2)

#Doing some random logical expressions and finding if their results are greater or less than the other.
addi $t0, $zero, 64
addi $t1, $zero, 55
and $t2, $t0, $t1
andi $t3, $t0, 10 #(Should be less than $t2)
slt $t4, $t2, $t3
nor $t2, $t0, $t1
sll $t3, $t0, 5 #(Should be less than $t2 unsigned)
sltu $t4, $t3, $t2

#Some bonus logical expressions
or $t2, $t0, $t1
ori $t3, $t0, 99
slti $t4, $t2, 80
sltiu $t4, $t2, 80
xor $t2, $t0, $t1
xori $t3, $t1, 99

addi $t0, $zero, 3
sllv $t2, $t0, $t0
srlv $t2, $t0, $t0
srav $t2, $t0, $t0

srl $t2, $t1, 3
sra $t2, $t1, 3

#Some subtraction operations
sub $t2, $t1, $t0
subu $t2, $t1, $t0


#Now let's test some branches and jumps
addi $t0, $zero, -1
Loop:
addi $t0, $t0, 1
beq $t0, $zero, Loop #should be taken
bne $t0, $zero, JumpOut
addi $t0, $t0, 2

JumpOut:
jal Function

j end


Function:
addi $t0, $t0, 2
jr $ra

end: