CFLAGS += -g -Wall -Wextra

all:
	lex lexer.l
	gcc $(CFLAGS) lex.yy.c -c
	gcc $(CFLAGS) lex.yy.o lexer_main.c -lfl -o lexer

clean:
	-rm -f lexer lex.yy.c