#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "sort.h"

void
insertion_sort(SAV *sav) {
	int key;
	size_t i, j;

	sav->ti = clock();
	for(i = 1; i < sav->arr->len; i++, sav->its++) {
		sav->cmps += 1;
		key = sav->arr->v[i];
		j = i - 1;
		while((j >= 0) && (sav->arr->v[j] > key)) {
			sav->cmps += 1;
			sav->arr->v[j + 1] = sav->arr->v[j];
			j--;

			sav->sel = i;
			sav->cmp = j;
			sav->its++;

			/* wait 'til main thread updates graphics */
			wait_main_thread(&(sav->status));
			if(sav->status == STOP) break;
		}
		sav->arr->v[j + 1] = key;
		sav->sel = i;
		sav->cmp = j;
		sav->swps += 1;

		/* wait 'til main thread updates graphics */
		wait_main_thread(&(sav->status));
		if(sav->status == STOP) break;
	}

	sav->tf = clock();

	if(sav->status != STOP) sav->status = SORTED;
}

void bubble_sort(SAV *sav) {
	size_t i, j;

	sav->ti = clock();
	for(i = 0; i < sav->arr->len - 1; i++, sav->its++) {
		for(j = 0; j < (sav->arr->len - 1 - i); j++, sav->its++) {
			sav->sel = j + 1;
			sav->cmp = j;
			sav->cmps += 1;
			if(sav->arr->v[j] - sav->arr->v[j + 1] > 0) {
				swap(sav->arr->v + j, sav->arr->v+j+1);
				sav->swps += 1;
			}

			/* wait 'til main thread updates graphics */
			wait_main_thread(&(sav->status));
			if(sav->status == STOP) break;
		}
		wait_main_thread(&(sav->status));
		if(sav->status == STOP) break;
	}
	sav->tf = clock();
	if(sav->status != STOP) sav->status = SORTED;
}
