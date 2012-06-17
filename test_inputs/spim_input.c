int fn(int k) {
	return 7;
}
char main(int s) {
	int i;
	i = fn(2); /*print i here*/
	i = s + 5;
	return 'g';
}

/*
IR:       
****** INTERMEDIATE REPRESENTATION ********

		print_int: nop
	  move $a0, $sp
	  li $v0, 1
	  syscall

when you enter a function, first you store the prev ra in sp-4 (so it's in the first word forward of sp)
then set fp to sp
then start moving sp forward as many bytes as the function needs
each time you need a local var, go forward from the fp by the var's offset
at the end of the function you take ra from the stack (sp - 4) and put it back in $ra
then you jump to it

expected instructions:
assign offsets to each local variable, so s is -8, i is -12
	.text
main:	sw $ra, 4($sp)
we know i is offset -8
sub $
	
*/
