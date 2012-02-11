#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "token_constants.h"

int yylex();
extern int yyleng;
extern FILE *yyin;
extern char *yytext;
extern int yylineno;
extern void *yylval;

void initialize_token_names();
void print_value(FILE *output, void *yylval);
                                         
/*
 	main: interface to the lexer. Reads input from stdin or a file, writes output to stdout or a file. Input is passed to yylex() to tokenize. main then prints the line number, the input read, the token type and the token value if available.	
	Argument:
		1st argument: input source. If the first argument is a filename, that file is taken as input. If it is blank or "-", stdin is taken as input.
		2nd argument: output source. If the first argument is a filename, output is written to that file. If it is blank or "-", output is printed to stdout.
	Return: 
		0 if executed normally
	Note: sample input and output for this function can be found in ./test_input_1.txt and ./test_output.txt, respectively.
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
	initialize_token_names();
	int token;
	yyin = input;
	
	for (token = yylex(); token != 0; token = yylex()) {
		fprintf(output, "Line number:\t%-5d\tToken text:\t%-20s\tToken type:\t%-25s\t", yylineno, yytext, token_names[token]);
		switch (token) {
			struct number *number;
			case INTEGER_CONST: 
			case SHORT_CONST: 
			case UNSIGNED_LONG_CONST: 
				number = (struct number *)yylval;
				fprintf(output, "Token value:\t%-12ld\tOverflow: %-1d", number->value, number->overflow);
				break;
			case STRING_CONST:
			case CHAR_CONST:
			case IDENTIFIER:
				print_value(output, yylval);		
				break;
		}    
		fprintf(output, "\n");
	}
	if (output != stdout)
		fclose(output);
	if (input != stdin)
		fclose(input);
	return 0;
}

void initialize_token_names() {
	ADD_TOKEN_NAME(token_names, DO);
	ADD_TOKEN_NAME(token_names, FOR);
	ADD_TOKEN_NAME(token_names, RETURN);
	ADD_TOKEN_NAME(token_names, BREAK);
	ADD_TOKEN_NAME(token_names, SHORT);
	ADD_TOKEN_NAME(token_names, ELSE);
	ADD_TOKEN_NAME(token_names, GOTO);
	ADD_TOKEN_NAME(token_names, SIGNED);
	ADD_TOKEN_NAME(token_names, UNSIGNED);
	ADD_TOKEN_NAME(token_names, CHAR);
	ADD_TOKEN_NAME(token_names, IF);
	ADD_TOKEN_NAME(token_names, VOID);
	ADD_TOKEN_NAME(token_names, INT);
	ADD_TOKEN_NAME(token_names, CONTINUE);
	ADD_TOKEN_NAME(token_names, LONG);
	ADD_TOKEN_NAME(token_names, WHILE);
	
	ADD_TOKEN_NAME(token_names, INTEGER_CONST);
	ADD_TOKEN_NAME(token_names, SHORT_CONST);
	ADD_TOKEN_NAME(token_names, UNSIGNED_LONG_CONST);
	ADD_TOKEN_NAME(token_names, STRING_CONST);
	ADD_TOKEN_NAME(token_names, CHAR_CONST);
	
	ADD_TOKEN_NAME(token_names, IDENTIFIER);
	
	ADD_TOKEN_NAME(token_names, LOGICAL_NOT);
	ADD_TOKEN_NAME(token_names, LOGICAL_OR);
	ADD_TOKEN_NAME(token_names, LOGICAL_AND);
	ADD_TOKEN_NAME(token_names, BITWISE_XOR);
	ADD_TOKEN_NAME(token_names, AMPERSAND);
	ADD_TOKEN_NAME(token_names, BITWISE_OR);
	ADD_TOKEN_NAME(token_names, BITWISE_COMPLEMENT);
	ADD_TOKEN_NAME(token_names, IS_EQUAL);
	ADD_TOKEN_NAME(token_names, IS_NOT_EQUAL);
	ADD_TOKEN_NAME(token_names, LESS_THAN);
	ADD_TOKEN_NAME(token_names, GREATER_THAN);
	ADD_TOKEN_NAME(token_names, LESS_THAN_OR_EQUAL);
	ADD_TOKEN_NAME(token_names, GREATER_THAN_OR_EQUAL);
	ADD_TOKEN_NAME(token_names, ASSIGN);
	ADD_TOKEN_NAME(token_names, ADD_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, SUBTRACT_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, MULTIPLY_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, DIVIDE_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, REMAINDER_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, BITWISE_AND_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, BITWISE_OR_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, BITWISE_XOR_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, BITSHIFT_LEFT_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, BITSHIFT_RIGHT_AND_ASSIGN);
	ADD_TOKEN_NAME(token_names, PLUS);
	ADD_TOKEN_NAME(token_names, DASH);
	ADD_TOKEN_NAME(token_names, STAR);
	ADD_TOKEN_NAME(token_names, SLASH);
	ADD_TOKEN_NAME(token_names, REMAINDER);
	ADD_TOKEN_NAME(token_names, PREINCREMENT);
	ADD_TOKEN_NAME(token_names, PREDECREMENT);
	ADD_TOKEN_NAME(token_names, POSTINCREMENT);
	ADD_TOKEN_NAME(token_names, POSTDECREMENT);
	ADD_TOKEN_NAME(token_names, BITSHIFT_LEFT);
	ADD_TOKEN_NAME(token_names, BITSHIFT_RIGHT);
	ADD_TOKEN_NAME(token_names, QUESTION_MARK);
		
	ADD_TOKEN_NAME(token_names, LEFT_PAREN);
	ADD_TOKEN_NAME(token_names, RIGHT_PAREN);
	ADD_TOKEN_NAME(token_names, LEFT_BRACKET);
	ADD_TOKEN_NAME(token_names, RIGHT_BRACKET);
	ADD_TOKEN_NAME(token_names, LEFT_CURLY_BRACE);
	ADD_TOKEN_NAME(token_names, RIGHT_CURLY_BRACE);
	ADD_TOKEN_NAME(token_names, COMMA);
	ADD_TOKEN_NAME(token_names, SEMICOLON);
	ADD_TOKEN_NAME(token_names, COLON);
	ADD_TOKEN_NAME(token_names, ERROR);
}

/*
	print_value: prints the given value to the given output
	Parameters:
		output: FILE pointer referencing either stdin or a file
		yylval: void pointer referencing either a struct number whose value field is to be printed, or a string which is to be printed as is		  
	Return: none
	Side effect: the global variable 
*/              

void print_value(FILE *output, void *yylval) {
	char *value = strdup((char *)yylval);
	assert(NULL != value);
	fprintf(output, "Token value:\t%-20s\t", value);			
	free(value);
	value = NULL;
}