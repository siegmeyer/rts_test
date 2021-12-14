#ifndef _TABLE_H
#define _TABLE_H

typedef struct
{
	struct Cell *next;
	char *value;
} Cell;

typedef struct
{
	struct Row *next;
	Cell *head_cell;
	size_t length;
} Row;

typedef struct
{
	Row *columns;
	Row *head;
	int error_code;
} Table;

#define	TABLE_OK			0
#define TABLE_NULL 			1
#define TABLE_HEAD_NULL		2

Table *table_create();
void table_row_add(Table *tbl, char **cell, size_t length);
void table_header_add(Table *tbl, char **cell, size_t length);

#endif
