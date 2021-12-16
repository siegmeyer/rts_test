#include "all.h"

void multi_alloc(size_t x, size_t y, int(**ptr)[x][y]);

int main() {
	
	size_t x = 2;
	size_t y = 3;
	int (*ptr)[x][y];

	multi_alloc(x,y,&ptr);
	free(ptr);

	Table *tbl = LoadTableToMem("data/units.dat");
	// Table *tbl = LoadTableToMem("data/test.dat");

	table_display(tbl);

	Row *search = NULL;
	table_search(tbl,"Unit","Marine",&search);

	if (search != NULL) {
		printf("%s ",search->cells[UNIT_HP].value);

	}

	table_destroy(tbl);
	return 0;
}

void multi_alloc(size_t x, size_t y, int(**ptr)[x][y]){
	*ptr = malloc(sizeof(int[x][y]));
	assert(*ptr != NULL);
}
