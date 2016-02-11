#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void insertion_sort(uint8_t *data, size_t data_len) {
	size_t j = 0, i = 0;
	uint8_t  key;

	for (j = 1 ;j < data_len; j++) {
		key = data[j];
		i = j - 1;
		while (i > 0 && data[i] > key) {
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
