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

#define SEL_COLOR	0x00FF0000 // RGBA
#define CMP_COLOR	0x00FFFF00

#define ANIM_SPEED	50
#define SPEED_STEP	10

#define ARR_LEN		100
#define ARR_MAX		500

#define X_BORDER	25
#define Y_BORDER	25
#define RECT_WIDTH	5

#define SPEED_MIN 5000
#define SPEED_MAX 0

SDL_Window *window;
SDL_Renderer *renderer;

int x, w, h, arr[ARR_LEN], speed;
size_t sel, cmp, arr_max, x_border, y_border, g_w, g_h;	
int min_w, min_h;

bool run = true;

void setup(void) {
	SDL_Init(SDL_INIT_VIDEO);

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
		WINDOW_TITLE,					// window title
		SDL_WINDOWPOS_UNDEFINED,		// initial x position
		SDL_WINDOWPOS_UNDEFINED,		// initial y position
		WINDOW_WIDTH,					// width, in pixels
		WINDOW_HEIGHT,					// height, in pixels
		SDL_WINDOW_OPENGL				// window flags
    );

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!window) end("SDL: window cannot be created");

	SDL_SetRenderDrawColor(renderer, 32, 32, 32, 0);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void cleanup(void) {
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
	SDL_Quit();
}

void drw_element(size_t height) {
	SDL_Rect rect;

	rect.x = X_BORDER + x; /* bottom left + x */
	rect.y = h - Y_BORDER + 1; /* bottom */
	rect.w = RECT_WIDTH; /* fixed width */
	rect.h = -height;

	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0); /* RGBA */
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawLine(renderer,
			x + X_BORDER,
			h - Y_BORDER,
			x + X_BORDER,
			h - Y_BORDER - height);

	x += RECT_WIDTH;
}

void drw_element_color(size_t height, unsigned int color) {
	SDL_Rect rect;
	unsigned char r, g, b, a;

	rect.x = X_BORDER + x; /* bottom left + x */
	rect.y = h - Y_BORDER + 1; /* bottom */
	rect.w = RECT_WIDTH; /* fixed width */
	rect.h = -height;

	r = (char)(color >> 24) & 0xFF;
	g = (char)(color >> 16) & 0xFF;
	b = (char)(color >> 8) & 0xFF;
	a = (char)(color) & 0xFF;

	SDL_RenderDrawRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderDrawLine(renderer,
			x + X_BORDER,
			h - Y_BORDER,
			x + X_BORDER,
			h - Y_BORDER - height);

	x += RECT_WIDTH;
}

void update_window_size(void) {
	SDL_GetWindowSize(window, &w, &h);

	g_w = (ARR_LEN * RECT_WIDTH);
	g_h = (ARR_MAX);

	x_border = X_BORDER;
	y_border = Y_BORDER;

	min_w = (g_w + (2 * x_border));
	min_h = (g_h + (2 * y_border));

	SDL_SetWindowMinimumSize(window, min_w, min_h);
	SDL_SetWindowMaximumSize(window, min_w, min_h);
}

void update_graph(void) {
	SDL_SetRenderDrawColor(renderer, 28, 28, 28, 0);
	SDL_RenderClear(renderer);

	SDL_GetWindowSize(window, &w, &h);

	/* reset 'x' in order to start drawing from the left */ 
	size_t i;
	for(i = x = 0; i < ARR_LEN; i++) {
		if(i == sel) drw_element_color(arr[i], SEL_COLOR);
		else if(i == cmp) drw_element_color(arr[i], CMP_COLOR);
		else drw_element(arr[i]);
	}

	SDL_RenderPresent(renderer);
}

void check_events(void) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT: run = false; break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode) {
			case SDL_SCANCODE_EQUALS: 
				if(speed > SPEED_MAX) speed -= SPEED_STEP;
				break;
			case SDL_SCANCODE_MINUS:
				if(speed < SPEED_MIN) speed += SPEED_STEP;
				break;
			default: break;
		   }
		default: break;
		}
	}
}

int main (void) {
	setup();
	size_t i, j;
	int key;

	speed = ANIM_SPEED;

	bool sorted = false;

	arr_max = ARR_MAX;

	update_window_size();

	/* create a random array */
	srand((unsigned int)time(NULL));
	for(i = 0; i < ARR_LEN; i++)
		while(!(arr[i] = rand() % arr_max))
			arr[i] = (rand() % arr_max);

	/* main loop */
	while(run) {
		check_events();
		/* sort the array while updating the graph */
		if(sorted == false) {
			for(i = 1; i < ARR_LEN; i++) {
				key = arr[i];
				j = i - 1;
				while((j >= 0) && (arr[j] > key)) {
					arr[j + 1] = arr[j];
					j = j - 1;
					sel = i;
					cmp = j;
					update_graph();
					SDL_Delay(speed);
					check_events();
					if(run == false) goto end_main_while;
				}
				arr[j + 1] = key;
				sel = i;
				cmp = j;
				check_events();
				if(run == false) goto end_main_while;
				update_graph();
				SDL_Delay(speed);
			}
			sel = cmp = i; 
			update_graph();
			SDL_Delay(speed);
			sorted = true;
		}
		update_graph();
		SDL_Delay(speed);
	}
end_main_while:
	
	cleanup();
	return 0;
}
