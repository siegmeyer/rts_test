#ifndef _TABLE_H
#define _TABLE_H

#define	TABLE_OK			0
#define TABLE_NULL 			1
#define TABLE_HEAD_NULL		2

typedef struct Cell
{
	char *value;
} Cell;

typedef struct Row
{
	struct Row *next;
	Cell *cells;
	size_t length;
} Row;

typedef struct Table
{
	Row *columns;
	Row *head;
	Row *tail;
	int error_code;
} Table;

Table *table_create();
void table_row_add(Table *tbl, char **cell, size_t length);
void table_header_add(Table *tbl, char **cell, size_t length);

void table_destroy(Table *tbl);
void table_display(Table *tbl);

#endif
