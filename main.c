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

/* pthread_create compliant start routine */
void *routine_wrapper(void *);

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

void *routine_wrapper(void *arg)
{
	SAV *sav = (SAV *)arg;

	assert((sav->sort_algo != ALGORITHMS_COUNT) && "Default sorting algorithm not set");

	sort_handler[sav->sort_algo](sav);

	return NULL;
}

/* TODO: Random, reversed, in_order arrays selector from GUI */
/* TODO: Support command line arguments */
/* TODO: Support sound */
/* TODO: More sorting algorithms */

int main (void)
{
	SAV *sav = NULL;
	Drw *drw = NULL;
	time_t tic, toc;

	pthread_t p1 = 0;
	status_t st;

	if((st = SAV_create(&sav)) != OK) goto end;
	if((st = Drw_create(&drw)) != OK) goto end;

	/* defaults */
	sav->sort_algo = INSERTION_SORT;
	sav->arr->shuffle_sel = RANDOM;
	sav->status = WELCOME;
	sav->sort_status = PAUSE;
	tic = time(NULL);

	arr_shuffle(sav->arr);

	/* main loop */
	while(sav->status != STOP) {
		check_events(drw, sav);

		SDL_SetRenderDrawColor(drw->rend, 29, 28, 28, 0);
		SDL_RenderClear(drw->rend);

		drw_array_graph(drw, sav);
		drw_status_bar(drw, sav);

		SDL_RenderPresent(drw->rend);

		if((sav->status == START) || (sav->status == WELCOME)) {
			/* Print welcome message during the first WELCOME_MSG_TIME seconds */
			if(((toc = time(NULL)) - tic) > WELCOME_MSG_TIME)
				sav->status = START;

			if(sav->sort_status == RUN) {
				sav->status = RUN;

				/* start sorting thread */
				pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);
			}
		}

		if(sav->status == RESTART) {
			/* if sorting thread is running stop it */
			sav->sort_status = STOP;
			pthread_join(p1, NULL);

			sort_reset_stats(sav);
			arr_shuffle(sav->arr);

			sav->status = START;
			sav->sort_status = PAUSE;
		}

		if(sav->sort_status == SORTED) {
			pthread_join(p1, NULL);
			sav->sel = sav->cmp = ARR_LEN + 1;
		}
	}

end:
	/* check if p1 has been initialized */
	if(p1 != 0) pthread_join(p1, NULL);

	SAV_destroy(sav);
	Drw_destroy(drw);
	return 0;
}

void check_events(Drw *drw, SAV *sav)
{
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
				if(sav->sort_status == PAUSE)
					sav->sort_status = RUN;
				else if(sav->sort_status == RUN)
					sav->sort_status = PAUSE;
				else if(sav->sort_status == SORTED) {
					sort_reset_stats(sav);
					arr_restore_from_bk(sav->arr);
					sav->status = START;
					sav->sort_status = RUN;
				}
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
			case SDL_SCANCODE_S:
				arr_shuffle_next(sav->arr);
				if(sav->sort_status == PAUSE) {
					if(sav->status == RUN) sav->status = RESTART;
					else arr_shuffle(sav->arr);
				}
				break;
			default: break;
			}
			break;
		case SDL_WINDOWEVENT:
			switch(event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				/* SDL_Log("Window resized to %dx%d", event.window.data1, event.window.data2); */
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
