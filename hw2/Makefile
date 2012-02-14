all:
	lex lexer.l
	yacc parser.y
	gcc y.tab.c -ly -lfl -o parser

standalone:
	lex lexer-standalone.lex
	gcc lex.yy.c -c
	gcc -pedantic -Wall lex.yy.o lexer.c -lfl -o lexer

clean:
	-rm -f lexer lex.yy.c lex.yy.o y.tab.c parser
