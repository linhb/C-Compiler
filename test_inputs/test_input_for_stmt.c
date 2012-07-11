void print_string(char *str) {}
void print_int(int i) {}
void read_int(int num) {}      
void main(void) {
	int num;
	print_string("Please enter a natural number: \n");
	read_int(num);
	print_string("\nYou entered ");
	print_int(num);
	print_string(".\nHere's your number times 1 to 10:\n");
	int i;
	for (i = 1; i <= 10; i++) {
		print_int(num * i);
		print_string("\n");
	}
}