%{
	#include <stdio.h>
	
	struct node {
		char *type;
		char *operator;
		struct node *left, *right;
		int value;
	}
%}

%token DO FOR RETURN BREAK SHORT ELSE GOTO SIGNED UNSIGNED CHAR IF VOID INT CONTINUE LONG WHILE 

%%
unsigned_type_specifier : UNSIGNED SHORT INT |
 UNSIGNED INT |
 UNSIGNED LONG INT     
;

void_type_specifier : VOID 
;

%%

#include <stdio.h>
#include "lex.yy.c"

main() {
	return yyparse();
}