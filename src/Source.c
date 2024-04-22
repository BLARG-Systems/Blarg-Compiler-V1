#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include "AstNode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUFSIZE 32

int filelen;

char* readfile(char* filename) {
	// Get file and verify access
	FILE* fp = fopen(filename, "r");


	if (fp != NULL) { // File exists and is readable
		char buffer[BUFSIZE * sizeof(char)];
		char* output = NULL;
		int total = 0;

		while (!feof(fp)) {  // Until the end of the file
			int read = fread(buffer, sizeof(char), BUFSIZE, fp);  // Read the next BUFSIZE characters from the file
			output = (char*)realloc(output, total + read);   // Note:  skipping error handling from realloc!
			memcpy(output + total, buffer, read);  // Copy what was read to the end of the output buffer
			total += read;  // Keep track of the total read
		}
		fclose(fp);

		output = (char*)realloc(output, total + 1);   // Note:  skipping error handling from realloc!
		output[total] = '\0';   // Null-terminate the string
		filelen = strlen(output);

		return output;
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

		struct Lexer lexer;
		lexer.source = buffer;
		lexer.source_len = filelen;
		lexer.index = 0;
		lexer.line = 1;
		lexer.line_index = 0;
		lexer.token_cnt = 0;
		lexer.tokens = (Token*)malloc((filelen) * sizeof(Token));

		LexSource(&lexer);

		free(lexer.source);

		int i = 0;
		printf("| ");
		for (int i = 0; i < lexer.token_cnt; ++i) {
			printf("%d | ", lexer.tokens[i].type);
		}
		printf("\n\n");

		Node* firstNode = ParseTokens(lexer.tokens, lexer.token_cnt);

		free(lexer.tokens);

		Node* printNode = firstNode;

		while (printNode != NULL) {
			if (printNode->type == NODE_VARIABLE || printNode->type == NODE_FUNCTION || printNode->type == NODE_FUNCTION_CALL) {
				printf("%i  - %s (%i)\n", printNode->type, printNode->var_name, strlen(printNode->var_name)); // Print variable nodes
			}
			else if (printNode->type >= NODE_ADD) {
				printf("%i  - EXPR \n", printNode->type);
			}

			printNode = printNode->next;
		}

		printf("DONE");
		
	}
	else {
		printf("No file argument supplied.");
		exit(-1);
	}
}