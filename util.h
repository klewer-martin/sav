#ifndef __UTIL_H__
#define  __UTIL_H__

#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN		120
#define ARR_MAX		500

#define X_BORDER	40
#define Y_BORDER	40
#define TOP_BORDER	50

#define RECT_WIDTH	6	

typedef enum {
	OK = 0,
	RUN,
	PAUSE,
	UPDATE,
	ERROR_MEMORY_ALLOC,
	ERROR_OPENING_FONT,
	ERROR_DRW,
	SORTED,
	RESTART,
	STOP
} status_t;

typedef struct {
	int *v;
	size_t len;
} Arr;

void end(const char *msg);
void swap(int *a, int *b);
void wait_main_thread(status_t *st);

#endif // __UTIL_H__
