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

	switch(sav->sel_algo) {
		case BUBBLE_SORT:  bubble_sort(sav); break;
		case INSERTION_SORT: insertion_sort(sav); break;
		case MERGE_SORT: merge_sort_wrapper(sav); break;
		case QUICK_SORT: quick_sort_wrapper(sav); break;
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

	pthread_t p1;
	status_t st;

	if((st = SAV_new(&sav)) != OK) goto end;
	if((st = Drw_new(&drw)) != OK) goto end;

	/* assigns random values to array */
	shuffle(sav->arr);

	/* start sorting thread */
	pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);

	/* selecting the sorting algorithms */
	sav->sel_algo = QUICK_SORT;

	/* main loop */
	sav->status = RUN;
	while(sav->status != STOP) {
		/* check_events(drw, sav); */
		if(sav->status == UPDATE) {
			/* drw_array_graph(drw, sav); */
			sav->status = RUN;
			SDL_RenderPresent(drw->rend);
		}
		if(sav->status == SORTED) {
			/* p1 ended */
			/* drw_array_graph(drw, sav); */
			SDL_RenderPresent(drw->rend);
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

	SAV_destroy(sav);
	Drw_destroy(drw);
	return 0;
}

void
check_events(Drw *drw, SAV *sav) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT: sav->status = STOP; break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode) {
			/* case SDL_SCANCODE_EQUALS: */ 
			/* 	if(speed > SPEED_MAX) speed -= SPEED_STEP; */
			/* 	break; */
			/* case SDL_SCANCODE_MINUS: */
			/* 	if(speed < SPEED_MIN) speed += SPEED_STEP; */
			/* 	break; */
			/* case SDL_SCANCODE_P: */
			/* 	if(status == PAUSE) *status = RUN; */
			/* 	else *status = PAUSE; */
			/* 	break; */
			case SDL_SCANCODE_R:
				if(sav->status == SORTED) sav->status = RESTART;
				else break;
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

