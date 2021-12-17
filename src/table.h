#ifndef _TABLE_H
#define _TABLE_H

#define	TABLE_OK				0
#define TABLE_NULL 				1
#define TABLE_NO_HEAD			2
#define TABLE_NO_COLUMNS		3
#define INVALID_ARGS			4
#define TABLE_COLUMN_NOT_FOUND	5

#define FOUND 					0
#define NOT_FOUND				1

#define DELIM					','

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
	int length;
	int error_code;
} Table;

Table *table_create();
void table_row_add(Table *tbl, char **cell, size_t length);
void table_header_add(Table *tbl, char **cell, size_t length);

void table_destroy(Table *tbl);
void table_display(Table *tbl);
int table_search(Table *tbl, char* col, char* value, Row **result);
char *table_get(Table *tbl, int id, char* col);

#endif
