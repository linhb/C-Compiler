%option noyywrap

%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include "token_constants.h"

	struct number *create_num(char *yytext);

	void *yylval;
%}
delimiter 	\s
whitespace	{delimiter}+
number    	[[:digit:]]+

%%
{number} {
	yylval = (struct number *)create_num(yytext);
	return NUM;
}
%%

struct number *create_num(char *yytext) {
	struct number *num = (struct number *)malloc(sizeof(struct number));
	num->value = strtoul(yytext, NULL, 10);
	return num;
}
