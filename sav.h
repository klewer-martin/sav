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
	BUBBLE_SORT_IMPROVED,
	INSERTION_SORT,
	MERGE_SORT,
	QUICK_SORT,
	SHELL_SORT,
	SELECTION_SORT,
	ALGORITHMS_COUNT
} sort_t;

typedef struct {
	Arr *arr;
	size_t sel, cmp, cmps, swps, its, B_used;
	time_t ti, tf;
	status_t status, prev_status, sort_status;
	sort_t sort_algo;
	size_t sort_delay;
} SAV;

status_t SAV_new(SAV **sav);
void SAV_destroy(SAV *sav);

void reset_sort_stats(SAV *sav);

#endif
