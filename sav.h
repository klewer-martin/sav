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
	BUBBLE_SORT = 0,
	INSERTION_SORT,
	MERGE_SORT,
	QUICK_SORT,
	SORT_MAX_ALGORITHMS
} sort_t;

typedef struct {
	Arr *arr;
	size_t sel, cmp, cmps, swps, its, B_used;
	clock_t ti, tf;
	status_t status;
	status_t sort_status;
	sort_t sort_algo;
} SAV; 

extern char *algo_strings[SORT_MAX_ALGORITHMS];

status_t SAV_new(SAV **sav);
void SAV_destroy(SAV *sav);

#endif
