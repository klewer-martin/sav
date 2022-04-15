#include "array.h"

#include <stdio.h>
#include <time.h>

void shuffle(Arr *arr) {
	srand((unsigned int)time(NULL));
	for(size_t i = 0; i < arr->len; i++)
		while(!(arr->v[i] = rand() % ARR_MAX));

	printf("ARRAY: Shuffling array done\n");
}
