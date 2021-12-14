#include <stdlib.h>
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
	tbl->head->head_cell = NULL;
	tbl->head->length = 0;

	tbl->error_code = TABLE_OK;

	return tbl;
}
