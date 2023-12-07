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

		if (fp != NULL)
		{
			// File exists and is readable
			fseek(fp, 0L, SEEK_END);
			int size = ftell(fp);

			char* srcContent;
			srcContent = (char*)malloc(size);

			rewind(fp);

			char srcTemp[65535];

			while (fgets(srcTemp, size, fp)) {
				strcat(srcContent, srcTemp);
				printf("%s", srcTemp);
			}

			printf("\n\nFULL STRING:\n");
			printf("%s", srcContent);

			fclose(fp);
		}
		else {
			printf("Unable to access BLARG! source file '%s'", filename);
			exit(-1);
		}
	}
	else {
		printf("No file argument supplied.");
		exit(-1);
	}
}