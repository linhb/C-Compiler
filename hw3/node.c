/*
Definitions of functions that create and print different kinds of nodes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "node.h"

extern int yylineno;  
int indent;
void print_indentation(FILE *output);

node *create_node(int node_type) {
	node *n = malloc(sizeof(*n));
	assert(n != NULL);
	n->line_number = yylineno;
	n->node_type = node_type;
	return n;
}

node *create_decl_node(node *decl_spec, node *ini_decl_list) {
	node *n = create_node(DECL_NODE);
	n->data.decl = malloc(sizeof(*n->data.decl));
	assert(n->data.decl != NULL);
	n->data.decl->declaration_specifier = decl_spec;
	n->data.decl->initialized_declarator_list = ini_decl_list;
	return n;
}

node *create_initialized_declarator_list_node(node *list, node *decl) {
	node *n = create_node(INITIALIZED_DECLARATOR_LIST_NODE);
	n->data.initialized_declarator_list = malloc(sizeof(*n->data.initialized_declarator_list));
	assert(n->data.initialized_declarator_list != NULL);
	n->data.initialized_declarator_list->initialized_declarator_list = list;
	n->data.initialized_declarator_list->initialized_declarator = decl;
	return n;
}
node *create_compound_number_type_specifier_node(node *reserved_words[]) {
	node *n = create_node(COMPOUND_NUMBER_TYPE_SPECIFIER_NODE);
	n->data.compound_number_type_specifier = malloc(sizeof(*n->data.compound_number_type_specifier));
	assert(n->data.compound_number_type_specifier != NULL);
	int i;
	for (i = 0; i< 3; i++) {
		n->data.compound_number_type_specifier->reserved_words[i] = reserved_words[i];
	}
	if (reserved_words[1]!=NULL)
	if (is_type(n, 0, "unsigned")) {
		n->data.compound_number_type_specifier->is_unsigned = 1;
	}
	if (is_type(n, 0, "short") || is_type(n, 1, "short")) {
		n->data.compound_number_type_specifier->number_type = NUMBER_TYPE_SHORT;
	}
	else if (is_type(n, 0, "long") || is_type(n, 1, "long")) {
		n->data.compound_number_type_specifier->number_type = NUMBER_TYPE_LONG;
	}	
	else if (is_type(n, 0, "char") || is_type(n, 1, "char")) {
		n->data.compound_number_type_specifier->number_type = NUMBER_TYPE_CHAR;
	}
	else {
		n->data.compound_number_type_specifier->number_type = NUMBER_TYPE_INT;
	}
	return n;
}
int is_type(node *n, int index, char *type) {
	if (n->data.compound_number_type_specifier->reserved_words[index] != NULL){
		return !strcmp(n->data.compound_number_type_specifier->reserved_words[index]->data.reserved_word->text, type);
	}
	else {
		return 0;
	}
}
node *create_increment_decrement_expr_node(node *operand, node *operator) {
	node *n = create_node(INCREMENT_DECREMENT_EXPR_NODE);
	n->data.increment_decrement_expr = malloc(sizeof(*n->data.increment_decrement_expr));
	assert(n->data.increment_decrement_expr != NULL);
	n->data.increment_decrement_expr->operand = operand;
	n->data.increment_decrement_expr->operator = operator;
	return n;
}
node *create_translation_unit_node(node *translation_unit, node *top_level_decl) {
	node *n = create_node(TRANSLATION_UNIT_NODE);
	n->data.translation_unit = malloc(sizeof(*n->data.translation_unit));
	assert(n->data.translation_unit != NULL);
	n->data.translation_unit->translation_unit = translation_unit;
	n->data.translation_unit->top_level_decl = top_level_decl;
	return n;
}
node *create_function_def_specifier_node(node *declaration_specifiers, node *declarator) {
	node *n = create_node(FUNCTION_DEF_SPECIFIER_NODE);
	n->data.function_def_specifier = malloc(sizeof(*n->data.function_def_specifier));
	assert(n->data.function_def_specifier != NULL);
	n->data.function_def_specifier->declaration_specifiers = declaration_specifiers;
	n->data.function_def_specifier->declarator = declarator;
	return n;
}
node *create_function_definition_node(node *function_def_specifier, node *compound_statement) {
	node *n = create_node(FUNCTION_DEFINITION_NODE);
	n->data.function_definition = malloc(sizeof(*n->data.function_definition));
	assert(n->data.function_definition != NULL);
	n->data.function_definition->function_def_specifier = function_def_specifier;
	n->data.function_definition->compound_statement = compound_statement;
	return n;
}
node *create_declaration_or_statement_list_node(node *declaration_or_statement_list, node *declaration_or_statement) {
	node *n = create_node(DECLARATION_OR_STATEMENT_LIST_NODE);
	n->data.declaration_or_statement_list = malloc(sizeof(*n->data.declaration_or_statement_list));
	assert(n->data.declaration_or_statement_list != NULL);
	n->data.declaration_or_statement_list->declaration_or_statement_list = declaration_or_statement_list;
	n->data.declaration_or_statement_list->declaration_or_statement = declaration_or_statement;
	return n;
}
node *create_compound_statement_node(node *declaration_or_statement_list) {
	node *n = create_node(COMPOUND_STATEMENT_NODE);
	n->data.compound_statement = malloc(sizeof(*n->data.compound_statement));
	assert(n->data.compound_statement != NULL);
	n->data.compound_statement->declaration_or_statement_list = declaration_or_statement_list;
	return n;
}
node *create_direct_declarator_node(node *declarator) {
	node *n = create_node(DIRECT_DECLARATOR_NODE);
	n->data.direct_declarator = malloc(sizeof(*n->data.direct_declarator));
	assert(n->data.direct_declarator != NULL);
	n->data.direct_declarator->declarator = declarator;
	return n;	
}  
node *create_function_declarator_node(node *direct_declarator, node *parameter_type_list) {	
	node *n = create_node(FUNCTION_DECLARATOR_NODE);
	n->data.function_declarator = malloc(sizeof(*n->data.function_declarator));
	assert(n->data.function_declarator != NULL);
	n->data.function_declarator->direct_declarator = direct_declarator;
	n->data.function_declarator->parameter_type_list = parameter_type_list;
	return n;	
}
node *create_parameter_list_node(node *parameter_list, node *parameter_decl) {
	node *n = create_node(PARAMETER_LIST_NODE);
	n->data.parameter_list = malloc(sizeof(*n->data.parameter_list));
	assert(n->data.parameter_list != NULL);
	n->data.parameter_list->parameter_list = parameter_list;
	n->data.parameter_list->parameter_decl = parameter_decl;
	if (parameter_list != NULL) {
		int number_of_params = parameter_list->data.parameter_list->number_of_params;
		n->data.parameter_list->number_of_params = number_of_params + 1;
	}
	else {
		// if 1 arg, no parameter_list node was created, so this function is never called, so this field will never be 1
		// if 2 args, 1 parameter_list node will be created which is the node being created right now
		n->data.parameter_list->number_of_params = 2;
	}
	// printf("HAZ %d PARAMS\n", n->data.parameter_list->number_of_params);
	return n;		
}
node *create_parameter_decl_node(node *declaration_specifiers, node *declarator){	
	node *n = create_node(PARAMETER_DECL_NODE);
	n->data.parameter_decl = malloc(sizeof(*n->data.parameter_decl));
	assert(n->data.parameter_decl != NULL);
	n->data.parameter_decl->declaration_specifiers = declaration_specifiers;
	n->data.parameter_decl->declarator = declarator;
	return n;		
}
node *create_array_declarator_node(node *direct_declarator, node *constant_expr) {
	node *n = create_node(ARRAY_DECLARATOR_NODE);
	n->data.array_declarator = malloc(sizeof(*n->data.array_declarator)); 
	assert(n->data.array_declarator != NULL);
	n->data.array_declarator->direct_declarator = direct_declarator;
	n->data.array_declarator->constant_expr = constant_expr;
	return n;			
}
node *create_binary_expr_node(node *left, node *op, node *right) {
	node *n = create_node(BINARY_EXPRESSION_NODE);
	n->data.binary_expression = malloc(sizeof(*n->data.binary_expression)); 
	assert(n->data.binary_expression != NULL);
	n->data.binary_expression->left = left;
	n->data.binary_expression->op = op;
	n->data.binary_expression->right = right;
	return n;				
}
node *create_subscript_expr_node(node *postfix_expr, node *expr) {
	node *n = create_node(SUBSCRIPT_EXPR_NODE);
	n->data.subscript_expr = malloc(sizeof(*n->data.subscript_expr)); 
	assert(n->data.subscript_expr != NULL);
	n->data.subscript_expr->postfix_expr = postfix_expr;
	n->data.subscript_expr->expr = expr;
	return n;			
}
node *create_unary_expr_node(node *left, node *right, int op_first) {
	node *n = create_node(UNARY_EXPRESSION_NODE);
	n->data.unary_expression = malloc(sizeof(*n->data.unary_expression)); 
	assert(n->data.unary_expression != NULL);
	n->data.unary_expression->op_first = op_first;
	if (op_first) {
		n->data.unary_expression->operator = left;
		n->data.unary_expression->operand = right;
	}
	else	{
		n->data.unary_expression->operator = right;
		n->data.unary_expression->operand = left;		
	}
	return n;				
}
node *create_statement_node(node *statement) {
	node *n = create_node(STATEMENT_NODE);
	n->data.statement = malloc(sizeof(*n->data.statement)); 
	assert(n->data.statement != NULL);
	n->data.statement->statement = statement;
	return n;
}
node *create_labeled_statement_node(node *label, node *statement) {	
	node *n = create_node(LABELED_STATEMENT_NODE);
	n->data.labeled_statement = malloc(sizeof(*n->data.labeled_statement)); 
	assert(n->data.labeled_statement != NULL);
	n->data.labeled_statement->label = label;
	n->data.labeled_statement->statement = statement;
	return n;
}
node *create_reserved_word_statement_node(node *reserved_word, node *expr) {
	node *n = create_node(RESERVED_WORD_STATEMENT_NODE);
	n->data.reserved_word_statement = malloc(sizeof(*n->data.reserved_word_statement));
	assert(n->data.reserved_word_statement != NULL);
	n->data.reserved_word_statement->reserved_word = reserved_word;
	n->data.reserved_word_statement->expr = expr;
	return n;	
}
node *create_if_else_statement_node(node *expr, node *if_statement, node *else_statement) {
	node *n = create_node(IF_ELSE_STATEMENT_NODE);
	n->data.if_else_statement = malloc(sizeof(*n->data.if_else_statement));
	assert(n->data.if_else_statement != NULL);
	n->data.if_else_statement->expr = expr;
	n->data.if_else_statement->if_statement = if_statement;
	n->data.if_else_statement->else_statement = else_statement;
	return n;		
}
node *create_while_statement_node(node *expr, node *statement) {
	node *n = create_node(WHILE_STATEMENT_NODE);
	n->data.while_statement = malloc(sizeof(*n->data.while_statement));
	assert(n->data.while_statement != NULL);
	n->data.while_statement->expr = expr;
	n->data.while_statement->statement = statement;
	return n;		
}
node *create_do_statement_node(node *statement, node *expr) {
	node *n = create_node(DO_STATEMENT_NODE);
	n->data.do_statement = malloc(sizeof(*n->data.do_statement));
	assert(n->data.do_statement != NULL);
	n->data.do_statement->statement = statement;
	n->data.do_statement->expr = expr;
	return n;		
}
node *create_for_statement_node(node *for_expr, node *statement) {
	node *n = create_node(FOR_STATEMENT_NODE);
	n->data.for_statement = malloc(sizeof(*n->data.for_statement));
	assert(n->data.for_statement != NULL);
	n->data.for_statement->for_expr = for_expr;
	n->data.for_statement->statement = statement;
	return n;		
}
node *create_for_expr_node(node *initial_clause, node *goal_expr, node *advance_expr) {
	node *n = create_node(FOR_EXPR_NODE);
	n->data.for_expr = malloc(sizeof(*n->data.for_expr));
	assert(n->data.for_expr != NULL);
	n->data.for_expr->initial_clause = initial_clause;
	n->data.for_expr->goal_expr = goal_expr;
	n->data.for_expr->advance_expr = advance_expr;
	return n;			
}
node *create_pointer_decl_node(node *pointer, node *direct_declarator) {
	node *n = create_node(POINTER_DECL_NODE);
	n->data.pointer_decl = malloc(sizeof(*n->data.pointer_decl));
	assert(n->data.pointer_decl != NULL);
	n->data.pointer_decl->pointer = pointer;
	n->data.pointer_decl->direct_declarator = direct_declarator;
	return n;		
}
node *create_function_call_node(node *postfix_expr, node *expression_list) {	
	node *n = create_node(FUNCTION_CALL_NODE);
	n->data.function_call = malloc(sizeof(*n->data.function_call));
	assert(n->data.function_call != NULL);
	n->data.function_call->postfix_expr = postfix_expr;
	n->data.function_call->expression_list = expression_list;
	return n;		
}
node *create_type_name_node(node *declaration_specifiers, node *abstract_declarator) {	
	node *n = create_node(TYPE_NAME_NODE);
	n->data.type_name = malloc(sizeof(*n->data.type_name));
	assert(n->data.type_name != NULL);
	n->data.type_name->declaration_specifiers = declaration_specifiers;
	n->data.type_name->abstract_declarator = abstract_declarator;
	return n;		
}
node *create_cast_expr_node(node *type_name, node *cast_expr) {
	node *n = create_node(CAST_EXPR_NODE);
	n->data.cast_expr = malloc(sizeof(*n->data.cast_expr)); 
	assert(n->data.cast_expr != NULL);
	n->data.cast_expr->type_name = type_name;
	n->data.cast_expr->cast_expr = cast_expr;
	return n;			
}
node *create_expression_list_node(node *expression_list, node *assignment_expr) {
	node *n = create_node(EXPRESSION_LIST_NODE);
	n->data.expression_list = malloc(sizeof(*n->data.expression_list)); 
	assert(n->data.expression_list != NULL);
	n->data.expression_list->expression_list = expression_list;
	n->data.expression_list->assignment_expr = assignment_expr;
	return n;			
}
node *create_direct_abstract_declarator_node(node *n1, node *n2, node *n3, node *n4) {
	node *n = create_node(DIRECT_ABSTRACT_DECLARATOR_NODE);
	n->data.direct_abstract_declarator = malloc(sizeof(*n->data.direct_abstract_declarator)); 
	assert(n->data.direct_abstract_declarator != NULL);
	n->data.direct_abstract_declarator->n1 = n1;
	n->data.direct_abstract_declarator->n2 = n2;
	n->data.direct_abstract_declarator->n3 = n3;
	n->data.direct_abstract_declarator->n4 = n4;
	return n;			
}                      
node *create_pointer_node(node *pointer) {
	node *n = create_node(POINTER_NODE);
	n->data.pointer = malloc(sizeof(*n->data.pointer)); 
	assert(n->data.pointer != NULL);
	n->data.pointer->pointer = pointer;
	return n;			
}

node *create_null_statement_node() {
	node *n = create_node(NULL_STATEMENT_NODE);
	return n;
}
node *create_ternary_expr(node *logical_or_expr, node *expr, node *conditional_expr) {
	node *n = create_node(TERNARY_EXPR_NODE);
	n->data.ternary_expr = malloc(sizeof(*n->data.ternary_expr));
	assert(n->data.ternary_expr != NULL);
	n->data.ternary_expr->logical_or_expr = logical_or_expr;
	n->data.ternary_expr->expr = expr;
	n->data.ternary_expr->conditional_expr = conditional_expr;
	return n;
}

/***************************** PRETTY PRINTER FUNCTIONS *******************************/

