#include "sav.h"
#include "sort.h"

void sort_reset_stats(SAV *sav) {
	if(sav == NULL) return;

	sav->sel = sav->cmp = ARR_MAX + 1;
	sav->cmps = sav->swps = sav->B_used = 0;
}

status_t SAV_create(SAV **sav) {
	if((*sav = (SAV *)malloc(sizeof(SAV))) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*sav)->sel = (*sav)->cmp = ARR_MAX + 1;
	(*sav)->cmps = (*sav)->swps = (*sav)->its = (*sav)->B_used = 0;

	(*sav)->status = RUN;
	(*sav)->sort_status = PAUSE;
	(*sav)->sort_algo = ALGORITHMS_COUNT;
	(*sav)->sort_delay = SORT_DELAY_DEFAULT;

	if(((*sav)->arr = (Arr *)malloc(sizeof(Arr))) == NULL)
		return ERROR_MEMORY_ALLOC;

	if(((*sav)->arr->v = (int *)malloc(sizeof(int) * ARR_LEN)) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*sav)->arr->len = ARR_LEN;
	(*sav)->arr->shuffle = NULL;

	if((*sav)->arr == NULL) {
		return ERROR_MEMORY_ALLOC;
	}

	return OK;
}

void SAV_destroy(SAV *sav) {
	if(sav == NULL) return;

	free(sav->arr->v);
	free(sav->arr);
	free(sav);
}

void sort_selector(SAV *sav) {
	if(sav->sort_algo == (ALGORITHMS_COUNT - 1))
		sav->sort_algo = 0;
	else sav->sort_algo++;
}
