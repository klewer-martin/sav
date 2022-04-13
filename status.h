#ifndef __STATUS_H__
#define __STATUS_H__

typedef enum {
	OK = 0,
	RUN,
	PAUSE,
	UPDATE,
	ERROR_MEMORY_ALLOC,
	ERROR_OPENING_FONT,
	ERROR_SDL_FONT_INIT,
	ERROR_NULL_POINTER,
	ERROR_DRW,
	SORTED,
	RESTART,
	STOP
} status_t;

#endif
