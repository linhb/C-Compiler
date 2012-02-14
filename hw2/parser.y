%{
	#include <stdio.h>
%}

%token IDENTIFIER
%token PLUS

%%
expr	:		IDENTIFIER PLUS IDENTIFIER	{printf("matched!\n");}
;
%%

#include <stdio.h>
#include "lex.yy.c"

main() {
	return yyparse();
}