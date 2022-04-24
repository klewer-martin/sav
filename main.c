#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#include "sav.h"
#include "drw.h"
#include "sort.h"
#include "util.h"
#include "sdl_extra.h"
#include "array.h"

#define WELCOME_MSG_TIME 3

void check_events(Drw *, SAV *);

/* void *(*start_routine)(void *), pthread_create routine */
void *routine_wrapper(void *);
void sort_selector(SAV *sav);

static void (*sort_handler[ALGORITHMS_COUNT])(SAV *) = {
	&bubble_sort,
	&bubble_sort_improved,
	&insertion_sort,
	&merge_sort_wrapper,
	&quick_sort_wrapper,
	&shell_sort,
	&selection_sort,
	&heap_sort
};

void *routine_wrapper(void *arg) {
	SAV *sav = (SAV *)arg;

	assert((sav->sort_algo != ALGORITHMS_COUNT) && "Default sorting algorithm not set");

	sort_handler[sav->sort_algo](sav);

	return NULL;
}

void sort_selector(SAV *sav) {
	if(sav->sort_algo == (ALGORITHMS_COUNT - 1))
		sav->sort_algo = 0;
	else sav->sort_algo++;
}

/* TODO: Support random, reversed, in_order arrays */
/* TODO: Support command line arguments */
/* TODO: Support sound */

int main (void) {
	SAV *sav = NULL;
	Drw *drw = NULL;
	time_t tic, toc;

	pthread_t p1 = 0;
	status_t st;

	if((st = SAV_new(&sav)) != OK) goto end;
	if((st = Drw_new(&drw)) != OK) goto end;

	/* assigns random values to array */
	shuffle(sav->arr);

	/* selecting the sorting algorithm */
	sav->sort_algo = SELECTION_SORT;

	sav->status = WELCOME;
	sav->sort_status = PAUSE;
	tic = time(NULL);

	/* main loop */
	while(sav->status != STOP) {
		check_events(drw, sav);

		SDL_SetRenderDrawColor(drw->rend, 29, 28, 28, 0);
		SDL_RenderClear(drw->rend);

		drw_array_graph(drw, sav);
		drw_status_bar(drw, sav);

		SDL_RenderPresent(drw->rend);

		/* Print welcome message only on startup */
		if(sav->status == WELCOME)
			if(((toc = time(NULL)) - tic) > WELCOME_MSG_TIME)
				sav->status = START;

		if((sav->status == START) || (sav->status == WELCOME)) {
			if(sav->sort_status == RUN) {
				sav->status = RUN;

				/* start sorting thread */
				pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);
			}
		}

		if(sav->status == RESTART) {
			/* if sorting thread is runnning stop it */
			sav->sort_status = STOP;
			pthread_join(p1, NULL);

			reset_sort_stats(sav);
			shuffle(sav->arr);

			sav->status = START;
			sav->sort_status = PAUSE;
		}

		if(sav->sort_status == SORTED)
			sav->sel = sav->cmp = ARR_LEN + 1;
	}

	end:

	/* check if p1 has been initialized */
	if(p1 != 0) pthread_join(p1, NULL);

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
				if(sav->status == RUN) sav->status = RESTART;
				break;
			case SDL_SCANCODE_SPACE:
				if(sav->sort_status == PAUSE) sav->sort_status = RUN;
				else if(sav->sort_status == RUN) sav->sort_status = PAUSE;
				break;
			case SDL_SCANCODE_Q:
				sav->status = sav->sort_status = STOP;
				break;
			case SDL_SCANCODE_EQUALS:
				set_sort_speed(sav, sav->sort_delay - 1);
				break;
			case SDL_SCANCODE_MINUS:
				set_sort_speed(sav, sav->sort_delay + 1);
				break;
			case SDL_SCANCODE_TAB:
				sort_selector(sav);
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
