#include <stdio.h>
#include <string.h>

#include "token_constants.h"

int yylex();
extern yyleng;
extern FILE *yyin;
extern char *yytext;
extern int yylineno;
extern void *yylval;


int main(int argc, char **argv) {
	FILE *input, *output;
	input = stdin;
	output = stdout;
	initialize_token_names();
	int token;
	char *name;
	struct number *number;
	char *id;
	
	for (token = yylex(); token != 0; token = yylex()) {
		get_token_name(name, token);
		printf("%s\t", name);
		if (token == NUM)
			printf("%d", yylval);
	}
	if (output != stdout)
		fclose(output);
	if (input != stdin)
		fclose(input);
	return 0;
}

void initialize_token_names() {
	token_names[NUM] = NUM;
}

void *get_token_name(char *name, int token_number) {
	strcpy(name, token_names[token_number]);
}

