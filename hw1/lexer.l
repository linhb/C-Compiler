%option noyywrap
%option yylineno
%option nounput

%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include "token_constants.h"

	struct number *create_num(char *yytext);
	void create_value_string();

	void *yylval;
%}

comments		\/\*.*\*\/
delimiter 	[ \t\n\v\f]
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

"!"      yylval	= (char *)token_names[LOGICAL_NOT];              	 return	LOGICAL_NOT;
"\|\|"     yylval	= (char *)token_names[LOGICAL_OR];               	 return	LOGICAL_OR;
"&&"     yylval	= (char *)token_names[LOGICAL_AND];              	 return	LOGICAL_AND;
"^"      yylval	= (char *)token_names[BITWISE_XOR];              	 return	BITWISE_XOR;
"&"      yylval	= (char *)token_names[AMPERSAND];              	 return	AMPERSAND;
"\|"      yylval	= (char *)token_names[BITWISE_OR];               	 return	BITWISE_OR;
"~"      yylval	= (char *)token_names[BITWISE_COMPLEMENT];       	 return	BITWISE_COMPLEMENT;
"=="     yylval	= (char *)token_names[IS_EQUAL];                 	 return	IS_EQUAL;
"!="     yylval	= (char *)token_names[IS_NOT_EQUAL];             	 return	IS_NOT_EQUAL;
"<"      yylval	= (char *)token_names[LESS_THAN];                	 return	LESS_THAN;
">"      yylval	= (char *)token_names[GREATER_THAN];             	 return	GREATER_THAN;
"<="     yylval	= (char *)token_names[LESS_THAN_OR_EQUAL];       	 return	LESS_THAN_OR_EQUAL;
">="     yylval	= (char *)token_names[GREATER_THAN_OR_EQUAL];    	 return	GREATER_THAN_OR_EQUAL;
"="      yylval	= (char *)token_names[ASSIGN];                   	 return	ASSIGN;
"+="     yylval	= (char *)token_names[ADD_AND_ASSIGN];           	 return	ADD_AND_ASSIGN;
"-="     yylval	= (char *)token_names[SUBTRACT_AND_ASSIGN];      	 return	SUBTRACT_AND_ASSIGN;
"*="     yylval	= (char *)token_names[MULTIPLY_AND_ASSIGN];      	 return	MULTIPLY_AND_ASSIGN;
"/="     yylval	= (char *)token_names[DIVIDE_AND_ASSIGN];        	 return	DIVIDE_AND_ASSIGN;
"%="     yylval	= (char *)token_names[REMAINDER_AND_ASSIGN];     	 return	REMAINDER_AND_ASSIGN;
"&="     yylval	= (char *)token_names[BITWISE_AND_AND_ASSIGN];   	 return	BITWISE_AND_AND_ASSIGN;
"|="     yylval = (char *)token_names[BITWISE_OR_AND_ASSIGN];    	return	BITWISE_OR_AND_ASSIGN;
"^="     yylval = (char *)token_names[BITWISE_XOR_AND_ASSIGN];   	return	BITWISE_XOR_AND_ASSIGN;
">>="    yylval	= (char *)token_names[BITSHIFT_LEFT_AND_ASSIGN]; 	 return	BITSHIFT_LEFT_AND_ASSIGN;
"<<="    yylval	= (char *)token_names[BITSHIFT_RIGHT_AND_ASSIGN];	 return	BITSHIFT_RIGHT_AND_ASSIGN;
"+"      yylval	= (char *)token_names[PLUS];                     	 return	PLUS;
"-"      yylval	= (char *)token_names[DASH];                    	 return	DASH;
"*"      yylval	= (char *)token_names[STAR];                 	 return	STAR;
"/"      yylval	= (char *)token_names[SLASH];                   	 return	SLASH;
"%"      yylval	= (char *)token_names[REMAINDER];                	 return	REMAINDER;
"++"     yylval	= (char *)token_names[PREINCREMENT];             	 return	PREINCREMENT;
"--"     yylval	= (char *)token_names[PREDECREMENT];             	 return	PREDECREMENT;
">>"     yylval	= (char *)token_names[BITSHIFT_LEFT];            	 return	BITSHIFT_LEFT;
"<<"     yylval	= (char *)token_names[BITSHIFT_RIGHT];           	 return	BITSHIFT_RIGHT;
"?"	     yylval	= (char *)token_names[QUESTION_MARK];           	 return	QUESTION_MARK;

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