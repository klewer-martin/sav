#include "sav.h"

status_t SAV_new(SAV **sav) {
	if((*sav = (SAV *)malloc(sizeof(SAV))) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*sav)->sel = (*sav)->cmp = ARR_MAX + 1;
	(*sav)->cmps = (*sav)->swps = (*sav)->its = (*sav)->B_used = 0;
	(*sav)->status = RUN;
	(*sav)->sort_status = PAUSE;
	(*sav)->sort_algo = ALGORITHMS_COUNT;

	if(((*sav)->arr = (Arr *)malloc(sizeof(Arr))) == NULL)
		return ERROR_MEMORY_ALLOC;

	if(((*sav)->arr->v = (int *)malloc(sizeof(int) * ARR_LEN)) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*sav)->arr->len = ARR_LEN;

	if((*sav)->arr == NULL) {
		return ERROR_MEMORY_ALLOC;
	}
	return 0;
}

void SAV_destroy(SAV *sav) {
	if(sav == NULL) return;

	free(sav->arr->v);
	free(sav->arr);
	free(sav);
}
