%verbose
%error-verbose

%{
	#include <stdio.h>
	#include <assert.h>
	#include "node.h"
	
	#define YYSTYPE node *
	int yylex();
	extern int yylineno;
  void yyerror(char const *s);
	extern node *root;
	int yydebug = 0;   

%}
%token DO FOR RETURN BREAK SHORT ELSE GOTO SIGNED UNSIGNED CHAR IF VOID INT CONTINUE LONG WHILE 
%token IDENTIFIER STRING_CONST NUMBER
%token LEFT_CURLY_BRACE RIGHT_CURLY_BRACE COMMA SEMICOLON COLON 
%token LEFT_BRACKET RIGHT_BRACKET
%token LEFT_PAREN RIGHT_PAREN
%token INCREMENT DECREMENT // unary operations
%token BITWISE_COMPLEMENT // unary
%token LOGICAL_NOT // unary
%token PLUS DASH   // unary/binary
%token AMPERSAND // unary
%token STAR // unary
%token SLASH REMAINDER // binary
%token BITSHIFT_LEFT BITSHIFT_RIGHT // binary
%token LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL // binary
%token IS_EQUAL IS_NOT_EQUAL // binary
%token BITWISE_XOR // binary
%token BITWISE_OR // binary
%token LOGICAL_AND // binary
%token LOGICAL_OR         // binary
%token QUESTION_MARK // ternary
%token ASSIGN ADD_AND_ASSIGN SUBTRACT_AND_ASSIGN MULTIPLY_AND_ASSIGN DIVIDE_AND_ASSIGN REMAINDER_AND_ASSIGN BITWISE_AND_AND_ASSIGN BITWISE_OR_AND_ASSIGN BITWISE_XOR_AND_ASSIGN BITSHIFT_LEFT_AND_ASSIGN BITSHIFT_RIGHT_AND_ASSIGN        // binary
%expect 1
%start root

%%
root : translation_unit {root = $1; assert (root != NULL);}
;
translation_unit : top_level_decl        
 | translation_unit top_level_decl       {printf("*********creating translation_unit node\n"); $$ = create_translation_unit_node($1, $2);}
;
top_level_decl : decl 
 | function_definition 
;
decl : declaration_specifiers initialized_declarator_list SEMICOLON 
	{
		printf("*********creating decl node\n"); $$ = create_decl_node($1, $2);
  }
;
function_definition : function_def_specifier compound_statement    {printf("*********creating function_definition node\n"); $$ = create_function_definition_node($1, $2);}
;
compound_statement : LEFT_CURLY_BRACE declaration_or_statement_list RIGHT_CURLY_BRACE   {printf("*********creating compound_statement node\n"); $$ = create_compound_statement_node($2);}
 | LEFT_CURLY_BRACE RIGHT_CURLY_BRACE {printf("*********creating compound_statement node\n"); $$ = create_compound_statement_node(NULL);}
;
declaration_or_statement_list : declaration_or_statement       
	| declaration_or_statement_list declaration_or_statement   {printf("*********creating declaration_or_statement_list node\n"); $$ = create_declaration_or_statement_list_node($1, $2);}
;
declaration_or_statement : decl 
 | statement 
;
statement : expression_statement   {printf("*********creating statement node\n"); $$ = create_statement_node($1);}
 | labeled_statement                                       
 | compound_statement                                     
 | conditional_statement                                   
 | iterative_statement 
 | break_statement                 {printf("*********creating statement node\n"); $$ = create_statement_node($1);}
 | continue_statement              {printf("*********creating statement node\n"); $$ = create_statement_node($1);}
 | return_statement                {printf("*********creating statement node\n"); $$ = create_statement_node($1);}
 | goto_statement                  {printf("*********creating statement node\n"); $$ = create_statement_node($1);}
 | null_statement                  {printf("*********creating null_statement node\n"); $$ = create_null_statement_node();}
;
labeled_statement : label COLON statement                  {printf("*********creating labeled_statement node\n"); $$ = create_labeled_statement_node($1, $3);}
;
expression_statement : expr SEMICOLON                     
;
conditional_statement : if_statement 
 | if_else_statement 
;
iterative_statement : while_statement 
 | do_statement 
 | for_statement 
;
break_statement : BREAK SEMICOLON 
;
continue_statement : CONTINUE SEMICOLON 
;
return_statement : RETURN expr SEMICOLON                     {printf("*********creating reserved_word_statement node\n"); $$ = create_reserved_word_statement_node($1, $2);}
 | RETURN SEMICOLON                  {printf("*********creating reserved_word_statement node\n"); $$ = create_reserved_word_statement_node($1, NULL);}
