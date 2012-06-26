#   .data
# newline: .asciiz "\n"
#   .text
#   .globl  main
# main: sw  $ra,4($sp)
	# first print what's in $fp and $sp
	# move $a0, $fp
	# li $v0, 1
	# syscall
	# la $a0, newline
	# li $v0, 4
	# syscall
	# move $a0, $sp
	# li $v0, 1
	# syscall
	# la $a0, newline
	# li $v0, 4
	# syscall
	# let's allocate a local var m, set it to 17, then print it
	# to allocate, move stack pointer down 4 bytes, store that in t0
	# first set $fp to $sp so we have a static reference point
  # move $fp, $sp
  # sub $sp, $sp, 4 # move sp forward by 4, so now sp is 4 lower than fp
  # li $t0, 17
  # # move $t1, -84($fp)
  # sw $t0, -4($fp)
  # lw $a0, -4($fp)
  # li $v0, 1
  # syscall
  # li  $v0,10    # v0 <- syscall code for exit
  # syscall


# expected output of spim_input.c, 6/17

#   .text
#   .globl  main
# fn: nop
#       sub $sp, $sp, 80
#       sw $s7, 36($sp)
#       sw $s6, 32($sp)
#       sw $s5, 28($sp)
#       sw $s4, 24($sp)
#       sw $s3, 20($sp)
#       sw $s2, 16($sp)
#       sw $s1, 12($sp)
#       sw $s0, 08($sp)
#       sw $fp, 04($sp)
#       sw $ra, 0($sp)
#       addi $fp, $sp, 80
#       li $t0, 70
#       move $v0, $t0
#       lw $fp, -80($fp)
#       lw $ra, 0($sp)
#       lw $s7, 36($sp)
#       lw $s6, 32($sp)
#       lw $s5, 28($sp)
#       lw $s4, 24($sp)
#       lw $s3, 20($sp)
#       lw $s2, 16($sp)
#       lw $s1, 12($sp)
#       lw $s0, 08($sp)
#       add $sp, $sp, 80
#       jr $ra
# main: nop
#       sub $sp, $sp, 80
#       sw $s7, 36($sp)
#       sw $s6, 32($sp)
#       sw $s5, 28($sp)
#       sw $s4, 24($sp)
#       sw $s3, 20($sp)
#       sw $s2, 16($sp)
#       sw $s1, 12($sp)
#       sw $s0, 08($sp)
#       sw $fp, 04($sp)
#       sw $ra, 0($sp)
#       addi $fp, $sp, 80
#       sub $sp, $sp, 4
#       add $t1, $fp, 84
#       li $t2, 2
#       sub $sp, $sp, 4
#       sw $t2, -84($fp)
#       li $s2, 732
#       jal fn
#   move $a0, $v0
#   li $v0, 1
#   syscall
#   move $a0, $s2
#   li $v0, 1
#   syscall
#       move $t3, $v0
#       sw $t3, -84($fp)
#       add $t4, $fp, -84
#       add $t5, $fp, 4
#       li $t6, 5
#       lw $t7, 0($t5)
#       add $t8, $t7, $t6
#       sw $t8, -84($fp)
#       li $t9, 103
#       move $v0, $t9
#       # test things worked correctly by printing $t9 which should be, and was, 103
#   move $a0, $t9
#   li $v0, 1
#   syscall
#       li $v0, 10
#       syscall


print_int: nop
      # move first parameter, ie 0($fp) into a0
      lw $a0, 0($sp)
      li $v0, 1
      syscall
      jr $ra
print_string: nop
    # move first parameter, ie 0($fp) into a0
    lw $a0, 0($sp)
    li $v0, 4
    syscall
    jr $ra      
main: nop
        move $fp, $sp
        sub $sp, $sp, 4
        li $t0, 187
        .data
str1:   .asciiz   "Enter a number:\t"
        .text
        la $t2, str1
        li $v0, 4
        move $a0, $t2
        syscall
        sw $t0, 0($sp)
        jal print_int
        li $v0, 10
        syscall