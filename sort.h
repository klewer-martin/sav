#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include <stdbool.h>

#include "sav.h"

void bubble_sort(SAV *);
void insertion_sort(SAV *);

void merge(SAV *, int, int, int);
void merge_sort(SAV *, int, int);
void merge_sort_wrapper(SAV *);

void quick_sort_wrapper(SAV *sav);
void quick_sort(SAV *sav, int low, int high);
void quick_sort_partition(SAV *sav, int low, int *middle, int high);

static void (*sort_handler[ALGORITHMS_COUNT])(SAV *) = {
	&bubble_sort,
	&insertion_sort,
	&merge_sort_wrapper,
	&quick_sort_wrapper
};

/* static const char *algo_strings[ALGORITHMS_COUNT]; */
static const char *algo_strings[ALGORITHMS_COUNT] = {
	"bubble",
	"insertion",
	"merge",
	"quick"
};

#endif // __SORT_H__
