#include "Parser.h"
#include "AstNode.h"
#include "Lexer.h"
#include "Token.h"
#include <stdio.h>
#include <stdlib.h>

static Node* ParseIntVariable(Token* tokens, int* i) {
	Node* newNode;
	newNode->type = NODE_VARIABLE;
	newNode->var_type = "integer";
	newNode->start_line = tokens[*i].line;
	
	if (tokens[*i + 1].type == TOKEN_IDENTIFIER) {
		newNode->var_name = tokens[*i + 1].str_value;
	}
	else {
		printf("ERROR: Missing identifier after 'integer' on line %i.", newNode->start_line);
		exit(-1);
	}

	if (tokens[*i + 2].type != TOKEN_EQUALS)  {
		printf("ERROR: Missing assignment after identifier on line %i.", newNode->start_line);
		exit(-1);
	}

	if (tokens[*i + 3].type == TOKEN_LITERAL_INT) {
		newNode->int_value = tokens[*i + 3].int_value;
	}
	else {
		printf("ERROR: Missing literal after identifier on line %i.", newNode->start_line);
		exit(-1);
	}

	*i += 3;
}

static Node* ParseStringVariable(Token* tokens, int* i) {
	Node* newNode;
	newNode->type = NODE_VARIABLE;
	newNode->var_type = "string";
	newNode->start_line = tokens[*i].line;

	if (tokens[*i + 1].type == TOKEN_IDENTIFIER) {
		newNode->var_name = tokens[*i + 1].str_value;
	}
	else {
		printf("ERROR: Missing identifier after 'string' on line %i.", newNode->start_line);
		exit(-1);
	}

	if (tokens[*i + 2].type != TOKEN_EQUALS) {
		printf("ERROR: Missing assignment after identifier on line %i.", newNode->start_line);
		exit(-1);
	}

	if (tokens[*i + 3].type == TOKEN_LITERAL_STRING) {
		newNode->str_value = tokens[*i + 3].str_value;
	}
	else {
		printf("ERROR: Missing literal after identifier on line %i.", newNode->start_line);
		exit(-1);
	}

	*i += 3;
}

static Node* ParseBoolVariable(Token* tokens, int* i) {
	Node* newNode;
	newNode->type = NODE_VARIABLE;
	newNode->var_type = "boolean";
	newNode->start_line = tokens[*i].line;

	if (tokens[*i + 1].type == TOKEN_IDENTIFIER) {
		newNode->var_name = tokens[*i + 1].str_value;
	}
	else {
		printf("ERROR: Missing identifier after 'boolean' on line %i.", newNode->start_line);
		exit(-1);
	}

	if (tokens[*i + 2].type != TOKEN_EQUALS) {
		printf("ERROR: Missing assignment after identifier on line %i.", newNode->start_line);
		exit(-1);
	}

	if (tokens[*i + 3].type == TOKEN_LITERAL_BOOL) {
		newNode->bool_value = tokens[*i + 3].bool_value;
	}
	else {
		printf("ERROR: Missing literal after identifier on line %i.", newNode->start_line);
		exit(-1);
	}

	*i += 3;
}

static Node* ParseExpression(Token* tokens, int* i) {
	Node* newNode;
	Node* left;
	Node* right;

	if (tokens[*i + 1].type >= 106 && tokens[*i + 1].type <= 109) {
		newNode->type = tokens[*i + 1].type + 194;
		newNode->start_line = tokens[*i + 1].line;
		newNode->nodes = malloc(sizeof(Node) * 2);
		newNode->nodes[0] = *left;
		newNode->nodes[1] = *right;
	}
	else {
		printf("ERROR: Missing operation after identifier on line %i.", newNode->start_line);
		exit(-1);
	}

	if (tokens[*i].type == TOKEN_IDENTIFIER) {
		left->type = NODE_VARIABLE_REF;
		left->var_name = tokens[*i].str_value;
		left->start_line = tokens[*i].line;
	}
	else if (tokens[*i].type >= 400 && tokens[*i].type <= 402) {
		left->type = tokens[*i].type - 300;
		left->start_line = tokens[*i].line;

		if (tokens[*i].type == TOKEN_LITERAL_INT) {
			left->int_value = tokens[*i].int_value;
		} else if (tokens[*i].type == TOKEN_LITERAL_STRING) {
			left->str_value = tokens[*i].str_value;
		} else if (tokens[*i].type == TOKEN_LITERAL_BOOL) {
			left->bool_value = tokens[*i].bool_value;
		}
	}

	if (tokens[*i + 2].type == TOKEN_IDENTIFIER) {
		right->type = NODE_VARIABLE_REF;
		right->var_name = tokens[*i + 2].str_value;
		right->start_line = tokens[*i + 2].line;
	}
	else if (tokens[*i + 2].type >= 400 && tokens[*i].type <= 402) {
		right->type = tokens[*i + 2].type - 300;
		right->start_line = tokens[*i + 2].line;

		if (tokens[*i + 2].type == TOKEN_LITERAL_INT) {
			right->int_value = tokens[*i + 2].int_value;
		}
		else if (tokens[*i + 2].type == TOKEN_LITERAL_STRING) {
			right->str_value = tokens[*i + 2].str_value;
		}
		else if (tokens[*i + 2].type == TOKEN_LITERAL_BOOL) {
			right->bool_value = tokens[*i + 2].bool_value;
		}
	}
}

Node* ParseTokens(Token* tokens, int token_cnt) {
	Node* thisNode = NULL;

	for (int i = 0; i < token_cnt; ++i) {
		Node* newNode = NULL;

		printf("%i\n", tokens[i].type);

		switch (tokens[i].type)
		{
			case(TOKEN_INTEGER): {
				newNode = ParseIntVariable(tokens, &i);
				break;
			}
			case(TOKEN_STRING): {
				newNode = ParseStringVariable(tokens, &i);
				break;
			}
			case(TOKEN_BOOL): {
				newNode = ParseBoolVariable(tokens, &i);
				break;
			}
			case(TOKEN_IDENTIFIER): {
				if (tokens[i + 1].type < 400 || tokens[i + 1].type > 402) { break; }
				newNode = ParseExpression(tokens, &i);
				break;
			}
			case(TOKEN_LITERAL_INT): {
				if (tokens[i + 1].type < 400 || tokens[i + 1].type > 402) { break; }
				newNode = ParseExpression(tokens, &i);
				break;
			}
			case(TOKEN_LITERAL_STRING): {
				if (tokens[i + 1].type < 400 || tokens[i + 1].type > 402) { break; }
				newNode = ParseExpression(tokens, &i);
				break;
			}
			case(TOKEN_LITERAL_BOOL): {
				if (tokens[i + 1].type < 400 || tokens[i + 1].type > 402) { break; }
				newNode = ParseExpression(tokens, &i);
				break;
			}
			default: {
				break;
			}
		}

		if (newNode != NULL) {
			if (thisNode == NULL) {
				thisNode = newNode;
			}
			else {
				thisNode->next = newNode;
				thisNode = newNode;
			}
		}
	}

	return thisNode;
}