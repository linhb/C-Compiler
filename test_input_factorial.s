	.text
	.globl main
print_string:	nop
	li	$v0, 4
	syscall
	jr	$ra
print_int:	nop
	li	$v0, 1
	syscall
	jr	$ra
read_int:	nop
	li	$v0, 5
	syscall
	jr	$ra
main:	nop
	addi	$sp, $sp, -80
	sw	$s7, 36($sp)
	sw	$s6, 32($sp)
	sw	$s5, 28($sp)
	sw	$s4, 24($sp)
	sw	$s3, 20($sp)
	sw	$s2, 16($sp)
	sw	$s1, 12($sp)
	sw	$s0, 8($sp)
	sw	$ra, 4($sp)
	sw	$fp, 0($sp)
	addi	$fp, $sp, 80
	move	$fp, $sp
	sub	$sp, $sp, 12
	.data
string_1:	.asciiz	"Please enter a natural number: 
"
	.text
	la	$a0, string_1
	sw	$t9, 76($sp)
	sw	$t8, 72($sp)
	sw	$t7, 68($sp)
	sw	$t6, 64($sp)
	sw	$t5, 60($sp)
	sw	$t4, 56($sp)
	sw	$t3, 52($sp)
	sw	$t2, 48($sp)
	sw	$t1, 44($sp)
	sw	$t0, 40($sp)
	jal	print_string
	lw	$t0, 40($sp)
	lw	$t1, 44($sp)
	lw	$t2, 48($sp)
	lw	$t3, 52($sp)
	lw	$t4, 56($sp)
	lw	$t5, 60($sp)
	lw	$t6, 64($sp)
	lw	$t7, 68($sp)
	lw	$t8, 72($sp)
	lw	$t9, 76($sp)
	sub	$8, $fp, 84
	jal	read_int
	sw	$v0, 0($8)
	sub	$8, $fp, 88
	li	$9, 1
	sub	$10, $fp, 88
	sw	$9, 0($10)
	sub	$11, $fp, 92
	li	$12, 1
	sub	$13, $fp, 92
	sw	$12, 0($13)
label_0:	nop
	sub	$14, $fp, 92
	sub	$15, $fp, 84
	lw	$16, 0($15)
	lw	$17, 0($14)
	sle	$18, $17, $16
	beqz	$18, label_1
	sub	$8, $fp, 88
	sub	$9, $fp, 88
	sub	$10, $fp, 92
	lw	$11, 0($10)
	lw	$12, 0($9)
	mul	$13, $12, $11
	sub	$14, $fp, 88
	sw	$13, 0($14)
	sub	$8, $fp, 92
	lw	$9, 0($8)
	move	$a0, $9
	jal	print_int
	.data
string_2:	.asciiz	": "
	.text
	la	$a0, string_2
	sw	$t9, 76($sp)
	sw	$t8, 72($sp)
	sw	$t7, 68($sp)
	sw	$t6, 64($sp)
	sw	$t5, 60($sp)
	sw	$t4, 56($sp)
	sw	$t3, 52($sp)
	sw	$t2, 48($sp)
	sw	$t1, 44($sp)
	sw	$t0, 40($sp)
	jal	print_string
	lw	$t0, 40($sp)
	lw	$t1, 44($sp)
	lw	$t2, 48($sp)
	lw	$t3, 52($sp)
	lw	$t4, 56($sp)
	lw	$t5, 60($sp)
	lw	$t6, 64($sp)
	lw	$t7, 68($sp)
	lw	$t8, 72($sp)
	lw	$t9, 76($sp)
	sub	$8, $fp, 88
	lw	$9, 0($8)
	move	$a0, $9
	jal	print_int
	.data
string_3:	.asciiz	"
"
	.text
	la	$a0, string_3
	sw	$t9, 76($sp)
	sw	$t8, 72($sp)
	sw	$t7, 68($sp)
	sw	$t6, 64($sp)
	sw	$t5, 60($sp)
	sw	$t4, 56($sp)
	sw	$t3, 52($sp)
	sw	$t2, 48($sp)
	sw	$t1, 44($sp)
	sw	$t0, 40($sp)
	jal	print_string
	lw	$t0, 40($sp)
	lw	$t1, 44($sp)
	lw	$t2, 48($sp)
	lw	$t3, 52($sp)
	lw	$t4, 56($sp)
	lw	$t5, 60($sp)
	lw	$t6, 64($sp)
	lw	$t7, 68($sp)
	lw	$t8, 72($sp)
	lw	$t9, 76($sp)
	sub	$8, $fp, 92
	sub	$9, $fp, 92
	li	$10, 1
	lw	$11, 0($9)
	add	$12, $11, $10
	sub	$13, $fp, 92
	sw	$12, 0($13)
	jal	label_0
label_1:	nop
	li	$v0, 10
	syscall
