#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#include "sort.h"

#define DELAY	5

void insertion_sort(SAV *sav) {
	int key;
	size_t i, j;

	if((sav->sort_status == STOP) || (sav->status == STOP)) return;
	while(sav->sort_status == PAUSE);

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

			/* Delay */
			for(size_t i = 0; i < DELAY; i++) {
				if((sav->sort_status == STOP) || (sav->status == STOP))
					goto end;

				SDL_Delay(1);
			}
			while(sav->sort_status == PAUSE);
		}
		sav->arr->v[j + 1] = key;
		sav->sel = i;
		sav->cmp = j;
		sav->swps += 1;

		/* Delay */
		for(size_t i = 0; i < DELAY; i++) {
			if((sav->sort_status == STOP) || (sav->status == STOP))
				goto end;

			SDL_Delay(1);
		}
		while(sav->sort_status == PAUSE);
	}
	end:

	sav->tf = clock();

	if(sav->status != STOP) sav->sort_status = SORTED;
}

void bubble_sort(SAV *sav) {
	size_t i, j;

	if((sav->sort_status == STOP) || (sav->status == STOP)) return;
	while(sav->sort_status == PAUSE);

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

			/* Delay */
			for(size_t i = 0; i < DELAY; i++) {
				if((sav->sort_status == STOP) || (sav->status == STOP))
					goto end;

				SDL_Delay(1);
			}
			while(sav->sort_status == PAUSE);
		}

		/* Delay */
		for(size_t i = 0; i < DELAY; i++) {
			if((sav->sort_status == STOP) || (sav->status == STOP))
				goto end;

			SDL_Delay(1);
		}
		while(sav->sort_status == PAUSE);
	}
	end:

	sav->tf = clock();
	if(sav->status != STOP) sav->sort_status = SORTED;
}

void merge(SAV *sav, int low, int middle, int high) {
	size_t n1, n2, i, j, k;

	if((sav->sort_status == STOP) || (sav->status == STOP)) return;
	while(sav->sort_status == PAUSE);

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

		while(sav->sort_status == PAUSE);

		/* Delay */
		for(size_t i = 0; i < DELAY; i++) {
			if((sav->sort_status == STOP) || (sav->status == STOP))
				goto end;

			SDL_Delay(1);
		}
	}
	end:

	while(i < n1) sav->arr->v[k++] = B[i++];
    while(j < n2) sav->arr->v[k++] = C[j++];
}

void merge_sort(SAV *sav, int low, int high) {
	if(sav == NULL) return;

	if((sav->sort_status == STOP) || (sav->status == STOP))
		return;

	while(sav->sort_status == PAUSE);

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
	if(sav->status != STOP) sav->sort_status = SORTED;
}

void quick_sort_partition(SAV *sav, int low, int *middle, int high) {
	int i, j, pivot;

	pivot = high;
	sav->sel = pivot;
	/* printf("SORT: pivot: %d\n", pivot); */

	for(i = j = low; j < high; j++, sav->cmps += 1) {
		if(sav->arr->v[j] < sav->arr->v[pivot]) {
			swap(&(sav->arr->v[i++]), &(sav->arr->v[j]));
			sav->swps += 1;
		}

		if(sav->status != STOP) sav->status = UPDATE;
		while(sav->sort_status == PAUSE);

		for(size_t i = 0; i < 5; i++) {
			if(sav->sort_status == STOP) goto end;
			SDL_Delay(1);
		}
	}
	end:

	swap(&(sav->arr->v[i]), &(sav->arr->v[pivot]));
	sav->swps += 1;
	*middle = i;
}

void quick_sort(SAV *sav, int low, int high) {
	int pivot;

	if(sav->status == STOP) return;
	while(sav->sort_status == PAUSE);

	if ((high - low) > 0) {
		quick_sort_partition(sav, low, &pivot, high);
		quick_sort(sav, low, pivot - 1);
		quick_sort(sav, pivot + 1, high);
	}
}

void quick_sort_wrapper(SAV *sav) {
	sav->ti = clock();
	quick_sort(sav, 0, sav->arr->len - 1);
	printf("SORT: sorting array done\n");
	if(sav->sort_status != STOP) sav->sort_status = SORTED;
	sav->tf = clock();
}
