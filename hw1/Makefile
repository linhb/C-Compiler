all:
	lex lexer.l
	gcc lex.yy.c -c
	gcc -pedantic -std=c99 -Wall lex.yy.o lexer_main.c -lfl -o lexer -g

clean:
	-rm -f lexer lex.yy.c