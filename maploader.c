#include "all.h"

BYTE *LoadFileToMem(const char *fileName)
{
	FILE *file;
	BYTE *buf;
	int in;
	char **row;
	int line_inc = 0;
	int word_inc = 0;
	ItemList *list;

	file = fopen(fileName, "r");
	if (file == NULL) {
		perror("Error opening file");
		return NULL;
	}

	list = itemlist_create();

	char *letter_buffer = (char*) malloc(sizeof(char)*255);
	char **word_buffer = (char**) malloc(sizeof(char**)*25);
	char ***line_buffer = (char***) malloc(sizeof(char***)*100);

	int i = 0;
	do {
		in = fgetc(file);
		// printf("%c", in);
		if (in == '\t' || in == '\n') {
			letter_buffer[i++] = '\0'; // finish the word
			printf("%d", i);
			word_buffer[word_inc] = (char*) malloc(sizeof(char) * i);
			for (int k = 0; k < i; k++) {
				word_buffer[word_inc][k] = letter_buffer[k];
			}
			printf("%s", word_buffer[word_inc]);
			letter_buffer[0] = '\0';
			i = 0;
			word_inc++;

			if (in == '\n') {
				line_buffer[line_inc++] = (char**) malloc(sizeof(char**) * word_inc);
				for (int j = 0; j < word_inc; j++) {
					// line_buffer[line_inc] = word_buffer[j]
				}
			}

			continue;
		}

		letter_buffer[i++] = in;
		
	} while(!feof(file));

	free(letter_buffer);
	free(word_buffer);
	free(line_buffer);
	

// 	WOpenFile(pszName, &file, FALSE);
// 	fileLen = WGetFileSize(file, NULL);

// 	if (pdwFileLen)
// 		*pdwFileLen = fileLen;

// 	if (!fileLen)
// 		app_fatal("Zero length SFILE:\n%s", pszName);

// 	buf = (BYTE *)DiabloAllocPtr(fileLen);

// 	WReadFile(file, buf, fileLen);
// 	WCloseFile(file);
	fclose(file);

	return buf;
}
