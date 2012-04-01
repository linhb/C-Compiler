%option noyywrap
%option yylineno
%option nounput

%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <assert.h>
	#include "node.h"

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

do 					 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, DO); return DO;	
for     		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, FOR); return FOR;	
return  		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, RETURN); return RETURN;	
break   		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, BREAK); return BREAK;	
short   		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, SHORT); return SHORT;	
else    		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, ELSE); return ELSE;	
goto    		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, GOTO); return GOTO;	
signed  		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, SIGNED); return SIGNED;	
unsigned		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, UNSIGNED); return UNSIGNED;	
char    		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, CHAR); return CHAR;	
if 					 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, IF); return IF;	
void    		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, VOID); return VOID;	
int     		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, INT); return INT;	
continue		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, CONTINUE); return CONTINUE;
long    		 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, LONG); return LONG;	
while				 printf("*********creating reserved_word node\n"); yylval = create_reserved_word_node(yytext, WHILE); return WHILE;

{identifier}	{
	printf("*********creating identifier node %s\n", yytext); yylval = create_identifier_node(yytext);
	return IDENTIFIER;
}
{number} {
	create_number_node(yytext);
	printf("*********creating number node %s\n", yytext); 
	int type = yylval->data.number->type;
	return type;
}
{string} {
	printf("*********creating string node\n"); yylval = create_string_node(yytext);
	return STRING_CONST;
}
{char_const}	{
	printf("*********creating char node\n"); yylval = create_char_node(yytext);
	return INTEGER_CONST;
}

"!"                    	 printf("*********creating operator node\n"); yylval = create_operator_node(yytext, LOGICAL_NOT); return	LOGICAL_NOT;
"\|\|" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, LOGICAL_OR); return LOGICAL_OR;
"&&" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, LOGICAL_AND); return LOGICAL_AND;
"^" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITWISE_XOR); return BITWISE_XOR;
"&" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, AMPERSAND); return AMPERSAND;
"\|" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITWISE_OR); return BITWISE_OR;
"~" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITWISE_COMPLEMENT); return BITWISE_COMPLEMENT;
"==" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, IS_EQUAL); return IS_EQUAL;
"!=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, IS_NOT_EQUAL); return IS_NOT_EQUAL;
"<" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, LESS_THAN); return LESS_THAN;
">" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, GREATER_THAN); return GREATER_THAN;
"<=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, LESS_THAN_OR_EQUAL); return LESS_THAN_OR_EQUAL;
">=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, GREATER_THAN_OR_EQUAL); return GREATER_THAN_OR_EQUAL;
"=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, ASSIGN); return ASSIGN;
"+=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, ADD_AND_ASSIGN); return ADD_AND_ASSIGN;
"-=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, SUBTRACT_AND_ASSIGN); return SUBTRACT_AND_ASSIGN;
"*=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, MULTIPLY_AND_ASSIGN); return MULTIPLY_AND_ASSIGN;
"/=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, DIVIDE_AND_ASSIGN); return DIVIDE_AND_ASSIGN;
"%=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, REMAINDER_AND_ASSIGN); return REMAINDER_AND_ASSIGN;
"&=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITWISE_AND_AND_ASSIGN); return BITWISE_AND_AND_ASSIGN;
"|=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITWISE_OR_AND_ASSIGN); return BITWISE_OR_AND_ASSIGN;
"^=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITWISE_XOR_AND_ASSIGN); return BITWISE_XOR_AND_ASSIGN;
">>=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITSHIFT_LEFT_AND_ASSIGN); return BITSHIFT_LEFT_AND_ASSIGN;
"<<=" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITSHIFT_RIGHT_AND_ASSIGN); return BITSHIFT_RIGHT_AND_ASSIGN;
"+" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, PLUS); return PLUS;
"-" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, DASH); return DASH;
"*" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, STAR); return STAR;
"/" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, SLASH); return SLASH;
"%" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, REMAINDER); return REMAINDER;
"++" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, INCREMENT); return INCREMENT;
"--" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, DECREMENT); return DECREMENT;
">>" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITSHIFT_LEFT); return BITSHIFT_LEFT;
"<<" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, BITSHIFT_RIGHT); return BITSHIFT_RIGHT;
"?" printf("*********creating operator node\n"); yylval = create_operator_node(yytext, QUESTION_MARK); return QUESTION_MARK;

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