#ifndef __UTIL_H__
#define  __UTIL_H__

#include <stdio.h>
#include <stdlib.h>

#include "status.h"

void end(const char *msg);
void swap(int *a, int *b);
void wait_main_thread(status_t *st);

#endif // __UTIL_H__
