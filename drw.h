#ifndef __DRAW_H__
#define __DRAW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "sav.h"
#include "util.h"
#include "sdl_extra.h"
#include "sort.h"

#define SEL_COLOR	0x00FF0000 /* RGBA (A not used rn) */
#define CMP_COLOR	0x00FFFF00
#define NORM_COLOR	0xFF000000

#define FONT_SIZE	12
#define FONT_NAME	"VictorMono-Regular.ttf"
#define FONT_COLOR	0xBBBBBB

#define BAR_HEIGHT	15
#define BAR_BORDER	2

#define WIN_MIN_W	800
#define WIN_MIN_H	600

#define X_BORDER	40
#define Y_BORDER	40
#define TOP_BORDER	150
#define RECT_WIDTH	5

typedef struct {
	SDL_Renderer *rend;
	SDL_Window *win;
	SDL_Rect bar_rect, bar_text_rect;
	TTF_Font *font;
	int w, h, bar_text_len;
	size_t x_border, y_border;
	char *bar_text;
} Drw;

status_t drw_create(Drw **drw);
void drw_destroy(Drw *drw);

void drw_element(SDL_Renderer *rend, int x, int y, int h);
void drw_element_color(Drw *drw, int x, int y, int h, unsigned int col);
status_t drw_update_frame(Drw *, SAV *);

void drw_array_graph(Drw *drw, SAV *sav);
status_t drw_status_bar(Drw *drw, SAV *sav);

#endif
