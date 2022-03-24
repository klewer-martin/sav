#include "util.h"

void end(const char *msg) {
	fprintf("%s\n", msg);
	exit(1);
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = (*a);
	(*a) = (*b);
	(*b) = tmp;
}
