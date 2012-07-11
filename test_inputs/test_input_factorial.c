void print_string(char *str) {}
void print_int(int i) {}
void read_int(int num) {}      
void main(void) {
	int num;
	print_string("Please enter a natural number: \n");
	read_int(num);
	int result;
	result = 1;
	int i;
	for (i = 1; i <= num; i++) {
		result *= i;
		print_int(i);
		print_string(": ");
		print_int(result);
		print_string("\n");
	}
}