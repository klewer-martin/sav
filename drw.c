#include "drw.h"

#define X_BORDER	40
#define Y_BORDER	40
#define RECT_WIDTH	5

void drw_element(SDL_Renderer *rend, int x, int y, int h) {
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

void drw_element_color(SDL_Renderer *rend, int x, int y, int h, unsigned int col) {
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
