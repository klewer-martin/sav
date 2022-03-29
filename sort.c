#include <stdio.h>
#include <stdbool.h>

#include "sort.h"
#include "util.h"

typedef enum {
	RUN,
	PAUSE,
	STOP
} status_t;

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

/* int insertion_sort(int *arr, size_t len) { */
/* 	static size_t i = 1; */
/* 	int j; */

/* 	int key; */

/* 	if(i < len) { */
/* 		key = arr[i]; */
/* 		j = i - 1; */

/* 		while((j >= 0) && (arr[j] > key)) { */
/* 			arr[j + 1] = arr[j]; */
/* 			j = j - 1; */
/* 		} */

/* 		arr[j + 1] = key; */
/* 		i++; */
/* 		return 1; */
/* 	} */

/* 	return 0; */
/* } */

/* void insertion_sort(int *arr, size_t len) { */
	/* int key; */
	/* size_t i, j; */

	/* extern status_t status; */
	/* extern size_t sel, cmp; */
	/* bool sorted = false; */
	/* extern bool update; */

	/* /1* if((sorted == false) && (status == RUN)) { *1/ */
	/* while((status == RUN) && (sorted != true)) { */
	/* 	if(status != PAUSE) { */
	/* 		for(i = 1; i < len; i++) { */
	/* 			key = arr[i]; */
	/* 			j = i - 1; */
	/* 			while((j >= 0) && (arr[j] > key)) { */
	/* 				arr[j + 1] = arr[j]; */
	/* 				j = j - 1; */
	/* 				sel = i; */
	/* 				cmp = j; */
	/* 				/1* update_array_graph(rend, win); *1/ */
	/* 				/1* SDL_Delay(speed); *1/ */
	/* 				/1* if(status == PAUSED) goto end_sort; *1/ */
	/* 			} */
	/* 			arr[j + 1] = key; */
	/* 			sel = i; */
	/* 			cmp = j; */
	/* 			/1* if(status == PAUSED) goto end_sort; *1/ */
	/* 			/1* update_array_graph(rend, win); *1/ */
	/* 			/1* SDL_Delay(speed); *1/ */
	/* 		} */
	/* 	sel = cmp = i; */ 
	/* 	update = true; */
	/* 	/1* goto end_sort; *1/ */
	/* 	/1* update_array_graph(rend, win); *1/ */
	/* 	/1* SDL_Delay(speed); *1/ */
	/* 	/1* sorted = true; *1/ */
	/* 	} */
	/* } */
	/* update_array_graph(rend, win); */
	/* SDL_Delay(speed); */
	/* return 0; */
/* } */

