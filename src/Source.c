#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// cl src\Source.c /Fe:blargify.exe

char* readfile(char* filename) {
	// Get file and verify access
	FILE* fp = fopen(filename, "r");
	

	if (fp != NULL) { // File exists and is readable

		// Go to end of file, read length, then return to beginning of file
		fseek(fp, 0L, SEEK_END);
		long length = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		// Reserve memory for file string
		char* srcBuffer = (char*) malloc((length) * sizeof(char));printf("WHY");

		// Read file into srcBuffer, append EOF indicator
		fread(srcBuffer, 1, length, fp);
		srcBuffer[length] = '\0';

		fclose(fp);

		printf(srcBuffer);

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
		int dot = strrchr(filename, '.');
		if (dot == NULL || strcmp(dot, ".blarg") != 0) {
			printf("File '%s' is not a .blarg file.", filename);
			exit(-1);
		}

		char* buffer = readfile(filename);

		printf(buffer);

		for (int i = 0; i < strlen(buffer); i++) {
			printf("%c\n", buffer[i]);
		}
	}
	else {
		printf("No file argument supplied.");
		exit(-1);
	}
}