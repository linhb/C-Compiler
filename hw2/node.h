#ifndef _NODE_H
#define _NODE_H

#include <stdio.h>

#define NUMBER_NODE            1
#define STRING_NODE            7
#define IDENTIFIER_NODE        2
#define DECLARATION_OR_STATEMENT_LIST_NODE              3
#define BINARY_EXPRESSION_NODE 4
#define UNARY_EXPRESSION_NODE  5
#define DECL_NODE        8
#define INITIALIZED_DECLARATOR_LIST_NODE        9
#define RESERVED_WORD_NODE        12
#define RESERVED_WORD_LIST_NODE        13
#define OPERATOR_NODE        14
#define INCREMENT_DECREMENT_EXPR_NODE 15
#define TRANSLATION_UNIT_NODE 16
#define FUNCTION_DEF_SPECIFIER_NODE 17
#define FUNCTION_DEFINITION_NODE 18  
#define COMPOUND_STATEMENT_NODE 19
#define DIRECT_DECLARATOR_NODE 20
#define FUNCTION_DECLARATOR_NODE 21
#define PARAMETER_LIST_NODE 22
#define PARAMETER_DECL_NODE 23 
#define ARRAY_DECLARATOR_NODE 24  
#define SUBSCRIPT_EXPR_NODE 25  
#define STATEMENT_NODE 26          
#define LABELED_STATEMENT_NODE 27
#define RESERVED_WORD_STATEMENT_NODE 28 
#define IF_ELSE_STATEMENT_NODE 29
#define WHILE_STATEMENT_NODE 30
#define DO_STATEMENT_NODE 31
#define FOR_STATEMENT_NODE 32
#define FOR_EXPR_NODE 33
#define POINTER_DECL_NODE 34
#define FUNCTION_CALL_NODE 35
#define TYPE_NAME_NODE 36

typedef struct t_node {
	int node_type;
	int line_number;
	union {
		struct n_number *number;
		struct n_string *string;
		struct n_identifier *identifier;
		struct n_list *list;
		struct n_expression *expression;
		struct n_binary_expression *binary_expression;
		struct n_unary_expression *unary_expression;
		struct n_decl *decl;
		struct n_initialized_declarator_list *initialized_declarator_list;
		struct n_reserved_word *reserved_word;
		struct n_reserved_word_list *reserved_word_list;
		struct n_operator *operator;
		struct n_increment_decrement_expr *increment_decrement_expr;
		struct n_translation_unit *translation_unit;
		struct n_function_def_specifier *function_def_specifier;
		struct n_function_definition *function_definition;  
		struct n_declaration_or_statement_list *declaration_or_statement_list;
		struct n_compound_statement *compound_statement;
		struct n_direct_declarator *direct_declarator;
		struct n_function_declarator *function_declarator;
		struct n_parameter_list *parameter_list;
		struct n_parameter_decl *parameter_decl;
		struct n_array_declarator *array_declarator;
		struct n_subscript_expr *subscript_expr; 
		struct n_statement *statement;
		struct n_labeled_statement *labeled_statement;
		struct n_reserved_word_statement *reserved_word_statement;
		struct n_if_else_statement *if_else_statement;
		struct n_while_statement *while_statement;
		struct n_do_statement *do_statement;
		struct n_for_statement *for_statement;
		struct n_for_expr *for_expr;
		struct n_pointer_decl *pointer_decl;
		struct n_function_call *function_call;
		struct n_type_name *type_name;
	} data;
} node;

typedef struct n_number {
	long int value;
	int overflow;
	int type;
} number;

typedef struct n_string {
	char *value;
} string;

typedef struct n_identifier {
	char *name;
} identifier;

typedef struct n_list {
	node *list;
	node *item;
} list;

typedef struct n_binary_expression {
	node *left;
	node *op;
	node *right;
} binary_expression; 

typedef struct n_unary_expression {
	node *operator;
	node *operand; 
	int op_first;
} unary_expression;

typedef struct n_expression {
	node *expression;
} expression;

typedef struct n_decl {
	node *declaration_specifier;
	node *initialized_declarator_list;
} decl;

