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

static void InsertToken(Lexer lexer, int line, int line_index, TokenType type, int* token_cnt) {
	Token t = MakeToken(line, line_index);
	t.type = type;

	lexer.tokens[*token_cnt] = t;
	++*token_cnt;
}

void Lex(Lexer lexer) {
	int token_cnt = 0;
	int line = 0;
	int line_index = 0;
	char* c;
	lexer.index = 0;
	printf("%d", lexer.source_len);

	printf("Testing\n");
	while (true) {
		if (lexer.index == lexer.source_len) {
			InsertToken(lexer, line, line_index, TOKEN_END_OF_FILE, &token_cnt);
			break;
		} 

		c = &lexer.source[lexer.index];
		printf("%c\n", c[0]);
		printf("%d\n", lexer.index);
		if (strncmp(c, "\n", 1) == 0) {
			//printf("Newline!");
			InsertToken(lexer, line, line_index, TOKEN_END_OF_LINE, &token_cnt);
			++line;
			line_index = 0;
			++lexer.index;
			continue;
		}

		++line_index;
		++lexer.index;
	}
}