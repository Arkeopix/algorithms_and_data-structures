/* This works exacltly like when you sort cards */
/* You get the first one and swap it with every card that is higher that the one you currently hold */
/* {9 8 7 42 6} will be sorted like the following: */
/* 1) 9 8 7 42 6 */
/* 1.1) 8 9 7 42 6 */
/* 2) 8 9 7 42 6 */
/* 2.1) 8 7 9 42 6 */
/* 2.2) 7 8 9 42 6 */
/* 3) 7 8 9 42 6 */
/* 4) 7 8 9 42 6 */
/* 4.1) 7 8 9 6 42 */
/* 4.2) 7 8 6 9 42 */
/* 4.3) 7 6 8 9 42 */
/* 4.4) 6 7 8 9 42 */
/* and thats it */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void insertion_sort(uint8_t *data, const size_t data_len) {
	size_t j = 0, i = 0;
	uint8_t  key;

	for (j = 1 ;j < data_len; j++) {
		key = data[j];
		i = j - 1;
		/* i need to enter this loop for each value of i, from n to 0  */
		/* comparing an unsigned int like this is plain dumb */
		while (i >= 0 && data[i] > key) {
			data[i + 1] = data[i];
			i = i - 1;
		}
		data[i + 1] = key;
	}
}

int main(void) {
	uint8_t array[10] = {9, 8, 7, 42, 6, 4, 90, 64, 22, 20};
	size_t i = 0;

	insertion_sort(array, 10);
	for (i = 0; i < 10; i++) {
		printf("%d ", array[i]);
	}
	return 0;
}
