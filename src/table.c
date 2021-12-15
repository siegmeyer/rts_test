#include "all.h"

Table *table_create() {
	Table *tbl;

	tbl = (Table*)malloc(sizeof(Table));

	if (tbl == NULL) 
		return NULL;

	tbl->head = (Row*)malloc(sizeof(Row));
	tbl->columns = (Row*)malloc(sizeof(Row));

	if (tbl->head == NULL || tbl->columns == NULL) {
		tbl->error_code = TABLE_HEAD_NULL;
		return tbl;
	}

	tbl->head->next = NULL;
	tbl->head->cells = NULL;
	tbl->head->length = 0;

	tbl->columns->next = NULL;
	tbl->columns->cells = NULL;
	tbl->columns->length = 0;

	tbl->tail = tbl->head;
	tbl->error_code = TABLE_OK;

	return tbl;
}

//
// Need to actually test this for memory leaks.
//
void table_destroy(Table *tbl){
	if (tbl == NULL) return;

	if (tbl->columns != NULL) {
		for (int i = 0; i < tbl->columns->length; i++) {
			free(tbl->columns->cells[i].value);
		}
		free(tbl->columns->cells);
		free(tbl->columns);
	}

	Row *cur = tbl->head;

	while (cur != NULL) {
		// Free the values
		for (int i = 0; i < cur->length; i++) {
			free(cur->cells[i].value);
		}

		// Free the Cell objects
		free(cur->cells);
		Row *next = cur->next;

		// Free the row object
		free(cur);
		cur = next;
	}

	free(tbl);
}

void table_row_add(Table *tbl, char **cell, size_t length) {
	Row *row;

	row = (Row*)malloc(sizeof(Row));

	assert (row != NULL); 

	row->next = NULL;
	row->cells = (Cell*)malloc(sizeof(Cell) * length);
	row->length = length;

	tbl->tail->next = row;
	tbl->tail = row;

	for (int i = 0; i < row->length; i++){

		size_t copysize = sizeof(char) * (strlen(cell[i]) + 1);

		Cell c;
		c.value = (char*)malloc(copysize);
		strncpy(c.value, cell[i], copysize);

		row->cells[i] = c;
	}

}

void table_header_add(Table *tbl, char **cell, size_t length) {
	Row *header;

	header = (Row*)malloc(sizeof(Row));

	assert (header != NULL);

	header->next = NULL;
	header->cells = (Cell*)malloc(sizeof(Cell) * length);
	header->length = length;

	if (tbl->columns != NULL) {
		free(tbl->columns->cells);
		free(tbl->columns);
	}

	tbl->columns = header;

	for (int i = 0; i < header->length; i++){
		size_t copysize = sizeof(char) * (strlen(cell[i]) + 1);

		Cell c;
		c.value = (char*)malloc(copysize);
		strncpy(c.value, cell[i], copysize);

		header->cells[i] = c;
	}
}

void table_display(Table *tbl) {
	if (tbl == NULL) return;

	// Loop and dump the columns first
	if (tbl->columns != NULL) {
		for (int i = 0; i < tbl->columns->length; i++) {
			printf("%s\t", tbl->columns->cells[i].value);
		}
	}

	Row *cur = tbl->head;
	while (cur != NULL) {

		for (int i = 0; i < cur->length; i++) {
			printf("%s\t", cur->cells[i].value);
			
		}

		printf("\n");
		cur = cur->next;
	}

}

