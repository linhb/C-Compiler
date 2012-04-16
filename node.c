/*
Definitions of functions that create and print different kinds of nodes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "node.h"
#include "y.tab.h"

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

node *create_number_node(char *yytext) {
	node *num = create_node(NUMBER_NODE);
	// DEBUG
	// printf("node type %d\n", num->node_type);
	num->data.number = malloc(sizeof(number));
	assert(num->data.number != NULL);
	num->data.number->value = strtoul(yytext, NULL, 10);
	unsigned long int ul_limit = 4294967295UL;
	unsigned long int int_limit = 2147483647UL;
	unsigned long int value = num->data.number->value;
	if (value <= int_limit)
		num->data.number->type = INT;    
 	else if (value <= ul_limit)
		num->data.number->type = LONG;    
	else { /* overflow */
		num->data.number->value = ul_limit;
		num->data.number->type = LONG;    
		num->data.number->overflow = 1;
	}
	return num;
}     
node *create_string_node(char *yytext) {
	node *string = create_node(STRING_NODE);
	string->data.string = malloc(sizeof(*string->data.string));
	string->data.string->value = escape_string(yytext);
	assert(string->data.string->value != NULL);
	string->data.string->length = strlen(string->data.string->value);
	return string;
}
node *create_char_node(char *yytext) { // yytext = "'\127'"
	node *char_node = create_node(NUMBER_NODE);
	char_node->data.number = malloc(sizeof(*char_node->data.number));
	// extract the escape sequence from yytext with escape_string, then extract the integer value and assign it to value
	char_node->data.number->value = escape_string(yytext)[0];
	char_node->data.number->type = CHAR;
	return char_node;
}

node *create_identifier_node(char *yytext) {
	node *identifier = create_node(IDENTIFIER_NODE);
	identifier->data.identifier = malloc(sizeof(*identifier->data.identifier));
	identifier->data.identifier->name = strdup(yytext);
	assert(identifier->data.identifier->name != NULL);
	return identifier;
}
node *create_reserved_word_node(char *yytext, int value) {
	node *reserved_word = create_node(RESERVED_WORD_NODE);
	reserved_word->data.reserved_word = malloc(sizeof(*reserved_word->data.reserved_word));
	reserved_word->data.reserved_word->text = strdup(yytext);
	assert(reserved_word->data.reserved_word->text != NULL);
	reserved_word->data.reserved_word->value = value;
	return reserved_word;
}
node *create_operator_node(char *yytext, int value) {
	node *operator = create_node(OPERATOR_NODE);
	operator->data.operator = malloc(sizeof(*operator->data.operator));
	operator->data.operator->text = strdup(yytext);
	assert(operator->data.operator->text != NULL);
	operator->data.operator->value = value;
	return operator;
}
char *escape_string(char *yytext) {
	int yytext_size = strlen(yytext);
	/* this will end up malloc'ing more memory than needed if yytext contains escape sequences, because something like \n that takes up 2 chars in yytext will only take up 1 char in string */
	char *string = malloc(yytext_size);
	int i;  // index of current char in yytext
	int j = 0; // index of char being written to in string
	for (i = 1; i < yytext_size - 1; j++) {  // start at 1 and end 1 char short of the actual end to get rid of the single/double quotes
		if (yytext[i] == '\\') {
			if (yytext[i+1] == 'n') {
				string[j] = '\n';
				// advance current char by 2 because two chars in yytext have just been processed at once
				i = i + 2;
			}
			else if (yytext[i+1] == 't') {
				string[j] = '\t';
				i = i + 2;
			}			
			else if (yytext[i+1] == 'b') {
				string[j] = '\b';
				i = i + 2;
			}
			else if (yytext[i+1] == 'r') {
				string[j] = '\r';
				i = i + 2;
			}
			else if (yytext[i+1] == 'f') {
				string[j] = '\f';
				i = i + 2;
			}
			else if (yytext[i+1] == 'v') {
				string[j] = '\v';
				i = i + 2;
			}
			else if (yytext[i+1] == 'a') {
				string[j] = '\a';
				i = i + 2;
			}
			else if (yytext[i+1] == '\\') {
				string[j] = '\\';
				i = i + 2;
			}
			else if (yytext[i+1] == '\'') {
				string[j] = '\'';
				i = i + 2;
			}
			else if (yytext[i+1] == '\"') {
				string[j] = '\"';
				i = i + 2;
			}
			else if (yytext[i+1] == '0') {
				string[j] = '\0';
				i = i + 2;
			}
			else if (yytext[i+1] == '?') {
				string[j] = '?';
				i = i + 2;
			}
			else if (yytext[i+1] >= '0' && yytext[i+1] <= '7') {
				int value = strtoul(&yytext[i+1], NULL, 8);
				if (value <= 7) {
					string[j] = value;
					i = i + 2;
				}
					// values from 8 (010) to 63 (077) take up 3 chars, so advance by 3
				else if (value <= 63) {
					string[j] = value;
					i = i + 3;
				}
				else if (value <= 255) {
					string[j] = value;
					i = i + 4;
				}
				else
					i = i + 4;					
			}
			else // invalid escape code, ignore the \ and the character that follows, move on
				i = i + 2;
		}
		else {
			string[j] = yytext[i];
			i++;
		}
	}
	return string;
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
		n->data.compound_number_type_specifier->number_type = SHORT;
	}
	else if (is_type(n, 0, "long") || is_type(n, 1, "long")) {
		n->data.compound_number_type_specifier->number_type = LONG;
	}	
	else if (is_type(n, 0, "char") || is_type(n, 1, "char")) {
		n->data.compound_number_type_specifier->number_type = CHAR;
	}
	else {
		n->data.compound_number_type_specifier->number_type = INT;
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
		// if 1 arg, no parameter_list node was created, so this function is never called, so number_of_params will never be 1
		// if 2 args, 1 parameter_list node will be created which is the node being created right now, which will have NULL parameter_list
		// there will only be a parent parameter_list node of type PARAMETER_LIST_NODE if there are 3 or more arguments
	if (parameter_list != NULL && parameter_list->node_type == PARAMETER_LIST_NODE) {
		int number_of_params = parameter_list->data.parameter_list->number_of_params;
		n->data.parameter_list->number_of_params = number_of_params + 1;
	}
	else {
		n->data.parameter_list->number_of_params = 2;
	}
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
node *create_abstract_declarator_node(node *pointer, node *direct_abstract_declarator) {
	node *n = create_node(ABSTRACT_DECLARATOR_NODE);
	n->data.abstract_declarator = malloc(sizeof(*n->data.abstract_declarator));
	assert(n->data.abstract_declarator != NULL);
	n->data.abstract_declarator->pointer = pointer;
	n->data.abstract_declarator->direct_abstract_declarator = direct_abstract_declarator;
	return n;
}

node *create_comma_expr_node(node *comma_expr, node *assignment_expr) {
	node *n = create_node(COMMA_EXPR_NODE);
	n->data.comma_expr = malloc(sizeof(*n->data.comma_expr));
	assert(n->data.comma_expr != NULL);
	n->data.comma_expr->comma_expr = comma_expr;
	n->data.comma_expr->assignment_expr = assignment_expr;
	return n;
}

/***************************** PRETTY PRINTER FUNCTIONS *******************************/

void print_node(FILE *output, node *n) {
	assert(n != NULL);
	// DEBUG
	// printf("\nPrinting node type %d\n", n->node_type);
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
	case ABSTRACT_DECLARATOR_NODE:
		print_abstract_declarator_node(output, n);
		break;
	case COMMA_EXPR_NODE:
		print_comma_expr_node(output, n);
		break;
	default:
		fprintf(stderr, "ERROR: Can't print current node of type %d", n->node_type);
	}	
}

