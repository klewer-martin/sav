#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "sort.h"

void set_sort_speed(SAV *sav, size_t new_value) {
	if(sav == NULL) return;

	if((new_value > 0) && (new_value <= SORT_DELAY_MAX)) {
		printf("INFO: Updating sort_delay to: %ld\n", new_value);
		sav->sort_delay = new_value;
	}
}

status_t sort_delay(const SAV *sav) {
	size_t i;

	for(i = 0; i < sav->sort_delay; i++, SDL_Delay(1))
		if((sav->sort_status == STOP) || (sav->status == STOP))
			return STOP;

	return OK;
}

status_t sort_pause(const SAV *sav) {
	while(sav->sort_status == PAUSE)
		if(sort_delay(sav) == STOP) return STOP;

	return sav->sort_status == STOP ? STOP : OK;
}

void insertion_sort(SAV *sav) {
	int key;
	int i, j;

	if(sav == NULL) return;
	if(sort_pause(sav) == STOP) return;

	sav->ti = time(NULL);

	for(i = 1; (i < sav->arr->len) && (sav->sort_status != STOP); i++) {
		if(sort_delay(sav) == STOP) break;
		if(sort_pause(sav) == STOP) break;

		sav->cmps += 1;
		key = sav->arr->v[i];
		j = i - 1;
		while((j >= 0) && (sav->arr->v[j] > key)) {
			sav->cmps += 1;
			sav->arr->v[j + 1] = sav->arr->v[j];
			j--;

			sav->sel = i;
			sav->cmp = j + 1;
			sav->its++;

			if(sort_delay(sav) == STOP) break;
			if(sort_pause(sav) == STOP) break;
		}
		sav->arr->v[j + 1] = key;
		sav->sel = i;
		sav->cmp = j + 1;
		sav->swps += 1;
	}

	sav->tf = time(NULL);

	if(sav->sort_status != STOP) sav->sort_status = SORTED;
	sav->sel = sav->cmp = ARR_MAX + 1;
}

void bubble_sort(SAV *sav) {
	size_t i, j;

	if(sav == NULL) return;

	sav->ti = time(NULL);
	for(i = 0; (i < sav->arr->len - 1) && (sav->sort_status != STOP); i++) {
		for(j = 0; j < (sav->arr->len - 1 - i); j++, sav->its++) {
			sav->sel = j + 1;
			sav->cmp = j;
			sav->cmps += 1;
			if(sav->arr->v[j] - sav->arr->v[j + 1] > 0) {
				swap(sav->arr->v + j, sav->arr->v+j+1);
				sav->swps += 1;
			}
			if(sort_delay(sav) == STOP) break;
			if(sort_pause(sav) == STOP) break;
		}
		if(sort_delay(sav) == STOP) break;
		if(sort_pause(sav) == STOP) break;
	}

	sav->tf = time(NULL);
	if(sav->status != STOP) sav->sort_status = SORTED;
	sav->sel = sav->cmp = ARR_MAX + 1;
}

void bubble_sort_improved(SAV *sav) {
	size_t i, j;
	bool swap_happen;

	if(sav == NULL) return;

	sav->ti = time(NULL);
	swap_happen = false;
	for(i = 0; (i < sav->arr->len - 1) && (sav->sort_status != STOP); i++) {
		for(j = 0; j < (sav->arr->len - 1 - i); j++, sav->its++) {
			sav->sel = j + 1;
			sav->cmp = j;
			sav->cmps += 1;
			if(sav->arr->v[j] - sav->arr->v[j + 1] > 0) {
				swap(sav->arr->v + j, sav->arr->v+j+1);
				sav->swps += 1;
				swap_happen = true;
			}
			if(sort_delay(sav) == STOP) break;
			if(sort_pause(sav) == STOP) break;
		}
		if(sort_delay(sav) == STOP) break;
		if(sort_pause(sav) == STOP) break;
		if(swap_happen == false) break;
	}

	sav->tf = time(NULL);
	if(sav->status != STOP) sav->sort_status = SORTED;
	sav->sel = sav->cmp = ARR_MAX + 1;
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

	/* C middle high */
	for(i = middle, j = 0; i < high; i++, j++)
		C[j] = sav->arr->v[i];

	/* merge B and C in order */
	for(k = low, i = j = 0; (k < high) && (i < n1) && (j < n2); k++) {
		if(B[i] <= C[j]) {
			sav->arr->v[k] = B[i++];
			sav->cmps += 1;
		}
		else {
			sav->cmps += 1;
			sav->arr->v[k] = C[j++];
		}

		sav->sel = k;
		sav->cmps += 1;
		sav->its += 1;

		/* double delay; to match speed of other algorithms */
		if(sort_delay(sav) == STOP) return;
		if(sort_delay(sav) == STOP) return;
		if(sort_pause(sav) == STOP) return;
	}

	while(i < n1) {
		sav->sel = k;
		sav->arr->v[k++] = B[i++];
		if(sort_delay(sav) == STOP) return;
		if(sort_delay(sav) == STOP) return;
		if(sort_pause(sav) == STOP) return;
	}
    while(j < n2) {
		sav->sel = k;
		sav->arr->v[k++] = C[j++];
		if(sort_delay(sav) == STOP) return;
		if(sort_delay(sav) == STOP) return;
		if(sort_pause(sav) == STOP) return;
	}
}

void merge_sort(SAV *sav, int low, int high) {
	int middle;

	middle = ((high + low) / 2);

	if((high - low) > 1) {
		/* sort the middle low portion of the array */
		merge_sort(sav, low, middle);

		/* sort the middle high portion of the array */
		merge_sort(sav, middle, high);

		/* merge both arrays ordered */
		merge(sav, low, middle, high);

		sav->cmps += 1;
	}
}

