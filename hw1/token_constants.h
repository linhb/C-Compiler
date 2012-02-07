// reserved words
#define	DO	1
#define	FOR	2
#define	RETURN	3
#define	BREAK	4
#define	SHORT	5
#define	ELSE	6
#define	GOTO	7
#define	SIGNED	8
#define	UNSIGNED	9
#define	CHAR	10
#define	IF	11
#define	VOID	12
#define	INT	13
#define	CONTINUE	14
#define	LONG	15
#define	WHILE	16

//constants
#define NUM_CONST 17
#define STRING_CONST 18
#define CHAR_CONST 19

#define ADD_TOKEN_NAME(TOKEN_NAMES, TOKEN) TOKEN_NAMES[TOKEN] = #TOKEN
const char *token_names[100];

struct number {
	unsigned long value;
};
