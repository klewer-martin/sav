#include "array.h"

#include <stdio.h>
#include <time.h>

static void (*shuffle_handler[MAX_SHUFFLE])(Arr *arr) = {
	&arr_in_order,
	&arr_reversed,
	&arr_random
};

status_t Arr_create(Arr **arr) {
	if(((*arr) = (Arr *)malloc(sizeof(Arr))) == NULL)
		return ERROR_MEMORY_ALLOC;

	if(((*arr)->v = malloc(sizeof(int) * (ARR_LEN + 4))) == NULL)
		return ERROR_MEMORY_ALLOC;

	if(((*arr)->bk = malloc(sizeof(int) * (ARR_LEN + 4))) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*arr)->len = ARR_LEN;
	(*arr)->shuffle = &arr_shuffle;

	return OK;
}

void Arr_destroy(Arr *arr) {
	free(arr->bk);
	free(arr->v);
	free(arr);
}

void arr_restore_from_bk(Arr *arr) {
	for(size_t i = 0; i < arr->len; i++)
		arr->v[i] = arr->bk[i];
}

void arr_random(Arr *arr) {
	srand((unsigned int)time(NULL));
	for(size_t i = 0; i < arr->len; i++)
		while(!(arr->v[i] = arr->bk[i] = rand() % ARR_MAX));

	printf("ARRAY: Shuffling array done\n");
}

void arr_reversed(Arr *arr) {
	size_t i;
	int per_element;

	per_element = (ARR_MAX / arr->len);
	for(i = 0; i < arr->len; i++)
		arr->v[i] = arr->bk[i] = (arr->len * per_element) - (i * per_element);
}

void arr_in_order(Arr *arr) {
	size_t i;
	int per_element;

	per_element = (ARR_MAX / arr->len);

	for(i = 0; i < arr->len; i++)
		arr->v[i] = arr->bk[i] = (i * per_element);
}

void arr_shuffle(Arr *arr) {
	shuffle_handler[arr->shuffle_sel](arr);
}

void arr_shuffle_next(Arr *arr) {
	arr->shuffle_sel = ((arr->shuffle_sel + 1) == MAX_SHUFFLE) ? 0 : arr->shuffle_sel + 1;
}
