	.text
	.globl main
fn:	nop
	ReturnWord	$t0
main:	nop
	ParamWord	$t2
	addi	$sp, $sp, -80
	sw		$s7, -36($sp)
	sw		$s6, -32($sp)
	sw		$s5, -28($sp)
	sw		$s4, -24($sp)
	sw		$s3, -20($sp)
	sw		$s2, -16($sp)
	sw		$s1, -12($sp)
	sw		$s0, -8($sp)
	sw		$ra, -4($sp)
	sw		$fp, 0($sp)
	addi	$fp, $sp, 80
	sub 	$sp, $sp, 8
	lw	$t7, $t5
	add	$t8, $t7, $t6
	ReturnByte	$t9
	li	$v0, 10
	syscall
