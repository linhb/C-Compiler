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
	move	$fp, $sp
	sub	$sp, $sp, 8
	.data
string_1:	.asciiz	"Please enter a natural number: 
"
	.text
	la	$a0, string_1
	jal	print_string
	sub	$8, $fp, 84
	jal	read_int
	sw	$v0, 0($8)
	.data
string_2:	.asciiz	"
You entered "
	.text
	la	$a0, string_2
	jal	print_string
	sub	$9, $fp, 84
	lw	$10, 0($9)
	move	$a0, $10
	jal	print_int
	.data
string_3:	.asciiz	".
Here's your number times 1 to 10:
"
	.text
	la	$a0, string_3
	jal	print_string
	sub	$11, $fp, 88
	li	$12, 1
	sub	$13, $fp, 88
	sw	$12, 0($13)
label_0:	nop
	sub	$14, $fp, 88
	li	$15, 10
	lw	$16, 0($14)
	sle	$17, $16, $15
	beqz	$17, label_1
	sub	$18, $fp, 84
	sub	$19, $fp, 88
	lw	$20, 0($19)
	lw	$21, 0($18)
	mul	$22, $21, $20
	move	$a0, $22
	jal	print_int
	.data
string_4:	.asciiz	"
"
	.text
	la	$a0, string_4
	jal	print_string
	sub	$23, $fp, 88
	sub	$24, $fp, 88
	li	$25, 1
	lw	$26, 0($24)
	add	$27, $26, $25
	sub	$28, $fp, 88
	sw	$27, 0($28)
	jal	label_0
label_1:	nop
	li	$v0, 10
	syscall