;
goto_statement : GOTO named_label SEMICOLON                  {printf("*********creating reserved_word_statement node\n"); $$ = create_reserved_word_statement_node($1, $2);}
;
named_label : IDENTIFIER      // do something
;
null_statement : SEMICOLON 
;
label : named_label 
;
if_else_statement : IF LEFT_PAREN expr RIGHT_PAREN statement ELSE statement          {printf("*********creating if_else_statement node\n"); $$ = create_if_else_statement_node($3, $5, $7);}
;
if_statement : IF LEFT_PAREN expr RIGHT_PAREN statement          {printf("*********creating if_else_statement node\n"); $$ = create_if_else_statement_node($3, $5, NULL);}
;
while_statement : WHILE LEFT_PAREN expr RIGHT_PAREN statement{printf("*********creating while_statement node\n"); $$ = create_while_statement_node($3, $5);}
;
do_statement : DO statement WHILE LEFT_PAREN expr RIGHT_PAREN SEMICOLON              {printf("*********creating do_statement node\n"); $$ = create_do_statement_node($2, $5);}
;
for_statement : FOR for_expr statement            {printf("*********creating for_statement node\n"); $$ = create_for_statement_node($2, $3);}
;
for_expr : LEFT_PAREN initial_clause SEMICOLON expr SEMICOLON expr RIGHT_PAREN   {printf("*********creating for_expr node\n"); $$ = create_for_expr_node($2, $4, $6);}
 | LEFT_PAREN SEMICOLON expr SEMICOLON expr RIGHT_PAREN    {printf("*********creating for_expr node\n"); $$ = create_for_expr_node(NULL, $3, $5);}
 | LEFT_PAREN initial_clause SEMICOLON SEMICOLON expr RIGHT_PAREN    {printf("*********creating for_expr node\n"); $$ = create_for_expr_node($2, NULL, $5);}
 | LEFT_PAREN initial_clause SEMICOLON expr SEMICOLON RIGHT_PAREN    {printf("*********creating for_expr node\n"); $$ = create_for_expr_node($2, $4, NULL);}
 | LEFT_PAREN initial_clause SEMICOLON SEMICOLON RIGHT_PAREN    {printf("*********creating for_expr node\n"); $$ = create_for_expr_node($2, NULL, NULL);}
 | LEFT_PAREN SEMICOLON expr SEMICOLON RIGHT_PAREN    {printf("*********creating for_expr node\n"); $$ = create_for_expr_node($3, NULL, NULL);}
 | LEFT_PAREN SEMICOLON SEMICOLON expr RIGHT_PAREN    {printf("*********creating for_expr node\n"); $$ = create_for_expr_node(NULL, NULL, $4);}
 | LEFT_PAREN SEMICOLON SEMICOLON RIGHT_PAREN   {printf("*********creating for_expr node\n"); $$ = create_for_expr_node(NULL, NULL, NULL);}
;
initial_clause : expr 
 | decl 
;  
function_def_specifier : declaration_specifiers declarator         {printf("*********creating function_def_specifier node\n"); $$ = create_function_def_specifier_node($1, $2);
	}
 | declarator
 // | error SEMICOLON                                         {yyerrok; yyclearin; }
;
initialized_declarator : declarator 
;
declarator : pointer_decl 
 | direct_declarator 
;
// pointer : STAR                   
//  | STAR pointer                  {printf("*********creating pointer node\n"); $$ = create_pointer_node($2);}
// ;
pointer_decl : STAR direct_declarator                       {printf("*********creating pointer_decl node\n"); $$ = create_pointer_decl_node($1, $2);}
	| STAR pointer_decl 	{printf("*********creating pointer_decl node\n"); $$ = create_pointer_decl_node($1, $2);}
;
direct_declarator : simple_declarator 
	| LEFT_PAREN declarator RIGHT_PAREN     {$$ = $2;}
 | function_declarator 
 | array_declarator                 
;
simple_declarator : IDENTIFIER       // do something
;
function_declarator : direct_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN   {printf("*********creating function_declarator node\n"); $$ = create_function_declarator_node($1, $3);}
;
parameter_decl : declaration_specifiers declarator       {printf("*********creating parameter_decl node\n"); $$ = create_parameter_decl_node($1, $2);}
 | declaration_specifiers abstract_declarator  {printf("*********creating parameter_decl node\n"); $$ = create_parameter_decl_node($1, $2);}
 | declaration_specifiers
;
pointer_abstract_declarator : STAR direct_abstract_declarator       {printf("*********creating abstract_declarator node\n"); $$ = create_abstract_declarator_node($1, $2);}
;
abstract_declarator : STAR 
	| pointer_abstract_declarator
| STAR pointer_abstract_declarator       {printf("*********creating abstract_declarator node\n"); $$ = create_abstract_declarator_node($1, $2);}
 | direct_abstract_declarator
