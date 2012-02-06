#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	// int a[2] = {1, 2};
	// a[3] = 3;
	// printf("%d\n", a[3]); // doesn't cause segfault, just print whatever is at that address

	// char *str = (char*) malloc(5*sizeof(char)); // warning: assignment makes integer from pointer without a cast
	// *str = "test";
	// printf("%s\n", *str);
	// free(str); // why does it say not allocated?

	// struct user {
	// 	char *name;
	// 	int age;
	// };
	// struct user A;
	// A.name = "A";
	// A.age = 24;
	// printf("%s\n", A.name);
	
	// char *str1 = "str1";
	// char *str2 = "str2";
	// printf("%d\n", strcmp(str1, str2));
	
	// int i = 2;
	// int j = i++; // error: lvalue required as increment operand
	// printf("%d\n", j);
	
	// 	int a = 1, b = 2, c = 3, i = 0;
	// 	i = (a, b); // i takes a's value without the parentheses, b's value with them
	// 	printf("%d\n", i);

	printf("\t\v\f");
}