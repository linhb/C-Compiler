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
void create_operator_node(char *yytext, int value);
char *escape_string(char *yytext);

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

do 					 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, DO); return DO;	
for     		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, FOR); return FOR;	
return  		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, RETURN); return RETURN;	
break   		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, BREAK); return BREAK;	
short   		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, SHORT); return SHORT;	
else    		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, ELSE); return ELSE;	
goto    		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, GOTO); return GOTO;	
signed  		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, SIGNED); return SIGNED;	
unsigned		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, UNSIGNED); return UNSIGNED;	
char    		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, CHAR); return CHAR;	
if 					 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, IF); return IF;	
void    		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, VOID); return VOID;	
int     		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, INT); return INT;	
continue		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, CONTINUE); return CONTINUE;
long    		 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, LONG); return LONG;	
while				 printf("*********creating reserved_word node\n"); create_reserved_word_node(yytext, WHILE); return WHILE;

{identifier}	{
	printf("*********creating identifier node\n"); create_identifier_node(yytext);
	return IDENTIFIER;
}
{number} {
	printf("*********creating number node\n"); create_number_node(yytext);
	int type = yylval->data.number->type;
	return type;
}
{string} {
	printf("*********creating string node\n"); create_string_node(yytext);
	return STRING_CONST;
}
{char_const}	{
	printf("*********creating char node\n"); create_char_node(yytext);
	return INTEGER_CONST;
}

"!"                    	 printf("*********creating operator node\n"); create_operator_node(yytext, LOGICAL_NOT); return	LOGICAL_NOT;
"\|\|" printf("*********creating operator node\n"); create_operator_node(yytext, LOGICAL_OR); return LOGICAL_OR;
"&&" printf("*********creating operator node\n"); create_operator_node(yytext, LOGICAL_AND); return LOGICAL_AND;
"^" printf("*********creating operator node\n"); create_operator_node(yytext, BITWISE_XOR); return BITWISE_XOR;
"&" printf("*********creating operator node\n"); create_operator_node(yytext, AMPERSAND); return AMPERSAND;
"\|" printf("*********creating operator node\n"); create_operator_node(yytext, BITWISE_OR); return BITWISE_OR;
"~" printf("*********creating operator node\n"); create_operator_node(yytext, BITWISE_COMPLEMENT); return BITWISE_COMPLEMENT;
"==" printf("*********creating operator node\n"); create_operator_node(yytext, IS_EQUAL); return IS_EQUAL;
"!=" printf("*********creating operator node\n"); create_operator_node(yytext, IS_NOT_EQUAL); return IS_NOT_EQUAL;
"<" printf("*********creating operator node\n"); create_operator_node(yytext, LESS_THAN); return LESS_THAN;
">" printf("*********creating operator node\n"); create_operator_node(yytext, GREATER_THAN); return GREATER_THAN;
"<=" printf("*********creating operator node\n"); create_operator_node(yytext, LESS_THAN_OR_EQUAL); return LESS_THAN_OR_EQUAL;
">=" printf("*********creating operator node\n"); create_operator_node(yytext, GREATER_THAN_OR_EQUAL); return GREATER_THAN_OR_EQUAL;
"=" printf("*********creating operator node\n"); create_operator_node(yytext, ASSIGN); return ASSIGN;
"+=" printf("*********creating operator node\n"); create_operator_node(yytext, ADD_AND_ASSIGN); return ADD_AND_ASSIGN;
"-=" printf("*********creating operator node\n"); create_operator_node(yytext, SUBTRACT_AND_ASSIGN); return SUBTRACT_AND_ASSIGN;
"*=" printf("*********creating operator node\n"); create_operator_node(yytext, MULTIPLY_AND_ASSIGN); return MULTIPLY_AND_ASSIGN;
"/=" printf("*********creating operator node\n"); create_operator_node(yytext, DIVIDE_AND_ASSIGN); return DIVIDE_AND_ASSIGN;
"%=" printf("*********creating operator node\n"); create_operator_node(yytext, REMAINDER_AND_ASSIGN); return REMAINDER_AND_ASSIGN;
"&=" printf("*********creating operator node\n"); create_operator_node(yytext, BITWISE_AND_AND_ASSIGN); return BITWISE_AND_AND_ASSIGN;
"|=" printf("*********creating operator node\n"); create_operator_node(yytext, BITWISE_OR_AND_ASSIGN); return BITWISE_OR_AND_ASSIGN;
"^=" printf("*********creating operator node\n"); create_operator_node(yytext, BITWISE_XOR_AND_ASSIGN); return BITWISE_XOR_AND_ASSIGN;
">>=" printf("*********creating operator node\n"); create_operator_node(yytext, BITSHIFT_LEFT_AND_ASSIGN); return BITSHIFT_LEFT_AND_ASSIGN;
"<<=" printf("*********creating operator node\n"); create_operator_node(yytext, BITSHIFT_RIGHT_AND_ASSIGN); return BITSHIFT_RIGHT_AND_ASSIGN;
"+" printf("*********creating operator node\n"); create_operator_node(yytext, PLUS); return PLUS;
"-" printf("*********creating operator node\n"); create_operator_node(yytext, DASH); return DASH;
"*" printf("*********creating operator node\n"); create_operator_node(yytext, STAR); return STAR;
"/" printf("*********creating operator node\n"); create_operator_node(yytext, SLASH); return SLASH;
"%" printf("*********creating operator node\n"); create_operator_node(yytext, REMAINDER); return REMAINDER;
"++" printf("*********creating operator node\n"); create_operator_node(yytext, INCREMENT); return INCREMENT;
"--" printf("*********creating operator node\n"); create_operator_node(yytext, DECREMENT); return DECREMENT;
">>" printf("*********creating operator node\n"); create_operator_node(yytext, BITSHIFT_LEFT); return BITSHIFT_LEFT;
"<<" printf("*********creating operator node\n"); create_operator_node(yytext, BITSHIFT_RIGHT); return BITSHIFT_RIGHT;
"?" printf("*********creating operator node\n"); create_operator_node(yytext, QUESTION_MARK); return QUESTION_MARK;

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
	num->data.number->is_char = 0;
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
	string->data.string->value = escape_string(yytext);
	assert(string->data.string->value != NULL);
	string->data.string->length = strlen(string->data.string->value);
	yylval = string;
}

