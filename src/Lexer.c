#include "Lexer.h"
#include "Token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool StrAreEqual(char* str1, char* str2) {
	return strcmp(str1, str2) == 0;
}

static Token MakeToken(int line, int line_index) {
	Token  this_token;
	this_token.line = lexer->line;
	this_token.line_index = line_index;

	return this_token;
}

static void InsertToken(Lexer lexer, int line, int line_index, TokenType type, int token_cnt) {
	Token t = MakeToken(line, line_index);
	t.type = type;

	lexer->tokens[token_cnt] = t;
	token_cnt++;
}

void Lex(Lexer* lexer) {
	int token_cnt;
	int line;
	int line_index;
	char c;
	while (true) {
		if (lexer->index == lexer->source_len) {
			InsertToken(lexer, line, line_index, TOKEN_END_OF_FILE, token_cnt);
			printf(token_cnt);
			continue
		} 

		c = lexer->source[lexer->index]
		if (StrAreEqual(lexer->source[lexer->index], "\n")) {
			InsertToken(lexer, line, line_index, TOKEN_END_OF_LINE, token_cnt);
			printf(token_cnt);
			continue
		}
		line_index++;;
	}
}