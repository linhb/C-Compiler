all:
	lex lexer.l
	yacc -t --report=state --debug parser.y
	gcc y.tab.c -c
	gcc -Wall y.tab.o node.c parser_main.c -ly -lfl -o parser

standalone:
	lex lexer-standalone.lex
	gcc lex.yy.c -c
	gcc -pedantic -Wall lex.yy.o lexer.c -lfl -o lexer

clean:
	-rm -f lexer lex.yy.c lex.yy.o y.tab.c parser
