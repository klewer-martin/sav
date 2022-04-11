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

void
shuffle(Arr *arr) {
	srand((unsigned int)time(NULL));
	for(size_t i = 0; i < arr->len; i++)
		while(!(arr->v[i] = rand() % ARR_MAX));
}

int
main (void) {
	SAV *sav;
	Drw *drw;
	SDL_Renderer *rend;
	SDL_Window *win;

	pthread_t p1;
	status_t st;

	setup(&win, &rend);

	if((st = SAV_New(&sav)) != OK) goto end;
	if((st = DRW_New(rend, win, &drw)) != OK) goto end;

	/* assigns random values to array */
	shuffle(sav->arr);

	/* start sorting thread */
	pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);

	/* selecting the sorting algorithms */
	sav->sel_algo = MERGE_SORT;

	/* main loop */
	while(sav->status != STOP) {
		check_events(drw, sav);
		if(sav->status == UPDATE) {
			drw_array_graph(drw, sav);
			sav->status = RUN;
			SDL_RenderPresent(rend);
		}
		if(sav->status == SORTED) {
			/* p1 ended */
			drw_array_graph(drw, sav);
			SDL_RenderPresent(rend);
		}
		if(sav->status == RESTART) {
			/* this state can only be achived if p1 ended */
			shuffle(sav->arr);
			sav->status = RUN;

			/* let's call p1 again */
			pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);
		}
	}

end:
	pthread_join(p1, NULL);

	SAV_Destroy(sav);
	DRW_Destroy(drw);

	cleanup(win, rend);
	return 0;
}
