#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

static const char ALPHABETDOWN[] = "abcdefghijklmnopqrstuvwxyz";
static const char ALPHABETUP[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/* the % operator defined inc c99 is in fact: not a modulo operator but a remainder operator*/
/* ie: -1 % 26 returns -1 instead of 25 */
/* so i had to write my modulo function */
static int modulo(int a, int b) {
    int r = a % b;
    return r < 0 ? r + b : r;
}

int main(int argc, char *argv[]) {
	int i = 0;
	int shift = 0;
	char *cipher = NULL;
	
	if (argc != 3) {
		printf("Usage: %s [message] [shift]\n", argv[0]);
		return -1;
	}

	shift = atoi(argv[2]);
	if (shift < 1 || shift > 25) {
		printf("shift must be between 1 and 25\n");
		return -1;
	}

	if ((cipher = calloc(strlen(argv[1]) + 1, sizeof *cipher)) == NULL) {
		perror("calloc");
		return -1;
	}
   
	for (i = 0; i < (int)strlen(argv[1]); i++) {
		if (islower(argv[1][i])) {
			cipher[i] = ALPHABETDOWN[modulo(((argv[1][i] - 97) + shift), 26)];
		} else if (isupper(argv[1][i])) {
			cipher[i] = ALPHABETUP[modulo(((argv[1][i] - 65) + shift), 26)];
		} else {
			cipher[i] = argv[1][i];
		}
	}
	cipher[strlen(argv[1])] = '\0';
	printf("encrypted string is:\t%s\n", cipher);

	printf("unencrypted string is:\t");
	for (i = 0; i < (int)strlen(cipher); i++) {
		if (islower(cipher[i])) {
			printf("%c", ALPHABETDOWN[modulo(((cipher[i] - 97) - shift), 26)]);
		} else if (isupper(cipher[i])) {
			printf("%c", ALPHABETUP[modulo(((cipher[i] - 65) - shift), 26)]);
		} else {
			printf("%c", cipher[i]);
		}		
	}
	printf("\n");

	free(cipher);
	return 0;
}
