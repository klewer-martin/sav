#ifndef __SAV_H__
#define __SAV_H__

#include "util.h"

typedef struct {
	Arr *arr;
	size_t sel, cmp;
	status_t status;
} SAV;

#endif
