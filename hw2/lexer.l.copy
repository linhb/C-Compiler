%option noyywrap
%option yylineno
%option nounput

%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <assert.h>
  #include "token_constants.h"

void create_num(char *yytext);
void create_value_string();

void *yylval;

%}
comments		\/\*([^\*]|\*[^\/])*?\*\/
delimiter 	[ \t\n\v\f]
whitespace	{delimiter}+
identifier	[A-Za-z_][A-Za-z0-9_]*
digit				[0-9]
escape			\\({digit}{1,3}|[ntbrfv\\\'\"a\?])
number    	{digit}+(E[+\-]{digit}+)?
string    	\"((\\\")|[^\"\n])*\"
char_const	\'({escape}|.)\'

%%
{comments}	
{whitespace}	

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
	create_num(yytext);
	return (((struct number*)yylval)->type);
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

.	return ERROR;

%%

/*
	create_num: read the numeric value of input containing a number, classify the number as int or long, creates a struct containing the number's value and type, and set yylval to the struct

	Parameters:
		yytext: string, contains the raw input read by lex
	Return: none
  Side effects: set global variable yylval to newly created struct number

*/

void create_num(char *yytext) {
	struct number *num = malloc(sizeof *num);
	assert(num != NULL);                   
	num->overflow = 0;
	num->value = strtoul(yytext, NULL, 10);
	unsigned long int ul_limit = 4294967295UL;
	unsigned long int int_limit = 2147483647UL;
	unsigned long int value = num->value;
	if (value <= int_limit)
		num->type = INTEGER_CONST;    
 	else if (value <= ul_limit)
		num->type = UNSIGNED_LONG_CONST;    
	else { /* overflow */
		num->value = ul_limit;
		num->type = UNSIGNED_LONG_CONST;    
		num->overflow = 1;
	}
	yylval = num;
}

/*
	create_value_string: create a string containing the value of identifier, string and char tokens, then point yylval to the created string
	Parameters: none
	Return: none
  Side effects: set global variable yylval to newly created string
*/

void create_value_string() {
	yylval = strdup(yytext);
	assert(yylval != NULL);
}