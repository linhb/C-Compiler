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
is_even:	nop
	sw	$s7, 36($sp)
	sw	$s6, 32($sp)
	sw	$s5, 28($sp)
	sw	$s4, 24($sp)
	sw	$s3, 20($sp)
	sw	$s2, 16($sp)
	sw	$s1, 12($sp)
	sw	$s0, 8($sp)
	sw	$fp, 4($sp)
	sw	$ra, 0($sp)
	addi	$fp, $sp, 80
	sub	$sp, $sp, 0
	sub	$8, $fp, 80
	li	$9, 2
	lw	$10, 0($8)
	rem	$11, $10, $9
	li	$12, 0
	seq	$13, $11, $12
	beqz	$13, label_0
	li	$8, 1
	move	$v0, $8
	add	$sp, $sp, 0
	lw	$ra, 0($sp)
	lw	$fp, 4($sp)
	lw	$s0, 8($sp)
	lw	$s1, 12($sp)
	lw	$s2, 16($sp)
	lw	$s3, 20($sp)
	lw	$s4, 24($sp)
	lw	$s5, 28($sp)
	lw	$s6, 32($sp)
	lw	$s7, 36($sp)
	jr	$ra
	j	label_1
label_0:	nop
	li	$8, 0
	move	$v0, $8
	add	$sp, $sp, 0
	lw	$ra, 0($sp)
	lw	$fp, 4($sp)
	lw	$s0, 8($sp)
	lw	$s1, 12($sp)
	lw	$s2, 16($sp)
	lw	$s3, 20($sp)
	lw	$s4, 24($sp)
	lw	$s5, 28($sp)
	lw	$s6, 32($sp)
	lw	$s7, 36($sp)
	jr	$ra
label_1:	nop
main:	nop
	sw	$s7, 36($sp)
	sw	$s6, 32($sp)
	sw	$s5, 28($sp)
	sw	$s4, 24($sp)
	sw	$s3, 20($sp)
	sw	$s2, 16($sp)
	sw	$s1, 12($sp)
	sw	$s0, 8($sp)
	sw	$fp, 4($sp)
	sw	$ra, 0($sp)
	addi	$fp, $sp, 80
	sub	$sp, $sp, 8
	.data
string_1:	.asciiz	"Please enter a natural number: 
"
	.text
	la	$a0, string_1
	addi	$sp, $sp, -80
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
	addi	$sp, $sp, 80
	sub	$8, $fp, 84
	jal	read_int
	sw	$v0, 0($8)
	.data
string_2:	.asciiz	"
You entered "
	.text
	la	$a0, string_2
	addi	$sp, $sp, -80
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
	addi	$sp, $sp, 80
	sub	$8, $fp, 84
	lw	$9, 0($8)
	move	$a0, $9
	jal	print_int
	sub	$8, $fp, 88
	sub	$9, $fp, 84
	sub	$sp, $sp, 4
	sw	$9, 0($sp)
	addi	$sp, $sp, -80
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
	jal	is_even
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
	addi	$sp, $sp, 80
	sub	$11, $fp, 88
	sw	$10, 0($11)
	sub	$12, $fp, 88
	li	$13, 1
	lw	$14, 0($12)
	seq	$15, $14, $13
	beqz	$15, label_2
	.data
string_3:	.asciiz	"
That's an even number.
"
	.text
	la	$a0, string_3
	addi	$sp, $sp, -80
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
	addi	$sp, $sp, 80
	j	label_3
label_2:	nop
	.data
string_4:	.asciiz	"
That's an odd number.
"
	.text
	la	$a0, string_4
	addi	$sp, $sp, -80
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
	addi	$sp, $sp, 80
label_3:	nop
	li	$v0, 10
	syscall
