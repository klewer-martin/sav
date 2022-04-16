#include <stdio.h>
#include <pthread.h>

#include "drw.h"
#include "sort.h"
#include "util.h"
#include "sdl_extra.h"
#include "array.h"

#define WELCOME_MSG_TIME 5

/* TODO: sorting algorithms should only keep track of sav->sort_status and not sav->status */
/* TODO: support restart even if the sorting algorithm didn't finish */

void check_events(Drw *, SAV *);
void *routine_wrapper(void *);

void *routine_wrapper(void *arg) {
	SAV *sav = (SAV *)arg;

	if(sav->sort_algo == ALGORITHMS_COUNT) {
		fprintf(stderr, "ERROR: \"sort_algo\" not set. exiting\n");
		sav->status = STOP;
	} else sort_handler[sav->sort_algo](sav);

	return NULL;
}

int main (void) {
	SAV *sav;
	Drw *drw;
	clock_t ti, tc;

	pthread_t p1;
	status_t st;

	if((st = SAV_new(&sav)) != OK) goto end;
	if((st = Drw_new(&drw)) != OK) goto end;

	/* assigns random values to array */
	shuffle(sav->arr);

	/* selecting the sorting algorithm */
	sav->sort_algo = QUICK_SORT;

	/* TODO: this thread should be called if the user wants to begin sorting the array */
	/* start sorting thread */
	pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);

	sav->status = WELCOME;
	sav->sort_status = PAUSE;
	ti = clock();

	/* main loop */
	while(sav->status != STOP) {
		check_events(drw, sav);

		SDL_SetRenderDrawColor(drw->rend, 29, 28, 28, 0);
		SDL_RenderClear(drw->rend);

		drw_array_graph(drw, sav);
		drw_status_bar(drw, sav);
		SDL_RenderPresent(drw->rend);

		if(sav->status == WELCOME)
			if((((tc = clock()) - ti) / CLOCKS_PER_SEC) > WELCOME_MSG_TIME)
				sav->status = START;

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

void check_events(Drw *drw, SAV *sav) {
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
			case SDL_SCANCODE_SPACE:
				if(sav->sort_status == PAUSE) sav->status = sav->sort_status = RUN;
				else if(sav->sort_status == RUN) sav->sort_status = PAUSE;
				break;
			default: break;
			}
			break;
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
			break;
		default: break;
		}
	}
}
