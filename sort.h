#ifndef __SORT_H__
#define __SORT_H__

#include <stdio.h>
#include <stdbool.h>

#include "sav.h"
#include "util.h"

void bubble_sort(SAV *);
void insertion_sort(SAV *);

void merge(SAV *, int, int, int);
void merge_sort(SAV *, int, int);
void merge_sort_wrapper(SAV *);

#endif // __SORT_H__
