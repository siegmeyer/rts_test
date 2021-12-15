#include "all.h"

void multi_alloc(size_t x, size_t y, int(**ptr)[x][y]);

int main() {
	
	// char *str0 = "test string";
	// char *str1 = (char*) malloc(sizeof(char) * 11);
	// char *str2;


	// memcpy(str1, str0, 11);

	// str2 = str1;
	// memset(str1, 0, 11);
	// printf("%s", str2);

	//MAPDATA* map;
	size_t x = 2;
	size_t y = 3;
	int (*ptr)[x][y];

	multi_alloc(x,y,&ptr);
	free(ptr);

	char ***file;

	file = LoadTableToMem("data/test.dat");

	return 0;
}

void multi_alloc(size_t x, size_t y, int(**ptr)[x][y]){
	*ptr = malloc(sizeof(int[x][y]));
	assert(*ptr != NULL);
}
