#include "all.h"
#include <time.h>

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
		printf("%s ",search->cells[UNIT_STAT_HP].value);
	}

	// char* tester;
	// time_t start = time(NULL);
	// for (int i = 0; i < 100000000; i++) {
	// 	tester = table_get(tbl, UNIT_BATTLECRUISER, "time");
	// }

	// printf("DONE in %ld seconds", time(NULL) - start);
	table_destroy(tbl);
	return 0;
}

void multi_alloc(size_t x, size_t y, int(**ptr)[x][y]){
	*ptr = malloc(sizeof(int[x][y]));
	assert(*ptr != NULL);
}
