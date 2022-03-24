#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include "drw.h"
#include "util.h"

#define WINDOW_TITLE "Sorting Algorithms Visualized"
#define WINDOW_WIDTH 	0
#define WINDOW_HEIGHT 	0

#define X_BORDER	50
#define Y_BORDER	50
#define RECT_WIDTH	5

#define INIT_SIZE 50

typedef struct {
	SDL_Window *window;
	SDL_Renderer *rend;
	int w, h;
	size_t x_border, y_border;
} Root;

Root root;
static size_t x = 0;	

void setup(void) {
	SDL_Init(SDL_INIT_VIDEO);

    // Create an application window with the following settings:
    root.window = SDL_CreateWindow(
		WINDOW_TITLE,					// window title
		SDL_WINDOWPOS_UNDEFINED,		// initial x position
		SDL_WINDOWPOS_UNDEFINED,		// initial y position
		WINDOW_WIDTH,					// width, in pixels
		WINDOW_HEIGHT,					// height, in pixels
		SDL_WINDOW_OPENGL | 
		SDL_WINDOW_RESIZABLE			// window flags
    );

	root.x_border = 5;
	root.y_border = 5;

	root.rend = SDL_CreateRenderer(root.window, -1, SDL_RENDERER_ACCELERATED);

	if (!root.window) end("SDL: window cannot be created");

	SDL_SetRenderDrawColor(root.rend, 32, 32, 32, 0);
	SDL_RenderClear(root.rend);
	SDL_RenderPresent(root.rend);
	SDL_RenderClear(root.rend);
}

void cleanup(void) {
	SDL_DestroyRenderer(root.rend);
    SDL_DestroyWindow(root.window);
	SDL_Quit();
}

void drw_element(size_t height) {
	SDL_Rect r;

	r.x = X_BORDER + x; // bottom left + x
	r.y = root.h - Y_BORDER + 1; // bottom
	r.w = RECT_WIDTH; // fixed width
	r.h = -height;

	SDL_RenderDrawRect(root.rend, &r);
	SDL_SetRenderDrawColor(root.rend, 255, 0, 0, 0);
	SDL_RenderFillRect(root.rend, &r);

	SDL_SetRenderDrawColor(root.rend, 0, 0, 0, 0);
	SDL_RenderDrawLine(root.rend,
			x + X_BORDER,
			root.h - Y_BORDER,
			x + X_BORDER,
			root.h - Y_BORDER - height);

	x += RECT_WIDTH;
}

void bubble_sort(int *arr, size_t len)
{
	if(arr == NULL) return;

	size_t swaps, top;
	top = len;
	for(size_t i = 0; i < len; ++i) {
		for(size_t j = 0; j < (top - 1); j++) {
			if(arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				swaps++;
			} else if(arr[top - 1] == (arr[top] - 1)) {
				len--;
			}
		}
		if(swaps == 0) break;
		top--;
	}
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
		SDL_SetRenderDrawColor(root.rend, 28, 28, 28, 0);
		SDL_RenderPresent(root.rend);
		SDL_RenderClear(root.rend);
		SDL_GetWindowSize(root.window, &root.w, &root.h);

		for(size_t i = 0; i < len; i++)
			drw_element(arr[i]);

		SDL_RenderPresent(root.rend);
		x = 0;
	}
	
	cleanup();
	return 0;
}
