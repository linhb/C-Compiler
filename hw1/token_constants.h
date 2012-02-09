// reserved words
#define          	DO               	1
#define          	FOR              	2
#define          	RETURN           	3
#define          	BREAK            	4
#define          	SHORT            	5
#define          	ELSE             	6
#define          	GOTO             	7
#define          	SIGNED           	8
#define          	UNSIGNED         	9
#define          	CHAR             	10
#define          	IF               	11
#define          	VOID             	12
#define          	INT              	13
#define          	CONTINUE         	14
#define          	LONG             	15
#define          	WHILE            	16
//constants
#define          	NUM_CONST        	17
#define          	STRING_CONST     	18
#define          	CHAR_CONST       	19
//identifier
#define          	IDENTIFIER       	20
//operators
#define          	LOGICAL_OP       	21
#define          	BITWISE_OP       	22
#define          	COMPARISON_OP    	23
#define          	ASSIGNMENT_OP    	24
#define          	ARITHMETIC_OP    	25
#define          	BITSHIFT_OP      	26
//separators
#define          	LEFT_PAREN       	27
#define          	RIGHT_PAREN      	28
#define          	LEFT_BRACKET     	29
#define          	RIGHT_BRACKET    	30
#define          	LEFT_CURLY_BRACE 	31
#define          	RIGHT_CURLY_BRACE	32
#define          	COMMA            	33
#define          	SEMICOLON        	34
#define          	COLON            	35

#define ADD_TOKEN_NAME(TOKEN_NAMES, TOKEN) TOKEN_NAMES[TOKEN] = #TOKEN
#define ADD_OPERATOR_NAME(OPERATOR_NAMES, OP) OPERATOR_NAMES[OP] = #OP

const char *token_names[100];
const char *operator_names[100];

#define	LOGICAL_NOT              	1
#define	LOGICAL_OR               	2
#define	LOGICAL_AND              	3

#define	BITWISE_XOR              	5
#define	BITWISE_AND              	6
#define	BITWISE_OR               	7
#define	BITWISE_COMPLEMENT       	8

#define	IS_EQUAL                 	9
#define	IS_NOT_EQUAL             	10
#define	LESS_THAN                	11
#define	GREATER_THAN             	12
#define	LESS_THAN_OR_EQUAL       	13
#define	GREATER_THAN_OR_EQUAL    	14

#define	ASSIGN                   	15
#define	ADD_AND_ASSIGN           	16
#define	SUBTRACT_AND_ASSIGN      	17
#define	MULTIPLY_AND_ASSIGN      	18
#define	DIVIDE_AND_ASSIGN        	19
#define	REMAINDER_AND_ASSIGN     	20
#define	BITWISE_AND_AND_ASSIGN   	21
#define	BITWISE_OR_AND_ASSIGN    	22
#define	BITWISE_XOR_AND_ASSIGN   	23
#define	BITSHIFT_LEFT_AND_ASSIGN 	24
#define	BITSHIFT_RIGHT_AND_ASSIGN	25

#define	PLUS                     	26
#define	DASH                    	27
#define	MULTIPLY                 	28
#define	DIVIDE                   	29
#define	REMAINDER                	30
#define	PREINCREMENT             	31
#define	PREDECREMENT             	32
#define	POSTINCREMENT            	33
#define	POSTDECREMENT            	34

#define	BITSHIFT_LEFT            	36
#define	BITSHIFT_RIGHT           	37

struct number {
	unsigned long value;
};
