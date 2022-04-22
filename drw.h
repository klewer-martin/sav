#ifndef __DRAW_H__
#define __DRAW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "sav.h"
#include "util.h"
#include "sdl_extra.h"
#include "sort.h"

#define SEL_COLOR	0x00FF0000 // RGBA (A not used rn)
#define CMP_COLOR	0x00FFFF00
#define NORM_COLOR	0xFF000000

/* #define SEL_COLOR	0xFF0000FF // RGBA (A not used rn) */
/* #define CMP_COLOR	0x00FF00FF */
/* #define NORM_COLOR	0xFFFFFFFF */

#define FONT_SIZE	12
#define FONT_NAME	"/home/mk/.local/share/fonts/VictorMono-Bold.ttf"
#define FONT_COLOR	0xBBBBBB

#define BAR_HEIGHT	14

#define WIN_MIN_W	800
#define WIN_MIN_H	600

#define X_BORDER	40
#define Y_BORDER	40
#define TOP_BORDER	50
#define RECT_WIDTH	5

typedef struct {
	SDL_Renderer *rend;
	SDL_Window *win;
	SDL_Surface *text_surface;
	SDL_Texture *text_texture;
	SDL_Color text_color;
	SDL_Rect bar_rect, bar_text_rect;
	TTF_Font *font;
	int w, h, font_size, bar_text_len, bar_border;
	size_t x_border, y_border;
	char *bar_text;
} Drw;

static char * const algo_sel_str[ALGORITHMS_COUNT] = {
	"bubble",
	"improved bubble",
	"insertion",
	"merge",
	"quick",
	"shell",
	"selection"
};

static char * const sort_status_str[STATUS_MAX] = {
	"READY",
	"SORTING",
	"PAUSED",
	"SORTED",
	"STOPPED"
};

status_t Drw_new(Drw **drw);
void Drw_destroy(Drw *drw);

void drw_element(SDL_Renderer *rend, int x, int y, int h);
void drw_element_color(Drw *drw, int x, int y, int h, unsigned int col);
void drw_text(Drw *drw, const char *text, int x, int y);

void drw_array_graph(Drw *drw, SAV *sav);
void drw_status_bar(Drw *drw, SAV *sav);

#endif