;
direct_abstract_declarator : LEFT_PAREN abstract_declarator RIGHT_PAREN      {printf("*********creating direct_abstract_declarator node\n"); $$ = create_direct_abstract_declarator_node($1, $2, $3, NULL);}
 | direct_abstract_declarator LEFT_BRACKET constant_expr RIGHT_BRACKET {printf("*********creating direct_abstract_declarator node\n"); $$ = create_direct_abstract_declarator_node($1, $2, $3, $4);}
 | LEFT_BRACKET constant_expr RIGHT_BRACKET {printf("*********creating direct_abstract_declarator node\n"); $$ = create_direct_abstract_declarator_node($1, $2, $3, NULL);}
 | direct_abstract_declarator LEFT_BRACKET RIGHT_BRACKET {printf("*********creating direct_abstract_declarator node\n"); $$ = create_direct_abstract_declarator_node($1, $2, $3, NULL);}
 | direct_abstract_declarator LEFT_PAREN parameter_type_list RIGHT_PAREN {printf("*********creating direct_abstract_declarator node\n"); $$ = create_direct_abstract_declarator_node($1, $2, $3, $4);}
 | LEFT_PAREN parameter_type_list RIGHT_PAREN {printf("*********creating direct_abstract_declarator node\n"); $$ = create_direct_abstract_declarator_node($1, $2, $3, NULL);}
 | direct_abstract_declarator LEFT_PAREN RIGHT_PAREN {printf("*********creating direct_abstract_declarator node\n"); $$ = create_direct_abstract_declarator_node($1, $2, $3, NULL);}
;
constant_expr : conditional_expr
;
parameter_list : parameter_decl               
	| parameter_list COMMA parameter_decl       {printf("*********creating parameter_list node\n"); $$ = create_parameter_list_node($1, $3);}
;
parameter_type_list : parameter_list 
;
array_declarator : direct_declarator LEFT_BRACKET constant_expr RIGHT_BRACKET  {printf("*********creating array_declarator node\n"); $$ = create_array_declarator_node($1, $3);}
| direct_declarator LEFT_BRACKET RIGHT_BRACKET         {printf("*********creating array_declarator node\n"); $$ = create_array_declarator_node($1, NULL);}
;
initialized_declarator_list : initialized_declarator             {printf("*********creating initialized_declarator_list node\n"); $$ = create_initialized_declarator_list_node(NULL, $1);}
	| initialized_declarator_list COMMA initialized_declarator     {printf("*********creating initialized_declarator_list node\n"); $$ = create_initialized_declarator_list_node($1, $3);}
;                                
expression_list : assignment_expr |
	assignment_expr COMMA expression_list          {printf("*********creating expression_list node\n"); $$ = create_expression_list_node($1, $3);}
;
expr : comma_expr 
;
comma_expr : assignment_expr 
	| comma_expr COMMA assignment_expr                       {printf("*********creating comma_expr node\n"); $$ = create_comma_expr_node($1, $3);}
