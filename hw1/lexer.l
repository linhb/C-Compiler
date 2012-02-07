%option noyywrap
%option yylineno

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
string    	\"[^\"\n]*\"
char_const	\'.\'

%%

DO      		yylval = (long int *) DO; return DO;
FOR     		yylval = (long int *) FOR; return FOR;
RETURN  		yylval = (long int *) RETURN; return RETURN;
BREAK   		yylval = (long int *) BREAK; return BREAK;
SHORT   		yylval = (long int *) SHORT; return SHORT;
ELSE    		yylval = (long int *) ELSE; return ELSE;
GOTO    		yylval = (long int *) GOTO; return GOTO;
SIGNED  		yylval = (long int *) SIGNED; return SIGNED;
UNSIGNED		yylval = (long int *) UNSIGNED; return UNSIGNED;
CHAR    		yylval = (long int *) CHAR; return CHAR;
IF      		yylval = (long int *) IF; return IF;
VOID    		yylval = (long int *) VOID; return VOID;
INT     		yylval = (long int *) INT; return INT;
CONTINUE		yylval = (long int *) CONTINUE; return CONTINUE;
LONG    		yylval = (long int *) LONG; return LONG;
WHILE   		yylval = (long int *) WHILE; return WHILE;

{number} {
	yylval = (struct number *)create_num(yytext);
	return NUM_CONST;
}
{string} {
	char *value = malloc(strlen(yytext) + 1);
	strcpy(value, yytext);
	yylval = value;
	return STRING_CONST;
}
{char_const}	yylval = &(yytext[1]); return CHAR_CONST;

%%

struct number *create_num(char *yytext) {
	struct number *num = (struct number *)malloc(sizeof(struct number));
	num->value = strtoul(yytext, NULL, 10);
	return num;
}
