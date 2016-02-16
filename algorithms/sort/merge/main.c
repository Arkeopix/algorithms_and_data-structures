#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void merge(int8_t *array, const size_t low_index, const size_t mid_index, const size_t upp_index) {
	size_t i, j, k = low_index;
	const size_t len_1 = mid_index - low_index + 1;
	const size_t len_2 = upp_index - mid_index;
	int8_t left_array[len_1], right_array[len_2];

	/* copy the left part of the array, from low_index + i up to len_1 */
	for (i = 0; i < len_1; i++) {
		left_array[i] = array[low_index + i];
	}
	/* copy the right part of the array, from mid_index + 1 up to the end */
	for (j = 0; j < len_2; j++) {
		right_array[j] = array[mid_index + 1 + j];
	}

	/* merge left_array and right_array back together, making sure to reinsert items in the right order */
	for (i = 0, j = 0; i < len_1 && j < len_2;) {
		if (left_array[i] <= right_array[j]) {
			array[k] = left_array[i];
			i++;
		} else {
			array[k] = right_array[j];
			j++;
		}
		k++;
	}

	/* Copy the leftovers from (left|right)_array */
	while (i < len_1) {
		array[k] = left_array[i];
        i++;
        k++;
	}
	while (j < len_2) {
		array[k] = right_array[j];
		j++;
		k++;
	}
} 

void merge_sort(int8_t *array, const int low_index, const int upp_index) {
	const size_t mid_index = (low_index + upp_index) / 2;
	
	if (low_index < upp_index) {
		merge_sort(array, low_index, mid_index);
		merge_sort(array, mid_index + 1, upp_index);
		merge(array, low_index, mid_index, upp_index);
	}
}

int main(void) {
	int8_t array[10] = {9, 3, 10, 4, 1, 42, 110, 99, 89, 2};
	size_t i = 0;
	
	merge_sort(array, 0, 10 - 1);
	for (i = 0; i < 10; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");
	return 0;
}
