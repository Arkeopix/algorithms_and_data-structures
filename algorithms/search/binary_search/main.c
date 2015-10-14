#include <stdio.h>
#define ARRAY_LENGHT 30

static const int primes[ARRAY_LENGHT] = {
	2,      3,      5,      7,     11,     13,     17,     19,     23,     29,
	31,     37,     41,     43,    47,     53,     59,     61,     67,     71,
	73,     79,     83,     89,    97,     101,    103,    107,    109,    113,
};

static int binary_search(const int to_find) {
	int min = 1;
	int max = ARRAY_LENGHT - 1;
	int guess = 0;
	
	while (max >= min) {
		guess = (min + max) / 2;
		if (primes[guess] == to_find) {
			return guess;
		} else if (primes[guess] < to_find) {
			min = guess + 1;
		} else {
			max = guess - 1;
		}
	}
	return -1;
}

int main() {
	int res = binary_search(113);
	printf("Found prime number at index: %d", res);
}
