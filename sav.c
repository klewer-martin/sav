#include "sav.h"

char *algo_strings[SORT_MAX_ALGORITHMS] = {
	"bubble",
	"insertion",
	"merge",
	"quick"
};

status_t
SAV_new(SAV **sav) {
	if((*sav = (SAV *)malloc(sizeof(SAV))) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*sav)->sel = (*sav)->cmps = (*sav)->swps = (*sav)->its = (*sav)->B_used = 0;
	(*sav)->cmp = ARR_MAX + 1;
	(*sav)->status = RUN;
	(*sav)->sel_algo = SORT_MAX_ALGORITHMS;

	if(((*sav)->arr = (Arr *)malloc(sizeof(Arr))) == NULL)
		return ERROR_MEMORY_ALLOC;

	if(((*sav)->arr->v = (int *)malloc(sizeof(int) * ARR_LEN)) == NULL)
		return ERROR_MEMORY_ALLOC;

	(*sav)->arr->len = ARR_LEN;

	if((*sav)->arr == NULL) {
		return ERROR_MEMORY_ALLOC;
	}
	return 0;
}

void
SAV_destroy(SAV *sav) {
	if(sav == NULL) return;

	free(sav->arr->v);
	free(sav->arr);
	free(sav);
}

void
check_events(Drw *drw, SAV *sav) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch(event.type) {
		case SDL_QUIT: sav->status = STOP; break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.scancode) {
			/* case SDL_SCANCODE_EQUALS: */ 
			/* 	if(speed > SPEED_MAX) speed -= SPEED_STEP; */
			/* 	break; */
			/* case SDL_SCANCODE_MINUS: */
			/* 	if(speed < SPEED_MIN) speed += SPEED_STEP; */
			/* 	break; */
			/* case SDL_SCANCODE_P: */
			/* 	if(status == PAUSE) *status = RUN; */
			/* 	else *status = PAUSE; */
			/* 	break; */
			case SDL_SCANCODE_R:
				if(sav->status == SORTED) sav->status = RESTART;
				else break;
			default: break;
		   }
		case SDL_WINDOWEVENT:
			switch(event.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				SDL_Log("Window resized to %dx%d", event.window.data1, event.window.data2);
				drw->w = event.window.data1;
				drw->h = event.window.data2;

				/* set new window borders */
				drw->x_border = (drw->w / 2) - ((sav->arr->len * RECT_WIDTH) / 2);
				drw->y_border = (drw->h / 2) - (ARR_MAX / 2);

				break;
			default: break;
		   }
		default: break;
		}
	}
}
