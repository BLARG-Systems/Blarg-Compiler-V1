#include "Lexer.h"
#include "Token.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static bool IsAlphabetic(char c) {
	return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

static bool IsDigit(char c) {
	return '0' <= c && c <= '9';
}

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

// Creates a token with IDENTIFIER type, and adds the specified value to the token
static void AddTokenIdentifierValue(Lexer* lexer, char* value) {
	Token t = MakeToken(TOKEN_IDENTIFIER, lexer->line, lexer->line_index);
	t.str_value = value;

	lexer->tokens[lexer->token_cnt] = t;
	++lexer->token_cnt;
}

// Creates a token with LITERAL_STRING type, and adds the specified value to the token
static void AddTokenStrValue(Lexer* lexer, char* value) {
	Token t = MakeToken(TOKEN_LITERAL_STRING, lexer->line, lexer->line_index);
	t.str_value = value;

	lexer->tokens[lexer->token_cnt] = t;
	++lexer->token_cnt;
}

// Creates a token with LITERAL_INT type, and adds the specified value to the token
static void AddTokenIntValue(Lexer* lexer, int value) {
	Token t = MakeToken(TOKEN_LITERAL_INT, lexer->line, lexer->line_index);
	t.int_value = value;

	lexer->tokens[lexer->token_cnt] = t;
	++lexer->token_cnt;
}

