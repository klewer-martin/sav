#include "sdl_extra.h"

status_t SDL_setup(SDL_Window **win, SDL_Renderer **rend) {
	int min_w, min_h;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return ERROR_SDL_INIT;

    *win = SDL_CreateWindow(
		WIN_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_RESIZABLE
    );

	*rend = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED);

	if ((*win == NULL) || (rend == NULL))
		return ERROR_NULL_POINTER;
	else if(TTF_Init() == -1)
		return ERROR_SDL_FONT_INIT;

	SDL_SetRenderDrawColor(*rend, 32, 32, 32, 0);
	SDL_RenderClear(*rend);
	SDL_RenderPresent(*rend);

	/* compute the window minimum size */
	min_w = ((ARR_LEN * RECT_WIDTH) + (2 * X_BORDER));
	min_h = ((ARR_MAX) + (2 * Y_BORDER) + TOP_BORDER);

	SDL_SetWindowMinimumSize(*win, min_w, min_h);
	/* SDL_SetWindowMaximumSize(*win, min_w, min_h); */
	return OK;
}

status_t SDL_cleanup(SDL_Window *win, SDL_Renderer *rend) {
	if((win == NULL) || (rend == NULL))
		return ERROR_NULL_POINTER;

	SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
	TTF_Quit();
	SDL_Quit();
	return OK;
}
