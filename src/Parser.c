#include "Parser.h"
#include "AstNode.h"
#include "Lexer.h"
#include "Token.h"
#include <stdio.h>

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

Node* ParseTokens(Token* tokens, int token_cnt) {
	Node* thisNode = NULL;

	for (int* i = 0; i < token_cnt; ++i) {
		Node* newNode = NULL;

		switch (tokens[*i].type)
		{
			case(TOKEN_INTEGER): {
				newNode = ParseIntVariable(tokens, i);
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