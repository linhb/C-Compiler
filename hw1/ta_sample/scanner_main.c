#include <stdio.h>
#include <string.h>

#include "scanner_tokens.h"

int yylex();
extern char *yytext;
extern int yyleng;
extern FILE *yyin;
extern int yylineno;

void *yylval;

const char *token_names[100];

/*
*  main - the entry point for assignment one. reads input from either stdin or a file specified on the command line. 
*          writes output to stdout or a file specified on the command line. after each call to yylex(), decodes the
*          name of the returned token, or prints an error if no token was found, or exits if the input stream has ended.
*          prints the current line number, name of the token, and other information depending on the type of the returned 
*          token.
*
*  Arguments:
*    first argument specifies the input file. if it is not provided or is equal to "-", input file is assumed to be
*      stdin.
*    second argument specifies the output file. if it is not provided or is equal to "-", output file is assumed to be
*      stdout.
*
*  Exit values:
*    0 for normal
*    1 for out of memory
*
*/
int main(int argc, char **argv) {
  FILE *input, *output;

  int token;
  char name[MAX_NAME_SIZE];

  struct number *number;
  char *id;

  /* figure out whether we're using stdin/stdout or file in/file out */
  if (argc < 2 || !strcmp("-", argv[1])) { // if there's fewer than 2 arguments, it must be just the program name and nothing else. 
    input = stdin;
  } else {
    input = fopen(argv[1], "r");
  }

  if (argc < 3 || !strcmp("-", argv[2])) { // if <3 arguments, no output file was given
    output = stdout;
  } else {
    output = fopen(argv[2], "w");
  }

  /* tell lex where to get input */
  yyin = input;

  /* set up the mappings from number -> name */
  init_names(); //from scanner_tokens.c, copies the numbers associated with each kind of token into an array token_names, so that eg token_names[42] = 42 which corresponds to SLASH. The numbers are from  scanner_tokens.h

  /* begin scanning */
  for (token = yylex(); 0 != token; token = yylex()) { // lex will supply the yylex function

    /* print the line number. use printf formatting and tabs to keep columns lined up */
    fprintf(output, "line = %-5d\t", yylineno);

    /* print the scanned text. try to use formatting but give up instead of truncating if the text is too long. */
    fprintf(output, (yyleng < 20 ? "text = %-20s\t" : "text = %s\t"), yytext);

    if (token > 0) {
      /* found a token */

      /* look up and print the token's name */
      get_token_name(name, token);
      fprintf(output, "token = %-15s\t", name);

      /* print information about the token */
      switch (token) { // when the token was fetched with yylex, whatever code was associated with its name in scanner.l was executed, so if yylval needed to be set it was set at that point
        case CHAR:
        case INT:
        case LONG:
        case RETURN:
        case SHORT:
        case SIGNED:
        case UNSIGNED:
          fprintf(output, " rsvwd = %-20s\n", name);
          break;

        case ASTERISK:
        case MINUS:
        case PLUS:
        case EQUALS:
        case SLASH:
        case LEFT_PAREN:
        case RIGHT_PAREN:
        case SEMICOLON:
          fprintf(output, "    op = %-20s\n", name);
          break;

        case NUMBER:
          number = (struct number *)yylval;

            /* print the type and value */
          fprintf(output, "  type = %8s %-12s\tvalue = %-10lu\n", 
            "UNSIGNED",
            "LONG", 
            number->value);

            /* this might be a good place to indicate overflow if it happened */
          break;

        case IDENTIFIER:
          id = (char *)yylval;
          if (NULL != id) {
              /* print the identifier name as copied from the source file */
            fprintf(output, "    id = %s\n", id);            

          } else {
              /* couldn't allocate memory */
            fputs("error = OUT_OF_MEMORY\n", output);
            return 1;
          }
        break;

      }

    } else {
      /* scanning error, unrecognized character */
      fputs("error = SCANNING_ERROR\n", output);
    }
  }
  /* scanning complete */

  if (output != stdout) {
    fclose(output);
  }
  if (input != stdin) {
    fclose(input);
  }

  return 0;
}

