void print_string(char *str) {}
void print_int(int i) {}
void read_int(int num) {}      
int is_prime(int n) {
	/* is prime if n % 2...n/2 != 0 */
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
