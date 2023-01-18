.data

fibs:.word   0, 1, 2, 3, 4, 5, 6, 7, 8, 9         # "array" of words to contain fib values
size: .word  10	           # size of "array" (agrees with array declaration)
prompt: .asciiz "How many Fibonacci numbers to generate? (2 <= x <= 19)"

.text

		jal LUI
		
Functions:
		addi $1, $0, 123
		addi $2, $0, 951

		add $3, $2, $1
		add $3, $2, $0
		addu $3, $2, $1
		and $4, $1, $2
		nor $5, $1, $2
		xor $6, $1, $2
		or $7, $1, $2
		sub $8, $3, $2
		subu $9, $10, $9

		ori $10, $1, 255
		andi $11, $10, 22
		addiu $12, $10, 120
		xori $13, $10, 25

		beq $0, $0, IDK

LUI:
		lui $14, 255
		
		slt $15, $1, $14
		slti $16, $14, 256
		
		bne $0, $0, Memory
		
IDK:
		addi $17, $0, -2
		sltu $17, $14, $17
		sltiu $18, $17, 1

		sll $20, $16, 13
		srl $21, $17, 3 
		sra $22, $17, 10

		addi $23, $0, 2

		addi $17, $0, 1

		sllv $24, $17, $23
		srlv $25, $17, $23
		srav $26, $17, $23
		
		j Exit

Memory:

		la   $s0, fibs        # load address of array
		la   $s5, size        # load address of size variable
		lw   $s5, 0($s5)      # load array size

		addi $20, $0, 69
		addi $19, $0, 65536

		sw $19, 0($s0)
		lw $21, 0($s0)
		lw $22, 16($s0)
		
		jr $31

Exit:

		addi  $2,  $0,  10              # Place "10" in $v0 to signal an "exit" or "halt"
		syscall                         # Actually cause the halt
