#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdlib.h>

#define ARR_LEN		128
#define ARR_MAX		512

typedef struct {
	int *v;
	size_t len;
} Arr;

void shuffle(Arr *arr);
void reversed(Arr *arr);
void in_order(Arr *arr);

#endif
