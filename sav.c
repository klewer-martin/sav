#include "sav.h"
#include "sort.h"

void sort_reset_stats(SAV *sav) {
	if(sav == NULL) return;

	sav->sel = sav->cmp = ARR_MAX + 1;
	sav->cmps = sav->swps = sav->B_used = 0;
}

status_t SAV_create(SAV **sav) {
	status_t st;

	if((*sav = (SAV *)malloc(sizeof(SAV))) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*sav)->sel = (*sav)->cmp = ARR_MAX + 1;
	(*sav)->cmps = (*sav)->swps = (*sav)->its = (*sav)->B_used = 0;

	/* defaults */
	(*sav)->status = WELCOME;
	(*sav)->sort_status = PAUSE;
	(*sav)->sort_algo = INSERTION_SORT;
	(*sav)->sort_delay = SAV_DEFAULT_SORT_DELAY;

	if((st = Arr_create(&(*sav)->arr)) != OK)
		return st;

	(*sav)->arr->shuffle_sel = RANDOM;

	return OK;
}

void SAV_destroy(SAV *sav) {
	if(sav == NULL) return;

	Arr_destroy(sav->arr);
	free(sav);
}

void sort_selector(SAV *sav) {
	if(sav->sort_algo == (ALGORITHMS_COUNT - 1))
		sav->sort_algo = 0;
	else sav->sort_algo++;
}
