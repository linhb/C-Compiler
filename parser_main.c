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
	//traverse result here, replace relevant nodes with ST entries
	if (yynerrs > 0)
		result = 1;
	switch (result) {
	case 0:
		fputs("\n****** SYMBOL TABLES ********\n", output);
		add_types();
		file_scope_symbol_table = malloc(sizeof(symbol_table));
		assert(file_scope_symbol_table != NULL);
		identifier_id = 1;
		current_scope_level = 1;
		st_id = 1;
		file_scope_symbol_table->scope_level = current_scope_level;
		file_scope_symbol_table->st_id = st_id;
		create_symbol_table(root, file_scope_symbol_table);
		print_symbol_table(output, file_scope_symbol_table);
		type_check(root);
		fputs("\n****** PARSE TREE ********\n", output);
		print_node(output, root);
		fputs("\n", output);
		// ir *ir_list = generate_ir_from_node(root);
		ir *ir_list = malloc(sizeof(*list));
		ir_list->first = malloc(sizeof(*item));
		generate_ir_from_node(root);
		add_ir_opcodes();
		fputs("\n****** INTERMEDIATE REPRESENTATION ********\n", output);
		print_ir(ir_list, output);
		// generate_code(ir_list);
		break;
	case 1:
		fprintf(stderr, "Number of errors: %d", yynerrs);
		break;
	case 2:
		fprintf(stderr, "Out of memory");
		break;
	}
	if (output != stdout)
		fclose(output);
	if (input != stdin)
		fclose(input);
	return 0;
}
