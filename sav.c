#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include <unistd.h>
#include <pthread.h>

#include "drw.h"
#include "util.h"
/* #include "sort.h" */
#include "sdl_extra.h"

#define SEL_COLOR	0x00FF0000 // RGBA
#define CMP_COLOR	0x00FFFF00

typedef struct {
	int *v;
	size_t len;
} Arr;

/* Maybe in a future */
/* typedef struct {
	int sel, cmp;
	status_t st;
	Arr *arr;
	SDL_Renderer *rend;
	SDL_Window *win;
} Graph;
*/

/* variables */
SDL_Renderer *rend;
SDL_Window *win;
Arr *arr = NULL;

size_t sel, cmp;
status_t st;

/* functions declarations */
void update_array_graph(SDL_Renderer *rend, SDL_Window *win, Arr *arr);
void wait_main_thread(void);
void *routine_wrapper(void *arg);
void insertion_sort(Arr *arr);


/* functions definitions */
void
update_array_graph(SDL_Renderer *rend, SDL_Window *win, Arr *arr) {
	int x, w, h;

	SDL_GetWindowSize(win, &w, &h);

	SDL_SetRenderDrawColor(rend, 29, 28, 28, 0);
	SDL_RenderClear(rend);

	size_t i;
	for(i = x = 0; i < arr->len; i++, x += RECT_WIDTH) {
		if(i == sel) drw_element_color(rend, x, h, arr->v[i], SEL_COLOR);
		else if(i == cmp) drw_element_color(rend, x, h, arr->v[i], CMP_COLOR);
		else drw_element(rend, x, h, arr->v[i]);
	}

	SDL_RenderPresent(rend);
}

void
wait_main_thread(void) {
	if(st != STOP) st = UPDATE;

	/* wait 'til main thread changes st value to RUN */
	while(st == UPDATE);
}

void
insertion_sort(Arr *arr) {
	int key;
	size_t i, j;

	for(i = 1; i < arr->len; i++) {
		key = arr->v[i];
		j = i - 1;
		while((j >= 0) && (arr->v[j] > key)) {
			arr->v[j + 1] = arr->v[j];
			j = j - 1;
			sel = i;
			cmp = j;

			/* wait 'til main thread updates graphics */
			wait_main_thread();
			if(st == STOP) break;
		}
		arr->v[j + 1] = key;
		sel = i;
		cmp = j;
		/* wait 'til main thread updates graphics */
		wait_main_thread();
		if(st == STOP) break;
	}
}

void *
routine_wrapper(void *arg) {
	Arr *arr = (Arr *)arg;

	insertion_sort(arr);

	return NULL;
}

int
main (void) {
	size_t i;
	pthread_t p1;

	sel = cmp = 0;

	setup(&win, &rend);

	arr = (Arr *)malloc(sizeof(Arr));
	arr->v = (int *)malloc(sizeof(int) * ARR_LEN);
	arr->len = ARR_LEN;

	/* create a random array */
	srand((unsigned int)time(NULL));
	for(i = 0; i < arr->len; i++)
		while(!(arr->v[i] = rand() % ARR_MAX))

	st = RUN;

	pthread_create(&p1, NULL, &routine_wrapper, (void *)arr);

	/* main loop */
	while(st != STOP) {
		check_events(&st); 
		if(st == UPDATE) {
			update_array_graph(rend, win, arr);
			st = RUN;
		}
	}

	pthread_join(p1, NULL);
	cleanup(win, rend);
	return 0;
}
