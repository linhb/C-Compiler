#include <stdio.h>
#include <string.h>

#include "token_constants.h"

int yylex();
extern int yyleng;
extern FILE *yyin;
extern char *yytext;
extern int yylineno;
extern void *yylval;

void initialize_token_names();
void get_token_name(char *name, int token_number);

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
		printf("%s\t", token_names[token]);
		if (token == NUM) {
			number = (struct number*)yylval;
			printf("%ld", number->value);
		}
	}
	if (output != stdout)
		fclose(output);
	if (input != stdin)
		fclose(input);
	return 0;
}

void initialize_token_names() {
	ADD_TOKEN_NAME(token_names, NUM);
}

// void get_token_name(char *name, int token_number) {
// 	strcpy(name, token_names[token_number]);
// }
// 
