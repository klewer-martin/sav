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

void merge(SAV *sav, int low, int middle, int high) {
	size_t n1, n2, i, j, k;

	n1 = middle - low;
	n2 = high - middle;

	int B[n1], C[n2];

	sav->B_used += n1;
	sav->B_used += n2;

	/* B holds middle low array */
	for(i = low, j = 0; i < middle; i++, j++) 
		B[j] = sav->arr->v[i];

	/* C middle high part of the array */ 
	for(i = middle, j = 0; i < high; i++, j++)
		C[j] = sav->arr->v[i];

	/* merge B1 and C1 in order */
	for(k = low, i = j = 0; (k < high) && (i < n1) && (j < n2); k++) {
		if(B[i] <= C[j]) sav->arr->v[k] = B[i++];
		else sav->arr->v[k] = C[j++];

		sav->sel = (k + 1);
		sav->cmps += 1;
		sav->its += 1;

		wait_main_thread(&(sav->status));
		if(sav->status == STOP) return;
	}

	while(i < n1)
        sav->arr->v[k++] = B[i++];

    while (j < n2)
        sav->arr->v[k++] = C[j++];
}

void merge_sort(SAV *sav, int low, int high) {
	if(sav == NULL) return;

	int middle;

	middle = ((high + low) / 2);
	sav->its += 1;

	if((high - low) > 1) {
		/* sort the middle low portion of the array */
		merge_sort(sav, low, middle);

		/* sort the middle high portion of the array */
		merge_sort(sav, middle, high);

		/* merge both arrays ordered */
		merge(sav, low, middle, high);
	}
}

void merge_sort_wrapper(SAV *sav) {
	sav->ti = clock();
	merge_sort(sav, 0, sav->arr->len);
	sav->tf = clock();
	sav->sel = sav->arr->len + 1;
	if(sav->status != STOP) sav->status = SORTED;
}
