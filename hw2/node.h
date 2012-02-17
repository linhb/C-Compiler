#ifndef _NODE_H
#define _NODE_H
typedef struct t_node {
	int node_type;
	int line_number;
	union {
		struct n_number *number;
		struct n_identifier *identifier;
		struct n_list *list;
		struct n_expression *expression;
		struct n_binary_expression *binary_expression;
		struct n_unary_expression *unary_expression;
	} data;
} node;

typedef struct n_number {
	long int value;
	int overflow;
	int type;
} number;

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
#endif
