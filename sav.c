#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "drw.h"
#include "util.h"

status_t SAV_New(SAV **sav) {
	if((*sav = (SAV *)malloc(sizeof(SAV))) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*sav)->sel = (*sav)->cmps = (*sav)->swps = (*sav)->its = 0;
	(*sav)->cmp = ARR_MAX + 1;
	(*sav)->status = RUN;
	(*sav)->sel_algo = SORT_MAX_ALGORITHMS;

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

void SAV_Destroy(SAV *sav) {
	free(sav->arr->v);
	free(sav->arr);
	free(sav);
}
