#include "drw.h"

void
drw_element(SDL_Renderer *rend, int x, int y, int h) {
	SDL_Rect rect;

	rect.x = x + X_BORDER; /* top left + x */
	rect.y = y - Y_BORDER; /* top left + y, (y < 0) */
	rect.w = RECT_WIDTH; /* fixed width */
	rect.h = -h;

	SDL_RenderDrawRect(rend, &rect);
	SDL_SetRenderDrawColor(rend, 255, 0, 0, 0); /* RGBA */
	SDL_RenderFillRect(rend, &rect);

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
	SDL_RenderDrawLine(rend, x + X_BORDER, y - Y_BORDER, x + X_BORDER, y - Y_BORDER - h);
}

void
drw_element_color(SDL_Renderer *rend, int x, int y, int h, unsigned int col) {
	SDL_Rect rect;
	unsigned char r, g, b, a;

	rect.x = x + X_BORDER; /* bottom left + x */
	rect.y = y - Y_BORDER; /* bottom */
	rect.w = RECT_WIDTH; /* fixed width */
	rect.h = -h;

	r = (char)(col >> 24) & 0xFF;
	g = (char)(col >> 16) & 0xFF;
	b = (char)(col >> 8) & 0xFF;
	a = (char)(col) & 0xFF;

	SDL_RenderDrawRect(rend, &rect);
	SDL_SetRenderDrawColor(rend, r, g, b, a);
	SDL_RenderFillRect(rend, &rect);

	SDL_SetRenderDrawColor(rend, 0, 0, 0, 0);
	SDL_RenderDrawLine(rend, x + X_BORDER, y - Y_BORDER, x + X_BORDER, y - Y_BORDER - h);
}

void
drw_array_graph(SDL_Renderer *rend, SDL_Window *win, SAV *sav) {
	int x, w, h;

	SDL_GetWindowSize(win, &w, &h);

	SDL_SetRenderDrawColor(rend, 29, 28, 28, 0);
	SDL_RenderClear(rend);

	size_t i;
	for(i = x = 0; i < sav->arr->len; i++, x += RECT_WIDTH) {
		if(i == sav->sel) drw_element_color(rend, x, h, sav->arr->v[i], SEL_COLOR);
		else if(i == sav->cmp) drw_element_color(rend, x, h, sav->arr->v[i], CMP_COLOR);
		else drw_element(rend, x, h, sav->arr->v[i]);
	}

	SDL_RenderPresent(rend);
}
