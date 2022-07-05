#include "util.h"

#include <stdio.h>
#include <stdlib.h>

void end(const char *msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = (*a);
	(*a) = (*b);
	(*b) = tmp;
}
