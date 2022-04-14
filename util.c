#include "util.h"

void
wait_main_thread(status_t *st) {
	if((*st != STOP) && (*st != PAUSE)) *st = UPDATE;

	/* wait 'til main thread changes st value to RUN */
	while((*st == UPDATE) || (*st == PAUSE));
}

void
end(const char *msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
}

void
swap(int *a, int *b)
{
	int tmp;
	tmp = (*a);
	(*a) = (*b);
	(*b) = tmp;
}
