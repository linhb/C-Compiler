void print_string(char *str) {}
void print_int(int i) {}
void read_int(int num) {}      
int is_prime(int n) {	/* is prime if n % 2...n/2 != 0 */
	if (n <= 1) {
		return 0;
	}
	else if (n == 2) {
		return 1;
	}
	else {
		int i;
		for (i = 2; i <= (n / 2); i++) {
			if (n % i == 0) {
				return 0;
			}
		}
	}
	return 1;
}
int main(int argc, char **argv){
	print_string("Please enter a natural number: \n");
	int num;
	read_int(num);
	int result;
	result = is_prime(num);
	print_int(num);
	if (result == 1) {
		print_string(" is a prime!\n");
	}
	else {
		print_string(" is NOT a prime!\n");
	}
}
/*
int a;
int fn(int k) {
	char *cs;
	short s[3];
	s[2] = 74;
	return 7;
}
char main(int i, char c, short s) {
	int j, k;
	char l;
	short m, n;  
	i = 8;
	j = fn(2); 
	i = ((s + 5) >> 2) % 5;
	return 'g';
}
                   */

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
