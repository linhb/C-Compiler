all:
	lex lexer.l
	yacc -td parser.y
	gcc y.tab.c -c
	gcc -Wall -c -g -std=c99 node.c parser_main.c
	gcc -Wall y.tab.o node.o parser_main.o -ly -lfl -o compiler

clean:
	-rm -f lexer lex.yy.c lex.yy.o y.tab.c compiler node.o parser_main.o y.tab.o y.output y.tab.h
