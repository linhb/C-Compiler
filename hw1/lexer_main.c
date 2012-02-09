#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "token_constants.h"

int yylex();
extern int yyleng;
extern FILE *yyin;
extern char *yytext;
extern int yylineno;
extern void *yylval;

void initialize_token_names();
void print_value(FILE *output, void *yylval);

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
		if (token > 0) {
			fprintf(output, "Line number:\t%d\tToken text:\t%s\tToken type:\t%s\t", yylineno, yytext, token_names[token]);
			switch (token) {
				struct number *number;
				case NUM_CONST: 
					number = (struct number *)yylval;
					fprintf(output, "Token value:\t%ld\t", number->value);
					break;
				case STRING_CONST:
				case CHAR_CONST:
				case IDENTIFIER:
					print_value(output, yylval);		
					break;
				case LOGICAL_NOT:
				case LOGICAL_OR:
				case LOGICAL_AND:
				case BITWISE_XOR:
				case AMPERSAND:
				case BITWISE_OR:
				case BITWISE_COMPLEMENT:
				case IS_EQUAL:
				case IS_NOT_EQUAL:
				case LESS_THAN:
				case GREATER_THAN:
				case LESS_THAN_OR_EQUAL:
				case GREATER_THAN_OR_EQUAL:
				case ASSIGN:
				case ADD_AND_ASSIGN:
				case SUBTRACT_AND_ASSIGN:
				case MULTIPLY_AND_ASSIGN:
				case DIVIDE_AND_ASSIGN:
				case REMAINDER_AND_ASSIGN:
				case BITWISE_AND_AND_ASSIGN:
				case BITWISE_OR_AND_ASSIGN:
				case BITWISE_XOR_AND_ASSIGN:
				case BITSHIFT_LEFT_AND_ASSIGN:
				case BITSHIFT_RIGHT_AND_ASSIGN:
				case PLUS:
				case DASH:
				case STAR:
				case SLASH:
				case REMAINDER:
				case PREINCREMENT:
				case PREDECREMENT:
				case POSTINCREMENT:
				case POSTDECREMENT:
				case BITSHIFT_LEFT:
				case BITSHIFT_RIGHT:
				case QUESTION_MARK:

				case LEFT_PAREN:
				case RIGHT_PAREN:
				case LEFT_BRACKET:
				case RIGHT_BRACKET:
				case LEFT_CURLY_BRACE:
				case RIGHT_CURLY_BRACE:
				case COMMA:
				case SEMICOLON:
				case COLON:
					print_value(output, yylval);		
					break;
				case DO:
				case FOR:
				case RETURN:
				case BREAK:
				case SHORT:
				case ELSE:
				case GOTO:
				case SIGNED:
				case UNSIGNED:
				case CHAR:
				case IF:
				case VOID:
				case INT:
				case CONTINUE:
				case LONG:
				case WHILE:
					break;
			}
		}
		else {
			fprintf(output, "ERROR");
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
	
	ADD_TOKEN_NAME(token_names, NUM_CONST);
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
}

void print_value(FILE *output, void *yylval) {
	char *value = strdup((char *)yylval);
	fprintf(output, "Token value:\t%s\t", value);			
	free(value);
}