typedef struct n_initialized_declarator_list {
	node *initialized_declarator_list;
	node *initialized_declarator;
} initialized_declarator_list;
typedef struct n_reserved_word {
	char *text;
	int value;
} reserved_word;
typedef struct n_reserved_word_list {
	node *reserved_words[3];
} reserved_word_list;
typedef struct n_operator {
	char *text;
	int value;	
} operator;
typedef struct n_increment_decrement_expr {
	node *operand;
	node *operator;
} increment_decrement_expr;
typedef struct n_translation_unit {
	node *translation_unit;
	node *top_level_decl;
} translation_unit;
typedef struct n_function_def_specifier
{
	node *declaration_specifiers;
	node *declarator;
} function_def_specifier;
typedef struct n_function_definition	
{
	node *function_def_specifier;
	node *compound_statement;
} function_definition; 
typedef struct n_declaration_or_statement_list 
{
	node *declaration_or_statement_list;
	node *declaration_or_statement;
} declaration_or_statement_list;
typedef struct n_compound_statement
{
	node *declaration_or_statement_list;
} compound_statement;   
typedef struct n_direct_declarator {
	node *declarator;
} direct_declarator;
typedef struct n_function_declarator
{
	node *direct_declarator;
	node *parameter_type_list;
} function_declarator;  
typedef struct n_parameter_list {
	node *parameter_list;
	node *parameter_decl;
} parameter_list; 
typedef struct n_parameter_decl  {
	node *declaration_specifiers;
	node *declarator;
} parameter_decl;         
typedef struct n_array_declarator
{
	node *direct_declarator;
	node *constant_expr;
} array_declarator;
typedef struct n_subscript_expr
{
	node *postfix_expr;
	node *expr;
} subscript_expr;
typedef struct n_statement
{
	node *statement;
} statement;
typedef struct n_labeled_statement
{
	node *label;
	node *statement;
} labeled_statement;
typedef struct n_reserved_word_statement
{
	node *reserved_word;
	node *expr;
} reserved_word_statement;
typedef struct n_if_else_statement
{
	node *expr;
	node *if_statement;
	node *else_statement;
} if_else_statement;
typedef struct n_while_statement
{
	node *expr;
	node *statement;
} while_statement;
typedef struct n_do_statement
{
	node *statement;
	node *expr;
} do_statement;
typedef struct n_for_statement
{
	node *for_expr;
	node *statement;
} for_statement;
typedef struct n_for_expr
{
	node *initial_clause;
	node *goal_expr;
	node *advance_expr;
} for_expr;
typedef struct n_pointer_decl
{
	node *pointer;
	node *direct_declarator;
} pointer_decl;   
typedef struct n_function_call
{
	node *postfix_expr;
	node *expression_list;
} function_call;
typedef struct n_type_name
{
	node *declaration_specifiers;
	node *abstract_declarator;
} type_name;

node *create_node(int node_type);
node *create_decl_node(node *declaration_specifier, node *initialized_declarator_list);
node *create_initialized_declarator_list_node(node *list, node *decl);
node *create_reserved_word_list_node(node *reserved_words[]);
node *create_increment_decrement_expr_node(node *operand, node *operator);
node *create_translation_unit_node(node *translation_unit, node *top_level_decl);
node *create_function_def_specifier_node(node *declaration_specifiers, node *declarator);
node *create_function_definition_node(node *function_def_specifier, node *compound_statement);
node *create_declaration_or_statement_list_node(node *declaration_or_statement_list, node *declaration_or_statement);
node *create_compound_statement_node(node *declaration_or_statement_list);
node *create_direct_declarator_node(node *declarator);
node *create_function_declarator_node(node *direct_declarator, node *parameter_type_list);
node *create_parameter_list_node(node *parameter_list, node *parameter_decl);
node *create_parameter_decl_node(node *declaration_specifiers, node *declarator);
node *create_array_declarator_node(node *direct_declarator, node *constant_expr);
node *create_binary_expr_node(node *left, node *op, node *right);
node *create_unary_expr_node(node *left, node *right, int op_first);
node *create_subscript_expr_node(node *postfix_expr, node *expr);
node *create_statement_node(node *statement);
node *create_labeled_statement_node(node *label, node *statement);
node *create_reserved_word_statement_node(node *reserved_word, node *expr);
node *create_if_else_statement_node(node *expr, node *if_statement, node *else_statement);
node *create_while_statement_node(node *expr, node *statement);
node *create_do_statement_node(node *statement, node *expr);
node *create_for_statement_node(node *for_expr, node *statement);
node *create_for_expr_node(node *initial_clause, node *goal_expr, node *advance_expr);
node *create_pointer_decl_node(node *pointer, node *direct_declarator);
node *create_function_call_node(node *postfix_expr, node *expression_list);
node *create_type_name_node(node *declaration_specifiers, node *abstract_declarator);

/***************************** PRETTY PRINTER FUNCTIONS *******************************/

void print_node(FILE *output, node *n);
void print_number_node(FILE *output, node *n);
void print_string_node(FILE *output, node *n);
void print_identifier_node(FILE *output, node *n);
void print_list_node(FILE *output, node *n);
void print_unary_expr_node(FILE *output, node *n);
void print_decl_node(FILE *output, node *n);
void print_initialized_declarator_list_node(FILE *output, node *n);
void print_reserved_word_node(FILE *output, node *n);
void print_reserved_word_list_node(FILE *output, node *n);
void print_operator_node(FILE *output, node *n);
void print_increment_decrement_expr_node(FILE *output, node *n);
void print_translation_unit_node(FILE *output, node *n);
void print_function_def_specifier_node(FILE *output, node *n);
void print_function_definition_node(FILE *output, node *n);
void print_declaration_or_statement_list_node(FILE *output, node *n);
void print_compound_statement_node(FILE *output, node *n);
void print_direct_declarator_node(FILE *output, node *n);
void print_function_declarator_node(FILE *output, node *n);
void print_parameter_list_node(FILE *output, node *n);
void print_parameter_decl_node(FILE *output, node *n);
void print_array_declarator_node(FILE *output, node *n);
void print_binary_expr_node(FILE *output, node *n);
void print_subscript_expr_node(FILE *output, node *n);
void print_statement_node(FILE *output, node *n);
void print_labeled_statement_node(FILE *output, node *n);
void print_reserved_word_statement_node(FILE *output, node *n);
void print_if_else_statement_node(FILE *output, node *n);
void print_while_statement_node(FILE *output, node *n);
void print_do_statement_node(FILE *output, node *n);
void print_for_statement_node(FILE *output, node *n);
void print_for_expr_node(FILE *output, node *n);
void print_pointer_decl_node(FILE *output, node *n);
void print_function_call_node(FILE *output, node *n);
void print_type_name_node(FILE *output, node *n);
#endif
