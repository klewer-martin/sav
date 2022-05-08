#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdlib.h>

#define ARR_LEN		128
#define ARR_MAX		512

typedef enum {
	IN_ORDER,
	REVERSED,
	RANDOM,
	MAX_SHUFFLE
} shuffle_t;

typedef struct _Arr {
	int *v;
	size_t len;
	shuffle_t shuffle_sel;
	void (*shuffle)(struct _Arr *arr);
} Arr;

static char *const shuffle_t_str[MAX_SHUFFLE] = {
	"in_order",
	"reversed",
	"random",
};

void arr_random(Arr *arr);
void arr_reversed(Arr *arr);
void arr_in_order(Arr *arr);

void arr_shuffle(Arr *arr);
void arr_shuffle_next(Arr *arr);

#endif
