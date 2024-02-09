#include "Lexer.h"
#include "Token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Creates a token with the provided data
static Token MakeToken(TokenType type, int line, int line_index) {
	Token this_token;
	this_token.type = type;
	this_token.line = line;
	this_token.line_index = line_index;

	return this_token;
}

// Creates a token of the specified type, then adds it to the token array
static void AddToken(Lexer* lexer, TokenType type) {
	Token t = MakeToken(type, lexer->line, lexer->line_index);

	lexer->tokens[lexer->token_cnt] = t;
	++lexer->token_cnt;
}

static void AddTokenStrValue(Lexer* lexer, TokenType type, char* value) {
	Token t = MakeToken(type, lexer->line, lexer->line_index, value);
	t.bool_value = value

	lexer->tokens[lexer->token_cnt] = t;
	++lexer->token_cnt;
}

static void AddTokenIntValue(Lexer* lexer, TokenType type, int value) {
	Token t = MakeToken(type, lexer->line, lexer->line_index, value);
	t.bool_value = value

		lexer->tokens[lexer->token_cnt] = t;
	++lexer->token_cnt;
}

static void AddTokenBoolValue(Lexer* lexer, TokenType type, bool value) {
	Token t = MakeToken(type, lexer->line, lexer->line_index, value);
	t.bool_value = value

		lexer->tokens[lexer->token_cnt] = t;
	++lexer->token_cnt;
}

// Returns -1 for newline, 0 if no match found, 1 if a match is found. If any match is found, a token is created and added to the token array. Also eats whitespace!
static int EatChar(Lexer* lexer, char c) {
	switch (c) { // I better never have to update this
		case '\n': {
			AddToken(lexer, TOKEN_END_OF_LINE);
			++lexer->line;
			lexer->line_index = 0;
			++lexer->index;
			return -1;
		}
		case ' ': {
			break;
		}
		case '	': {
			break;
		}
		case '(': {
			AddToken(lexer, TOKEN_LEFT_PARENTHESIS);
			break;
		}
		case ')': {
			AddToken(lexer, TOKEN_RIGHT_PARENTHESIS);
			break;
		}
		case '{': {
			AddToken(lexer, TOKEN_LEFT_CURLYBRACE);
			break;
		}
		case '}': {
			AddToken(lexer, TOKEN_RIGHT_CURLYBRACE);
			break;
		}
		case '\'': {
			AddToken(lexer, TOKEN_SINGLE_QUOTE);
			break;
		}
		case '"': {
			AddToken(lexer, TOKEN_DOUBLE_QUOTE);
			break;
		}
		case '*': {
			AddToken(lexer, TOKEN_STAR);
			break;
		}
		case '/': {
			AddToken(lexer, TOKEN_FORWARD_SLASH);
			break;
		}
		case '-': {
			AddToken(lexer, TOKEN_DASH);
			break;
		}
		case '+': {
			AddToken(lexer, TOKEN_PLUS);
			break;
		}
		case '~': {
			AddToken(lexer, TOKEN_TILDE);
			break;
		}
		case '=': {
			AddToken(lexer, TOKEN_EQUALS);
			break;
		}
		case '?': {
			AddToken(lexer, TOKEN_QUESTION);
			break;
		}
		case '&': {
			AddToken(lexer, TOKEN_AMPERSAND);
			break;
		}
		case '^': {
			AddToken(lexer, TOKEN_CARRAT);
			break;
		}
		case '|': {
			AddToken(lexer, TOKEN_VERTICAL_BAR);
			break;
		}
		default: {
			return 0;
		}
	}
	return 1;
}

// Returns 0 if no match found, 1 if a match is found. If any match is found, a token is created and added to the token array.
static int EatSymbol(Lexer* lexer, char* s) {
	if (strncmp(s, ":)", 2) == 0) { AddToken(lexer, TOKEN_END_OF_STATEMENT); }
	else if (strncmp(s, ":(", 2) == 0) { AddToken(lexer, TOKEN_ELSE); }
	else if (strncmp(s, "&&", 2) == 0) { AddToken(lexer, TOKEN_AND); }
	else if (strncmp(s, "||", 2) == 0) { AddToken(lexer, TOKEN_OR); }
	else { return 0; }
	return 1;
}

// Returns 0 if no match found, 1 if a match is found. If any match is found, a token is created and added to the token array, then the indexs are incremented by the keyword length.
static int EatKeyword(Lexer* lexer, char* s) {
	if (strncmp(s, "expect", 6) == 0) { AddToken(lexer, TOKEN_EXPECT); lexer->line_index += 6; lexer->index += 6; }
	else if (strncmp(s, "while", 5) == 0) { AddToken(lexer, TOKEN_WHILE); lexer->line_index += 5; lexer->index += 5; }
	else if (strncmp(s, "int", 3) == 0) { AddToken(lexer, TOKEN_INTEGER); lexer->line_index += 3; lexer->index += 3; }
	else if (strncmp(s, "str", 3) == 0) { AddToken(lexer, TOKEN_STRING); lexer->line_index += 3; lexer->index += 3; }
	else if (strncmp(s, "bool", 4) == 0) { AddToken(lexer, TOKEN_BOOL); lexer->line_index += 4; lexer->index += 4; }
	else if (strncmp(s, "fun", 3) == 0) { AddToken(lexer, TOKEN_FUN); lexer->line_index += 3; lexer->index += 3; }
	else if (strncmp(s, "null", 4) == 0) { AddToken(lexer, TOKEN_NULL); lexer->line_index += 4; lexer->index += 4; }
	else if (strncmp(s, "true", 4) == 0) { AddTokenBoolValue(lexer, TOKEN_LITERAL_BOOL, true); lexer->line_index += 4; lexer->index += 4; }
	else if (strncmp(s, "false", 5) == 0) { AddTokenBoolValue(lexer, TOKEN_LITERAL_BOOL, false); lexer->line_index += 5; lexer->index += 5; }
	else { return 0; }
	return 1;
}

// Attempts to parse the token at the current index, and adds a token to the token array if valid.
static void EatToken(Lexer* lexer) {
	if (lexer->index == lexer->source_len) {
		AddToken(lexer, TOKEN_END_OF_FILE);
		return;
	}

	char c;
	c = lexer->source[lexer->index];

	//printf("%c",c);
	int ateChar = EatChar(lexer, c);
	//printf("%d\n", ateChar);
	if (ateChar > 0) {
		printf("%c\n", c);
		++lexer->line_index;
		++lexer->index;
		return;
	}
	else if (ateChar < 0) {
		return;
	}
	
	char* s;
	s = &lexer->source[lexer->index];

	int ateSymbol = EatSymbol(lexer, s);
	if (ateSymbol > 0) {
		printf("%c%c\n", s[0], s[1]);
		lexer->line_index += 2;
		lexer->index += 2;
		return;
	}

	int ateKeyword = EatKeyword(lexer, s);
	if (ateKeyword > 0) {
		return;
	}

	++lexer->line_index;
	++lexer->index;
}

void LexSource(Lexer* lexer) {
	for (int i = 0; i < lexer->source_len+1; ++i) {
		EatToken(lexer);
		//printf("[%i]  |  %i  ----  %i\n", lexer->index, lexer->token_cnt, lexer->tokens[lexer->token_cnt - 1].type);
		if (lexer->token_cnt > 0 && lexer->tokens[lexer->token_cnt - 1].type == 0) {
			printf("Lexing complete.\n\n");
			break;
		}
	}
}