void merge_sort_wrapper(SAV *sav) {
	if(sav == NULL) return;

	sav->ti = time(NULL);
	merge_sort(sav, 0, sav->arr->len);
	sav->tf = time(NULL);

	sav->sel = sav->arr->len + 1;
	if(sav->status != STOP) sav->sort_status = SORTED;
	sav->sel = sav->cmp = ARR_MAX + 1;
}

void quick_sort_partition(SAV *sav, int low, int *middle, int high) {
	int i, j, pivot;

	pivot = high;
	sav->sel = pivot;

	for(i = j = low; j < high; j++, sav->cmps += 1) {
		if(sav->arr->v[j] < sav->arr->v[pivot]) {
			swap(&(sav->arr->v[i++]), &(sav->arr->v[j]));
			sav->swps += 1;
		}
		sav->cmp = j;

		if(sort_delay(sav) == STOP) return;
		if(sort_delay(sav) == STOP) return;
		if(sort_pause(sav) == STOP) return;
	}

	swap(&(sav->arr->v[i]), &(sav->arr->v[pivot]));
	sav->swps += 1;
	*middle = i;
}

void quick_sort(SAV *sav, int low, int high) {
	int pivot;

	if(sort_pause(sav) == STOP) return;

	if ((high - low) > 0) {
		quick_sort_partition(sav, low, &pivot, high);
		quick_sort(sav, low, pivot - 1);
		quick_sort(sav, pivot + 1, high);
	}
}

void quick_sort_wrapper(SAV *sav) {
	if(sav == NULL) return;

	sav->ti = time(NULL);
	quick_sort(sav, 0, sav->arr->len - 1);
	if(sav->sort_status != STOP) sav->sort_status = SORTED;
	sav->sel = sav->cmp = ARR_MAX + 1;
	sav->tf = time(NULL);
}

void shell_sort(SAV *sav) {
	int gap, i, j, temp;

	if(sav == NULL) return;

	sav->ti = time(NULL);

    for (gap = ((sav->arr->len) / 2); gap > 0; gap /= 2) {
		sav->cmps += 1;
        for (i = gap; i < sav->arr->len; i += 1) {
			temp = sav->arr->v[i];
			sav->sel = i;
            for (j = i; j >= gap && sav->arr->v[j - gap] > temp; j -= gap) {
                sav->arr->v[j] = sav->arr->v[j - gap];
				sav->cmp = j - gap;
				sav->cmps += 1;

				if(sort_delay(sav) == STOP) return;
				if(sort_pause(sav) == STOP) return;
			}
            sav->arr->v[j] = temp;
			sav->swps += 1;
			if(sort_delay(sav) == STOP) return;
			if(sort_pause(sav) == STOP) return;
        }
		if(sort_delay(sav) == STOP) return;
		if(sort_pause(sav) == STOP) return;
    }
	sav->tf = time(NULL);

	if(sav->sort_status != STOP) sav->sort_status = SORTED;
}

void selection_sort(SAV *sav)
{
	int i, j;
	int min;

	if(sav == NULL) return;

	sav->ti = time(NULL);

	for (i = 0; i < sav->arr->len; i++) {
		min = i;
		for (j = i + 1; j < sav->arr->len; j++) {
			sav->sel = j;
			if (sav->arr->v[j] < sav->arr->v[min]) min = j;
			sav->cmps += 1;
			sav->cmp = j;
			if(sort_delay(sav) == STOP) return;
			if(sort_pause(sav) == STOP) return;
		}
		sav->cmp = min;
		if(sort_delay(sav) == STOP) return;
		if(sort_pause(sav) == STOP) return;
		swap(&sav->arr->v[i], &sav->arr->v[min]);
		sav->swps += 1;
	}

	sav->tf = time(NULL);
	if(sav->sort_status != STOP) sav->sort_status = SORTED;
}


/* build max_heap */
void heapify(SAV *sav, int len, int i) {
	/* Find largest among root, left child and right child */
	int root = i;
	int child_left = 2 * i + 1;
	int child_right = 2 * i + 2;

	sav->cmp = root;
	sav->cmps += 1;
	if((child_left < len) && (sav->arr->v[child_left] > sav->arr->v[root]))
		root = child_left;

	sav->cmp = root;
	sav->cmps += 1;
	if((child_right < len) && (sav->arr->v[child_right] > sav->arr->v[root]))
		root = child_right;

	/* Swap and continue heapifying if root is not root */
	sav->cmp = root;
	sav->cmps += 1;
	if(root != i) {
		sav->swps += 1;
		swap(&(sav->arr->v[i]), &sav->arr->v[root]);
		heapify(sav, len, root);
	}

	if(sort_delay(sav) == STOP) return;
	if(sort_pause(sav) == STOP) return;
}

/* Main function to do heap sort */
void heap_sort(SAV *sav) {
	int i;
	if(sav == NULL) return;

	sav->ti = time(NULL);

	/* Build max heap */
	for (i = ((sav->arr->len / 2) - 1); i >= 0; i--) {
		heapify(sav, sav->arr->len, i);
	}

	/* Heap sort */
	for (i = (sav->arr->len - 1); i >= 0; i--) {
		/* The root element gets swapped with the last one, then gets ignored */
		sav->sel = i;

		sav->swps += 1;
		swap(&sav->arr->v[0], &sav->arr->v[i]);

		if(sort_delay(sav) == STOP) return;
		if(sort_pause(sav) == STOP) return;

		/* Heapify root element to get highest element at root again */
		heapify(sav, i, 0);
	}

	if(sav->sort_status != STOP) sav->sort_status = SORTED;
	sav->sel = sav->cmp = ARR_MAX + 1;
	sav->tf = time(NULL);
}
