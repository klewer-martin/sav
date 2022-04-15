#ifndef __SAV_H__
#define __SAV_H__

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "util.h"
#include "array.h"

typedef enum {
	BUBBLE_SORT,
	INSERTION_SORT,
	MERGE_SORT,
	QUICK_SORT,
	ALGORITHMS_COUNT
} sort_t;

typedef struct {
	Arr *arr;
	size_t sel, cmp, cmps, swps, its, B_used;
	clock_t ti, tf;
	status_t status;
	status_t sort_status;
	sort_t sort_algo;
} SAV;

status_t SAV_new(SAV **sav);
void SAV_destroy(SAV *sav);

#endif
