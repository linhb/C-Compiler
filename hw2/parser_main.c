#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

int yyparse();
FILE *yyin;
extern int yynerrs;
node *root;
                                         
/*
 	main: interface to the parser. Reads input from stdin or a file, writes output to stdout or a file. 
	Argument:
		1st argument: input source. If the first argument is a filename, that file is taken as input. If it is blank or "-", stdin is taken as input.
		2nd argument: output source. If the first argument is a filename, output is written to that file. If it is blank or "-", output is printed to stdout.
	Return: 
		0 if executed normally
*/

int main(int argc, char **argv) {
	FILE *input, *output;
	if (argc < 2 || !strcmp(argv[1], "-")) {
		input = stdin;		
	} else {
		input = fopen(argv[1], "r");
	}
	if (argc < 3 || !strcmp(argv[2], "-")) {
		output = stdout;
	} else {
		output = fopen(argv[2], "w");
	}
	int result;
	yyin = input;
 
	result = yyparse();
	assert(root != NULL);
	switch (result) {
	case 0:
		fputs("\n", output);
		print_node(output, root);
		fputs("\n", output);
		break;
	case 1:
		fprintf(stderr, "Number of errors: %d", yynerrs);
		break;
	case 2:
		fprintf(stderr, "Out of memory");
	}
	if (output != stdout)
		fclose(output);
	if (input != stdin)
		fclose(input);
	return 0;
}