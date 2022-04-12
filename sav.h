#ifndef __SAV_H__
#define __SAV_H__

#include "util.h"

#include <time.h>
#include <SDL2/SDL.h>

typedef enum {
	BUBBLE_SORT = 0,
	INSERTION_SORT,
	MERGE_SORT,
	SORT_MAX_ALGORITHMS
} sort_t;

typedef struct {
	Arr *arr;
	size_t sel, cmp, cmps, swps, its, B_used;
	clock_t ti, tf;
	status_t status;
	sort_t sel_algo;
} SAV;

extern char *algo_strings[SORT_MAX_ALGORITHMS];

status_t SAV_New(SAV **sav);
void SAV_Destroy(SAV *sav);

#endif