void print_node(FILE *output, node *n) {
	assert(n != NULL);
	switch (n->node_type) {
	case NUMBER_NODE:
		print_number_node(output, n);
		break;
	case STRING_NODE:
		print_string_node(output, n);
		break;
	case IDENTIFIER_NODE:
		print_identifier_node(output, n);
		break;
	case UNARY_EXPRESSION_NODE:  
		print_unary_expr_node(output, n);
		break;
	case DECL_NODE:        
		print_decl_node(output, n);
		break;
	case INITIALIZED_DECLARATOR_LIST_NODE:        
		print_initialized_declarator_list_node(output, n);
		break;
	case RESERVED_WORD_NODE:
		print_reserved_word_node(output, n);
		break;
	case COMPOUND_NUMBER_TYPE_SPECIFIER_NODE:
		print_compound_number_type_specifier_node(output, n);
		break;
	case OPERATOR_NODE:
		print_operator_node(output, n);
		break;                        
	case INCREMENT_DECREMENT_EXPR_NODE:
		print_increment_decrement_expr_node(output, n);
		break;  
	case TRANSLATION_UNIT_NODE:
		print_translation_unit_node(output, n);
		break;
	case FUNCTION_DEF_SPECIFIER_NODE:
		print_function_def_specifier_node(output, n);
		break;
	case FUNCTION_DEFINITION_NODE:
		print_function_definition_node(output, n);
		break;
	case DECLARATION_OR_STATEMENT_LIST_NODE:
		print_declaration_or_statement_list_node(output, n);
		break;
	case COMPOUND_STATEMENT_NODE:
		print_compound_statement_node(output, n);
		break;
	case DIRECT_DECLARATOR_NODE:
		print_direct_declarator_node(output, n);
		break;
	case FUNCTION_DECLARATOR_NODE:
		print_function_declarator_node(output, n);
		break;
	case PARAMETER_LIST_NODE:
		print_parameter_list_node(output, n);
		break;
	case PARAMETER_DECL_NODE:
		print_parameter_decl_node(output, n);
		break;
	case ARRAY_DECLARATOR_NODE:
		print_array_declarator_node(output, n);
		break;
	case BINARY_EXPRESSION_NODE:
		print_binary_expr_node(output, n);
		break;
	case SUBSCRIPT_EXPR_NODE:
		print_subscript_expr_node(output, n);
		break;
	case STATEMENT_NODE:
		print_statement_node(output, n);
		break;
	case LABELED_STATEMENT_NODE:
		print_labeled_statement_node(output, n);
		break;
	case RESERVED_WORD_STATEMENT_NODE:
		print_reserved_word_statement_node(output, n);
		break;
	case IF_ELSE_STATEMENT_NODE:
		print_if_else_statement_node(output, n);
		break;
	case WHILE_STATEMENT_NODE:
		print_while_statement_node(output, n);
		break;
	case DO_STATEMENT_NODE:
		print_do_statement_node(output, n);
		break;
	case FOR_STATEMENT_NODE:
		print_for_statement_node(output, n);
		break;
	case FOR_EXPR_NODE:
		print_for_expr_node(output, n);
		break;
	case POINTER_DECL_NODE:
		print_pointer_decl_node(output, n);
		break;
	case FUNCTION_CALL_NODE:
		print_function_call_node(output, n);
		break;
	case TYPE_NAME_NODE:
		print_type_name_node(output, n);
		break;
	case CAST_EXPR_NODE:
		print_cast_expr_node(output, n);
		break;
	case EXPRESSION_LIST_NODE:
		print_expression_list_node(output, n);
		break;
	case DIRECT_ABSTRACT_DECLARATOR_NODE:
		print_direct_abstract_declarator_node(output, n);
		break;
	case POINTER_NODE:
		print_pointer_node(output, n);
		break;
	case NULL_STATEMENT_NODE:
		print_null_statement_node(output, n);
		break;    
	case TERNARY_EXPR_NODE:
		print_ternary_expr_node(output, n);
		break;
	default:
		fprintf(stderr, "Can't print current node of type %d", n->node_type);
	}	
}

