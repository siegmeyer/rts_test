#ifndef __ITEM_H
#define __ITEM_H

typedef struct
{
	struct Item *next;
	int id;
	int type_id;
	char *name;
	int hp;
} Item;

typedef struct
{
	Item *head;
	int error_code;
} ItemList;

ItemList *itemlist_create();

#endif
