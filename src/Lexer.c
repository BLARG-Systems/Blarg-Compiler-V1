#include "Lexer.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

static bool StrAreEqual(char* str1, char* str2) {
	return strcmp(str1, str2) == 0;
}

void Lex(Lexer* lexer) {
	int token_cnt;
	char c;
	while (true) {
		if (lexer->index == lexer->source_len) {
			// EOF
		} else if (StrAreEqual(lexer->source[lexer->index], "\n")) {
			// Newline
		}
	}
}