void print_number_node(FILE *output, node *n) {
	if (n->data.number->is_char)
		fprintf(output, "'%c'", (char)n->data.number->value);
	else
		fprintf(output, "%lu", n->data.number->value);
}

void print_string_node(FILE *output, node *n) {
/*
	prints individual char values for debugging
	int i;
	for (i = 0; i < strlen(n->data.string->value); i++) {
		fprintf(output, "%d\n", n->data.string->value[i]);
	}
*/
	// fprintf(output, "\"%s\"", n->data.string->value);
	fputs("\"", output);
	int j;
	for (j = 0; j < n->data.string->length; j++) {
		fprintf(output, "%c", n->data.string->value[j]);
	}
	fputs("\"", output);
}
void print_identifier_node(FILE *output, node *n) {
	fprintf(output, "%s", n->data.identifier->name);
	if (n->data.identifier->symbol_table_identifier != NULL) {
		fprintf(output, "\t/* symbol %d */\t", n->data.identifier->symbol_table_identifier->id_number);
	}
}
void print_decl_node(FILE *output, node *n) {
	print_indentation(output);
	print_node(output, n->data.decl->declaration_specifier);
	print_node(output, n->data.decl->initialized_declarator_list);
	fputs(";\n", output);
}
void print_initialized_declarator_list_node(FILE *output, node *n) {
	if (n->data.initialized_declarator_list->initialized_declarator_list != NULL) {
		print_node(output, n->data.initialized_declarator_list->initialized_declarator_list);
	  fputs(", ", output);                                                     
	}
	print_node(output, n->data.initialized_declarator_list->initialized_declarator);
}        
void print_reserved_word_node(FILE *output, node *n) {
	fprintf(output, "%s ", n->data.reserved_word->text);
}
void print_compound_number_type_specifier_node(FILE *output, node *n) {
	int i;
	for (i = 0; i < 3; i++) {
		if (n->data.compound_number_type_specifier->reserved_words[i] != NULL)
			print_node(output, n->data.compound_number_type_specifier->reserved_words[i]);
	}
}
void print_operator_node(FILE *output, node *n) {
	fprintf(output, "%s", n->data.operator->text);
}
void print_increment_decrement_expr_node(FILE *output, node *n){
	print_node(output, n->data.increment_decrement_expr->operand);
	char *text = n->data.increment_decrement_expr->operator->data.operator->text;
	fprintf(output, "%s%s", text, text);
}
void print_translation_unit_node(FILE *output, node *n){
	if(n->data.translation_unit != NULL)
	{
		print_node(output, n->data.translation_unit->translation_unit);	
	}
	print_node(output, n->data.translation_unit->top_level_decl);
}
void print_function_def_specifier_node(FILE *output, node *n){ 
	if(n->data.function_def_specifier->declaration_specifiers != NULL)
	{       
		print_node(output, n->data.function_def_specifier->declaration_specifiers);	
	}
	print_node(output, n->data.function_def_specifier->declarator);
}
void print_function_definition_node(FILE *output, node *n){
	if(n->data.function_definition->function_def_specifier != NULL)
	{
		print_node(output, n->data.function_definition->function_def_specifier);	
	}
	print_node(output, n->data.function_definition->compound_statement);
}
void print_declaration_or_statement_list_node(FILE *output, node *n){
	if(n->data.declaration_or_statement_list->declaration_or_statement_list != NULL)
	{
		print_node(output, n->data.declaration_or_statement_list->declaration_or_statement_list);	
	}
	print_node(output, n->data.declaration_or_statement_list->declaration_or_statement);
}
void print_compound_statement_node(FILE *output, node *n){
	fputs("\n", output);
	print_indentation(output);
	fputs("{\n", output);
	indent++;
	if(n->data.compound_statement->declaration_or_statement_list != NULL)	
	{
		print_node(output, n->data.compound_statement->declaration_or_statement_list);
	}
	indent--;
	print_indentation(output);
	fputs("}\n", output);
}
void print_direct_declarator_node(FILE *output, node *n){  
	fputs("(", output);
	print_node(output, n->data.direct_declarator->declarator);
	fputs(")", output);
}
void print_function_declarator_node(FILE *output, node *n) {
	print_node(output, n->data.function_declarator->direct_declarator);
	fputs("(", output);
	print_node(output, n->data.function_declarator->parameter_type_list);
	fputs(")", output);
}
void print_parameter_list_node(FILE *output, node *n) {
	if (n->data.parameter_list->parameter_list != NULL) {
		print_node(output, n->data.parameter_list->parameter_list);
		fputs(", ", output);
	}
	print_node(output, n->data.parameter_list->parameter_decl);
}
void print_parameter_decl_node(FILE *output, node *n) {
	print_node(output, n->data.parameter_decl->declaration_specifiers);
	print_node(output, n->data.parameter_decl->declarator);
}
void print_array_declarator_node(FILE *output, node *n) {  
	print_node(output, n->data.array_declarator->direct_declarator);
	fputs("[", output);
	if (n->data.array_declarator->constant_expr != NULL)
		print_node(output, n->data.array_declarator->constant_expr);
	fputs("]", output);
}
void print_binary_expr_node(FILE *output, node *n) {
	fputs("(", output);
	print_node(output, n->data.binary_expression->left);
	print_node(output, n->data.binary_expression->op);
	print_node(output, n->data.binary_expression->right);
	fputs(")", output);	
}
void print_subscript_expr_node(FILE *output, node *n) {  
	print_node(output, n->data.subscript_expr->postfix_expr);
	fputs("[", output);
	print_node(output, n->data.subscript_expr->expr);
	fputs("]", output);
}
void print_unary_expr_node(FILE *output, node *n){
	fputs("(", output);
	if (n->data.unary_expression->op_first) {
		print_node(output, n->data.unary_expression->operator);
		print_node(output, n->data.unary_expression->operand);
	}
	else {
		print_node(output, n->data.unary_expression->operand);
		print_node(output, n->data.unary_expression->operator);		
	}
	fputs(")", output);
}
void print_statement_node(FILE *output, node *n){
	print_indentation(output);
	print_node(output, n->data.statement->statement);
	fputs(";\n", output);
}
void print_labeled_statement_node(FILE *output, node *n) {
	print_indentation(output);
	print_node(output, n->data.labeled_statement->label);
	fputs(" : ", output);
	print_node(output, n->data.labeled_statement->statement);	
	fputs("\n", output);
}
void print_reserved_word_statement_node(FILE *output, node *n) {
	print_node(output, n->data.reserved_word_statement->reserved_word);
	if (n->data.reserved_word_statement->expr)
		print_node(output, n->data.reserved_word_statement->expr);
}
void print_if_else_statement_node(FILE *output, node *n) {
	print_indentation(output);
	fputs("if ", output);	
	print_node(output, n->data.if_else_statement->expr);
	print_node(output, n->data.if_else_statement->if_statement);
	if (n->data.if_else_statement->else_statement != NULL) {
		print_indentation(output);
		fputs("else\n", output);	
		print_node(output, n->data.if_else_statement->else_statement);
	}
}
void print_while_statement_node(FILE *output, node *n){
	print_indentation(output);
	fputs("while (", output);
	print_node(output, n->data.while_statement->expr);
	fputs(")", output);
	print_node(output, n->data.while_statement->statement);
}
void print_do_statement_node(FILE *output, node *n){
	print_indentation(output);
	fputs("do", output);
	print_node(output, n->data.do_statement->statement);
	print_indentation(output);
	fputs("while (", output);
	print_node(output, n->data.do_statement->expr);
	fputs(");\n", output);
}
void print_for_statement_node(FILE *output, node *n){
	print_indentation(output);
	fputs("for", output);
	print_node(output, n->data.for_statement->for_expr);
	fputs("\n", output);
	print_node(output, n->data.for_statement->statement);
}
void print_for_expr_node(FILE *output, node *n){
	fputs("(", output);
	if (n->data.for_expr->initial_clause != NULL)
		print_node(output, n->data.for_expr->initial_clause);
	fputs(";", output);
	if (n->data.for_expr->goal_expr != NULL)
		print_node(output, n->data.for_expr->goal_expr);
	fputs(";", output);
	if (n->data.for_expr->advance_expr != NULL)
		print_node(output, n->data.for_expr->advance_expr);
	fputs(")\n", output);
}
void print_pointer_decl_node(FILE *output, node *n) {
	fputs("(", output);
	print_node(output, n->data.pointer_decl->pointer);
	print_node(output, n->data.pointer_decl->direct_declarator);
	fputs(")", output);
}
void print_function_call_node(FILE *output, node *n) {
	print_node(output, n->data.function_call->postfix_expr);
	fputs("(", output);
	if (n->data.function_call->expression_list)
		print_node(output, n->data.function_call->expression_list);
	fputs(")", output);
}
void print_type_name_node(FILE *output, node *n) {
	print_node(output, n->data.type_name->declaration_specifiers);
	if (n->data.type_name->abstract_declarator != NULL)
		print_node(output, n->data.type_name->abstract_declarator);
}
void print_cast_expr_node(FILE *output, node *n){
	fputs("(", output);
	print_node(output, n->data.cast_expr->type_name);
	fputs(")", output);
	print_node(output, n->data.cast_expr->cast_expr);
}
void print_expression_list_node(FILE *output, node *n){
	print_node(output, n->data.expression_list->expression_list);
	fputs(", ", output);
	print_node(output, n->data.expression_list->assignment_expr);
}
void print_direct_abstract_declarator_node(FILE *output, node *n){
	print_node(output, n->data.direct_abstract_declarator->n1);
	print_node(output, n->data.direct_abstract_declarator->n2);
	print_node(output, n->data.direct_abstract_declarator->n3);
	if (n->data.direct_abstract_declarator->n4 != NULL)
		print_node(output, n->data.direct_abstract_declarator->n4);
}
void print_pointer_node(FILE *output, node *n){
	fputs("*", output);
	print_node(output, n->data.pointer->pointer);
}
void print_null_statement_node(FILE *output, node *n) {
	print_indentation(output);
	fputs(";\n", output);
}
void print_ternary_expr_node(FILE *output, node *n) {
	print_node(output, n->data.ternary_expr->logical_or_expr);
	fputs(" ? ", output);
	print_node(output, n->data.ternary_expr->expr);
	fputs(" : ", output);
	print_node(output, n->data.ternary_expr->conditional_expr);	
}
void print_indentation(FILE *output) {
	int i;
	for (i = 1; i <= indent; i++) {
		fputs("  ", output);
	}
}

