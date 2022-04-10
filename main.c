#include <stdio.h>
#include <pthread.h>

#include "drw.h"
#include "sort.h"
#include "util.h"
#include "sdl_extra.h"

char *algo_strings[SORT_MAX_ALGORITHMS] = {
	"bubble",
	"insertion",
	"merge"
};

void *
routine_wrapper(void *arg) {
	SAV *sav = (SAV *)arg;

	switch(sav->sel_algo) {
		case BUBBLE_SORT:  bubble_sort(sav); break;
		case INSERTION_SORT: insertion_sort(sav); break;
		case MERGE_SORT: merge_sort_wrapper(sav); break;
		default:  {
			fprintf(stderr, "\"sel_algo\" not set. exiting\n");
			sav->status = STOP;
			break;
		}
	}
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

	/* start sorting thread */
	pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);

	/* selecting the sorting algorithms */
	sav->sel_algo = MERGE_SORT;

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
