#include "Lexer.h"
#include "Token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static bool StrAreEqual(char* str1, char* str2) {
	return strncmp(str1, str2, 1) == 0;
}

static Token MakeToken(int line, int line_index) {
	Token this_token;
	this_token.line = line;
	this_token.line_index = line_index;

	return this_token;
}

static void AddToken(Lexer* lexer, TokenType type) {
	Token t = MakeToken(lexer->line, lexer->line_index);
	t.type = type;

	lexer->tokens[lexer->token_cnt] = t;
	++lexer->token_cnt;
}

static void EatToken(Lexer* lexer) {
	char c;

	if (lexer->index == lexer->source_len) {
		AddToken(lexer, TOKEN_END_OF_FILE);
		return;
	}

	c = lexer->source[lexer->index];
	//printf("%c\n", c);

	switch (c) {
		case '\n': {
			AddToken(lexer, TOKEN_END_OF_LINE);
			++lexer->line;
			lexer->line_index = 0;
			++lexer->index;
			return;
		}
		case '(': {
			AddToken(lexer, TOKEN_LEFT_PARENTHESIS);
		}
	}

	++lexer->line_index;
	++lexer->index;
}

void LexSource(Lexer* lexer) {
	for (int i = 0; i < lexer->source_len+1; ++i) {
		//printf("%i\n", lexer->source_len);
		//printf("%i\n\n", i);
		EatToken(lexer);
		printf("[%i]  |  %i  ----  %i\n", lexer->index, lexer->token_cnt, lexer->tokens[lexer->token_cnt - 1].type);
		if (lexer->token_cnt > 0 && lexer->tokens[lexer->token_cnt - 1].type == 0) {
			printf("Lexing complete.\n\n");
			break;
		}
	}
}