/***********SYMBOL TABLE DEFINITIONS****************/                                       

// symbol_table_entry *create_symbol_table_entry(node *declaration_specifiers, node *initialized_declarator_list){  
// 	symbol_table_entry *entry = malloc(sizeof(*entry));
// 	entry->name = initialized_declarator_list->data.identifier->name;
// 	entry->scope_id = scope;	
// 	switch (declaration_specifiers->node_type) {
// 	case RESERVED_WORD_NODE: /* can only be int, short, long, char */
// 		// switch (declaration_specifiers->data.reserved_word->value) {
// 		// case INT:
// 		// case LONG:
// 		// case SHORT:
// 		// case CHAR:
// 			assert(entry != NULL);
// 			entry->type = ARITHMETIC_TYPE;
// 			entry->data.arithmetic_type_entry = malloc(sizeof(*entry->data.arithmetic_type_entry));
// 			entry->data.arithmetic_type_entry->arithmetic_type = declaration_specifiers;
// 		// 	break;
// 		// }
// 		break;
// 	}
// 	return entry;
// }
// void print_symbol_table_entry(FILE *output, symbol_table_entry *entry) {
// 	switch (entry->type) {
// 	case ARITHMETIC_TYPE:
// 		print_node(output, entry->data.arithmetic_type_entry->arithmetic_type);
// 		break;
// 	}
// 	fputs(entry->name, output);
// }


