#include "drw.h"

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
drw_array_graph(Drw *drw, SAV *sav) {
	int x, w, h;

	SDL_GetWindowSize(drw->win, &w, &h);

	SDL_SetRenderDrawColor(drw->rend, 29, 28, 28, 0);
	SDL_RenderClear(drw->rend);

	size_t i;
	for(i = x = 0; i < sav->arr->len; i++, x += RECT_WIDTH) {
		if(i == sav->sel) drw_element_color(drw->rend, x, h, sav->arr->v[i], SEL_COLOR);
		else if(i == sav->cmp) drw_element_color(drw->rend, x, h, sav->arr->v[i], CMP_COLOR);
		else drw_element_color(drw->rend, x, h, sav->arr->v[i], NORM_COLOR);
	}
	drw_status_bar(drw, sav);
}

void
drw_status_bar(Drw *drw, SAV *sav) {
	SDL_Rect rect;
	int bar_border = 2;

	rect.x = bar_border; /* top left + x */
	rect.y = drw->h - bar_border; /* top left + y, (y < 0) */
	rect.w = drw->w - (2 * bar_border); /* fixed width */
	rect.h = -BAR_HEIGHT;

	SDL_RenderDrawRect(drw->rend, &rect);
	SDL_SetRenderDrawColor(drw->rend, 0, 0, 0, 0); /* RGBA */
	SDL_RenderFillRect(drw->rend, &rect);

	if((sav->status == RUN) || (sav->status == UPDATE))
		drw_text(drw, "SORTING -- insertion sort", 10, drw->h - drw->font_size - 5);
	else if(sav->status == SORTED)
		drw_text(drw, "SORTED -- insertion sort", 10, drw->h - drw->font_size - 5);

	/* SDL_RenderCopy(drw->rend, drw->text_texture, NULL, &text_rect); */
}

void drw_text(Drw *drw, char *text, int x, int y) {
	drw->text_surface = TTF_RenderText_Blended(drw->font, text, drw->text_color);
	drw->text_texture = SDL_CreateTextureFromSurface(drw->rend, drw->text_surface);

	SDL_Rect text_rect = { 10 + x, drw->h - drw->font_size - 5, drw->text_surface->w, drw->text_surface->h };

	SDL_RenderCopy(drw->rend, drw->text_texture, NULL, &text_rect);
}

status_t DRW_New(SDL_Renderer *rend, SDL_Window *win, Drw **drw) {
	if((*drw = (Drw *)malloc(sizeof(Drw))) == NULL)
		return ERROR_MEMORY_ALLOC;

	TTF_Font *font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSansMono.ttf", FONT_SIZE);
	if(!font) fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());

	(*drw)->rend = rend;
	(*drw)->win = win;
	(*drw)->font = font;
	(*drw)->font_size = FONT_SIZE;

	(*drw)->text_color.r = 255;
	(*drw)->text_color.g = 255;
	(*drw)->text_color.b = 255;

	SDL_GetWindowSize(win, &((*drw)->w), &((*drw)->h));

	return 0;
}

void DRW_Destroy(Drw *drw) {
	TTF_CloseFont(drw->font);
	free(drw);
}
