#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include <stdbool.h>

#include "sav.h"

#define SORT_DELAY_DEFAULT  5
#define SORT_DELAY_MAX      250

void set_sort_speed(SAV *sav, size_t new_value);

void bubble_sort(SAV *);
void bubble_sort_improved(SAV *);
void insertion_sort(SAV *);

void merge(SAV *, int, int, int);
void merge_sort(SAV *, int, int);
void merge_sort_wrapper(SAV *);

void quick_sort_wrapper(SAV *sav);
void quick_sort(SAV *sav, int low, int high);
void quick_sort_partition(SAV *sav, int low, int *middle, int high);

void shell_sort(SAV *sav);

#endif // __SORT_H__