void add_to_symbol_table_list(symbol_table *list, symbol_table *new) {
	symbol_table *old = get_last_symbol_table_list_element(list);
	if (old == NULL) { // empty list, so put 'new' in as first element
		old = new;
	}
	else {
		old->next = new;
	}
}
void add_to_symbol_table_identifier_list(symbol_table_identifier *list, symbol_table_identifier *new) {
	symbol_table_identifier *old = get_last_symbol_table_identifier_list_element(list);
	if (old == NULL) { // empty list, so put 'new' in as first element
		old = new;
	}
	else {
		old->next = new;
	}
}

symbol_table *get_last_symbol_table_list_element(symbol_table *list) {
	// list can be null, 1 element (next == NULL) or more
	if (list == NULL) {
		return NULL;
	}
	else {
		if (list->next == NULL) {
			return list;
		}
		else {
			symbol_table *last = list->next;
			while (last->next != NULL) {
				last = last->next;
			}
			return last;	
		}
	}
}
symbol_table_identifier *get_last_symbol_table_identifier_list_element(symbol_table_identifier *list) {
	// list can be null, 1 element (next == NULL) or more
	if (list == NULL) {
		return NULL;
	}
	else {
		if (list->next == NULL) {
			return list;
		}
		else {
			symbol_table_identifier *last = list->next;
			while (last->next != NULL) {
				last = last->next;
			}
			return last;	
		}
	}
}

