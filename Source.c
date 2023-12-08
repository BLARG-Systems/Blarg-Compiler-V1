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
			fseek(fp, 0L, SEEK_END);

			// Get size of file to allocate a large enough string
			int size = ftell(fp); 

			char* srcContent;
			srcContent = (char*) malloc(size * sizeof(char));

			// Move pointer back to beginning of file
			rewind(fp); 

			char srcTemp[65535];

			// Loop Through all lines in file, store to srcContent
			while (fgets(srcTemp, size, fp)) {
				// TODO: Optimize memory usage while reading lines

				strcat(srcContent, srcTemp);
				//printf("%s", srcTemp);
			}

			printf("FILE AS STRING:\n");
			printf("%s\n\n", srcContent);

			// Close file
			fclose(fp);
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