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

#define ARR_LEN		120
#define ARR_MAX		500

#define RECT_WIDTH	5

int arr[ARR_LEN];
SDL_Renderer *rend;
SDL_Window *win;
size_t sel, cmp;
status_t st;

void update_array_graph(SDL_Renderer *rend, SDL_Window *win);
void insertion_sort(int *arr, size_t len);

void update_array_graph(SDL_Renderer *rend, SDL_Window *win) {
	int x, w, h;

	SDL_GetWindowSize(win, &w, &h);

	SDL_SetRenderDrawColor(rend, 29, 28, 28, 0);
	SDL_RenderClear(rend);

	size_t i;
	for(i = x = 0; i < ARR_LEN; i++, x += RECT_WIDTH) {
		if(i == sel) drw_element_color(rend, x, h, arr[i], SEL_COLOR);
		else if(i == cmp) drw_element_color(rend, x, h, arr[i], CMP_COLOR);
		else drw_element(rend, x, h, arr[i]);
	}

	SDL_RenderPresent(rend);
}

void insertion_sort(int *arr, size_t len) {
	int key;
	size_t i, j;

	for(i = 1, st = RUN; i < len; i++) {
		key = arr[i];
		j = i - 1;
		while((j >= 0) && (arr[j] > key)) {
			arr[j + 1] = arr[j];
			j = j - 1;
			sel = i;
			cmp = j;
			update_array_graph(rend, win);
			check_events(&st);
			if(st == STOP) break;
		}
		arr[j + 1] = key;
		sel = i;
		cmp = j;
		update_array_graph(rend, win);
		check_events(&st);
		if(st == STOP) break;
	}
}

int main (void) {
	size_t i, len;

	len = ARR_LEN;
	sel = cmp = 0;

	setup(&win, &rend);

	/* create a random array */
	srand((unsigned int)time(NULL));
	for(i = 0; i < len; i++)
		while(!(arr[i] = rand() % ARR_MAX))
			arr[i] = (rand() % ARR_MAX);

	/* main loop */
	st = RUN;
	while(st != STOP) {
		check_events(&st);
		update_array_graph(rend, win);
		insertion_sort(arr, len);
	}
	
	cleanup(win, rend);
	return 0;
}
