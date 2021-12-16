#include "all.h"

Table *table_create() {
	Table *tbl;

	tbl = (Table*)malloc(sizeof(Table));

	if (tbl == NULL) 
		return NULL;

	tbl->head = NULL;
	tbl->columns = NULL;
	tbl->tail = NULL;
	tbl->length = 0;

	tbl->error_code = TABLE_OK;

	return tbl;
}

//
// Need to actually test this for memory leaks.
//
void table_destroy(Table *tbl){
	if (tbl == NULL) return;

	if (tbl->columns != NULL) {
		for (size_t i = 0; i < tbl->columns->length; i++) {
			free(tbl->columns->cells[i].value);
		}
		free(tbl->columns->cells);
		free(tbl->columns);
	}

	Row *cur = tbl->head;

	while (cur != NULL) {
		// Free the values
		for (size_t i = 0; i < cur->length; i++) {
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

	if (tbl->tail != NULL) {
		tbl->tail->next = row;
	}

	if (tbl->length == 0) {
		tbl->head = row;
	}

	tbl->tail = row;
	tbl->length++;

	for (size_t i = 0; i < row->length; i++){

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
		for (size_t i = 0; i < tbl->columns->length; i++) {
			free(tbl->columns->cells[i].value);
		}
		free(tbl->columns->cells);
		free(tbl->columns);
	}

	tbl->columns = header;

	for (size_t i = 0; i < header->length; i++){
		size_t copysize = sizeof(char) * (strlen(cell[i]) + 1);

		Cell c;
		c.value = (char*)malloc(copysize);
		strncpy(c.value, cell[i], copysize);

		header->cells[i] = c;
	}
}

int table_search(Table *tbl, char *key, char *value, Row **result){

	if (tbl == NULL) 					return TABLE_NULL;
	if (key == NULL || value == NULL) 	return INVALID_ARGS;
	if (tbl->columns == NULL) 			return TABLE_NO_COLUMNS;

	int col_id = -1;

	*result = NULL;

	for (size_t i = 0; i < tbl->columns->length; i++) {
		if (strcmp(tbl->columns->cells[i].value, key) == 0) {
			col_id = i;
		}
	}

	if (col_id < 0) {
		return TABLE_COLUMN_NOT_FOUND;
	}

	Row *cur = tbl->head;
	while (cur != NULL) {
		if (strcmp(cur->cells[col_id].value, value) == 0) {
			*result = cur;
			// printf("%zu ", result->length);
			return FOUND;
		}
		cur = cur->next;
	}

	return NOT_FOUND;
}

void table_display(Table *tbl) {
	if (tbl == NULL) return;

	// Loop and dump the columns first
	if (tbl->columns != NULL) {
		for (size_t i = 0; i < tbl->columns->length; i++) {
			printf("%s\t", tbl->columns->cells[i].value);
		}
		printf("\n");
	}

	Row *cur = tbl->head;
	while (cur != NULL) {

		for (size_t i = 0; i < cur->length; i++) {
			printf("%s\t", cur->cells[i].value);
		}

		printf("\n");
		cur = cur->next;
	}

}

