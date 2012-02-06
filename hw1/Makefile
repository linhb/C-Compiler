all:
	lex lexer.l
	gcc lex.yy.c -c
	gcc -pedantic -Wall lex.yy.o lexer_main.c -lfl -o lexer -g

clean:
	-rm -f lexer lex.yy.c