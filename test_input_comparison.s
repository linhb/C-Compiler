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
	sub	$sp, $sp, 4
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
string_3:	.asciiz	"
"
	.text
	la	$a0, string_3
	jal	print_string
	sub	$11, $fp, 84
	li	$12, 9000
	lw	$13, 0($11)
	sgt	$14, $13, $12
	beqz	$14, label_0
	.data
string_4:	.asciiz	"That's OVER 9000!!!
"
	.text
	la	$a0, string_4
	jal	print_string
	jal	label_1
label_0:	nop
	.data
string_5:	.asciiz	"That wasn't over 9000 :(
"
	.text
	la	$a0, string_5
	jal	print_string
label_1:	nop
	li	$v0, 10
	syscall
