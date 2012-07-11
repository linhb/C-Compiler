void print_string(char *str) {}
void print_int(int i) {}
void read_int(int num) {}      
int main(int argc, char **argv){
	int num;
	print_string("Please enter a natural number: \n");
	read_int(num);
	print_string("\nYou entered ");
	print_int(num);
	print_string("\n");
	if (num > 9000) {
		print_string("That's OVER 9000!!!\n");
	}
	else {
		print_string("That wasn't over 9000 :(\n");
	}
}
