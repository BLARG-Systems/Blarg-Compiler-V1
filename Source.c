#include <stdio.h>
#include <stdbool.h>

// cl Source.c /Fe:blargify.exe

int main(int argc, char* argv[]) {
	if (argc > 1) {
		char* filename = argv[1];

		// Check if file ends in .blarg
		int dot = strrchr(filename, '.');
		if (!dot || strcmp(dot, ".blarg")) {
			printf("File '%s' is not a .blarg file.", filename);
			exit(-1);
		}

		// Get file and verify access
		FILE* fp = fopen(filename, "r");

		if (fp != NULL) { // File exists and is readable
			// Go to end of file, read length, then return to beginning of file
			fseek(fp, 0L, SEEK_END);
			long length = ftell(fp); 
  			fseek (f, 0, SEEK_SET);

			char* srcBuffer = (char*) malloc(size * sizeof(char));

			fread (buffer, 1, length, f);
			
  			fclose (f);

			printf("FILE AS STRING:\n");
			printf("%s\n\n", srcBuffer);
		}
		else { // File does not exist or cannot be read from
			printf("Unable to access BLARG! source file '%s'", filename);
			exit(-1);
		}
	}
	else {
		printf("No file argument supplied.");
		exit(-1);
	}
}