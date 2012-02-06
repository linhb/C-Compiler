#include <string.h>

#include "scanner_tokens.h"

const char *token_names[100];

/*
 * get_token_name - get the name of a token returned by yylex()
 *
 * Parameters:
 *  name - char * - token name will be copied here
 *  token - int - the token returned by yylex()
 * 
 * Return: none
 * Side effects: none
 *
 */
void get_token_name(char *name, int token) {
  strcpy(name, token_names[token]);
}

/* map enumerated types back to strings */
#define ADD_NAME(ARRAY, TOKEN) ARRAY[TOKEN] = #TOKEN

/* 
 * init_names - set up the mappings from enumerated values to strings for tokens, reserved words,
 *              operators, number types, and number errors. must be called before any get_*_name is called. 
 *
 * Parameters: none
 *
 * Return: none
 *
 * Side effects: the tables mapping enumerated values to strings are initialized, so that get_*_name methods above
 *                can be called.
 */
void init_names() {
  ADD_NAME(token_names, IDENTIFIER);
  ADD_NAME(token_names, NUMBER);
  
  ADD_NAME(token_names, CHAR);
  ADD_NAME(token_names, INT);
  ADD_NAME(token_names, LONG);
  ADD_NAME(token_names, SHORT);
  ADD_NAME(token_names, SIGNED);
  ADD_NAME(token_names, UNSIGNED);

  ADD_NAME(token_names, ASTERISK);
  ADD_NAME(token_names, MINUS);
  ADD_NAME(token_names, PLUS);
  ADD_NAME(token_names, EQUALS);
  ADD_NAME(token_names, SLASH);
  ADD_NAME(token_names, LEFT_PAREN);
  ADD_NAME(token_names, RIGHT_PAREN);
  ADD_NAME(token_names, SEMICOLON);
}
