#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include <unistd.h>
#include <pthread.h>

#include "sav.h"
#include "drw.h"
#include "util.h"
#include "sort.h"
#include "sdl_extra.h"

void *
routine_wrapper(void *arg) {
	SAV *sav = (SAV *)arg;

	insertion_sort(sav);

	return NULL;
}

int
main (void) {
	SAV *sav = NULL;
	SDL_Renderer *rend;
	SDL_Window *win;
	pthread_t p1;

	setup(&win, &rend);

	if((sav = (SAV *)malloc(sizeof(SAV))) == NULL)
		return ERROR_MEMORY_ALLOC;

	sav->sel = sav->cmp = 0;
	sav->status = RUN;

	if((sav->arr = (Arr *)malloc(sizeof(Arr))) == NULL)
		return ERROR_MEMORY_ALLOC;

	if((sav->arr->v = (int *)malloc(sizeof(int) * ARR_LEN)) == NULL)
		return ERROR_MEMORY_ALLOC;

	sav->arr->len = ARR_LEN;

	if(sav->arr == NULL) {
		return ERROR_MEMORY_ALLOC;
	}

	/* assigns random values to array */
	srand((unsigned int)time(NULL));
	for(size_t i = 0; i < sav->arr->len; i++)
		while(!(sav->arr->v[i] = rand() % ARR_MAX));

	pthread_create(&p1, NULL, &routine_wrapper, (void *)sav);

	/* main loop */
	while(sav->status != STOP) {
		check_events(&(sav->status)); 
		if(sav->status == UPDATE) {
			drw_array_graph(rend, win, sav);
			sav->status = RUN;
		}
	}

	pthread_join(p1, NULL);

	free(sav->arr);
	free(sav);

	cleanup(win, rend);
	return 0;
}