void create_char_node(char *yytext) { // yytext = "'\127'"
	node *char_node = malloc(sizeof(*char_node));
	assert(char_node != NULL);
	char_node->node_type = NUMBER_NODE;
	char_node->data.number = malloc(sizeof(*char_node->data.number));
	// extract the escape sequence from yytext with escape_string, then extract the integer value and assign it to value
	char_node->data.number->value = escape_string(yytext)[0];
	char_node->data.number->type = INTEGER_CONST;
	char_node->data.number->is_char = 1;
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
void create_operator_node(char *yytext, int value) {
	node *operator = malloc(sizeof(*operator));
	assert(operator != NULL);
	operator->node_type = OPERATOR_NODE;
	operator->data.operator = malloc(sizeof(*operator->data.operator));
	operator->data.operator->text = strdup(yytext);
	assert(operator->data.operator->text != NULL);
	operator->data.operator->value = value;
	yylval = operator;
}
char *escape_string(char *yytext) {
	int yytext_size = strlen(yytext);
	/* this will end up malloc'ing more memory than needed if yytext contains escape sequences, because something like \n that takes up 2 chars in yytext will only take up 1 char in string */
	char *string = malloc(yytext_size);
	int i;  // index of current char in yytext
	int j = 0; // index of char being written to in string
	for (i = 1; i < yytext_size - 1; j++) {  // start at 1 and end 1 char short of the actual end to get rid of the single/double quotes
		if (yytext[i] == '\\') {
			if (yytext[i+1] == 'n') {
				string[j] = '\n';
				// advance current char by 2 because two chars in yytext have just been processed at once
				i = i + 2;
			}
			else if (yytext[i+1] == 't') {
				string[j] = '\t';
				i = i + 2;
			}			
			else if (yytext[i+1] == 'b') {
				string[j] = '\b';
				i = i + 2;
			}
			else if (yytext[i+1] == 'r') {
				string[j] = '\r';
				i = i + 2;
			}
			else if (yytext[i+1] == 'f') {
				string[j] = '\f';
				i = i + 2;
			}
			else if (yytext[i+1] == 'v') {
				string[j] = '\v';
				i = i + 2;
			}
			else if (yytext[i+1] == 'a') {
				string[j] = '\a';
				i = i + 2;
			}
			else if (yytext[i+1] == '\\') {
				string[j] = '\\';
				i = i + 2;
			}
			else if (yytext[i+1] == '\'') {
				string[j] = '\'';
				i = i + 2;
			}
			else if (yytext[i+1] == '\"') {
				string[j] = '\"';
				i = i + 2;
			}
			else if (yytext[i+1] == '0') {
				string[j] = '\0';
				i = i + 2;
			}
			else if (yytext[i+1] == '?') {
				string[j] = '?';
				i = i + 2;
			}
			else if (yytext[i+1] >= '0' && yytext[i+1] <= '7') {
				int value = strtoul(&yytext[i+1], NULL, 8);
				if (value <= 7) {
					string[j] = value;
					i = i + 2;
				}
					// values from 8 (010) to 63 (077) take up 3 chars, so advance by 3
				else if (value <= 63) {
					string[j] = value;
					i = i + 3;
				}
				else if (value <= 255) {
					string[j] = value;
					i = i + 4;
				}
				else
					i = i + 4;					
			}
			else // invalid escape code, ignore the \ and the character that follows, move on
				i = i + 2;
		}
		else {
			string[j] = yytext[i];
			i++;
		}
	}
	return string;
}