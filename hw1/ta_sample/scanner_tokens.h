#ifndef _SCANNER_TOKENS_H
#define _SCANNER_TOKENS_H

/* tokens */ 
#define IDENTIFIER      1
#define NUMBER          2


/* reserved words */
#define CHAR      11
#define INT       18
#define LONG      19
#define RETURN    20
#define SHORT     21
#define SIGNED    22
#define UNSIGNED  23

/* operators */ 
#define ASTERISK        34
#define MINUS           36
#define PLUS            37
#define EQUALS          38
#define SLASH           42
                        
#define LEFT_PAREN      64
#define RIGHT_PAREN     65
                        
#define SEMICOLON       71

/* call init_token_names before calling get_token_name, because it sets up the mapping table */
void init_names();


#define MAX_NAME_SIZE   100

/* call get_token_name to find the name of a token, given its number */
void get_token_name(char *name, int token);
void get_reserved_word_name(char *name, int word);
void get_operator_name(char *name, int op);

struct number {
  unsigned long value;
  int overflow;
};

#endif
