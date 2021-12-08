#include <stdlib.h>
#include "item.h"

ItemList *itemlist_create() {
	ItemList l;

	l.head = NULL;

	return (ItemList*)malloc(sizeof(l));
}
