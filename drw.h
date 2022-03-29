#ifndef __DRAW_H__
#define __DRAW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include "util.h"

void drw_element(SDL_Renderer *rend, int x, int y, int h);
void drw_element_color(SDL_Renderer *rend, int x, int y, int h, unsigned int col);

#endif // __DRAW_H__
