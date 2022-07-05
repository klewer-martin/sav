#ifndef __SAV_H__
#define __SAV_H__

#include <time.h>
#include <stdbool.h>

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
	HEAP_SORT,
	ALGORITHMS_COUNT
} sort_t;

typedef struct {
	Arr *arr;
	size_t sel, cmp, cmps, swps, its, B_used;
	time_t ti, tf;
	status_t status, prev_status, sort_status;
	sort_t sort_algo;
	size_t sort_delay;
	bool quit;
} SAV;

status_t SAV_create(SAV **sav);
void SAV_destroy(SAV *sav);

void sort_reset_stats(SAV *sav);
void sort_selector(SAV *sav);

#endif
