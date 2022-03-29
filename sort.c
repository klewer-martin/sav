#include <stdio.h>
#include <stdbool.h>

#include "sort.h"
#include "util.h"

int bubble_sort(int *arr, size_t len) {
	if(arr == NULL) return 1;

	/* size_t swaps, top; */
	/* top = len; */

	static size_t i = 0;
	static size_t j = 100;

	if(i < len) {
		if(j > (i + 1)) {
			if(arr[j] < arr[j - 1])
				swap(&arr[j], &arr[j + 1]);

			printf("j: %ld\n", j);

			j--;
			return 1;
		}
		/* if(swaps == 0) break; */
		printf("i: %ld\n", i);
		i++;
		j = 100;
	} else return 0;

	return 1;
}