// Creates a token with LITERAL_BOOL type, and adds the specified value to the token
static void AddTokenBoolValue(Lexer* lexer, bool value) {
	Token t = MakeToken(TOKEN_LITERAL_BOOL, lexer->line, lexer->line_index);
	t.bool_value = value;

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
	case '<': {
		AddToken(lexer, TOKEN_LESSTHAN);
		break;
	}
	case '>': {
		AddToken(lexer, TOKEN_GREATERTHAN);
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
	case '.': {
		AddToken(lexer, TOKEN_PERIOD);
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
	else if (strncmp(s, ":/", 2) == 0) {
		for (int i = 1; i < strlen(s); ++i) {
			if (strncmp(&s[i], "\\:", 2) == 0) {
				lexer->line_index += i;
				lexer->index += i;

				return 1;
			}
		}
		printf("ERROR: MISSING \\: TO END COMMEND ON LINE %i.", lexer->line);
		exit(-1);
	}
	else if (strncmp(s, "\\:", 2) == 0) {
		printf("ERROR: UNEXPECTED END OF COMMENT ON LINE %i.", lexer->line);
		exit(-1);
	}
	else { return 0; }
	return 1;
}

// Returns 0 if no match found, 1 if a match is found. If any match is found, a token is created and added to the token array, then the indexs are incremented by the keyword length.
static int EatKeyword(Lexer* lexer, char* s) { // Yes... this is possibly one of the messiest way of doing this, but that's a future problem!
	if (strncmp(s, "expect", 6) == 0) { AddToken(lexer, TOKEN_EXPECT); lexer->line_index += 6; lexer->index += 6; }
	else if (strncmp(s, "while", 5) == 0) { AddToken(lexer, TOKEN_WHILE); lexer->line_index += 5; lexer->index += 5; }
	else if (strncmp(s, "integer", 7) == 0) { AddToken(lexer, TOKEN_INTEGER); lexer->line_index += 7; lexer->index += 7; }
	else if (strncmp(s, "string", 6) == 0) { AddToken(lexer, TOKEN_STRING); lexer->line_index += 6; lexer->index += 6; }
	else if (strncmp(s, "boolean", 7) == 0) { AddToken(lexer, TOKEN_BOOL); lexer->line_index += 7; lexer->index += 7; }
	else if (strncmp(s, "fun", 3) == 0) { AddToken(lexer, TOKEN_FUN); lexer->line_index += 3; lexer->index += 3; }
	else if (strncmp(s, "null", 4) == 0) { AddToken(lexer, TOKEN_NULL); lexer->line_index += 4; lexer->index += 4; }
	else if (strncmp(s, "true", 4) == 0) { AddTokenBoolValue(lexer, true); lexer->line_index += 4; lexer->index += 4; }
	else if (strncmp(s, "false", 5) == 0) { AddTokenBoolValue(lexer, false); lexer->line_index += 5; lexer->index += 5; }
	else { return 0; }
	return 1;
}

// Returns 0 if no literal found, 1 if a literal is found. Will terminate with code -1 if the literal was incomplete.
static int EatLiteral(Lexer* lexer, char* s) {
	char c = s[0];
	int length = 0;

	switch (c) { // Get string literal
	case '"': {
		for (int i = 1; i < strlen(s); ++i) {
			++length;
			if (s[i] == '"') {
				char* str_value = (char*)malloc(length);

				for (i = 1; i < length; ++i) {
					str_value[i - 1] = s[i];
				}

				//printf(strcat(str_value, "\0"));

				AddTokenStrValue(lexer, str_value);

				lexer->line_index += length + 1;
				lexer->index += length + 1;

				return 1;
			}
		}
		printf("ERROR: MISSING \" TO END STRING ON LINE %i.", lexer->line);
		exit(-1);
	}
	case '\'': {
		for (int i = 1; i < strlen(s); ++i) {
			++length;
			if (s[i] == '\'') {
				char* str_value = (char*)malloc(length);

				for (i = 1; i < length; ++i) {
					str_value[i - 1] = s[i];
				}

				AddTokenStrValue(lexer, str_value);

				lexer->line_index += length + 1;
				lexer->index += length + 1;

				return 1;
			}
		}
		printf("ERROR: MISSING ' TO END STRING ON LINE %i.", lexer->line);
		exit(-1);
	}
	case '`': {
		for (int i = 1; i < strlen(s); ++i) {
			++length;
			if (s[i] == '`') {
				char* str_value = (char*)malloc(length);

				for (i = 1; i < length; ++i) {
					str_value[i - 1] = s[i];
				}

				AddTokenStrValue(lexer, str_value);

				lexer->line_index += length + 1;
				lexer->index += length + 1;

				return 1;
			}
		}
		printf("ERROR: MISSING ` TO END STRING ON LINE %i.", lexer->line);
		exit(-1);
	}
	}

	if (IsDigit(c)) { // Get integer literal
		for (int i = 1; i < strlen(s); ++i) {
			++length;
			if (!IsDigit(s[i])) {
				char* str_value = (char*)malloc(length);

				for (i = 0; i < length; ++i) {
					str_value[i] = s[i];
				}

				char* ptr;
				AddTokenIntValue(lexer, (int)strtol(str_value, &ptr, 10));

				lexer->line_index += length;
				lexer->index += length;

				return 1;
			}
		}
		printf("ERROR: INTEGER DID NOT END.");
		exit(-1);
	}
	else if (IsAlphabetic(c) || c == '_') { // Get identifier
		for (int i = 1; i < strlen(s); ++i) {
			++length;
			if (!IsAlphabetic(s[i])) {
				char* str_value = (char*)malloc(length);

				for (i = 0; i < length; ++i) {
					str_value[i] = s[i];
				}

				AddTokenIdentifierValue(lexer, str_value);

				lexer->line_index += length;
				lexer->index += length;

				return 1;
			}
		}
		printf("ERROR: IDENTIFIER DID NOT END.");
		exit(-1);
	}

	return 0;
}

// Attempts to parse the token at the current index, and adds a token to the token array if valid.
static void EatToken(Lexer* lexer) {
	if (lexer->index == lexer->source_len) {
		AddToken(lexer, TOKEN_END_OF_FILE);
		return;
	}

	char* s;
	s = &lexer->source[lexer->index];

	printf("\n%s\n", s);

	int ateLiteral = EatLiteral(lexer, s);
	if (ateLiteral > 0) {
		return;
	}

	char c;
	c = lexer->source[lexer->index];

	int ateChar = EatChar(lexer, c);
	if (ateChar > 0) {
		++lexer->line_index;
		++lexer->index;
		return;
	}
	else if (ateChar < 0) {
		return;
	}

	int ateSymbol = EatSymbol(lexer, s);
	if (ateSymbol > 0) {
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
	for (int i = 0; i < lexer->source_len + 1; ++i) {
		EatToken(lexer);
		printf("[%i]  |  %i  ----  %i\n", lexer->index, lexer->token_cnt, lexer->tokens[lexer->token_cnt - 1].type);
		if (lexer->token_cnt > 0 && lexer->tokens[lexer->token_cnt - 1].type == 0) {
			printf("Lexing complete.\n\n");
			break;
		}
	}
}