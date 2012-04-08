/*
Header file containing integer constants that stand for different types of nodes, as well as prototypes for node creating and node printing functions
*/

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
#define COMPOUND_NUMBER_TYPE_SPECIFIER_NODE        13
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
#define CAST_EXPR_NODE 37
#define EXPRESSION_LIST_NODE 38
#define DIRECT_ABSTRACT_DECLARATOR_NODE 39 
#define POINTER_NODE 40
#define NULL_STATEMENT_NODE 41
#define TERNARY_EXPR_NODE 42
#define ABSTRACT_DECLARATOR_NODE 43
#define COMMA_EXPR_NODE 44

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
		struct n_compound_number_type_specifier *compound_number_type_specifier;
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
		struct n_cast_expr *cast_expr;
		struct n_expression_list *expression_list;
		struct n_direct_abstract_declarator *direct_abstract_declarator;
		struct n_pointer *pointer;
		struct n_ternary_expr *ternary_expr;
		struct n_abstract_declarator *abstract_declarator;
		struct n_comma_expr *comma_expr;
	} data;
} node;

typedef struct n_number {
	long int value;
	int overflow;
	int type;
	int is_unsigned;
} number;

typedef struct n_string {
	int length;
	char *value;
} string;

typedef struct n_identifier {
	char *name;
	struct t_symbol_table_identifier *symbol_table_identifier;
	int scope_level;
	int st_id;
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
	// struct t_symbol_table_entry *symbol_table_entry;
} decl;

typedef struct n_initialized_declarator_list {
	node *initialized_declarator_list;
	node *initialized_declarator;
} initialized_declarator_list;
typedef struct n_reserved_word {
	char *text;
	int value;
} reserved_word;
typedef struct n_compound_number_type_specifier {
	node *reserved_words[3];
	int number_type;
	int is_unsigned;
} compound_number_type_specifier;
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
	int number_of_params;
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
typedef struct n_cast_expr
{
	node *type_name;
	node *cast_expr;
} cast_expr;
typedef struct n_expression_list
{
	node *expression_list;
	node *assignment_expr;
} expression_list;
typedef struct n_direct_abstract_declarator
{
	node *n1;
	node *n2;
	node *n3;
	node *n4;
} direct_abstract_declarator;               
typedef struct n_pointer
{
	node *pointer;
} pointer;
typedef struct n_ternary_expr
{
	node *logical_or_expr;
	node *expr;
	node *conditional_expr;
} ternary_expr;
typedef struct n_abstract_declarator
{
	node *pointer;
	node *direct_abstract_declarator;
} abstract_declarator;
typedef struct n_comma_expr
{
	node *comma_expr;
	node *assignment_expr;
} comma_expr;

node *create_node(int node_type);
node *create_number_node(char *yytext);
node *create_string_node(char *yytext);
node *create_char_node(char *yytext);
node *create_identifier_node(char *yytext);
node *create_reserved_word_node(char *yytext, int value);
node *create_operator_node(char *yytext, int value);
char *escape_string(char *yytext);
node *create_decl_node(node *declaration_specifier, node *initialized_declarator_list);
node *create_initialized_declarator_list_node(node *list, node *decl);
node *create_compound_number_type_specifier_node(node *reserved_words[]);
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
node *create_cast_expr_node(node *type_name, node *cast_expr);
node *create_expression_list_node(node *expression_list, node *assignment_expr);
node *create_direct_abstract_declarator_node(node *n1, node *n2, node *n3, node *n4);
node *create_pointer_node(node *pointer);
node *create_null_statement_node();  
node *create_ternary_expr(node *logical_or_expr, node *expr, node *conditional_expr);
node *create_abstract_declarator_node(node *pointer, node *direct_abstract_declarator);
node *create_comma_expr_node(node *comma_expr, node *assignment_expr);
int is_type(node *n, int index, char *type);

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
void print_compound_number_type_specifier_node(FILE *output, node *n);
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
void print_cast_expr_node(FILE *output, node *n);
void print_expression_list_node(FILE *output, node *n);
void print_direct_abstract_declarator_node(FILE *output, node *n);
void print_pointer_node(FILE *output, node *n);
void print_null_statement_node(FILE *output, node *n);
void print_ternary_expr_node(FILE *output, node *n);
void print_abstract_declarator_node(FILE *output, node *n); 
void print_comma_expr_node(FILE *output, node *n); 

/***********SYMBOL TABLE DEFINITIONS AND HEADERS****************/

#define ARITHMETIC_TYPE 1 
#define POINTER_TYPE 2 
#define ARRAY_TYPE 3
#define FUNCTION_TYPE 4
#define VOID_TYPE 5

const char *types[400];

