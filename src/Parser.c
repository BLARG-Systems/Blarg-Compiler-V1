#include "Parser.h"
#include "AstNode.h"
#include "Lexer.h"
#include "Token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static Node* ParseIntVariable(Token* tokens, int* i) {
	Node* newNode = malloc(sizeof(Node));
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

	return newNode;
}

static Node* ParseStringVariable(Token* tokens, int* i) {
	Node* newNode = malloc(sizeof(Node));
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

	return newNode;
}

static Node* ParseBoolVariable(Token* tokens, int* i) {
	Node* newNode = malloc(sizeof(Node));
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

	return newNode;
}

static Node* ParseExpression(Token* tokens, int* i, Node* prevNode) {
	Node* newNode = malloc(sizeof(Node));
	Node* left = malloc(sizeof(Node));
	Node* right = malloc(sizeof(Node));

	if (tokens[*i + 1].type >= TOKEN_PLUS || tokens[*i + 1].type <= TOKEN_FORWARD_SLASH) {
		newNode->type = tokens[*i + 1].type + 194;
		newNode->start_line = tokens[*i + 1].line;
		newNode->nodes = malloc(sizeof(Node) * 2);
		newNode->nodes[0] = left;
		newNode->nodes[1] = right;
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
	else if (tokens[*i].type >= TOKEN_LITERAL_INT && tokens[*i].type <= TOKEN_LITERAL_BOOL) {
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
	else if (tokens[*i + 2].type >= TOKEN_LITERAL_INT && tokens[*i].type <= TOKEN_LITERAL_BOOL) {
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

	*i += 3;

	return newNode;
}

/*static Node* ParseFunCall(Token* tokens, int* i) {
	Node* funCallNode = malloc(sizeof(Node));
	funCallNode->type = NODE_FUNCTION_CALL;
	funCallNode->var_name = tokens[*i].str_value;
	funCallNode->start_line = tokens[*i].line;


}*/

Node* ParseTokens(Token* tokens, int token_cnt) {
	Node* firstNode = NULL;
	Node* thisNode = NULL;

	int nodeCnt = 0;

	for (int i = 0; i < token_cnt; ++i) {
		Node* newNode = NULL;

		printf("TOKEN: %i - ", tokens[i].type);

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
				if (tokens[i + 1].type >= TOKEN_PLUS && tokens[i + 1].type <= TOKEN_FORWARD_SLASH) {
					newNode = ParseExpression(tokens, &i, NULL);
				}
				else if (tokens[i + 1].type == 100) {
					//newNode = ParseFunCall(tokens, &i);
				}
				else {
					printf("ERROR: Unexpected identifier on line %i.", tokens[i + 2].line);
					exit(-1);
				}

				break;
			}
			case(TOKEN_LITERAL_INT): {
				if (tokens[i + 1].type >= TOKEN_PLUS && tokens[i + 1].type <= TOKEN_FORWARD_SLASH) {
					newNode = ParseExpression(tokens, &i, NULL);
				}
				else {
					printf("ERROR: Unexpected integer on line %i.", tokens[i + 2].line);
					exit(-1);
				}
				
				break;
			}
			case(TOKEN_LITERAL_STRING): {
				if (tokens[i + 1].type >= TOKEN_PLUS && tokens[i + 1].type <= TOKEN_FORWARD_SLASH) {
					newNode = ParseExpression(tokens, &i, NULL);
				}
				else if (tokens[i - 1].type == 100) {

				}
				else {
					printf("ERROR: Unexpected string on line %i.", tokens[i + 2].line);
					exit(-1);
				}
				break;
			}
			case(TOKEN_LITERAL_BOOL): {
				if (tokens[i + 1].type >= TOKEN_PLUS && tokens[i + 1].type <= TOKEN_FORWARD_SLASH) {
					newNode = ParseExpression(tokens, &i, NULL);
				}
				else {
					printf("ERROR: Unexpected bool on line %i.", tokens[i + 2].line);
					exit(-1);
				}
				
				break;
			}
			case(TOKEN_PLUS): {
				break;
			}
			case(TOKEN_DASH): {
				break;
			}
			case(TOKEN_STAR): {
				break;
			}
			case(TOKEN_FORWARD_SLASH): {
				break;
			}
			default: {
				break;
			}
		}

		if (newNode != NULL) {
			if (thisNode == NULL) {
				thisNode = newNode;
				++nodeCnt;
			}
			else {
				thisNode->next = newNode;
				newNode->prev = thisNode;
				thisNode = newNode;
				++nodeCnt;
			}

			printf("%i  - %s\n", newNode->type, newNode->var_name); // Print variable nodes
		}

		if (firstNode == NULL && thisNode != NULL) {
			firstNode = thisNode;
		}
	}

	thisNode->next = NULL;
	firstNode->prev = NULL;

	printf("--- %i ---\n", nodeCnt); // Print number of collected nodes

	return firstNode;
}