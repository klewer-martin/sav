#ifndef __SDL_EXTRA_H__
#define __SDL_EXTRA_H__

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
/* #include <SDL2/SDL_video.h> */
/* #include <SDL2/SDL_image.h> */

/* typedef struct { */
/* 	status_t status; */
/* 	int speed; */
/* 	size_t sel, cmp, swap; */
/* 	void (*sort)(int *arr, size_t len); */
/* } Sav; */

#include "util.h"

void check_events(status_t *status);
void setup(SDL_Window **win, SDL_Renderer **rend);
void cleanup(SDL_Window *win, SDL_Renderer *rend);

#endif

