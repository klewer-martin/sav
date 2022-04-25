#include "array.h"

#include <stdio.h>
#include <time.h>

void shuffle(Arr *arr) {
	srand((unsigned int)time(NULL));
	for(size_t i = 0; i < arr->len; i++)
		while(!(arr->v[i] = rand() % ARR_MAX));

	printf("ARRAY: Shuffling array done\n");
}

void reversed(Arr *arr) {
	size_t i;
	int per_element;

	per_element = (ARR_MAX / arr->len);
	for(i = 0; i < arr->len; i++)
		arr->v[i] = (arr->len * per_element) - (i * per_element);
}

void in_order(Arr *arr) {
	size_t i;
	int per_element;

	per_element = (ARR_MAX / arr->len);

	for(i = 0; i < arr->len; i++)
		arr->v[i] = (i * per_element);
}
