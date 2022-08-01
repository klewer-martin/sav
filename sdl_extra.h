#ifndef __SDL_EXTRA_H__
#define __SDL_EXTRA_H__

#include "array.h"
#include "status.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define X_BORDER	40
#define Y_BORDER	40
#define TOP_BORDER	50
#define RECT_WIDTH	5

#define WIN_TITLE "SAV: Sorting Algorithms Visualized"

status_t SDL_setup(SDL_Window **win, SDL_Renderer **rend);
status_t SDL_cleanup(SDL_Window *win, SDL_Renderer *rend);

#endif

