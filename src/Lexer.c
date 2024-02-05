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

// Returns -1 for newline, 0 if no match found, 1 if a match is found. If any match is found, a token is created and added to the token array.
static int EatChar(Lexer* lexer, char c) {
	switch (c) { // I better never have to update this
		case '\n': {
			AddToken(lexer, TOKEN_END_OF_LINE);
			++lexer->line;
			lexer->line_index = 0;
			++lexer->index;
			return -1;
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

// Returns 0 if no match found, 1 if a match is found. If any match is found, a token is created and added to the token array.
static int EatKeyword(Lexer* lexer, char* s) {

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
		++lexer->line_index;
		++lexer->index;
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