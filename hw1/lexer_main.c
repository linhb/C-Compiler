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
// void get_token_name(char *name, int token_number);

int main(int argc, char **argv) {
	FILE *input, *output;
	input = stdin;
	output = stdout;
	initialize_token_names();
	int token;
	// char *name;
	struct number *number;
	char *id;
	
	for (token = yylex(); token != 0; token = yylex()) {
		// name = malloc(strlen(token_names[token]) + 1);
		// strcpy(name, token_names[token]);
		printf("Line number:\t%d\tToken text:\t%s\tToken type:\t%s\t", yylineno, yytext, token_names[token]);
		if (token == NUM_CONST) {
			number = (struct number*)yylval;
			printf("Token value:\t%ld\t", number->value);
			free(yylval);
		}
		if (token == STRING_CONST || token == CHAR_CONST) {
			char *value = (char *)yylval;
			printf("Token value:\t%s\t", value);
		}
		if (token == CHAR_CONST) {
			char value = (char)yylval;
			printf("Token value:\t%s\t", value);
		}
		printf("\n");
		if (yylval != 0)
			free(yylval);
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
}

// void get_token_name(char *name, int token_number) {
// 	strcpy(name, token_names[token_number]);
// }
// 
