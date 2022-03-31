#include <stdio.h>
#include <stdbool.h>

#include "sort.h"

void
insertion_sort(SAV *sav) {
	int key;
	size_t i, j;

	for(i = 1; i < sav->arr->len; i++) {
		key = sav->arr->v[i];
		j = i - 1;
		while((j >= 0) && (sav->arr->v[j] > key)) {
			sav->arr->v[j + 1] = sav->arr->v[j];
			j--;

			sav->sel = i;
			sav->cmp = j;

			/* wait 'til main thread updates graphics */
			wait_main_thread(&(sav->status));
			if(sav->status == STOP) break;
		}
		sav->arr->v[j + 1] = key;
		sav->sel = i;
		sav->cmp = j;
		/* wait 'til main thread updates graphics */
		wait_main_thread(&(sav->status));
		if(sav->status == STOP) break;
	}
	if(sav->status != STOP) sav->status = SORTED;
}
