%{
	#include <stdio.h>
	#include "node.h"

%}
%token DO FOR RETURN BREAK SHORT ELSE GOTO SIGNED UNSIGNED CHAR IF VOID INT CONTINUE LONG WHILE 
%token IDENTIFIER STRING_CONST INTEGER_CONST LONG_CONST UNSIGNED_LONG_CONST
%token LEFT_CURLY_BRACE RIGHT_CURLY_BRACE COMMA SEMICOLON COLON 
%token LEFT_BRACKET RIGHT_BRACKET
%token LEFT_PAREN RIGHT_PAREN
%token INCREMENT DECREMENT
%token BITWISE_COMPLEMENT
%token LOGICAL_NOT
%token PLUS DASH
%token AMPERSAND
%token STAR
%token SLASH REMAINDER
%token BITSHIFT_LEFT BITSHIFT_RIGHT
%token LESS_THAN GREATER_THAN LESS_THAN_OR_EQUAL GREATER_THAN_OR_EQUAL
%token IS_EQUAL IS_NOT_EQUAL
%token BITWISE_XOR
%token BITWISE_OR
%token LOGICAL_AND
%token LOGICAL_OR        
%token QUESTION_MARK
%token ASSIGN ADD_AND_ASSIGN SUBTRACT_AND_ASSIGN MULTIPLY_AND_ASSIGN DIVIDE_AND_ASSIGN REMAINDER_AND_ASSIGN BITWISE_AND_AND_ASSIGN BITWISE_OR_AND_ASSIGN BITWISE_XOR_AND_ASSIGN BITSHIFT_LEFT_AND_ASSIGN BITSHIFT_RIGHT_AND_ASSIGN       

%%
translation_unit : top_level_decl |
 translation_unit top_level_decl 
;
top_level_decl : decl |
 function_definition 
;
decl : declaration_specifiers initialized_declarator_list SEMICOLON 
;
function_definition : function_def_specifier compound_statement 
;
compound_statement : LEFT_BRACKET declaration_or_statement_list RIGHT_BRACKET |
                     LEFT_BRACKET RIGHT_BRACKET
;
declaration_or_statement_list : declaration_or_statement |
 declaration_or_statement_list declaration_or_statement 
;
declaration_or_statement : decl |
 statement 
;
statement : expression_statement // |
 // labeled_statement |
 // compound_statement |
 // conditional_statement |
 // iterative_statement |
 // break_statement |
 // continue_statement |
 // return_statement |
 // goto_statement |
 // null_statement              
;
expression_statement : expr SEMICOLON 
;
function_def_specifier : declaration_specifiers declarator |
                         declarator
;
initialized_declarator : declarator 
;
declarator : pointer_decl |
 direct_declarator 
;
pointer : STAR |
 STAR pointer 
;
pointer_decl : pointer direct_declarator 
;
direct_declarator : simple_declarator |
 LEFT_PAREN declarator RIGHT_PAREN // |
  // function_declarator |
  // array_declarator                 
;
simple_declarator : IDENTIFIER 
;
initialized_declarator_list : initialized_declarator |
 initialized_declarator_list COMMA initialized_declarator 
expr : comma_expr 
;
comma_expr : assignment_expr |
 comma_expr COMMA assignment_expr 
;
assignment_expr : conditional_expr |
 unary_expr ASSIGN assignment_expr 
;
conditional_expr : logical_or_expr |
 logical_or_expr QUESTION_MARK expr COLON conditional_expr 
;
logical_or_expr : logical_and_expr |
 logical_or_expr LOGICAL_OR logical_and_expr 
;
logical_and_expr : bitwise_or_expr |
 logical_and_expr LOGICAL_AND bitwise_or_expr 
;
bitwise_and_expr : equality_expr |
 bitwise_and_expr AMPERSAND equality_expr 
;
equality_expr : relational_expr |
 equality_expr IS_NOT_EQUAL relational_expr 
;
relational_expr : shift_expr |
 relational_expr relational_op shift_expr 
;
relational_op : LESS_THAN |
 LESS_THAN_OR_EQUAL |
 GREATER_THAN |
 GREATER_THAN_OR_EQUAL 
;
shift_expr : additive_expr |
 shift_expr shift_op additive_expr 
;
shift_op : BITSHIFT_RIGHT |
           BITSHIFT_LEFT
;
additive_expr : multiplicative_expr |
 additive_expr add_op multiplicative_expr 
;
add_op : PLUS |
         DASH
;
multiplicative_expr : cast_expr |
 multiplicative_expr mult_op cast_expr 
;
mult_op :  STAR |
					 SLASH |
					 REMAINDER 
;
cast_expr : unary_expr // |
 // LEFT_PAREN type_name RIGHT_PAREN cast_expr 
;
// type_name : declaration_specifiers abstract_declarator_opt 
;
declaration_specifiers : type_specifier 
;
type_specifier : integer_type_specifier |
 void_type_specifier 
;
integer_type_specifier : signed_type_specifier |
 unsigned_type_specifier |
 character_type_specifier 
;
signed_type_specifier : SHORT |
 SHORT INT |
 SIGNED SHORT |
 SIGNED SHORT INT |
 INT |
 SIGNED INT |
 SIGNED |
 LONG |
 LONG INT |
 SIGNED LONG |
 SIGNED LONG INT
;
character_type_specifier : CHAR |
 SIGNED CHAR |
 UNSIGNED CHAR 
;
bitwise_or_expr : bitwise_xor_expr |
 bitwise_or_expr BITWISE_OR bitwise_xor_expr 
;
bitwise_xor_expr : bitwise_and_expr |
 bitwise_xor_expr BITWISE_XOR bitwise_and_expr 
;
unary_expr : postfix_expr // |
 // unary_minus_expr |
 // unary_plus_expr |
 // logical_negation_expr |
 // bitwise_negation_expr |
 // address_expr |
 // indirection_expr |
 // preincrement_expr |
 // predecrement_expr
;
postfix_expr : // primary_expr |
 subscript_expr // |
  // function_call |
  // postincrement_expr |
  // postdecrement_expr 
;
// primary_expr : identifier |
//  constant |
//  paranthesized_expr 

subscript_expr : postfix_expr LEFT_BRACKET expr RIGHT_BRACKET 
;
// function_call : postfix_expr LEFT_PAREN expression_list_opt RIGHT_PAREN 

postdecrement_expr : postfix_expr DASH DASH
;
postincrement_expr : postfix_expr PLUS PLUS 
;
unsigned_type_specifier : UNSIGNED SHORT INT |	
 UNSIGNED INT |
 UNSIGNED LONG INT     
;

void_type_specifier : VOID 
;

%%

#include <stdio.h>
#include "lex.yy.c"

main() {
	return yyparse();
}

// %token IDENTIFIER CHAR_CONST STRING_CONST INTEGER_CONST LONG_CONST UNSIGNED_LONG_CONST
