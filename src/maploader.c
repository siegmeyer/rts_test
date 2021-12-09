#include "all.h"

BYTE ***LoadFileToMem(const char *fileName)
{
	FILE *file;
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

	BYTE cell[255];
	BYTE **row = (BYTE**)malloc(sizeof(BYTE**)* 25);
	BYTE ***table = (BYTE***)malloc(sizeof(BYTE***)* 100);

	int i = 0;
	do {

		in = fgetc(file);
		
		//
		// If normal character.
		//
		if (in != '\t' && in != '\n' && in != EOF) {
			cell[i++] = (BYTE)in;
			continue;
		}

		//
		// Otherwise, a cell has been completed.
		//
		cell[i++] = '\0';

		// Prep memory for row then copy word in
		row[cell_inc] = (BYTE*)malloc(sizeof(BYTE)* i);
		memcpy(row[cell_inc], cell, i);

		// "Erase" cell
		cell[0] = '\0';
		i = 0;
		cell_inc++;

		if (in == '\n' || in == EOF) {
			
			if (row_inc == 0)
				cell_max = cell_inc;

			table[row_inc] = (BYTE**)malloc(sizeof(BYTE**)* cell_max);
			memcpy(table[row_inc], row, sizeof(BYTE**)* cell_max);
			row_inc++;

			cell_inc = 0;
			// reset the row
			memset(row, 0, sizeof(BYTE*)* cell_max);
		}
		
	} while(!feof(file));
	
	

	for (int a = 0; a < row_inc; a++) {
		printf("\n");
		//printf("%d", a);
		for (int b = 0; b < cell_max; b++) {
			// printf("%d-", b);
			printf("%s\t", table[a][b]);
		}
	}

	printf("done\n");
	
	char temp[20];
	scanf("%s",&temp);

	printf("%s\n", temp);

	// free(cell);
	free(row);
	free(table);
	
	fclose(file);

	return table;
}
