#ifndef __DRAW_H__
#define __DRAW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "sav.h"
#include "util.h"
#include "sort.h"

#define SEL_COLOR	0x00FF0000 // RGBA (A not used rn)
#define CMP_COLOR	0x00FFFF00
#define NORM_COLOR	0xFF000000

#define FONT_SIZE	11
#define BAR_HEIGHT	14

typedef struct {
	SDL_Renderer *rend;
	SDL_Window *win;
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;
	SDL_Color text_color;
	TTF_Font *font;
	int w, h, font_size;
} Drw;

status_t DRW_New(SDL_Renderer *rend, SDL_Window *win, Drw **drw);
void DRW_Destroy(Drw *drw);

void drw_element(SDL_Renderer *rend, int x, int y, int h);
void drw_element_color(SDL_Renderer *rend, int x, int y, int h, unsigned int col);
void drw_array_graph(Drw *drw, SAV *sav);
void drw_status_bar(Drw *drw, SAV *sav);
void drw_text(Drw *drw, char *text, int x, int y);

void loading_animation(Drw *drw, SAV *sav);

#endif // __DRAW_H__
