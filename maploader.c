#include "all.h"

BYTE *LoadFileToMem(const char *fileName)
{
	FILE *file;
	BYTE *buf;
	int in;

	int row_inc = 0;
	int cell_inc = 0;
	int cell_max = 0;
	ItemList *list;

	file = fopen(fileName, "r");
	if (file == NULL) {
		perror("Error opening file");
		return NULL;
	}

	list = itemlist_create();

	char cell[255];
	char **row = (char**) malloc(sizeof(char**)*25);
	char ***table = (char***) malloc(sizeof(char***)*100);

	int i = 0;
	do {

		in = fgetc(file);
		
		//
		// If normal character.
		//
		if (in != '\t' && in != '\n' && in != EOF) {
			cell[i++] = in;
			continue;
		}

		// Finish the word
		cell[i++] = '\0';

		// Prep memory for row then copy word in
		row[cell_inc] = (char*) malloc(sizeof(char) * i);
		memcpy(row[cell_inc], cell, i);

		// "Erase" cell
		cell[0] = '\0';
		i = 0;
		cell_inc++;

		if (in == '\n' || in == EOF) {
			table[row_inc] = (char**) malloc(sizeof(char**) * cell_inc);
			memcpy (table[row_inc], row, sizeof(char**) * cell_inc);
			row_inc++;

			if (cell_inc > cell_max) 
				cell_max = cell_inc;
			
			cell_inc = 0;
		}
		
	} while(!feof(file));
	
	for (int a = 0; a < row_inc; a++) {
		printf("\n");
		for (int b = 0; b < cell_max; b++) {
			// printf("%d-", b);
			printf("%s\t", table[a][b]);
		}
	}

	// free(cell);
	free(row);
	free(table);
	

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
