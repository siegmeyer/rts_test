#include "all.h"

char ***LoadTableToMem(const char *fileName)
{
	FILE *file;
	int in;

	int row_inc = 0;
	int cell_inc = 0;
	size_t cell_max = 0;
	Table *tbl;

	file = fopen(fileName, "r");
	if (file == NULL) {
		perror("Error opening file");
		return NULL;
	}

	tbl = table_create();

	char cell[NUM_CHARS];
	char **row = (char**)malloc(sizeof(char**) * NUM_COLS);
	char ***table = (char***)malloc(sizeof(char***) * NUM_ROWS);

	int i = 0;
	do {

		in = fgetc(file);
		
		//
		// If normal character.
		//
		if (in != '\t' && in != '\n' && in != EOF) {
			cell[i++] = (char)in;
			continue;
		}

		//
		// Otherwise, a cell has been completed.
		//
		cell[i++] = '\0';

		// Prep memory for row then copy word in
		row[cell_inc] = (char*)malloc(sizeof(char) * i);
		memcpy(row[cell_inc], cell, i);

		// "Erase" cell
		cell[0] = '\0';
		i = 0;
		cell_inc++;

		if (in == '\n' || in == EOF) {
			
			if (row_inc == 0)
				cell_max = cell_inc;

			table[row_inc] = (char**)malloc(sizeof(char**)* cell_max);
			memcpy(table[row_inc], row, sizeof(char**)* cell_max);
			row_inc++;

			cell_inc = 0;
			// reset the row
			memset(row, 0, sizeof(char*)* cell_max);
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

	for (int a = 0; a < row_inc; a++) {
		for (int b = 0; b < cell_max; b++) {
			free(table[a][b]);
		}
		free(table[a]);
	}

	free(row);
	free(table);

	printf("done\n");
	
	char temp[20];
	scanf("%s", temp);

	printf("%s\n", temp);

	
	fclose(file);

	return table;
}
