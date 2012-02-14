%{
	#include <stdio.h>
%}

%token ID
%token PLUS

%%
expr	:		ID PLUS ID	{printf("matched!\n");}
;
%%

#include <stdio.h>
#include "lex.yy.c"

main() {
	return yyparse();
}