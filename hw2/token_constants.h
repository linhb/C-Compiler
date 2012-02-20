/*
This file defines the numbers that stand for each type of token returned by yylex().
*/

/*  reserved words */
#define DO                       	1
#define FOR                      	2
#define RETURN                   	3
#define BREAK                    	4
#define SHORT                    	5
#define ELSE                     	6
#define GOTO                     	7
#define SIGNED                   	8
#define UNSIGNED                 	9
#define CHAR                     	10
#define IF                       	11
#define VOID                     	12
#define INT                      	13
#define CONTINUE                 	14
#define LONG                     	15
#define WHILE                    	16
/* constants */
#define INTEGER_CONST            	17
#define SHORT_CONST              	66
#define UNSIGNED_LONG_CONST               	67
#define STRING_CONST             	18
#define CHAR_CONST               	19
/* identifier */
#define IDENTIFIER               	20
/* operators */
#define LOGICAL_NOT              	21
#define LOGICAL_OR               	22
#define LOGICAL_AND              	23
#define BITWISE_XOR              	24
#define AMPERSAND                	25
#define BITWISE_OR               	26
#define BITWISE_COMPLEMENT       	27
#define IS_EQUAL                 	28
#define IS_NOT_EQUAL             	29
#define LESS_THAN                	30
#define GREATER_THAN             	31
#define LESS_THAN_OR_EQUAL       	32
#define GREATER_THAN_OR_EQUAL    	33
#define ASSIGN                   	34
#define ADD_AND_ASSIGN           	35
#define SUBTRACT_AND_ASSIGN      	36
#define MULTIPLY_AND_ASSIGN      	37
#define DIVIDE_AND_ASSIGN        	38
#define REMAINDER_AND_ASSIGN     	39
#define BITWISE_AND_AND_ASSIGN   	40
#define BITWISE_OR_AND_ASSIGN    	41
#define BITWISE_XOR_AND_ASSIGN   	42
#define BITSHIFT_LEFT_AND_ASSIGN 	43
#define BITSHIFT_RIGHT_AND_ASSIGN	44
#define PLUS                     	45
#define DASH                     	46
#define STAR                     	47
#define SLASH                    	48
#define REMAINDER                	49
#define PREINCREMENT             	50
#define PREDECREMENT             	51
#define POSTINCREMENT            	52
#define POSTDECREMENT            	53
#define BITSHIFT_LEFT            	54
#define BITSHIFT_RIGHT           	55
#define QUESTION_MARK            	65
/* separators */
#define LEFT_PAREN               	56
#define RIGHT_PAREN              	57
#define LEFT_BRACKET             	58
#define RIGHT_BRACKET            	59
#define LEFT_CURLY_BRACE         	60
#define RIGHT_CURLY_BRACE        	61
#define COMMA                    	62
#define SEMICOLON                	63
#define COLON                    	64

#define ERROR                    	68

/*
add the name of each token type to a global array, token_names, that yylex() uses to retrieve token names
*/

#define ADD_TOKEN_NAME(TOKEN_NAMES, TOKEN) TOKEN_NAMES[TOKEN] = #TOKEN

const char *token_names[100];

struct number {
	int type;
	unsigned long value;
	int overflow;
};