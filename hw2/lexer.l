%option noyywrap
%option yylineno
%option nounput

%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <assert.h>
	#include "node.h"

void create_number_node(char *yytext);
void create_string_node(char *yytext);
void create_char_node(char *yytext);
void create_identifier_node(char *yytext);
void create_reserved_word_node(char *yytext, int value);

%}
comments		\/\*([^\*]|\*[^\/])*?\*\/
delimiter 	[ \t\n\v\f]
whitespace	{delimiter}+
identifier	[A-Za-z_][A-Za-z0-9_]*
digit				[0-9]
octal_digit	[0-7]
escape			\\({octal_digit}{1,3}|[ntbrfv\\\'\"a\?])                          
number    	{digit}+(E[+\-]{digit}+)?
string    	\"((\\\")|[^\"\n])*\"
char_const	\'({escape}|.)\'
                                                                         
%%
{comments}	
{whitespace}	

do 					 create_reserved_word_node(yytext, DO); return DO;	
for     		 create_reserved_word_node(yytext, FOR); return FOR;	
return  		 create_reserved_word_node(yytext, RETURN); return RETURN;	
break   		 create_reserved_word_node(yytext, BREAK); return BREAK;	
short   		 create_reserved_word_node(yytext, SHORT); return SHORT;	
else    		 create_reserved_word_node(yytext, ELSE); return ELSE;	
goto    		 create_reserved_word_node(yytext, GOTO); return GOTO;	
signed  		 create_reserved_word_node(yytext, SIGNED); return SIGNED;	
unsigned		 create_reserved_word_node(yytext, UNSIGNED); return UNSIGNED;	
char    		 create_reserved_word_node(yytext, CHAR); return CHAR;	
if 					 create_reserved_word_node(yytext, IF); return IF;	
void    		 create_reserved_word_node(yytext, VOID); return VOID;	
int     		 create_reserved_word_node(yytext, INT); return INT;	
continue		 create_reserved_word_node(yytext, CONTINUE); return CONTINUE;
long    		 create_reserved_word_node(yytext, LONG); return LONG;	
while				 create_reserved_word_node(yytext, WHILE); return WHILE;

{identifier}	{
	create_identifier_node(yytext);
	return IDENTIFIER;
}
{number} {
	create_number_node(yytext);
	int type = yylval->data.number->type;
	return type;
}
{string} {
	create_string_node(yytext);
	return STRING_CONST;
}
{char_const}	{
	create_char_node(yytext);
	return INTEGER_CONST;
}

"!"                    	 return	LOGICAL_NOT;
"\|\|"                    	 return	LOGICAL_OR;
"&&"                   	 return	LOGICAL_AND;
"^"                    	 return	BITWISE_XOR;
"&"                    	 return	AMPERSAND;
"\|"                     	 return	BITWISE_OR;
"~"             	 return	BITWISE_COMPLEMENT;
"=="                      	 return	IS_EQUAL;
"!="                  	 return	IS_NOT_EQUAL;
"<"                      	 return	LESS_THAN;
">"                   	 return	GREATER_THAN;
"<="            	 return	LESS_THAN_OR_EQUAL;
">="         	 return	GREATER_THAN_OR_EQUAL;
"="                         	 return	ASSIGN;
"+="                	 return	ADD_AND_ASSIGN;
"-="           	 return	SUBTRACT_AND_ASSIGN;
"*="           	 return	MULTIPLY_AND_ASSIGN;
"/="             	 return	DIVIDE_AND_ASSIGN;
"%="          	 return	REMAINDER_AND_ASSIGN;
"&="        	 return	BITWISE_AND_AND_ASSIGN;
"|="         	return	BITWISE_OR_AND_ASSIGN;
"^="        	return	BITWISE_XOR_AND_ASSIGN;
">>="     	 return	BITSHIFT_LEFT_AND_ASSIGN;
"<<="    return	BITSHIFT_RIGHT_AND_ASSIGN;
"+"                           	 return	PLUS;
"-"                          	 return	DASH;
"*"                       	 return	STAR;
"/"                         	 return	SLASH;
"%"                      	 return	REMAINDER;
"++"                  	 return	INCREMENT;
"--"                  	 return	DECREMENT;
">>"                 	 return	BITSHIFT_LEFT;
"<<"                	 return	BITSHIFT_RIGHT;
"?"	                	 return	QUESTION_MARK;

"("                          return LEFT_PAREN;
")"                         return RIGHT_PAREN;
"["                        return LEFT_BRACKET;
"]"                       return RIGHT_BRACKET;
"{"                    return LEFT_CURLY_BRACE;
"}"                   return RIGHT_CURLY_BRACE;
","                               return COMMA;
";"                           return SEMICOLON;
":"                               return COLON;

.	return -1;

%%

/*
	create_num: read the numeric value of input containing a number, classify the number as int or long, creates a struct containing the number's value and type, and set yylval to the struct

	Parameters:
		yytext: string, contains the raw input read by lex
	Return: none
  Side effects: set global variable yylval to newly created struct number

*/

void create_number_node(char *yytext) {
	node *num = malloc(sizeof(*num));
	assert(num != NULL);                   
	num->node_type = NUMBER_NODE;
	num->data.number = malloc(sizeof(number));
	assert(num->data.number != NULL);
	num->data.number->value = strtoul(yytext, NULL, 10);
	unsigned long int ul_limit = 4294967295UL;
	unsigned long int int_limit = 2147483647UL;
	unsigned long int value = num->data.number->value;
	if (value <= int_limit)
		num->data.number->type = INTEGER_CONST;    
 	else if (value <= ul_limit)
		num->data.number->type = UNSIGNED_LONG_CONST;    
	else { /* overflow */
		num->data.number->value = ul_limit;
		num->data.number->type = UNSIGNED_LONG_CONST;    
		num->data.number->overflow = 1;
	}
	yylval = num;
}     

/*
	create_string_node: create a string node containing the value of the string token, then point yylval to the created string node
	Parameters: none
	Return: none
  Side effects: set global variable yylval to newly created string node
*/

void create_string_node(char *yytext) {
	node *string = malloc(sizeof(*string));
	assert(string != NULL);
	string->node_type = STRING_NODE;
	string->data.string = malloc(sizeof(*string->data.string));
	string->data.string->value = strdup(yytext);
	assert(string->data.string->value != NULL);
	yylval = string;
}

void create_char_node(char *yytext) { // yytext = "'\127'"
	node *char_node = malloc(sizeof(*char_node));
	assert(char_node != NULL);
	char_node->node_type = NUMBER_NODE;
	char_node->data.number = malloc(sizeof(*char_node->data.number));
	char_node->data.number->value = (int)yytext[1];
	char_node->data.number->type = INTEGER_CONST;
	yylval = char_node;
}

void create_identifier_node(char *yytext) {
	node *identifier = malloc(sizeof(*identifier));
	assert(identifier != NULL);
	identifier->node_type = IDENTIFIER_NODE;
	identifier->data.identifier = malloc(sizeof(*identifier->data.identifier));
	identifier->data.identifier->name = strdup(yytext);
	assert(identifier->data.identifier->name != NULL);
	yylval = identifier;
}
void create_reserved_word_node(char *yytext, int value) {
	node *reserved_word = malloc(sizeof(*reserved_word));
	assert(reserved_word != NULL);
	reserved_word->node_type = RESERVED_WORD_NODE;
	reserved_word->data.reserved_word = malloc(sizeof(*reserved_word->data.reserved_word));
	reserved_word->data.reserved_word->text = strdup(yytext);
	assert(reserved_word->data.reserved_word->text != NULL);
	reserved_word->data.reserved_word->value = value;
	yylval = reserved_word;
}