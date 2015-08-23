/* Vigenere is like caesar, exept the key is a word and we shift each byte of plaintext with the numerical translation */
/* of each byte in the key:  */
/* plaintext "aaa" with key "abc" will return: "bcd" */
/* Once the key is over, if there is still plaintext to process, we start over at the begining of the key */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>

static const char ALPHADOWN[] = "abcdefghijklmnopqrstuvwxyz";
static const char ALPHAUP[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static int modulo(int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}

/* in place modification */
/* functional people would die seing this */
static void trim_spaces(char *s) {
	char *i = s, *j = s;

	while (*j != '\0') {
		*i = *j++;
		if (*i != ' ') {
			i++;
		}
	}
	*i = '\0';
}

int main(int argc, char *argv[]) {
	char *cipher = NULL;
	char *key = NULL;
	int i = 0, j = 0;

	if (argc != 3) {
		printf("Usage: ./%s [message] [key]\n", argv[0]);
		return -1;
	}

	if (strlen(argv[2]) > strlen(argv[1])) {
		printf("Key must be less or equaly long as the message\n");
		return -1;
	}
	
	if ((cipher = calloc(strlen(argv[1]) + 1, sizeof *cipher)) == NULL) {
		perror("calloc");
		return -1;
	}

	if ((key = calloc(strlen(argv[2]) + 1, sizeof *key)) == NULL) {
		perror("calloc");
		free(cipher);
		return -1;
	}
	
	for (i = 0; argv[2][i]; i++) {
		key[i] = tolower(argv[2][i]);
	}
	key[i] = '\0';
	
	for (i = 0, j = 0; i < (int)strlen(argv[1]); i++, j++) {
		if (j > (int)strlen(argv[2]) - 1) { j = 0; }
		if (islower(argv[1][i])) {
			cipher[i] = ALPHADOWN[modulo(((argv[1][i] - 97) + (key[j] - 97)) + 1, 26)];
		} else if (isupper(argv[1][i])) {
			cipher[i] = ALPHAUP[modulo(((argv[1][i] - 65) + (key[j] - 97)) + 1, 26)];
		} else {
			cipher[i] = argv[1][i];
			j--;
		}
	}
	cipher[strlen(argv[1])] = '\0';
	trim_spaces(cipher);
	printf("Encrypted string is:\t%s\n", cipher);

	printf("Unencrypted string is:\t");
	for (i = 0, j = 0; i < (int)strlen(cipher); i++, j++) {
		if (j > (int)strlen(argv[2]) - 1) { j = 0; }
		if (islower(cipher[i])) {
			printf("%c", ALPHADOWN[modulo(((cipher[i] - 97) - (key[j] - 97)) - 1, 26)]);
		} else if (isupper(cipher[i])) {
			printf("%c", ALPHAUP[modulo(((cipher[i] - 65) - (key[j] - 97)) - 1, 26)]);
		} else {
			printf("%c", cipher[i]);
			j--;
		}
	}
	printf("\n");
	free(cipher);
	free(key);
	return 0;
}
