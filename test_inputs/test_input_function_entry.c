void print_string(char *str) {}
void print_int(int i) {}
void read_int(int num) {}      
int is_even(int num) {
	if (num % 2 == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
int main(int argc, char **argv){
	int num;
	print_string("Please enter a natural number: \n");
	read_int(num);
	print_string("\nYou entered ");
	print_int(num);
	int result;
	result = is_even(num);
	if (result == 1) {
		print_string("\nThat's an even number.\n");
	}
	else {
		print_string("\nThat's an odd number.\n");
	}
}