void create_symbol_table(node *n, symbol_table *st) {
	switch (n->node_type) {
	case DECL_NODE:
		create_decl_node_symbol_table(n, st);
		break;
	case TRANSLATION_UNIT_NODE: // can be compound statement or function def
		create_symbol_table(n->data.translation_unit->translation_unit, st);
		create_symbol_table(n->data.translation_unit->top_level_decl, st);
		break;
	case FUNCTION_DEFINITION_NODE:
		create_function_def_specifier_node_symbol_table(n->data.function_definition->function_def_specifier, st, n->data.function_definition->compound_statement);
		break;
	case COMPOUND_STATEMENT_NODE:
		create_compound_statement_node_symbol_table(n, st, 1);
		break;
	case DECLARATION_OR_STATEMENT_LIST_NODE:
		create_declaration_or_statement_list_node_symbol_table(n, st);
		break;
	default:
		break;
	}
}

symbol_table_identifier *create_identifier(symbol_table *st) {
	symbol_table_identifier *current = malloc(sizeof(symbol_table_identifier));
	assert(current != NULL);
	add_to_symbol_table_identifier_list(st->identifiers, current);
	advance_current_identifier(current);
	return current;
}

void create_decl_node_symbol_table(node *n, symbol_table *st) {
	if (st->identifiers == NULL) {
		st->identifiers = malloc(sizeof(*st->identifiers));
		assert(st->identifiers != NULL);
	}
	symbol_table_identifier *current = create_identifier(st);
	node *decl_spec = n->data.decl->declaration_specifier;
	node *initialized_declarator_list = n->data.decl->initialized_declarator_list;
	int declarator_node_type =  initialized_declarator_list->data.initialized_declarator_list->initialized_declarator->node_type;
	if (declarator_node_type == POINTER_DECL_NODE) {
		printf("i has a pointer\n");
		current->type = POINTER_TYPE;     
		// current->name = 
		// i->data.pointer_identifier->base = ;
	}
	else if (declarator_node_type == ARRAY_DECLARATOR_NODE) {
		current->type = ARRAY_TYPE;
		current->name = initialized_declarator_list->data.initialized_declarator_list->initialized_declarator->data.array_declarator->direct_declarator->data.identifier->name;		initialized_declarator_list->data.initialized_declarator_list->initialized_declarator->data.array_declarator->direct_declarator->data.identifier->symbol_table_identifier = current;
		current->data.array_identifier = malloc(sizeof(*current->data.array_identifier));
		assert(current->data.array_identifier != NULL);
		array_identifier *ai = current->data.array_identifier;
		node *array_declarator = initialized_declarator_list->data.initialized_declarator_list->initialized_declarator;
		if (array_declarator->data.array_declarator->constant_expr->node_type == NUMBER_NODE) { 
			// if not NUMBER_NODE, it's an IDENTIFIER_NODE or expr, so size is unknown
			ai->size = array_declarator->data.array_declarator->constant_expr->data.number->value;
		}
		if (decl_spec->node_type == COMPOUND_NUMBER_TYPE_SPECIFIER_NODE) {
			ai->element_type = decl_spec->data.compound_number_type_specifier->number_type;
		}
	}
	else if (decl_spec->node_type == COMPOUND_NUMBER_TYPE_SPECIFIER_NODE) {
		current->type = ARITHMETIC_TYPE;
		current->name = initialized_declarator_list->data.initialized_declarator_list->initialized_declarator->data.identifier->name;
		initialized_declarator_list->data.initialized_declarator_list->
			initialized_declarator->data.identifier->symbol_table_identifier = current;
		current->data.arithmetic_identifier = malloc(sizeof(arithmetic_identifier));
		arithmetic_identifier *ai = current->data.arithmetic_identifier;
		assert(ai != NULL);
		ai->is_unsigned = decl_spec->data.compound_number_type_specifier->is_unsigned;
		ai->number_type = decl_spec->data.compound_number_type_specifier->number_type;
	}
}

