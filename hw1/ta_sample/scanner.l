%option yylineno
%option nounput
%option noyywrap

%{
  /*
   * scanner.l
   *
   * This file contains the specification for the (f)lex generated scanner
   * for the CSCI-E295 source language. It also contains some helper routines
   * which create structures to be returned to the calling program. 
   *
   */
   
    #include <stdlib.h>
    #include <errno.h>
    #include <string.h>
    #include <assert.h>

    #include "scanner_tokens.h"
    
    #define YYSTYPE void *
    extern YYSTYPE yylval;    
    
    char *create_identifier(char *text, int length);
    
    struct number *create_number(char *text, int length);
%}

newline         \n
ws              [ \t\v\f]

digit           [[:digit:]]
letter          [[:alpha:]]
nondigit        {letter}|_

id              {nondigit}({nondigit}|{digit})*

number          {digit}+

%%

{newline}   /* do nothing; lex is counting lines */
{ws}        /* do nothing */

  /* reserved words begin */
char        return CHAR; 
int         return INT; 
long        return LONG; 
return      return RETURN; 
short       return SHORT; 
signed      return SIGNED; 
unsigned    return UNSIGNED;
  /* reserved words end */

  /* operators begin */
\*          return ASTERISK; 
\+          return PLUS; 
-           return MINUS; 
\/          return SLASH; 
\=          return EQUALS; 

\(          return LEFT_PAREN; 
\)          return RIGHT_PAREN; 

;           return SEMICOLON; 
  /* operators end */

  /* constants begin */
{number}    yylval = (YYSTYPE)create_number(yytext, yyleng); return NUMBER;
  /* constants end */

  /* identifiers */
{id}        yylval = (YYSTYPE)create_identifier(yytext, yyleng); return IDENTIFIER;

.           return -1;

%%

 /*
  * create_identifier - allocate memory and store the name of an identifier in it, for 
  *                     return to the calling program
  *
  * Parameters:
  *   text - string - contains the name of the identifier as matched in the source program
  *   length - integer - the length of text (not including terminating NUL)
  *
  * Returns:
  *   a NUL-terminated string in newly allocated memory, containing the text copied from the
  *   source program. returns NULL if memory could not be allocated.
  *
  * Side-effects:
  *   memory may be allocated on the heap.
  *
  */
char *create_identifier(char *text, int length) {
  char *id;

  id = (char *)malloc(sizeof(char) * (length + 1));
  assert(NULL != id);
  strcpy(id, text);
  return id;
}

 /*
  * create_number - read the value of a number from a string
  *
  * Parameters:
  *   text - string - contains the constant as matched in the source program
  *   length - integer - the length of text (not including terminating NUL)
  *
  * Returns:
  *   a struct number containing the value from text and an overflow indication
  *
  */
struct number *create_number(char *text, int length) {
  struct number *num;
  assert(length > 0);
  
  num = (struct number *)malloc(sizeof(struct number));
  assert(NULL != num);
  
  if ('\'' != text[0]) {
    /* integer constant */
    errno = 0;

    num->value = strtoul(text, NULL, 10);
  
    /* 
      you could do type checking of integer constants here, or defer it until a later assignment.
      NOTE that this example type checking code is not quite correct for our class language! (why not?)
    */
    if (ERANGE == errno || num->value > 4294967295ul) {
      /* integer constant was too large for unsigned long. value will be MAX_ULONG, as defined by strtoul */

      /* do something about overflow here! */

    } else if (num->value > 2147483647) {
      /* the value has type unsigned int */

    } else if (num->value > 32767) {
      /* the value has type signed int */

    } else {
      /* the value has type signed short */
    }
  }
  return num;
}