#ifndef __SAV_H__
#define __SAV_H__

#include "util.h"

#include <time.h>
#include <SDL2/SDL.h>

typedef struct {
	Arr *arr;
	size_t sel, cmp, cmps, swps, its;
	clock_t ti, tf;
	status_t status;
} SAV;

status_t SAV_New(SAV **sav);
void SAV_Destroy(SAV *sav);

#endif
