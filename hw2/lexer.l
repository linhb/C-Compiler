%option noyywrap
%option yylineno
%option nounput

%{
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  #include <assert.h>

void create_num(char *yytext);
void create_value_string();

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

{identifier}	{
	create_value_string();
	return IDENTIFIER;
}

"+"                           	 return	PLUS;

.	return -1;

%%

/*
	create_num: read the numeric value of input containing a number, classify the number as int or long, creates a struct containing the number's value and type, and set yylval to the struct

	Parameters:
		yytext: string, contains the raw input read by lex
	Return: none
  Side effects: set global variable yylval to newly created struct number

*/

/*
	create_value_string: create a string containing the value of identifier, string and char tokens, then point yylval to the created string
	Parameters: none
	Return: none
  Side effects: set global variable yylval to newly created string
*/

void create_value_string() {
	yylval = strdup(yytext);
}