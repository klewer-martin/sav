#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdlib.h>

#define ARR_LEN		128
#define ARR_MAX		500

typedef struct {
	int *v;
	size_t len;
} Arr;

void shuffle(Arr *arr);

#endif
