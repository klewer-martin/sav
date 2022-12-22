#ifndef __SORT_H__
#define __SORT_H__

#include "sav.h"
#include "assert.h"

void set_sort_speed(SAV *sav, size_t new_value);
void *start_sorting(void *arg);

void bubble_sort(SAV *);
void bubble_sort_improved(SAV *);

void merge(SAV *, int, int, int);
void merge_sort(SAV *, int, int);
void merge_sort_wrapper(SAV *);

void quick_sort_wrapper(SAV *sav);
void quick_sort(SAV *sav, int low, int high);
void quick_sort_partition(SAV *sav, int low, int *middle, int high);

void insertion_sort(SAV *);
void shell_sort(SAV *sav);
void selection_sort(SAV *sav);

void heap_sort(SAV *sav);
/* void heapify(SAV *sav, int len, int i); */

#endif // __SORT_H__
