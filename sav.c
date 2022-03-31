#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "sav.h"
#include "drw.h"
#include "util.h"
#include "sort.h"
#include "sdl_extra.h"

status_t SAV_New(SAV **sav) {
	if((*sav = (SAV *)malloc(sizeof(SAV))) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*sav)->sel = (*sav)->cmp = 0;
	(*sav)->status = RUN;

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

void *
routine_wrapper(void *arg) {
	SAV *sav = (SAV *)arg;

	insertion_sort(sav);

	return NULL;
}

int
main (void) {
	SAV *sav;
	Drw *drw;
	SDL_Renderer *rend;
	SDL_Window *win;

	pthread_t p1;

	setup(&win, &rend);

	SAV_New(&sav);
	DRW_New(rend, win, &drw);

	/* assigns random values to array */
	srand((unsigned int)time(NULL));
	for(size_t i = 0; i < sav->arr->len; i++)
		while(!(sav->arr->v[i] = rand() % ARR_MAX));

	pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);

	/* main loop */
	while(sav->status != STOP) {
		check_events(&(sav->status)); 
		if(sav->status == UPDATE) {
			drw_array_graph(drw, sav);
			sav->status = RUN;
			SDL_RenderPresent(rend);
		}
		if(sav->status == SORTED) {
			drw_array_graph(drw, sav);
			SDL_RenderPresent(rend);
		}
	}

	pthread_join(p1, NULL);

	SAV_Destroy(sav);
	DRW_Destroy(drw);

	cleanup(win, rend);
	return 0;
}
