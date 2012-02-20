#ifndef _NODE_H
#define _NODE_H

#include <stdio.h>

#define boolean int

	
//	#define SHORT 				1
//	#define LONG          2
//	#define INT           3
	// #define CHAR          4
//	#define SIGNED        5
//	#define UNSIGNED      6

#define NUMBER_NODE            1
#define STRING_NODE            7
#define IDENTIFIER_NODE        2
#define LIST_NODE              3
#define BINARY_EXPRESSION_NODE 4
#define UNARY_EXPRESSION_NODE  5
#define EXPRESSION_NODE        6
#define DECL_NODE        8
#define INITIALIZED_DECLARATOR_LIST_NODE        9
// #define INTEGER_TYPE_SPECIFIER_NODE        10
// #define VOID_TYPE_SPECIFIER_NODE        11
#define RESERVED_WORD_NODE        12
#define RESERVED_WORD_LIST_NODE        13


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
		// struct n_integer_type_specifier *integer_type_specifier;
		// struct n_void_type_specifier *void_type_specifier;
		struct n_reserved_word *reserved_word;
		struct n_reserved_word_list *reserved_word_list;
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
	node *right;
	int operator;
} binary_expression; 

typedef struct n_unary_expression {
	int operator;
	node *operand;
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

// typedef struct n_integer_type_specifier {
// 	int sign;
// 	int number_type;
// 	/* if false, print INT after printing SIGNED/UNSIGNED and number_type. Should only be set to false if you want an extra INT */
// 	boolean shorthand;
// } integer_type_specifier;
// typedef struct n_void_type_specifier {} void_type_specifier;
typedef struct n_reserved_word {
	char *text;
	int value;
} reserved_word;

typedef struct n_reserved_word_list {
	node *reserved_word_list;
	node *reserved_word;
} reserved_word_list;

/* macro to print tokens that have the same value as their name */
#define TO_STR(TOKEN) #TOKEN 

node *create_node(int node_type);
node *create_decl_node(node *declaration_specifier, node *initialized_declarator_list);
node *create_initialized_declarator_list_node(node *list, node *decl);
// node *create_integer_type_specifier_node(int sign, int number_type, boolean shorthand);
// node *create_void_type_specifier_node();
node *create_reserved_word_list_node(node *reserved_word_list, node *reserved_word);

/***************************** PRETTY PRINTER FUNCTIONS *******************************/

void print_node(FILE *output, node *n);
void print_number_node(FILE *output, node *n);
void print_string_node(FILE *output, node *n);
void print_identifier_node(FILE *output, node *n);
void print_list_node(FILE *output, node *n);
// void print_binary_expression_node(FILE *output, node *n);
void print_unary_expression_node(FILE *output, node *n);
void print_decl_node(FILE *output, node *n);
void print_initialized_declarator_list_node(FILE *output, node *n);
// void print_integer_type_specifier_node(FILE *output, node *n);
// void print_void_type_specifier_node(FILE *output, node *n);
void print_reserved_word_node(FILE *output, node *n);
void print_reserved_word_list_node(FILE *output, node *n);
#endif
