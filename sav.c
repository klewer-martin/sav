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

	(*sav)->status = RUN;
	(*sav)->sort_status = PAUSE;
	(*sav)->sort_algo = ALGORITHMS_COUNT;
	(*sav)->sort_delay = SORT_DELAY_DEFAULT;

	if((st = Arr_create(&(*sav)->arr)) != OK)
		return st;

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
