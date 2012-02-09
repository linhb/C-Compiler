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
void initialize_operator_names();
void print_value(void *value);

int main(int argc, char **argv) {
	FILE *input, *output;
	input = stdin;
	output = stdout;
	initialize_token_names();
	initialize_operator_names();
	int token;
	
	for (token = yylex(); token != 0; token = yylex()) {
		if (token > 0) {
			printf("Line number:\t%d\tToken text:\t%s\tToken type:\t%s\t", yylineno, yytext, token_names[token]);
			switch (token) {
				struct number *number;
				case NUM_CONST: 
					number = (struct number *)yylval;
					printf("Token value:\t%ld\t", number->value);
					break;
				case STRING_CONST:
				case CHAR_CONST:
				case IDENTIFIER:
					print_value(yylval);		
					break;
				case LOGICAL_OP:
				case BITWISE_OP:
				case COMPARISON_OP:
				case ASSIGNMENT_OP:
				case ARITHMETIC_OP:
				case BITSHIFT_OP:
				
				case LEFT_PAREN:
				case RIGHT_PAREN:
				case LEFT_BRACKET:
				case RIGHT_BRACKET:
				case LEFT_CURLY_BRACE:
				case RIGHT_CURLY_BRACE:
				case COMMA:
				case SEMICOLON:
				case COLON:
					print_value(yylval);		
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
			printf("ERROR");
		}
		printf("\n");
		yylineno++;
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
	
	ADD_TOKEN_NAME(token_names, LOGICAL_OP);
	ADD_TOKEN_NAME(token_names,	BITWISE_OP);
	ADD_TOKEN_NAME(token_names,	COMPARISON_OP);
	ADD_TOKEN_NAME(token_names,	ASSIGNMENT_OP);
	ADD_TOKEN_NAME(token_names,	ARITHMETIC_OP);
	ADD_TOKEN_NAME(token_names,	BITSHIFT_OP);
	
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

void initialize_operator_names() {
	ADD_OPERATOR_NAME(operator_names, LOGICAL_NOT);
	ADD_OPERATOR_NAME(operator_names, LOGICAL_OR);
	ADD_OPERATOR_NAME(operator_names, LOGICAL_AND);
	ADD_OPERATOR_NAME(operator_names, BITWISE_XOR);
	ADD_OPERATOR_NAME(operator_names, BITWISE_AND);
	ADD_OPERATOR_NAME(operator_names, BITWISE_OR);
	ADD_OPERATOR_NAME(operator_names, BITWISE_COMPLEMENT);
	ADD_OPERATOR_NAME(operator_names, IS_EQUAL);
	ADD_OPERATOR_NAME(operator_names, IS_NOT_EQUAL);
	ADD_OPERATOR_NAME(operator_names, LESS_THAN);
	ADD_OPERATOR_NAME(operator_names, GREATER_THAN);
	ADD_OPERATOR_NAME(operator_names, LESS_THAN_OR_EQUAL);
	ADD_OPERATOR_NAME(operator_names, GREATER_THAN_OR_EQUAL);
	ADD_OPERATOR_NAME(operator_names, ASSIGN);
	ADD_OPERATOR_NAME(operator_names, ADD_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, SUBTRACT_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, MULTIPLY_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, DIVIDE_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, REMAINDER_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, BITWISE_AND_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, BITWISE_OR_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, BITWISE_XOR_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, BITSHIFT_LEFT_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, BITSHIFT_RIGHT_AND_ASSIGN);
	ADD_OPERATOR_NAME(operator_names, PLUS);
	ADD_OPERATOR_NAME(operator_names, DASH);
	ADD_OPERATOR_NAME(operator_names, MULTIPLY);
	ADD_OPERATOR_NAME(operator_names, DIVIDE);
	ADD_OPERATOR_NAME(operator_names, REMAINDER);
	ADD_OPERATOR_NAME(operator_names, PREINCREMENT);
	ADD_OPERATOR_NAME(operator_names, PREDECREMENT);
	ADD_OPERATOR_NAME(operator_names, POSTINCREMENT);
	ADD_OPERATOR_NAME(operator_names, POSTDECREMENT);
	ADD_OPERATOR_NAME(operator_names, BITSHIFT_LEFT);
	ADD_OPERATOR_NAME(operator_names, BITSHIFT_RIGHT);
}

void print_value(void *yylval) {
	char *value = strdup((char *)yylval);
	printf("Token value:\t%s\t", value);			
	free(value);
}