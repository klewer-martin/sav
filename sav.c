#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include "drw.h"
#include "util.h"
#include "sort.h"

#define WINDOW_TITLE "Sorting Algorithms Visualized"
#define WINDOW_WIDTH 	0
#define WINDOW_HEIGHT 	0

#define X_BORDER	50
#define Y_BORDER	50
#define RECT_WIDTH	5

typedef struct {
	SDL_Window *window;
	SDL_Renderer *rend;
	int w, h;
	size_t x_border, y_border;
} Root;

Root root;

SDL_Window *window;
SDL_Renderer *renderer;
int w, h;
size_t x = 0;	

void setup(void) {
	SDL_Init(SDL_INIT_VIDEO);

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
		WINDOW_TITLE,					// window title
		SDL_WINDOWPOS_UNDEFINED,		// initial x position
		SDL_WINDOWPOS_UNDEFINED,		// initial y position
		WINDOW_WIDTH,					// width, in pixels
		WINDOW_HEIGHT,					// height, in pixels
		SDL_WINDOW_OPENGL | 
		SDL_WINDOW_RESIZABLE			// window flags
    );

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!window) end("SDL: window cannot be created");

	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}

void cleanup(void) {
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

void drw_element(size_t height) {
	SDL_Rect r;

	r.x = X_BORDER + x; // bottom left + x
	r.y = h - Y_BORDER + 1; // bottom
	r.w = RECT_WIDTH; // fixed width
	r.h = -height;

	SDL_RenderDrawRect(renderer, &r);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderFillRect(renderer, &r);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawLine(renderer,
			x + X_BORDER,
			h - Y_BORDER,
			x + X_BORDER,
			h - Y_BORDER - height);

	x += RECT_WIDTH;
}

int main (void) {
	setup();

	size_t len = 100;
	int arr[len];
	size_t arr_max = 400;

	srand((unsigned int)time(NULL));
	for(size_t i = 0; i < len; i++)
		while(!(arr[i] = rand() % arr_max))
			arr[i] = (rand() % arr_max);

	bool run = true;
	bool sorted = false;

	while(run) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if(event.window.event == SDL_WINDOWEVENT_CLOSE) {
				event.type = SDL_QUIT;
				SDL_PushEvent(&event);
				run = false;
				break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 28, 28, 28, 0);
		SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
		SDL_GetWindowSize(window, &w, &h);

		for(size_t i = 0; i < len; i++)
			drw_element(arr[i]);

		SDL_RenderPresent(renderer);

		if(sorted == false) {
			if(!insertion_sort(arr, len)) {
				sorted = true;
				printf("The array has been sorted\n");
			}
		}

		SDL_Delay(100);

		x = 0;
	}
	
	cleanup();
	return 0;
}
