%option noyywrap
%option yylineno

%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include "token_constants.h"

	struct number *create_num(char *yytext);
	void create_value_string();

	void *yylval;
%}

comments		(\/\*.*\*\/)|(\/\/.*)\n
delimiter 	[ |\t\n]
whitespace	{delimiter}+
identifier	[A-Za-z_][A-Za-z0-9_]*
number    	[0-9]+
string    	\"[^\"\n]*\"
char_const	\'.\'

%%
{whitespace}	
{comments}	

do 					yylval = (char *)token_names[DO]; return DO;	
for     		yylval = (char *)token_names[FOR]; return FOR;	
return  		yylval = (char *)token_names[RETURN]; return RETURN;	
break   		yylval = (char *)token_names[BREAK]; return BREAK;	
short   		yylval = (char *)token_names[SHORT]; return SHORT;	
else    		yylval = (char *)token_names[ELSE]; return ELSE;	
goto    		yylval = (char *)token_names[GOTO]; return GOTO;	
signed  		yylval = (char *)token_names[SIGNED]; return SIGNED;	
unsigned		yylval = (char *)token_names[UNSIGNED]; return UNSIGNED;	
char    		yylval = (char *)token_names[CHAR]; return CHAR;	
if 					yylval = (char *)token_names[IF]; return IF;	
void    		yylval = (char *)token_names[VOID]; return VOID;	
int     		yylval = (char *)token_names[INT]; return INT;	
continue		yylval = (char *)token_names[CONTINUE]; 	return CONTINUE;
long    		yylval = (char *)token_names[LONG]; return LONG;	
while				yylval = (char *)token_names[WHILE]; return WHILE;

{identifier}	{
	create_value_string();
	return IDENTIFIER;
}
{number} {
	yylval = (struct number *)create_num(yytext);
	return NUM_CONST;
}
{string} {
	create_value_string();
	return STRING_CONST;
}
{char_const}	{
	create_value_string();
	return CHAR_CONST;
}

"!"      yylval	= (char *)operator_names[LOGICAL_NOT];              	 return	LOGICAL_OP;
"\|\|"     yylval	= (char *)operator_names[LOGICAL_OR];               	 return	LOGICAL_OP;
"&&"     yylval	= (char *)operator_names[LOGICAL_AND];              	 return	LOGICAL_OP;
"^"      yylval	= (char *)operator_names[BITWISE_XOR];              	 return	BITWISE_OP;
"&"      yylval	= (char *)operator_names[BITWISE_AND];              	 return	BITWISE_OP;
"\|"      yylval	= (char *)operator_names[BITWISE_OR];               	 return	BITWISE_OP;
"~"      yylval	= (char *)operator_names[BITWISE_COMPLEMENT];       	 return	BITWISE_OP;
"=="     yylval	= (char *)operator_names[IS_EQUAL];                 	 return	COMPARISON_OP;
"!="     yylval	= (char *)operator_names[IS_NOT_EQUAL];             	 return	COMPARISON_OP;
"<"      yylval	= (char *)operator_names[LESS_THAN];                	 return	COMPARISON_OP;
">"      yylval	= (char *)operator_names[GREATER_THAN];             	 return	COMPARISON_OP;
"<="     yylval	= (char *)operator_names[LESS_THAN_OR_EQUAL];       	 return	COMPARISON_OP;
">="     yylval	= (char *)operator_names[GREATER_THAN_OR_EQUAL];    	 return	COMPARISON_OP;
"="      yylval	= (char *)operator_names[ASSIGN];                   	 return	ASSIGNMENT_OP;
"+="     yylval	= (char *)operator_names[ADD_AND_ASSIGN];           	 return	ASSIGNMENT_OP;
"-="     yylval	= (char *)operator_names[SUBTRACT_AND_ASSIGN];      	 return	ASSIGNMENT_OP;
"*="     yylval	= (char *)operator_names[MULTIPLY_AND_ASSIGN];      	 return	ASSIGNMENT_OP;
"/="     yylval	= (char *)operator_names[DIVIDE_AND_ASSIGN];        	 return	ASSIGNMENT_OP;
"%="     yylval	= (char *)operator_names[REMAINDER_AND_ASSIGN];     	 return	ASSIGNMENT_OP;
"&="     yylval	= (char *)operator_names[BITWISE_AND_AND_ASSIGN];   	 return	ASSIGNMENT_OP;
"|="     yylval = (char *)operator_names[BITWISE_OR_AND_ASSIGN];    	return	ASSIGNMENT_OP;
"^="     yylval = (char *)operator_names[BITWISE_XOR_AND_ASSIGN];   	return	ASSIGNMENT_OP;
">>="    yylval	= (char *)operator_names[BITSHIFT_LEFT_AND_ASSIGN]; 	 return	ASSIGNMENT_OP;
"<<="    yylval	= (char *)operator_names[BITSHIFT_RIGHT_AND_ASSIGN];	 return	ASSIGNMENT_OP;
"+"      yylval	= (char *)operator_names[PLUS];                     	 return	ARITHMETIC_OP;
"-"      yylval	= (char *)operator_names[DASH];                    	 return	ARITHMETIC_OP;
"*"      yylval	= (char *)operator_names[MULTIPLY];                 	 return	ARITHMETIC_OP;
"/"      yylval	= (char *)operator_names[DIVIDE];                   	 return	ARITHMETIC_OP;
"%"      yylval	= (char *)operator_names[REMAINDER];                	 return	ARITHMETIC_OP;
"++"     yylval	= (char *)operator_names[PREINCREMENT];             	 return	ARITHMETIC_OP;
"--"     yylval	= (char *)operator_names[PREDECREMENT];             	 return	ARITHMETIC_OP;
">>"     yylval	= (char *)operator_names[BITSHIFT_LEFT];            	 return	BITSHIFT_OP;
"<<"     yylval	= (char *)operator_names[BITSHIFT_RIGHT];           	 return	BITSHIFT_OP;

"("      yylval = (char *)token_names[LEFT_PAREN];                    return LEFT_PAREN;
")"      yylval = (char *)token_names[RIGHT_PAREN];                   return RIGHT_PAREN;
"["      yylval = (char *)token_names[LEFT_BRACKET];                  return LEFT_BRACKET;
"]"      yylval = (char *)token_names[RIGHT_BRACKET];                 return RIGHT_BRACKET;
"{"      yylval = (char *)token_names[LEFT_CURLY_BRACE];              return LEFT_CURLY_BRACE;
"}"      yylval = (char *)token_names[RIGHT_CURLY_BRACE];             return RIGHT_CURLY_BRACE;
","      yylval = (char *)token_names[COMMA];                         return COMMA;
";"      yylval = (char *)token_names[SEMICOLON];                     return SEMICOLON;
":"      yylval = (char *)token_names[COLON];                         return COLON;

.	return -1;

%%

struct number *create_num(char *yytext) {
	struct number *num = (struct number *)malloc(sizeof(struct number));
	num->value = strtoul(yytext, NULL, 10);
	return num;
}

void create_value_string() {
	char *value = (char *)malloc(yyleng + 1);
	strcpy(value, yytext);
	yylval = value; 
}