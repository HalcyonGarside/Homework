.data
ArraySize: .word 10
Array: .word 1, 5, 2, 7, 4, 16, 485, -2, -33, 0

.text

Main:
	la $s0, Array
	la $s1, ArraySize
	addi $a0, $s0, 0
	addi $a1, $zero, 0
	sub $a2, $s1, 1
	jal MergeSort
	j End
	
MergeSort:
		# ArrayAddress = $a0
		# Left = $a1
		# Right = $a2
		
		slt $t0, $a1, $a2
		beq $t0, $zero, MergeR	# If Left ($a1) >= Right ($a2) return
		
		
		sub $t0, $a2, 1
		sra $t0, $t0, 1
		add $s0, $t0, $a1	# Middle ($s0) = Left + (Right - 1) / 2
		
		addi $fp, $sp, 0
		sub $sp, $sp, 20	
		sw $ra, 16($sp)
		sw $s0, 12($sp)
		sw $a1, 8($sp)
		sw $a2, 4($sp)
		sw $fp, 0($sp)
		
		
		addi $a2, $s0, 0
		jal MergeSort		# MergeSort(ArrayAddress, Left, Middle)
		
		lw $s0, 12($sp)
		lw $a1, 8($sp)
		lw $a2, 4($sp)
		lw $fp, 0($sp)
		
		addi $a1, $s0, 1
		jal MergeSort		# MergeSort(ArrayAddress, Middle + 1, Right)
		
		lw $s0, 12($sp)
		lw $a1, 8($sp)
		lw $a2, 4($sp)
		lw $fp, 0($sp)
		
		addi $a3, $a2, 0
		addi $a2, $s0, 0
		jal Merge		# Merge(ArrayAddress, Left, Middle, Right)
		
		lw $ra, 16($sp)
		addi $sp, $sp, 20
	MergeR:
		jr $ra
		
Merge:
	# ArrayAddress = $a0
	# Left = $a1
	# Middle = $a2
	# Right = $a3
	
	sub $t0, $a2, $a1
	addi $t0, $t0, 1	# Length of LeftArray
	
	sub $t1, $a3, $a2	# Length of RightArray
	
	sll $t2, $t0, 2
	sub $s1, $sp, $t2	# $s1 = Address of LeftArray
	
	sll $t3, $t1, 2
	sub $s2, $s1, $t3	# $s2 = Address of Right Array
	
	addi $t2, $zero, 0	# $t2 = i
	CopyToLeft:
		slt $t3, $t2, $t0
		beq $t3, $zero, ExitCopyToLeft
		sll $t3, $t2, 2		# Index of i
		add $t4, $t2, $a1
		sll $t4, $t4, 2		# Index of i + Left
		
		add $t4, $t4, $a0
		lw $t4, 0($t4)		# $t4 = Array[i + Left]
		add $t5, $s1, $t3
		sw $t4, 0($t5)		# LeftArray[i] = $t4
		addi $t2, $t2, 1
		j CopyToLeft
	ExitCopyToLeft:
	
	addi $t2, $zero, 0	# $t2 = i
	CopyToRight:
		slt $t3, $t2, $t1
		beq $t3, $zero, ExitCopyToRight
		sll $t3, $t2, 2		# Index of i
		addi $t4, $t2, 1
		add $t4, $t4, $a2
		sll $t4, $t4, 2		# Index of i + Middle + 1
		
		add $t4, $t4, $a0
		lw $t4, 0($t4)		# $t4 = Array[i + Middle + 1]
		add $t5, $s2, $t3
		sw $t4, 0($t5)		# RightArray[i] = $t4
		addi $t2, $t2, 1
		j CopyToRight
	ExitCopyToRight:
	
	addi $t2, $zero, 0	# i = $t2
	addi $t3, $zero, 0	# j = $t3
	addi $t4, $zero, 1	# k = $t4
				# n1 = $t0
				# n2 = $t1
				
	WhileLoop:
		slt $t5, $t2, $t0
		beq $t5, $zero, ExitWhile
		slt $t5, $t3, $t1
		beq $t5, $zero, ExitWhile
		
		sll $t5, $t2, 2
		add $t5, $t5, $s1	# &LeftArray[i] = $t5
		lw $t5, 0($t5)		# LeftArray[i] = $t5
		
		sll $t6, $t3, 2
		add $t6, $t6, $s2	# &RightArray[j] = $t6
		lw $t6, 0($t6)		# RightArray[i] = $t6
		
		addi $t7, $t6, 1
		slt $t7, $t5, $t7
		beq $t7, $zero, Else
		If:
		
		sll $s7, $t2, 2
		add $s7, $s7, $s1
		lw $s7, 0($s7)
		
		sll $t7, $t4, 2
		add $t7, $a0, $t7	# &Array[k] = $t7
		sw $s7, 0($t7)
		
		addi $t2, $t2, 1
		j EndIf
		Else:
		sll $s7, $t3, 2
		add $s7, $s7, $s2
		lw $s7, 0($s7)
		
		sll $t7, $t4, 2
		add $t7, $a0, $t7	# &Array[k] = $t7
		sw $s7, 0($t7)
		
		addi $t3, $t3, 1
		EndIf:
		addi $t4, $t4, 1
		j WhileLoop
	ExitWhile:
	
	CopyLeftBack:
		slt $t5, $t2, $t0
		beq $t5, $zero, EndCopyLeftBack
		
		sll $s7, $t2, 2
		add $s7, $s7, $s1
		lw $s7, 0($s7)
		
		sll $t7, $t4, 2
		add $t7, $a0, $t7	# &Array[k] = $t7
		sw $s7, 0($t7)
		
		addi $t2, $t2, 1
		addi $t4, $t4, 1
		j CopyLeftBack
	EndCopyLeftBack:
	
	CopyRightBack:
		slt $t5, $t3, $t1
		beq $t5, $zero, EndCopyRightBack
		
		sll $s7, $t3, 2
		add $s7, $s7, $s2
		lw $s7, 0($s7)
		
		sll $t7, $t4, 2
		add $t7, $a0, $t7	# &Array[k] = $t7
		sw $s7, 0($t7)
		
		addi $t3, $t3, 1
		addi $t4, $t4, 1
		j CopyRightBack
	EndCopyRightBack:

	jr $ra
End:
	add	$v0, $zero, 10
	syscall			#Terminate execution
	
	
	