void print_number_node(FILE *output, node *n) {
	if (n->data.number->type == CHAR)
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
		fprintf(output, "\t/* symbol %d */\t", n->data.identifier->symbol_table_identifier->identifier_id);
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
	fputs("(", output);
	print_node(output, n->data.array_declarator->direct_declarator);
	fputs("[", output);
	if (n->data.array_declarator->constant_expr != NULL)
		print_node(output, n->data.array_declarator->constant_expr);
	fputs("]", output);
	fputs(")", output);
}
void print_binary_expr_node(FILE *output, node *n) {
	fputs("(", output);
	print_node(output, n->data.binary_expression->left);
	print_node(output, n->data.binary_expression->op);
	print_node(output, n->data.binary_expression->right);
	fputs(")", output);	
}
void print_subscript_expr_node(FILE *output, node *n) {  
	node *postfix_expr = n->data.subscript_expr->postfix_expr;
	fputs("(", output);
	print_node(output, postfix_expr);
	fputs("[", output);
	print_node(output, n->data.subscript_expr->expr);
	fputs("]", output);
	fputs(")", output);
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
	fputs("if (", output);	
	print_node(output, n->data.if_else_statement->expr);
	fputs(")", output);	
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
void print_abstract_declarator_node(FILE *output, node *n) {
	print_node(output, n->data.abstract_declarator->pointer);
	print_node(output, n->data.abstract_declarator->direct_abstract_declarator);
}
void print_comma_expr_node(FILE *output, node *n) {
	if (n->data.comma_expr->comma_expr != NULL) {
		print_node(output, n->data.comma_expr->comma_expr);
	  fputs(", ", output);                                                     
	}
	print_node(output, n->data.comma_expr->assignment_expr);
}        
void print_indentation(FILE *output) {
	int i;
	for (i = 1; i <= indent; i++) {
		fputs("  ", output);
	}
}

symbol_table *add_to_symbol_table_list(symbol_table *list, symbol_table *new) {
	symbol_table *old = get_last_symbol_table_list_element(list);
	if (old == NULL) { // empty list, so put 'new' in as first element   
		list = malloc(sizeof(symbol_table));
		assert(list != NULL);
		list = new;
	}
	else {
		old->next = new;
	}
	return list;
}
symbol_table_identifier *add_to_symbol_table_identifier_list(symbol_table_identifier *list, symbol_table_identifier *new) {
	symbol_table_identifier *old = get_last_symbol_table_identifier_list_element(list);
	if (old == NULL) { // empty list, so put 'new' in as first element   
		list = malloc(sizeof(symbol_table_identifier));
		assert(list != NULL);
		list = new;
	}
	else {
		old->next = new;
	}
	return list;
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
symbol_table_identifier *find_identifier_in_symbol_table(symbol_table *st, char *name) {
	symbol_table_identifier *i;
	if ((i = find_identifier_in_same_symbol_table(st, name)) != NULL) {
		return i;
	}
	else if (st->parent != NULL) {
		return find_identifier_in_symbol_table(st->parent, name);
	}
	else {
		return NULL;
	}
}
symbol_table_identifier *find_identifier_in_same_symbol_table(symbol_table *st, char *name) {
	symbol_table_identifier *i;
	if (st->identifiers != NULL && ((i = find_in_identifier_list(st->identifiers, name)) != NULL)) {
		return i;
	}
	else {
		return NULL;
	}
}
symbol_table_identifier *find_in_identifier_list(symbol_table_identifier *list, char *name) {
	symbol_table_identifier *current = list;
	if (current->name != NULL && !strcmp(current->name, name)) { // check 1st element
		return current;
	}
	else if (current->next != NULL) { 
		while ((current = current->next) != NULL) {
			if (!strcmp(current->name, name)) { 
				return current;
			}
		}
		return NULL;
	}
	else { // list has only 1 element and it's not it, so not found
		return NULL;
	}
}

// void evaluate(node *n) {
// 	if all_numbers(n) {
// 		switch (n->node_type) {
// 			case BINARY_EXPRESSION_NODE:
// 			switch (n->data.binary_expression->op->data.operator->value) {
// 				
// 			}
// 			case UNARY_EXPRESSION_NODE:
// 			n->data.
// 			switch (n->data.unary_expression->operator->data.operator->value) {
// 				case BITWISE_COMPLEMENT:
// 				
// 			}
// 		}
// 	}
// }
int all_numbers(node *n) {
	switch (n->node_type) {
	case BINARY_EXPRESSION_NODE:
		return (all_numbers(n->data.binary_expression->left) && all_numbers(n->data.binary_expression->right));
	case UNARY_EXPRESSION_NODE:
		return all_numbers(n->data.unary_expression->operand);
	case NUMBER_NODE:
		return 1;
	case IDENTIFIER_NODE:
		return 0;
	case STRING_NODE:
		return 0;
	default:
		return 0;
	}
}
void create_symbol_table(node *n, symbol_table *st) {
	// evaluate(n);
	if (n != NULL) {
		switch (n->node_type) {
		case DECL_NODE:
			create_decl_node_symbol_table(n, st);
			break;
		case TRANSLATION_UNIT_NODE: 
			create_symbol_table(n->data.translation_unit->translation_unit, st);
			// printf("made ST for type %d", n->data.translation_unit->translation_unit->node_type);
			create_symbol_table(n->data.translation_unit->top_level_decl, st);
			// printf("made ST for type %d", n->data.translation_unit->top_level_decl->node_type);
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
		case PARAMETER_LIST_NODE:
			create_parameter_list_node_symbol_table(n, st);
			break;
		case PARAMETER_DECL_NODE:
			create_parameter_decl_node_symbol_table(n, st);
			break;
		case SUBSCRIPT_EXPR_NODE:
			create_subscript_expr_node_symbol_table(n, st);
			break;
		case BINARY_EXPRESSION_NODE:
			create_symbol_table(n->data.binary_expression->left, st);
			create_symbol_table(n->data.binary_expression->right, st);
			break;
		case STATEMENT_NODE:
			create_symbol_table(n->data.statement->statement, st);
			break;
			case IDENTIFIER_NODE: // if seeing an identifier here, it wasn't part of a declaration, so just have to add its ST entry to it
			create_identifier_node_symbol_table(n, st);
			break;
		case IF_ELSE_STATEMENT_NODE:
			create_symbol_table(n->data.if_else_statement->expr, st);
			create_symbol_table(n->data.if_else_statement->if_statement, st);
			create_symbol_table(n->data.if_else_statement->else_statement, st);
			break;
		case UNARY_EXPRESSION_NODE:
			create_symbol_table(n->data.unary_expression->operand, st);
			break;
		case CAST_EXPR_NODE:
			create_symbol_table(n->data.cast_expr->cast_expr, st);
			break;
		case DO_STATEMENT_NODE:
			create_symbol_table(n->data.do_statement->statement, st);
			create_symbol_table(n->data.do_statement->expr, st);
			break;
		case WHILE_STATEMENT_NODE:
			create_symbol_table(n->data.while_statement->expr, st);
			create_symbol_table(n->data.while_statement->statement, st);
			break;
		case FOR_STATEMENT_NODE:
			create_symbol_table(n->data.for_statement->for_expr, st);
			create_symbol_table(n->data.for_statement->statement, st);
			break;
		case FOR_EXPR_NODE:
			create_symbol_table(n->data.for_expr->initial_clause, st);
			create_symbol_table(n->data.for_expr->goal_expr, st);
			create_symbol_table(n->data.for_expr->advance_expr, st);
			break;
		case RESERVED_WORD_STATEMENT_NODE:
			create_symbol_table(n->data.reserved_word_statement->expr, st);
			break;
		case TERNARY_EXPR_NODE:
			create_symbol_table(n->data.ternary_expr->logical_or_expr, st);
			create_symbol_table(n->data.ternary_expr->expr, st);
			create_symbol_table(n->data.ternary_expr->conditional_expr, st);
			break;
		default:
			// DEBUG
			// printf("Node type %d: No action required\n", n->node_type);
			break;
		} 
	}
}

symbol_table_identifier *create_identifier(symbol_table *st) {
	symbol_table_identifier *current = malloc(sizeof(symbol_table_identifier));
	assert(current != NULL);
	advance_current_identifier(current);
	return current;
}
int redeclared_variable(symbol_table *st, char *name) {
	if (find_identifier_in_same_symbol_table(st, name) != NULL) {
		printf("ERROR: variable %s redeclared\n", name);
		return 1;
	}
	return 0;
}
node *get_identifier_from_declarator(node *n) {
	switch (n->node_type) {
	case IDENTIFIER_NODE:
		return n;
	case ARRAY_DECLARATOR_NODE:
		return get_identifier_from_declarator(n->data.array_declarator->direct_declarator);
	case POINTER_DECL_NODE:
		return get_identifier_from_declarator(n->data.pointer_decl->direct_declarator);
	case FUNCTION_DEF_SPECIFIER_NODE:
		return get_identifier_from_declarator(n->data.function_def_specifier->declarator->data.direct_declarator->declarator);
	default:
		printf("ERROR: tried to get name from unknown node %d\n", n->node_type);
	}
}
void create_decl_node_symbol_table(node *n, symbol_table *st) {
	node *decl_spec = n->data.decl->declaration_specifier;
	node *initialized_declarator_list = n->data.decl->initialized_declarator_list;
	// create ID for initialized_declarator_list from bottom to top
	symbol_table_identifier *current = create_identifier(st);
	create_decl_identifier(n, decl_spec, initialized_declarator_list->data.initialized_declarator_list->initialized_declarator, current, st);
	node *idl = initialized_declarator_list->data.initialized_declarator_list->initialized_declarator_list;
	while (idl != NULL) {
		symbol_table_identifier *current = create_identifier(st);
		create_decl_identifier(n, decl_spec, idl->data.initialized_declarator_list->initialized_declarator, current, st);
		idl = idl->data.initialized_declarator_list->initialized_declarator_list;
	}
}
symbol_table_identifier *create_decl_identifier(node *parent, node *decl_spec, node *declarator, symbol_table_identifier *current, symbol_table *st) {
	int declarator_node_type =  declarator->node_type;
	if (declarator_node_type == POINTER_DECL_NODE) {
		node *id = get_identifier_from_declarator(declarator->data.pointer_decl->direct_declarator);
		current->name = id->data.identifier->name;
		id->data.identifier->symbol_table_identifier = current;
	}
	else if (declarator_node_type == ARRAY_DECLARATOR_NODE) {
		node *id = get_identifier_from_declarator(declarator->data.array_declarator->direct_declarator);
		current->name = id->data.identifier->name;			
		id->data.identifier->symbol_table_identifier = current;
	}
	else if (decl_spec->node_type == COMPOUND_NUMBER_TYPE_SPECIFIER_NODE) { // vanilla primitive type
		node *id = get_identifier_from_declarator(declarator);
		current->name = id->data.identifier->name;
		id->data.identifier->symbol_table_identifier = current;
	}
	else if (decl_spec->node_type == RESERVED_WORD_NODE && !strcmp(decl_spec->data.reserved_word->text, "void")) {
		current->name = get_identifier_from_declarator(declarator)->data.identifier->name;
		printf("ERROR: variable %s: void is not a valid type\n", current->name);
		current = NULL;
	}
	else {
		printf("ERROR: unknown decl type %d\n", declarator_node_type);
	}
	if (current != NULL && redeclared_variable(st, current->name)) {
		current = NULL;
	}
	if (current != NULL) {
		current->type = get_type_from_decl_node(parent);
		st->identifiers = add_to_symbol_table_identifier_list(st->identifiers, current); 
  }       
	return current;
}

void create_function_def_specifier_node_symbol_table(node *n, symbol_table *st, node *compound_statement) {
	symbol_table_identifier *current = create_identifier(st);
	current->name = get_identifier_from_declarator(n->data.function_def_specifier->declarator->data.direct_declarator->declarator)->data.identifier->name;
	if (redeclared_variable(st, current->name)) {
		current = NULL;
	}
	else {
		current->type = get_type_from_decl_node(n);
		n->data.function_def_specifier->declarator->data.direct_declarator->declarator->data.identifier->symbol_table_identifier = current;
		//now prepare the function scope ST then add the arguments to it
		node *parameter_type_list = n->data.function_def_specifier->declarator->data.function_declarator->parameter_type_list;
		if (st->children == NULL) {
			st->children = malloc(sizeof(*st->children));
			assert(st->children != NULL);
			current_scope_level++;
			st->children->scope_level = current_scope_level;
			st_id++;
			st->children->st_id = st_id;
			st->children->parent = st;
			create_compound_statement_node_symbol_table(compound_statement, st->children, 0);
			current_scope_level--;
			st->children->parent_function_identifier = current;
			create_symbol_table(parameter_type_list, st->children);
		}
		else {
			symbol_table *new = malloc(sizeof(symbol_table));
			assert(new != NULL);
			current_scope_level++;
			new->scope_level = current_scope_level;
			st_id++;
			new->st_id = st_id;
			st->children = add_to_symbol_table_list(st->children, new);
			new->parent = st;
			create_compound_statement_node_symbol_table(compound_statement, new, 0);
			current_scope_level--;
			new->parent_function_identifier = current;
			create_symbol_table(parameter_type_list, new);
		} 
	}
	if (current != NULL) {
		st->identifiers = add_to_symbol_table_identifier_list(st->identifiers, current); 
	}
}

void create_compound_statement_node_symbol_table(node *n, symbol_table *st, int create_new_symbol_table) {
	if (n->data.compound_statement->declaration_or_statement_list != NULL) {
	// if create_new_symbol_table is 0, which is only in a function definition, then just 
		if (create_new_symbol_table) {
			if (st->children == NULL) {
				st->children = malloc(sizeof(*st->children));
				assert(st->children != NULL);
				current_scope_level++;
				st->children->scope_level = current_scope_level;
				st_id++;
				st->children->st_id = st_id;
				st->children->parent = st;
				create_symbol_table(n->data.compound_statement->declaration_or_statement_list, st->children);
			}
			else {
				symbol_table *new = malloc(sizeof(symbol_table));
				assert(new != NULL);
				current_scope_level++;
				new->scope_level = current_scope_level;
				st_id++;
				new->st_id = st_id;
				new->parent = st;
				st->children = add_to_symbol_table_list(st->children, new);
				create_symbol_table(n->data.compound_statement->declaration_or_statement_list, new);
			}
			current_scope_level--;
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
void create_parameter_list_node_symbol_table(node *n, symbol_table *st) {
	create_symbol_table(n->data.parameter_list->parameter_list, st);
	create_symbol_table(n->data.parameter_list->parameter_decl, st);
}
void create_parameter_decl_node_symbol_table(node *n, symbol_table *st)  {
	symbol_table_identifier *current = create_identifier(st);
	node *decl_spec = n->data.parameter_decl->declaration_specifiers;
	node *declarator = n->data.parameter_decl->declarator;
	current = create_decl_identifier(n, decl_spec, declarator, current, st);
}
void create_subscript_expr_node_symbol_table(node *n, symbol_table *st)  {
	// search the current ST and its parents for the closest matching ID name; 
	// if found, attach it to the id of the expr; 
	// if not found, print error
	node *postfix_expr = n->data.subscript_expr->postfix_expr;
	if (postfix_expr->node_type == IDENTIFIER_NODE) {
		node *identifier = postfix_expr;
		char *name = identifier->data.identifier->name;
		symbol_table_identifier *i = find_identifier_in_symbol_table(st, name);
		if (i != NULL) {
			identifier->data.identifier->symbol_table_identifier = i;
		}
		else {
			fprintf(stderr, "ERROR: Variable %s undeclared\n", name);
		}
	}
	else {
		create_symbol_table(postfix_expr, st);
	}	
}

void create_identifier_node_symbol_table(node *n, symbol_table *st)  {
	char *name = n->data.identifier->name;
	symbol_table_identifier *i = find_identifier_in_symbol_table(st, name);
	if (i != NULL) {
		n->data.identifier->symbol_table_identifier = i;
	}
	else {
		fprintf(stderr, "ERROR: Variable %s undeclared\n", name);
	}	
}


type *get_type_from_decl_node(node *n) {
	// n can contain a NUMBER_NODE, POINTER_DECL_NODE, ARRAY_DECLARATOR_NODE or FUNCTION_DECLARATOR_NODE
	type *id_type = malloc(sizeof(type));
	if (n->node_type == DECL_NODE || n->node_type == PARAMETER_DECL_NODE) {
		node *decl_spec;
		node *initialized_declarator_list;
		node *declarator;
		if (n->node_type == DECL_NODE) {
			decl_spec = n->data.decl->declaration_specifier;
			initialized_declarator_list = n->data.decl->initialized_declarator_list;
			declarator = initialized_declarator_list->data.initialized_declarator_list->initialized_declarator;	
		}
		else {
			decl_spec = n->data.parameter_decl->declaration_specifiers;
			declarator = n->data.parameter_decl->declarator;
		}
		node *reduced_node = create_node(n->node_type);
		reduced_node->data.decl = malloc(sizeof(*reduced_node->data.decl));
		reduced_node->data.decl->declaration_specifier = decl_spec;
		if (declarator->node_type == POINTER_DECL_NODE) {
			id_type->type = POINTER_TYPE;                     
			id_type->data.pointer_type = malloc(sizeof(pointer_type));
			reduced_node->data.decl->initialized_declarator_list = create_temp_ini_param_list(declarator->data.pointer_decl->direct_declarator);
			id_type->data.pointer_type->base_type = get_type_from_decl_node(reduced_node);
		}
		else if (declarator->node_type == ARRAY_DECLARATOR_NODE) {
			id_type->type = ARRAY_TYPE;
			id_type->data.array_type = malloc(sizeof(array_type));
			if (declarator->data.array_declarator->constant_expr != NULL && 
					declarator->data.array_declarator->constant_expr->node_type == NUMBER_NODE) { 
				// if not NUMBER_NODE, it's an IDENTIFIER_NODE or expr, so size is unknown
				id_type->data.array_type->size = declarator->data.array_declarator->constant_expr->data.number->value;
			}
			reduced_node->data.decl->initialized_declarator_list = create_temp_ini_param_list(declarator->data.array_declarator->direct_declarator);
			id_type->data.array_type->element_type = get_type_from_decl_node(reduced_node);
		}
		else if (declarator->node_type == IDENTIFIER_NODE) {
			// plain ol' vanilla arithmetic identifier
			id_type->type = ARITHMETIC_TYPE;
			id_type->data.arithmetic_type = malloc(sizeof(arithmetic_type));
			id_type->data.arithmetic_type->number_type = decl_spec->data.compound_number_type_specifier->number_type;
			id_type->data.arithmetic_type->is_unsigned = decl_spec->data.compound_number_type_specifier->is_unsigned;
		}
	}
	else if (n->node_type == FUNCTION_DEF_SPECIFIER_NODE) {
		// have declarator and param list, must figure out return type, argc, arg types
		id_type->type = FUNCTION_TYPE;
		node *decl_spec = n->data.function_def_specifier->declaration_specifiers;
		id_type->data.function_type = malloc(sizeof(function_type));
		if (decl_spec->node_type == RESERVED_WORD_NODE && !strcmp(decl_spec->data.reserved_word->text, "void")) {
			id_type->data.function_type = NULL;
		}
		else {
			node *reduced_node = create_node(DECL_NODE);
			reduced_node->data.decl = malloc(sizeof(*reduced_node->data.decl));
			reduced_node->data.decl->declaration_specifier = decl_spec;
			reduced_node->data.decl->initialized_declarator_list = create_temp_ini_param_list(n->data.function_def_specifier->declarator->data.function_declarator->direct_declarator);
			id_type->data.function_type->return_type = get_type_from_decl_node(reduced_node);
		}
		node *parameter_type_list = n->data.function_def_specifier->declarator->data.function_declarator->parameter_type_list;
		if (parameter_type_list->node_type == PARAMETER_LIST_NODE) {
			id_type->data.function_type->argc = parameter_type_list->data.parameter_list->number_of_params;
		}
		else if (parameter_type_list->node_type == PARAMETER_DECL_NODE) {
			// DEBUG
			// printf("param list not found, what's in param list is type %d\n", parameter_type_list->node_type);
			id_type->data.function_type->argc = 1;
		}
		else if (parameter_type_list->node_type == RESERVED_WORD_NODE) { // the only reserved word that can be a parameter is void, so 0 arguments
			id_type->data.function_type->argc = 0;
		}
		if (id_type->data.function_type->argc > 0) {
			if (id_type->data.function_type->argc == 1) {
				id_type->data.function_type->arg_types[0] = get_type_from_decl_node(parameter_type_list);
			}
			else {
				int i = 0;
				node *current_param_decl = parameter_type_list->data.parameter_list->parameter_decl;
				node *current_param_list = parameter_type_list->data.parameter_list->parameter_list;
				for (i = 0; i < id_type->data.function_type->argc; i++) {
					id_type->data.function_type->arg_types[i] = get_type_from_decl_node(current_param_decl);
					if (current_param_list->node_type == PARAMETER_LIST_NODE) {
						current_param_decl = current_param_list->data.parameter_list->parameter_decl;
						current_param_list = current_param_list->data.parameter_list->parameter_list;
					}
					else {
						current_param_decl = current_param_list;
					}
				}		
			}
		}
	}
	return id_type;
} 
type *get_incomplete_type_from(type *t) {
	switch (t->type) {
	case POINTER_TYPE:
		if (t->data.pointer_type->base_type == NULL) {
			return t;
		}
		else {
			return get_incomplete_type_from(t->data.pointer_type->base_type);
		}
	case ARRAY_TYPE:
		if (t->data.array_type->element_type == NULL) {
			return t;
		}
		else {
			return get_incomplete_type_from(t->data.array_type->element_type);
		}
	}
	printf("ERROR: type number %d isn't supposed to have an incomplete subtype\n", t->type);
	return NULL;
}
type *complete_type(type *incomplete, type *missing) {
	switch (incomplete->type) {
	case POINTER_TYPE:
		incomplete->data.pointer_type->base_type = missing;
	case ARRAY_TYPE:
		incomplete->data.array_type->element_type = missing;
	default:
		printf("ERROR: type number %d isn't supposed to have an incomplete subtype\n", incomplete->type);
	}
	return incomplete;
}
// type *get_type_from_decl_node(node *n, type *prev_type) {
// 	// n can contain a NUMBER_NODE, POINTER_DECL_NODE, ARRAY_DECLARATOR_NODE or FUNCTION_DECLARATOR_NODE
// 	type *id_type = malloc(sizeof(type));
// 	if (n->node_type == DECL_NODE || n->node_type == PARAMETER_DECL_NODE) {
// 		node *decl_spec;
// 		node *initialized_declarator_list;
// 		node *declarator;
// 		if (n->node_type == DECL_NODE) {
// 			decl_spec = n->data.decl->declaration_specifier;
// 			initialized_declarator_list = n->data.decl->initialized_declarator_list;
// 			declarator = initialized_declarator_list->data.initialized_declarator_list->initialized_declarator;	
// 		}
// 		else {
// 			decl_spec = n->data.parameter_decl->declaration_specifiers;
// 			declarator = n->data.parameter_decl->declarator;
// 		}
// 		node *reduced_node = create_node(n->node_type);
// 		reduced_node->data.decl = malloc(sizeof(*reduced_node->data.decl));
// 		reduced_node->data.decl->declaration_specifier = decl_spec;
// 		if (declarator->node_type == POINTER_DECL_NODE) {
// 			id_type->type = POINTER_TYPE;                     
// 			id_type->data.pointer_type = prev_type == NULL ? malloc(sizeof(pointer_type)) : prev_type;
// 			reduced_node->data.decl->initialized_declarator_list = create_temp_ini_param_list(declarator->data.pointer_decl->direct_declarator);
// 			id_type->data.pointer_type->base_type = get_type_from_decl_node(reduced_node);
// 		}
// 		else if (declarator->node_type == ARRAY_DECLARATOR_NODE) {
// 			id_type->type = ARRAY_TYPE;
// 			id_type->data.array_type = malloc(sizeof(array_type));
// 			if (declarator->data.array_declarator->constant_expr != NULL && 
// 					declarator->data.array_declarator->constant_expr->node_type == NUMBER_NODE) { 
// 				// if not NUMBER_NODE, resolve to NUMBER_NODE if possible, otherwise it's an IDENTIFIER_NODE or expr, so size is unknown
// 				id_type->data.array_type->size = declarator->data.array_declarator->constant_expr->data.number->value;
// 			}
// 			reduced_node->data.decl->initialized_declarator_list = create_temp_ini_param_list(declarator->data.array_declarator->direct_declarator);
// 			// populate element_type
// 			// wrap current type in prev_type if available
// 			// if (prev_type != NULL) {
// 			// 	type *incomplete = get_incomplete_type_from(prev_type);
// 			// 	prev_type = complete_type(incomplete, id_type);				
// 				id_type->data.array_type->element_type = prev_type;
// 			// }
// 			// else {
// 				id_type->data.array_type->element_type = get_type_from_decl_node(reduced_node, prev_type);
// 			// }
// 		}
// 		else if (declarator->node_type == IDENTIFIER_NODE) {
// 			// plain ol' vanilla arithmetic identifier
// 			id_type->type = ARITHMETIC_TYPE;
// 			id_type->data.arithmetic_type = malloc(sizeof(arithmetic_type));
// 			id_type->data.arithmetic_type->number_type = decl_spec->data.compound_number_type_specifier->number_type;
// 			id_type->data.arithmetic_type->is_unsigned = decl_spec->data.compound_number_type_specifier->is_unsigned;
// 			// if (prev_type != NULL) {
// 			// 	type *incomplete = get_incomplete_type_from(prev_type);
// 			// 	id_type = complete_type(incomplete, id_type);
// 			// }
// 		}
// 	}
// 	else if (n->node_type == FUNCTION_DEF_SPECIFIER_NODE) {
// 		// have declarator and param list, must figure out return type, argc, arg types
// 		id_type->type = FUNCTION_TYPE;
// 		node *decl_spec = n->data.function_def_specifier->declaration_specifiers;
// 		id_type->data.function_type = malloc(sizeof(function_type));
// 		if (decl_spec->node_type == RESERVED_WORD_NODE && !strcmp(decl_spec->data.reserved_word->text, "void")) {
// 			id_type->data.function_type = NULL;
// 		}
// 		else {
// 			node *reduced_node = create_node(DECL_NODE);
// 			reduced_node->data.decl = malloc(sizeof(*reduced_node->data.decl));
// 			reduced_node->data.decl->declaration_specifier = decl_spec;
// 			reduced_node->data.decl->initialized_declarator_list = create_temp_ini_param_list(n->data.function_def_specifier->declarator->data.function_declarator->direct_declarator);
// 			id_type->data.function_type->return_type = get_type_from_decl_node(reduced_node);
// 		}
// 		node *parameter_type_list = n->data.function_def_specifier->declarator->data.function_declarator->parameter_type_list;
// 		if (parameter_type_list->node_type == PARAMETER_LIST_NODE) {
// 			id_type->data.function_type->argc = parameter_type_list->data.parameter_list->number_of_params;
// 		}
// 		else if (parameter_type_list->node_type == PARAMETER_DECL_NODE) {
// 			// DEBUG
// 			// printf("param list not found, what's in param list is type %d\n", parameter_type_list->node_type);
// 			id_type->data.function_type->argc = 1;
// 		}
// 		else if (parameter_type_list->node_type == RESERVED_WORD_NODE) { // the only reserved word that can be a parameter is void, so 0 arguments
// 			id_type->data.function_type->argc = 0;
// 		}
// 		if (id_type->data.function_type->argc > 0) {
// 			if (id_type->data.function_type->argc == 1) {
// 				id_type->data.function_type->arg_types[0] = get_type_from_decl_node(parameter_type_list);
// 			}
// 			else {
// 				int i = 0;
// 				node *current_param_decl = parameter_type_list->data.parameter_list->parameter_decl;
// 				node *current_param_list = parameter_type_list->data.parameter_list->parameter_list;
// 				for (i = 0; i < id_type->data.function_type->argc; i++) {
// 					id_type->data.function_type->arg_types[i] = get_type_from_decl_node(current_param_decl);
// 					if (current_param_list->node_type == PARAMETER_LIST_NODE) {
// 						current_param_decl = current_param_list->data.parameter_list->parameter_decl;
// 						current_param_list = current_param_list->data.parameter_list->parameter_list;
// 					}
// 					else {
// 						current_param_decl = current_param_list;
// 					}
// 				}		
// 			}
// 		}
// 	}
// 	return id_type;
// }
node *create_temp_ini_param_list(node *ini_declarator) {
	node *initialized_declarator_list = create_node(INITIALIZED_DECLARATOR_LIST_NODE);
	initialized_declarator_list->data.initialized_declarator_list = malloc(sizeof(initialized_declarator_list));
	initialized_declarator_list->data.initialized_declarator_list->initialized_declarator = ini_declarator;
	return initialized_declarator_list;
}
void advance_current_identifier(symbol_table_identifier *current) {
	// // when first node, just start modifying current right away and don't set current->next
	// // otherwise, create current->next and set current to it, then proceed
	// if (identifier_id > 1) {
	// 	symbol_table_identifier *next = malloc(sizeof(*next));
	// 	current->next = next;
	// 	current = next;
	// }
	current->identifier_id = identifier_id;
	identifier_id++;
}

/************** SYMBOL TABLE PRINTING FUNCTIONS *******************/

void print_symbol_table(FILE *output, symbol_table *s) {
	// print identifiers
	print_indentation(output);
	fprintf(output, "Scope level %d:\n", s->scope_level);
	print_indentation(output);
	fprintf(output, "Symbol table #%d:\n", s->st_id);
	print_indentation(output);
	fputs("Identifiers:\n", output);
	symbol_table_identifier *i = s->identifiers;
	// while (i != NULL) {
	print_symbol_table_identifier(output, i);
	// 	i = i->next;
	// }
	fputs("\n", output);
	// print children
	if (s->children != NULL) {		
		print_indentation(output);
		fputs("Children:\n", output);
		indent++;
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
	if (i != NULL) {
		print_indentation(output);
		fprintf(output, "%s -> %s, %d, %s", i->name, i->name, i->identifier_id, type_to_s(i->type));
		if (i->next != NULL) {
			fputs("\n", output);
			print_symbol_table_identifier(output, i->next);
		}
	}
}
void add_types() {
	types[INT] = "int";
	types[LONG] = 	"long int";
	types[SHORT] = "short int";
	types[CHAR] = "char";
	types[VOID_TYPE] = "void";
	types[POINTER_TYPE] = "pointer";
}
char *sign_to_s(int is_unsigned) {
	switch (is_unsigned) {
	case 0:
		return "signed";
		break;
	case 1:
		return "unsigned";
		break;
	}
	return "ERROR: corrupted signedness";
}

char *type_to_s(type *t) {
	char *str = malloc(2000);
	char *args = malloc(1000);
	int i;
	int type = t->type; 
	// DEBUG
	// printf("printing type %d\n", t->type);
	switch (type) {
		case ARITHMETIC_TYPE:
			sprintf(str, "%s %s", sign_to_s(t->data.arithmetic_type->is_unsigned), types[t->data.arithmetic_type->number_type]);
			break;
		case POINTER_TYPE:
			sprintf(str, "pointer (%s)", type_to_s(t->data.pointer_type->base_type));
			break;
		case ARRAY_TYPE:
			sprintf(str, "array (%d, %s)", t->data.array_type->size, type_to_s(t->data.array_type->element_type));
			break;
		case FUNCTION_TYPE:
			if (t->data.function_type->argc > 0) {
				strcat(args, type_to_s(t->data.function_type->arg_types[0]));
				for (i = 1; i < t->data.function_type->argc; i++) {
					strcat(args, ", ");
					strcat(args, type_to_s(t->data.function_type->arg_types[i]));
				} 
			}
			sprintf(str, "function (%s, %d, [%s])", type_to_s(t->data.function_type->return_type), t->data.function_type->argc, args);
			break;
		default:
			printf("ERROR: Can't print ST entry of type %d\n", type);
	}
	return str;
}

void type_check(node *n) {
	switch (n->node_type) {
		case TRANSLATION_UNIT_NODE:
			type_check(n->data.translation_unit->translation_unit);
			type_check(n->data.translation_unit->top_level_decl);
			break;
		case DECLARATION_OR_STATEMENT_LIST_NODE:
			if (n->data.declaration_or_statement_list->declaration_or_statement_list != NULL) {
				type_check(n->data.declaration_or_statement_list->declaration_or_statement_list);
			}
			type_check(n->data.declaration_or_statement_list->declaration_or_statement);
			break;
		case UNARY_EXPRESSION_NODE:
			do_unary_conversion(n);
			break;
		case FUNCTION_DEFINITION_NODE:
			type_check(n->data.function_definition->compound_statement);
			break;
		case COMPOUND_STATEMENT_NODE:
			if (n->data.compound_statement->declaration_or_statement_list != NULL) {
				type_check(n->data.compound_statement->declaration_or_statement_list);
			}
			break;
		case STATEMENT_NODE:
			type_check(n->data.statement->statement);
			break;
		case BINARY_EXPRESSION_NODE:
			type_check(n->data.binary_expression->left);
			type_check(n->data.binary_expression->right);
			if (n->data.binary_expression->op->data.operator->value == ASSIGN) {
				assignment_type_check(n->data.binary_expression->left, n->data.binary_expression->right);
			}
			do_binary_conversion(n);
			break;
	}
}
node *get_core_operand_from_unary_expr(node *n) {
	node *operand = n->data.unary_expression->operand;
	if (operand->node_type == IDENTIFIER_NODE || operand->node_type == NUMBER_NODE) {
		return operand;
	}
	else {
		return get_core_operand_from_unary_expr(operand);
	}
}
//return an identifier node given an arbitrary node that may contain a single identifier node among its descendants
node *get_identifier_from_node(node *n) {
	switch (n->node_type) {
	case UNARY_EXPRESSION_NODE:
		return get_core_operand_from_unary_expr(n->data.unary_expression->operand);
	}
}
void do_unary_conversion(node *n) {
	// only !, ~, +, -, * and array
	// TODO look up operand's type, don't cast if int/long
	if (n->node_type == UNARY_EXPRESSION_NODE) {
		char *op = n->data.unary_expression->operator->data.operator->text;
		node *operand = n->data.unary_expression->operand;
		if (str_equals(op, "!") || str_equals(op, "~") || str_equals(op, "+") || str_equals(op, "-")) {
		// only insert cast if not already right type, ie short, char and not already cast to int  
			if (operand->node_type == CAST_EXPR_NODE && !cast_equal_or_larger_than_int(operand) /* &&
					(type_of_node(operand) == CHAR || type_of_node(operand) == SHORT) */) {
				n->data.unary_expression->operand = insert_cast_from_string("int", 0, operand);
				do_unary_conversion(operand->data.cast_expr->cast_expr);
			}
			else if (operand->node_type == UNARY_EXPRESSION_NODE) {
				do_unary_conversion(operand);
			}
			// if (operand->node_type == BINARY_EXPRESSION_NODE) {
			// 	do_binary_conversion(operand);
			// }
			else if (operand->node_type == IDENTIFIER_NODE && operand->data.identifier->symbol_table_identifier->type->type == ARITHMETIC_TYPE && !int_or_long(operand->data.identifier->symbol_table_identifier->type->data.arithmetic_type->number_type)) {
				n->data.unary_expression->operand = insert_cast_from_string("int", 0, operand);
			}
		}
	}
	else if (n->node_type == ARRAY_DECLARATOR_NODE) {
		
	}
	else if (n->node_type == CAST_EXPR_NODE) {
		do_unary_conversion(n->data.cast_expr->cast_expr);
	}
}

int str_equals(char *str1, char *str2) {
	return strcmp(str1, str2) == 0;
}

int cast_equal_or_larger_than_int(node *n) {
	if (n->node_type == CAST_EXPR_NODE) {
		int num_type = n->data.cast_expr->type_name->data.type_name->declaration_specifiers->data.compound_number_type_specifier->number_type;
		return int_or_long(num_type);
	}
	else {
		return 0;
	}
}
int int_or_long(int num_type) {
	return (num_type == INT || num_type == LONG);
}
int get_num_type_from_string(char *str) {
	if (str_equals(str, "int")) {
		return INT;
	}
	else if (str_equals(str, "long")) {
		return LONG;
	}
	else if (str_equals(str, "char")) {
		return CHAR;
	}
	else if (str_equals(str, "short")) {
		return SHORT;
	}
	else {
		printf("ERROR: string is not a number type: %s\n", str);
		return 999;
	}
}
// replace operand with the new cast_expr, and the original operand becomes the new cast_expr's cast_expr             
node *insert_cast(type *type, node *n) {	
	node *cast;
	if (type->type == ARITHMETIC_TYPE) {
		char *type_str = types[type->data.arithmetic_type->number_type];
		node *sign;
		node *num_type = create_reserved_word_node(type_str, type->data.arithmetic_type->number_type);
		if (type->data.arithmetic_type->is_unsigned) {
			sign = create_reserved_word_node("unsigned", UNSIGNED);
			node *words[] = {sign, num_type, NULL};
			cast = create_compound_number_type_specifier_node(words);		
		}
		else {
			node *words[] = {num_type, NULL, NULL};
			cast = create_compound_number_type_specifier_node(words);		
		}
	}
	return create_cast_expr_node(cast, n);
}
node *insert_cast_from_string(char *cast_type, int is_unsigned, node *n) {
	type *int_type = malloc(sizeof(*int_type));
	int_type->type = ARITHMETIC_TYPE;
	int_type->data.arithmetic_type = malloc(sizeof(*int_type->data.arithmetic_type));
	int_type->data.arithmetic_type->number_type = get_num_type_from_string(cast_type);
	int_type->data.arithmetic_type->is_unsigned = is_unsigned;
	return insert_cast(int_type, n);
}
void do_binary_conversion(node *n) {
	node *left = n->data.binary_expression->left;
	node *right = n->data.binary_expression->right;
	// extract identifier from left and right
	// look up type of left and right in symbol table
	type *left_type = type_of_expr(left);
	type *right_type = type_of_expr(right);
	if (is_arithmetic_type(left_type) && is_arithmetic_type(right_type)) {
		if (compare_arithmetic_types(left_type, right_type) == 1) {
			n->data.binary_expression->right = insert_cast(left_type, right);
		}
		else if (compare_arithmetic_types(left_type, right_type) == -1) {
			n->data.binary_expression->left = insert_cast(right_type, left);
		}
	}
}
void assignment_type_check(node *left, node *right) {
	if (left->node_type != IDENTIFIER_NODE) {
		printf("ERROR: destination of assignment is not a lvalue.\n");
	}
	else {
		type *left_type = type_of_expr(left);
		type *right_type = type_of_expr(right);
		if (left_type->type != right_type->type) {
			// allowed assignments of different types:
			// 0 to pointer
			if (!(left_type->type == POINTER_TYPE && right->node_type == NUMBER_NODE && right->data.number->value == 0)) {
				printf("ERROR: assignment to incompatible type\n");
			}
		}
	}
}
int is_arithmetic_type(type *t) {
	if (t->type == ARITHMETIC_TYPE) 
		return 1;
	else
		return 0;
}
type *type_of_expr(node *n) {
	// if n's children contain an identifier, take type of identifier, feed it through 
	type *t = malloc(sizeof(type));
	switch (n->node_type) {
	case BINARY_EXPRESSION_NODE:
		return larger_type(type_of_expr(n->data.binary_expression->left), type_of_expr(n->data.binary_expression->right));
	case UNARY_EXPRESSION_NODE:
		return type_of_unary_expr(n->data.unary_expression->operand);
	case NUMBER_NODE:
		t->type = ARITHMETIC_TYPE;
		t->data.arithmetic_type = malloc(sizeof(*t->data.arithmetic_type));
		t->data.arithmetic_type->number_type = n->data.number->type;
		t->data.arithmetic_type->is_unsigned = n->data.number->is_unsigned;
		return t;
	case IDENTIFIER_NODE:
		return n->data.identifier->symbol_table_identifier->type;
	case CAST_EXPR_NODE:
		// if the type_name has an abstract declarator, it's a pointer cast, otherwise an arithmetic cast
		// if (n->data.cast_expr->type_name->data.type_name->abstract_declarator != NULL) {
			return get_type_from_decl_node(n->data.cast_expr->type_name);
			// t->data.pointer_type = malloc(sizeof(*t->data.pointer_type));
			// t->data.pointer_type->
	}
}
type *larger_type(type *left_type, type *right_type) {
	if (rank(left_type) > rank(right_type)) {
		return left_type;
	}
	else if (rank(right_type) > rank(left_type)) {
		return right_type;
	}
	else { // equal rank, so if different signedness, unsigned type wins
		if (left_type->data.arithmetic_type->is_unsigned == right_type->data.arithmetic_type->is_unsigned) {
			return left_type; // could have returned right_type too; they're identical at this point
		}
		else if (left_type->data.arithmetic_type->is_unsigned) {
			return left_type;
		}
		else {
			return right_type;
		}
	}
}
// return 0 if equal, 1 if the first type is larger, -1 if 2nd type is larger
int compare_arithmetic_types(type *t1, type *t2) {
	assert(t1->type == ARITHMETIC_TYPE && t2->type == ARITHMETIC_TYPE);
	if (is_equal(t1, t2)) {
		return 0;
	}
	else {
		type *larger = larger_type(t1, t2);
		if (larger->data.arithmetic_type->is_unsigned == t1->data.arithmetic_type->is_unsigned &&
		    larger->data.arithmetic_type->number_type == t1->data.arithmetic_type->number_type) {
			return 1;
		}
		else {
			return -1;
		}
	}
}
int is_equal(type *t1, type *t2) {
	if (t1->type == t2->type) {
		switch (t1->type) {
			case ARITHMETIC_TYPE:
				return (t1->data.arithmetic_type->is_unsigned == t2->data.arithmetic_type->is_unsigned &&
								t1->data.arithmetic_type->number_type == t2->data.arithmetic_type->number_type);
			case POINTER_TYPE:
				return is_equal(t1->data.pointer_type->base_type, t2->data.pointer_type->base_type);
			case ARRAY_TYPE:
			;
			// TODO
			case FUNCTION_TYPE:
			;
			// TODO
		}
	}
	else {
		return 0;
	}
}
type *type_of_unary_expr(node *unary_expression) {
	node *operand = get_core_operand_from_unary_expr(unary_expression);
	switch (operand->node_type) {
	case IDENTIFIER_NODE:
		return operand->data.identifier->symbol_table_identifier->type;
	case NUMBER_NODE:
		return type_of_expr(operand);
	default:
		return NULL;
	}
}
int rank(type *t) {
	if (t->type == ARITHMETIC_TYPE) {
		switch (t->data.arithmetic_type->number_type) {
		case LONG:
			return 50;
		case INT:
			return 40;
		case SHORT:
			return 30;
		case CHAR:
			return 20;
		default:
			printf("ERROR: unknown number type: %d\n", t->data.arithmetic_type->number_type);
			return 9999;
		}
	}
	else {
		return NULL;
	}
}
ir *generate_ir(node *n) {
	// if binary, copy children's IR then 
	// if not, eg identifier
	switch (n->node_type) {
		case BINARY_EXPRESSION_NODE: {
			// copy instructions for left
			// if left's temp is lvalue, dereference
			// copy instructions for right
			// if left's temp is lvalue, dereference
			// generate op IR for left-op-right
			n->data.binary_expression->left->ir = generate_ir(n->data.binary_expression->left);
			n->ir = add_to_ir_list(n->ir, n->data.binary_expression->left->ir);
			if (n->data.binary_expression->left->temp->is_lvalue) {
				n->ir = add_to_ir_list(n->ir, create_load_word_indirect_ir(n->data.binary_expression->left->temp));
			}
			n->data.binary_expression->right->ir = generate_ir(n->data.binary_expression->right);
			n->ir = add_to_ir_list(n->ir, n->data.binary_expression->right->ir);
			if (n->data.binary_expression->right->temp->is_lvalue) {
				n->ir = add_to_ir_list(n->ir, create_load_word_indirect_ir(n->data.binary_expression->right->temp));
			}
			// switch (n->data.binary_expression->op->data.operator->value) {
			// 	case SLASH: {
			// 		
			// 	}
			// }
			break;
		}
		case IDENTIFIER_NODE:   {
		// load address into a temp, mark that temp as lvalue
			ir *identifier_ir = create_ir_node(LOAD, LoadAddr);
			load_ir *l = identifier_ir->data.load_ir;
			l->rd = malloc(sizeof(*l->rd));
			l->rd->id = temp_id;
			temp_id++;
			l->rd->is_lvalue = 1;
			l->rs = n->data.identifier->symbol_table_identifier;
			n->ir = identifier_ir;
			n->temp = l->rd;
			break;      
		}
		case NUMBER_NODE: {
			printf("number IR\n");
			break;
		}
		case FUNCTION_DEFINITION_NODE: {
			// n->ir = generate_ir(n->data.function_definition->function_def_specifier);
			n->ir = add_to_ir_list(n->ir, generate_ir(n->data.function_definition->compound_statement));
			break;
		}
		case COMPOUND_STATEMENT_NODE: {
			n->ir = add_to_ir_list(n->ir, generate_ir(n->data.compound_statement->declaration_or_statement_list));
			break;
		}
		case DECLARATION_OR_STATEMENT_LIST_NODE: {
			n->ir = add_to_ir_list(n->ir, generate_ir(n->data.declaration_or_statement_list->declaration_or_statement_list));
			n->ir = add_to_ir_list(n->ir, generate_ir(n->data.declaration_or_statement_list->declaration_or_statement));
			break;
		}
		case STATEMENT_NODE: {
			n->ir = add_to_ir_list(n->ir, generate_ir(n->data.statement->statement));
			break;
		}
	}
	return n->ir;
}

ir *create_ir_node(int ir_type, int opcode) {
	ir *ir_node = malloc(sizeof(*ir_node));
	ir_node->ir_type = ir_type;
	ir_node->opcode = opcode;
	switch (ir_type) {
	case OP:
		ir_node->data.op_ir = malloc(sizeof(*ir_node->data.op_ir));
		break;
	case LOAD:
		ir_node->data.load_ir = malloc(sizeof(*ir_node->data.load_ir));
		break;
	case STORE:
		ir_node->data.store_ir = malloc(sizeof(*ir_node->data.store_ir));
		break;
	}
	return ir_node;
} 
ir *create_load_word_indirect_ir(temp *rs) {
	ir *ir = create_ir_node(OP, LoadWordIndirect);
	ir->data.op_ir->rd = malloc(sizeof(temp));
	ir->data.op_ir->rd->id = temp_id;
	temp_id++;
	ir->data.op_ir->rd->is_lvalue = 0;
	ir->data.op_ir->rs = rs;
	return ir;
}
ir *get_last_ir_list_element(ir *list) {
	// list can be null, 1 element (next == NULL) or more
	if (list == NULL) {
		return NULL;
	}
	else {
		if (list->next == NULL) {
			return list;
		}
		else {
			ir *last = list->next;
			while (last->next != NULL) {
				last = last->next;
			}
			return last;	
		}
	}
}
ir *add_to_ir_list(ir *list, ir *new) {
	if (new != NULL) {
		ir *old = get_last_ir_list_element(list);
		if (old == NULL) { // empty list, so put 'new' in as first element   
			list = malloc(sizeof(ir));
			assert(list != NULL);
			*list = *new;
		}
		else {
			old->next = new;
		}
	}
	return list;
}
void print_ir(ir *ir, FILE *output) {
	// op_ir: opcode, temp rd, temp rs, temp rt
	// load_ir: opcode, temp rd, symbol rs
	// store_ir: opcode, symbol rd, temp rs
	fprintf(output, "%s(", opcodes[ir->opcode]);
	switch (ir->ir_type) {
		case OP:
			fprintf(output, "t_%d", ir->data.op_ir->rd->id);
			fprintf(output, ", t_%d", ir->data.op_ir->rs->id);
			if (ir->data.op_ir->rt != NULL) {
				fprintf(output, ", t_%d", ir->data.op_ir->rt->id);			
			}
			break;
		case LOAD:
			fprintf(output, "t_%d, ", ir->data.load_ir->rd->id);
			fprintf(output, "%s", ir->data.load_ir->rs->name);
			break;
		case STORE:
			fprintf(output, "%s, ", ir->data.store_ir->rd->name);
			fprintf(output, "t_%d", ir->data.store_ir->rs->id);
			break;
		default:
			fprintf(output, "ERROR: unknown IR node type: %d\n", ir->ir_type);
	}
	fputs(")\n", output);
	if (ir->next != NULL) {
		print_ir(ir->next, output);
	}
}

void add_ir_opcodes() {
	opcodes[LoadAddr] = "LoadAddr";
	opcodes[LoadWordIndirect] = "LoadWordIndirect";
}
