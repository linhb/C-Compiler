all:
	lex lexer.l
	yacc -td parser.y
	gcc y.tab.c -c
	gcc -Wall y.tab.o -g node.c parser_main.c -ly -lfl -o parser

clean:
	-rm -f lexer lex.yy.c lex.yy.o y.tab.c parser