void create_function_def_specifier_node_symbol_table(node *n, symbol_table *st, node *compound_statement) {
	if (st->identifiers == NULL) {
		st->identifiers = malloc(sizeof(*st->identifiers));
		assert(st->identifiers != NULL);
	}
	symbol_table_identifier *current = create_identifier(st);
	current->type = FUNCTION_TYPE;
	current->name = n->data.function_def_specifier->declarator->data.direct_declarator->declarator->data.identifier->name;
	n->data.function_def_specifier->declarator->data.direct_declarator->declarator->data.identifier->symbol_table_identifier = current;
	node *decl_spec = n->data.function_def_specifier->declaration_specifiers;
	current->data.function_identifier = malloc(sizeof(*current->data.function_identifier));
	if (decl_spec->node_type == RESERVED_WORD_NODE && !strcmp(decl_spec->data.reserved_word->text, "void")) {
		current->data.function_identifier->return_type = VOID_TYPE;
	}
	else if (n->data.function_def_specifier->declarator->node_type == POINTER_DECL_NODE) {
		current->data.function_identifier->return_type = POINTER_TYPE;
	}
	else if (decl_spec->node_type == COMPOUND_NUMBER_TYPE_SPECIFIER_NODE) {
		current->data.function_identifier->return_type = decl_spec->data.compound_number_type_specifier->number_type; 
	}
	node *parameter_type_list = n->data.function_def_specifier->declarator->data.function_declarator->parameter_type_list;
	if (parameter_type_list->node_type == PARAMETER_LIST_NODE) {
		current->data.function_identifier->argc = parameter_type_list->data.parameter_list->number_of_params;
	}
	else {
		current->data.function_identifier->argc = 1;
	}
	//now prepare the function scope ST then add the arguments to it
	if (st->children == NULL) {
		st->children = malloc(sizeof(*st->children));
		assert(st->children != NULL);
		create_compound_statement_node_symbol_table(compound_statement, st->children, 0);
		create_symbol_table(parameter_type_list, st->children);
	}
	else {
		symbol_table *new = malloc(sizeof(symbol_table));
		assert(new != NULL);
		add_to_symbol_table_list(st->children, new);
		create_compound_statement_node_symbol_table(compound_statement, new, 0);
		create_symbol_table(parameter_type_list, new);
	}
}

