#include <stdio.h>
#include <pthread.h>

#include "drw.h"
#include "sort.h"
#include "util.h"
#include "sdl_extra.h"
#include "array.h"

void check_events(Drw *, SAV *);
void *routine_wrapper(void *);

void *
routine_wrapper(void *arg) {
	SAV *sav = (SAV *)arg;

	switch(sav->sort_algo) {
		case BUBBLE_SORT:  bubble_sort(sav); break;
		case INSERTION_SORT: insertion_sort(sav); break;
		case MERGE_SORT: merge_sort_wrapper(sav); break;
		case QUICK_SORT: quick_sort_wrapper(sav); break;
		default:  {
			fprintf(stderr, "\"sort_algo\" not set. exiting\n");
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

	pthread_t p1;
	status_t st;

	if((st = SAV_new(&sav)) != OK) goto end;
	if((st = Drw_new(&drw)) != OK) goto end;

	/* assigns random values to array */
	shuffle(sav->arr);

	/* selecting the sorting algorithms */
	sav->sort_algo = BUBBLE_SORT;

	/* start sorting thread */
	pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);


	sav->status = START;
	sav->sort_status = PAUSE;

	/* main loop */
	while(sav->status != STOP) {
		check_events(drw, sav);

		drw_array_graph(drw, sav);
		drw_status_bar(drw, sav);
		SDL_RenderPresent(drw->rend);

		if((sav->sort_status == SORTED) && (sav->status == RESTART)) {
			/* this state can only be achived if p1 ended */
			shuffle(sav->arr);
			sav->status = RUN;
			sav->sort_status = RUN;

			/* let's call p1 again */
			pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);
		}
	}

	end:
	pthread_join(p1, NULL);

	SAV_destroy(sav);
	Drw_destroy(drw);
	return 0;
}

void
check_events(Drw *drw, SAV *sav) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT:
			sav->status = sav->sort_status = STOP;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode) {
			case SDL_SCANCODE_R:
				if(sav->sort_status == SORTED) sav->status = RESTART;
				break;
			/* case SDL_SCANCODE_S: */
			/* 	shuffle(sav->arr); */
			/* 	break; */
			case SDL_SCANCODE_SPACE:
				printf("status: %d, sort_status: %d\n", sav->status, sav->sort_status);
				/* if(sav->status == START) sav->status = sav->sort_status = RUN; */
				if(sav->sort_status == PAUSE) sav->status = sav->sort_status = RUN;
				else if(sav->sort_status == RUN) sav->sort_status = PAUSE;

				break;
			default: break;
		   }
		case SDL_WINDOWEVENT:
			switch(event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				SDL_Log("Window resized to %dx%d", event.window.data1, event.window.data2);
				drw->w = event.window.data1;
				drw->h = event.window.data2;

				/* set new window borders */
				drw->x_border = (drw->w / 2) - ((sav->arr->len * RECT_WIDTH) / 2);
				drw->y_border = (drw->h / 2) - (ARR_MAX / 2);

				break;
			default: break;
		   }
		default: break;
		}
	}
}

