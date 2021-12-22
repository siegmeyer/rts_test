#include "all.h"

Table *LoadTableToMem(const char *fileName)
{
	int in;

	int row_inc = 0;
	int cell_inc = 0;
	size_t cell_max = 0;
	Table *tbl = table_create();

	FILE *file = fopen(fileName, "r");
	if (file == NULL) {
		perror("Error opening file");
		return NULL;
	}

	char cell[NUM_CHARS];
	char **row = (char**)malloc(sizeof(char*) * NUM_COLS);

	int i = 0;
	do {

		in = fgetc(file);
		
		// If normal character.
		if (in != DELIM && in != '\n' && in != EOF) {
			cell[i++] = (char)in;
			continue;
		}

		// Otherwise, a cell has been completed.
		cell[i++] = '\0';

		// Prep memory for cell then copy word in
		row[cell_inc] = (char*)malloc(sizeof(char) * i);
		memcpy(row[cell_inc], cell, i);

		// "Erase" cell
		cell[0] = '\0';
		i = 0;
		cell_inc++;
		if (in == '\n' || in == EOF) {
			
			// Set the max length with the first row
			if (row_inc == 0){
				cell_max = cell_inc;
			}

			// Pad out the row if it's missing some columns
			if (cell_inc < cell_max) {
				int fill = cell_max - cell_inc;

				for (int k = 0; k < fill; k++){
					row[cell_inc+k] = (char*)malloc(sizeof(char) * 3);
					strcpy(row[cell_inc+k], "||");
				} 
			}
			
			if (row_inc == 0) {
				table_header_add(tbl, row, cell_max);
			} 
			else {
				table_row_add(tbl, row, cell_max);
			}

			row_inc++;

			// Free each cell in the temp row
			for (int i = 0; i < cell_inc; i++) {
				free(row[i]);
			}

			cell_inc = 0;

			// reset the row
			memset(row, 0, sizeof(char*)* cell_max);
		}
		
	} while(!feof(file));
		
	fclose(file);

	free(row);
		
	return tbl;
}