void create_compound_statement_node_symbol_table(node *n, symbol_table *st, int create_new_symbol_table) {
	if (n->data.compound_statement->declaration_or_statement_list != NULL) {
	// if create_new_symbol_table is 0, which is only in a function definition, then just 
		if (create_new_symbol_table) {
			if (st->children == NULL) {
				st->children = malloc(sizeof(*st->children));
				assert(st->children != NULL);
				create_symbol_table(n->data.compound_statement->declaration_or_statement_list, st->children);
			}
			else {
				printf("OHAI\n");
				symbol_table *new = malloc(sizeof(symbol_table));
				assert(new != NULL);
				add_to_symbol_table_list(st->children, new);
				create_symbol_table(n->data.compound_statement->declaration_or_statement_list, new);
			}
		}
		else {
			create_symbol_table(n->data.compound_statement->declaration_or_statement_list, st);
		}
	}
}

void create_declaration_or_statement_list_node_symbol_table(node *n, symbol_table *st) {
	if (n->data.declaration_or_statement_list->declaration_or_statement_list != NULL) {
		create_symbol_table(n->data.declaration_or_statement_list->declaration_or_statement_list, st);
	}
	create_symbol_table(n->data.declaration_or_statement_list->declaration_or_statement, st);
}
void advance_current_identifier(symbol_table_identifier *current) {
	// // when first node, just start modifying current right away and don't set current->next
	// // otherwise, create current->next and set current to it, then proceed
	// if (id_number > 1) {
	// 	symbol_table_identifier *next = malloc(sizeof(*next));
	// 	current->next = next;
	// 	current = next;
	// }
	current->id_number = id_number;
	id_number++;
}

/************** SYMBOL TABLE PRINTING FUNCTIONS *******************/

void print_symbol_table(FILE *output, symbol_table *s) {
	// print identifiers
	print_indentation(output);
	fputs("Identifiers:\n", output);
	symbol_table_identifier *i = s->identifiers;
	while (i != NULL) {
		print_indentation(output);
		print_symbol_table_identifier(output, i);
		i = i->next;
	}
	fputs("\n", output);
	// print children
	if (s->children != NULL) {		
		indent++;
		print_indentation(output);
		fputs("Children:\n", output);
		print_symbol_table(output, s->children); // this will print any subsequent children when those children print their siblings
		indent--;
	}
	fputs("\n", output);
	// print next ST                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       
	if (s->next != NULL) {
		print_symbol_table(output, s->next); // this will print all subsequent siblings
	}
}
void print_symbol_table_identifier(FILE *output, symbol_table_identifier *i) {
	fprintf(output, "%s -> %s, %d, ", i->name, i->name, i->id_number);
	switch (i->type) {
	case ARITHMETIC_TYPE:
		print_arithmetic_identifier(output, i);
		break;
	case POINTER_TYPE:
		print_pointer_identifier(output, i);
		break;
	case ARRAY_TYPE:
		print_array_identifier(output, i);
		break;
	case FUNCTION_TYPE:
		print_function_identifier(output, i);
		break;
	}
}

void print_arithmetic_identifier(FILE *output, symbol_table_identifier *i) {
	char *sign = i->data.arithmetic_identifier->is_unsigned ? "unsigned" : "signed";
	fprintf(output, "%s %s\n", sign, types[i->data.arithmetic_identifier->number_type]);
}
void print_pointer_identifier(FILE *output, symbol_table_identifier *i) {
	
}
void print_array_identifier(FILE *output, symbol_table_identifier *i) {
	fprintf(output, "array (%d, %s)\n", i->data.array_identifier->size, types[i->data.array_identifier->element_type]);
}
void print_function_identifier(FILE *output, symbol_table_identifier *i) {
	function_identifier *data = i->data.function_identifier;
	fprintf(output, "function (%s, %d, %s)\n", types[data->return_type], data->argc, children_identifier_to_string(data->argv));
}

void add_types() {
	types[NUMBER_TYPE_INT] = "int";
	types[NUMBER_TYPE_LONG] = 	"long int";
	types[NUMBER_TYPE_SHORT] = "short int";
	types[NUMBER_TYPE_CHAR] = "char";
	types[VOID_TYPE] = "void";
	types[POINTER_TYPE] = "pointer";
}

int get_type_from_node(node *n) {
	// can return constants representing one of: int, long, short, char, pointer, array 
	
}

char *children_identifier_to_string(symbol_table_identifier *i) {
	return "pretend string is here";
}