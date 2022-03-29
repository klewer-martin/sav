#ifndef __DRAW_H__
#define __DRAW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>

#include "util.h"
#include "sav.h"

#define SEL_COLOR	0x00FF0000 // RGBA (A not used rn)
#define CMP_COLOR	0x00FFFF00

void drw_element(SDL_Renderer *rend, int x, int y, int h);
/* void draw_array_graph(SDL_Renderer *rend, SDL_Window *win, Arr *arr); */
void drw_element_color(SDL_Renderer *rend, int x, int y, int h, unsigned int col);

void drw_array_graph(SDL_Renderer *rend, SDL_Window *win, SAV *sav);

#endif // __DRAW_H__
