#ifndef __UTIL_H__
#define  __UTIL_H__

#include "status.h"

#define UNHEX(color) \
    ((color) >> (8 * 3)) & 0xFF, \
    ((color) >> (8 * 2)) & 0xFF, \
    ((color) >> (8 * 1)) & 0xFF, \
    ((color) >> (8 * 0)) & 0xFF


void end(const char *msg);
void swap(int *a, int *b);

#endif // __UTIL_H__
