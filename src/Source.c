#include "Lexer.h"
#include "Token.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// cl src\Source.c /Fe:blargify.exe

int filelen;

char* readfile(char* filename) {
	// Get file and verify access
	FILE* fp = fopen(filename, "r");
	

	if (fp != NULL) { // File exists and is readable
		// Go to end of file, read length, then return to beginning of file
		fseek(fp, 0, SEEK_END);
		filelen = ftell(fp) - 7;
		fseek(fp, 0, SEEK_SET);

		// Reserve memory for file string
		char* srcBuffer = malloc(filelen * sizeof(char));

		// Read file into srcBuffer, append EOF indicator
		fread(srcBuffer, 1, filelen, fp);
		srcBuffer[filelen] = '\0';

		fclose(fp);

		return srcBuffer;
	}
	else { // File does not exist or cannot be read from
		printf("Unable to access BLARG! source file '%s'", filename);
		exit(-1);
		return NULL;
	}
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		char* filename = argv[1];

		// Check if file ends in .blarg
		char* dot = strrchr(filename, '.');
		if (dot == NULL || strcmp(dot, ".blarg") != 0) {
			printf("File '%s' is not a .blarg file.", filename);
			exit(-1);
		}

		char* buffer = readfile(filename);

		struct List tokens;
		ListInit(&tokens);

		struct Lexer lexer;
		lexer.source = buffer;
		lexer.source_len = filelen;
		lexer.index = 0;
		lexer.line = 1;
		lexer.line_index = 0;
		lexer.tokens = &tokens; //(Token*) malloc((filelen) * sizeof(Token));

		LexSource(&lexer);
		
		int i = 0;
		for (int i = 0; i < lexer.tokens->size; ++i) {
			Token* thisToken = (Token*) ListGet(lexer.tokens, i);
			TokenType thisTokenType = thisToken->type;

			printf("%d | ", thisTokenType);//lexer.tokens[i].type);
		}
	}
	else {
		printf("No file argument supplied.");
		exit(-1);
	}
}