typedef struct t_symbol_table
{
	struct t_symbol_table_identifier *identifiers;        // both identifiers and children are linked lists
	struct t_symbol_table *children;
	struct t_symbol_table *next;
	struct t_symbol_table *parent;
	struct t_symbol_table_identifier *parent_function_identifier;
	int scope_level;
	int st_id;
	/*scope level goes up and down as you enter and exit blocks, but st_id only goes up 
		rules for searching for ids:
		search in scopes that are same or higher in scope level. if same level, must also be same id
	*/
} symbol_table;                       
int current_scope_level;
int st_id;

typedef struct t_symbol_table_identifier
{ 
	char *name;
	int identifier_id; // not meant to be consecutive; there'll be gaps when a redeclared variable is encountered
	struct t_symbol_table_identifier *next;
	struct t_type *type;
} symbol_table_identifier;  // calling it symbol_table_identifier as opposed to plain identifier which is a node
// example: 
// old: i->data.arithmetic_identifier->is_signed -> 
// i->type->data.arithmetic_type->
typedef struct t_type {
	int type;
	union {
		struct t_arithmetic_type *arithmetic_type;
		struct t_pointer_type *pointer_type;
		struct t_array_type *array_type;
		struct t_function_type *function_type;
	} data;
} type;
typedef struct t_arithmetic_type
{
	int is_unsigned;
	int number_type;     
} arithmetic_type;
typedef struct t_array_type
{
	type *element_type;
	int size; // can be null if size isn't specified or can't be determined at compile time
} array_type;

void add_types();

typedef struct t_pointer_type
{
	type *base_type;
} pointer_type;

typedef struct t_function_type
{
	type *return_type;
	int argc;
	type *arg_types[20]; // hack to get around "invalid use of flexible array member" error with an untyped array
} function_type;

// returns pointer to updated ST
symbol_table *add_to_symbol_table_list(symbol_table *list, symbol_table *new);
symbol_table_identifier *add_to_symbol_table_identifier_list(symbol_table_identifier *list, symbol_table_identifier *new);
symbol_table *get_last_symbol_table_list_element(symbol_table *list);
symbol_table_identifier *get_last_symbol_table_identifier_list_element(symbol_table_identifier *list);
symbol_table_identifier *find_in_identifier_list(symbol_table_identifier *list, char *name);
symbol_table_identifier *find_identifier_in_symbol_table(symbol_table *st, char *name);
symbol_table_identifier *find_identifier_in_same_symbol_table(symbol_table *st, char *name);

void create_symbol_table(node *result, symbol_table *st);
int redeclared_variable(symbol_table *st, char *name);
node *get_identifier_from_declarator(node *n);
void create_decl_node_symbol_table(node *n, symbol_table *st);
symbol_table_identifier *create_decl_identifier(node *parent, node *decl_spec, node *declarator, symbol_table_identifier *current, symbol_table *st);
void create_function_def_specifier_node_symbol_table(node *n, symbol_table *st, node *compound_statement);
void create_compound_statement_node_symbol_table(node *n, symbol_table *st, int create_new_symbol_table);
void create_declaration_or_statement_list_node_symbol_table(node *n, symbol_table *st);
void create_parameter_list_node_symbol_table(node *n, symbol_table *st);
void create_parameter_decl_node_symbol_table(node *n, symbol_table *st);
void create_subscript_expr_node_symbol_table(node *n, symbol_table *st); 
void create_identifier_node_symbol_table(node *n, symbol_table *st);

symbol_table_identifier *create_identifier(symbol_table *st);
node *create_temp_ini_param_list(node *ini_declarator);
void advance_current_identifier();

void print_symbol_table(FILE *output, symbol_table *s);
void print_symbol_table_identifier(FILE *output, symbol_table_identifier *i);
void print_arithmetic_identifier(FILE *output, symbol_table_identifier *i);
void print_pointer_identifier(FILE *output, symbol_table_identifier *i);
void print_array_identifier(FILE *output, symbol_table_identifier *i);
void print_function_identifier(FILE *output, symbol_table_identifier *i);
symbol_table *file_scope_symbol_table;
int identifier_id;

type *get_type_from_decl_node(node *n);
char *type_to_s(type *t);
void children_identifier_as_string(symbol_table_identifier *i);

void type_check(node *n); 
void do_unary_conversion(node *n);
int get_num_type_from_string(char *str);
node *insert_cast(type *t, node *n);
node *insert_cast_from_string(char *type, int is_unsigned, node *n);
int is_arithmetic_type(type *t);
void do_binary_conversion(node *n);
type *type_of_expr(node *n);
int cast_equal_or_larger_than_int(node *n);
int int_or_long(int num_type);
type *larger_type(type *left, type *right);
type *type_of_unary_expr(node *unary_expression);
int rank(type *t);
int str_equals(char *str1, char *str2);
node *get_core_operand_from_unary_expr(node *n);
node *get_identifier_from_node(node *n);
int compare_arithmetic_types(type *t1, type *t2);
void assignment_type_check(node *left, node *right);
#endif