;
assignment_expr : conditional_expr 
 | unary_expr assignment_op assignment_expr                       {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
assignment_op : ASSIGN |
 ADD_AND_ASSIGN |
 SUBTRACT_AND_ASSIGN |
 MULTIPLY_AND_ASSIGN |
 DIVIDE_AND_ASSIGN |
 REMAINDER_AND_ASSIGN | 
 BITSHIFT_LEFT_AND_ASSIGN |
 BITSHIFT_RIGHT_AND_ASSIGN |
 BITWISE_AND_AND_ASSIGN |
 BITWISE_OR_AND_ASSIGN |
 BITWISE_XOR_AND_ASSIGN 
;
conditional_expr : logical_or_expr 
	| logical_or_expr QUESTION_MARK expr COLON conditional_expr {$$ = create_ternary_expr($1, $3, $5);}
;
logical_or_expr : logical_and_expr 
 | logical_or_expr LOGICAL_OR logical_and_expr             {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
logical_and_expr : bitwise_or_expr 
 | logical_and_expr LOGICAL_AND bitwise_or_expr            {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
bitwise_and_expr : equality_expr 
 | bitwise_and_expr AMPERSAND equality_expr                {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
equality_expr : relational_expr 
 | equality_expr equality_op relational_expr              {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
equality_op : IS_EQUAL |
 IS_NOT_EQUAL 
;
relational_expr : shift_expr 
 | relational_expr relational_op shift_expr                {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
relational_op : LESS_THAN 
 | LESS_THAN_OR_EQUAL 
 | GREATER_THAN 
 | GREATER_THAN_OR_EQUAL 
;
shift_expr : additive_expr 
 | shift_expr shift_op additive_expr{printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
shift_op : BITSHIFT_RIGHT 
 | BITSHIFT_LEFT
;
additive_expr : multiplicative_expr 
 | additive_expr add_op multiplicative_expr                {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
add_op : PLUS 
 | DASH
;
multiplicative_expr : cast_expr 
 | multiplicative_expr mult_op cast_expr                   {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
mult_op :  STAR 
 | SLASH 
 | REMAINDER 
;
cast_expr : unary_expr                                        
	| LEFT_PAREN type_name RIGHT_PAREN cast_expr                 {printf("*********creating cast_expr node\n"); $$ = create_cast_expr_node($2, $4);}
;
type_name : declaration_specifiers abstract_declarator        {printf("*********creating type_name node\n"); $$ = create_type_name_node($1, $2);}
 |           declaration_specifiers   {printf("*********creating type_name node\n"); $$ = create_type_name_node($1, NULL);}
;
declaration_specifiers : type_specifier     
	| error SEMICOLON                  {yyerrok; yyclearin; }
;
type_specifier : integer_type_specifier    
| void_type_specifier 
;
integer_type_specifier : signed_type_specifier 
 | unsigned_type_specifier 
 | character_type_specifier 
;
signed_type_specifier : SHORT      {node *words[] = {$1, NULL, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | SHORT INT                       {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | SIGNED SHORT                    {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | SIGNED SHORT INT                {node *words[] = {$1, $2, $3}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | INT                             {node *words[] = {$1, NULL, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | SIGNED INT                      {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | SIGNED                          {node *words[] = {$1, NULL, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | LONG                            {node *words[] = {$1, NULL, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | LONG INT                        {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | SIGNED LONG                     {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
| SIGNED LONG INT                  {node *words[] = {$1, $2, $3}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
;
character_type_specifier : CHAR    {node *words[] = {$1, NULL, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | SIGNED CHAR                     {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | UNSIGNED CHAR                   {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
;
bitwise_or_expr : bitwise_xor_expr 
 | bitwise_or_expr BITWISE_OR bitwise_xor_expr              {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
bitwise_xor_expr : bitwise_and_expr 
 | bitwise_xor_expr BITWISE_XOR bitwise_and_expr            {printf("*********creating binary_expr node\n"); $$ = create_binary_expr_node($1, $2, $3);}
;
unary_expr : postfix_expr 
 | unary_minus_expr 
 | unary_plus_expr 
 | logical_negation_expr 
 | bitwise_negation_expr 
 | address_expr 
 | indirection_expr 
 | preincrement_expr 
 | predecrement_expr
;
unary_minus_expr : DASH cast_expr       {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 1);}
;
unary_plus_expr : PLUS cast_expr        {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 1);}
;
logical_negation_expr : LOGICAL_NOT cast_expr                   {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 1);}
;
bitwise_negation_expr : BITWISE_COMPLEMENT cast_expr            {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 1);}
;
address_expr : AMPERSAND cast_expr      {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 1);}
;
indirection_expr : STAR cast_expr      {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 1);}
;
postfix_expr : primary_expr 
 | subscript_expr 
 | function_call 
 | postincrement_expr 
 | postdecrement_expr 
;
primary_expr : IDENTIFIER        // do something
 | STRING_CONST
 | NUMBER 
 | parenthesized_expr 
;
parenthesized_expr : LEFT_PAREN expr RIGHT_PAREN               {$$ = $2;}
;
subscript_expr : postfix_expr LEFT_BRACKET expr RIGHT_BRACKET           {printf("*********creating subscript_expr node\n"); $$ = create_subscript_expr_node($1, $3);}
;
predecrement_expr : DECREMENT unary_expr                      {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 1);}
;
preincrement_expr : INCREMENT unary_expr                      {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 1);}
;
function_call : postfix_expr LEFT_PAREN expression_list RIGHT_PAREN      {printf("*********creating function_call node\n"); $$ = create_function_call_node($1, $3);}
 | postfix_expr LEFT_PAREN RIGHT_PAREN           {printf("*********creating function_call node\n"); $$ = create_function_call_node($1, NULL);}
;
postdecrement_expr : postfix_expr DECREMENT      {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 0);}
;
postincrement_expr : postfix_expr INCREMENT      {printf("*********creating unary_expr node\n"); $$ = create_unary_expr_node($1, $2, 0);}
;
unsigned_type_specifier : UNSIGNED SHORT INT     {node *words[] = {$1, $2, $3}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
	| UNSIGNED SHORT     {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
	 | UNSIGNED      {node *words[] = {$1, NULL, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
	| UNSIGNED LONG     {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | UNSIGNED INT                                   {node *words[] = {$1, $2, NULL}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
 | UNSIGNED LONG INT                              {node *words[] = {$1, $2, $3}; printf("*********creating compound_number_type_specifier node\n"); $$ = create_compound_number_type_specifier_node(words);}
;
void_type_specifier : VOID 
;
%%

#include <stdio.h>
#include "lex.yy.c"

void yyerror(char const *s) {
  fprintf(stderr, "ERROR at line %d: %s\n", yylineno, s);
}

