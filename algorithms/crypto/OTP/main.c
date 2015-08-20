/*
 * One Time pad uses a secret randomly generated key called a pad and xor it against the message.
 * In order to be truly secure, the key must be used only once and must be truly random
 */

#define _BSD_SOURCE
#include <linux/random.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

static const char DEVURANDOM[] = "/dev/urandom";
static const char KEYCHAR[] = "ABCDEFGHIJKLMNOPQURSTUVWXYZ";

/*
 * opens /dev/urandom, check wether urandom has high entropy
 * The function also checks wether the file opened if a character device and is a random device
 * returns the file descriptor or -1 on error
 */
static int open_urandom(const int string_len) {
	int fd;
	int entropy = 0;

	if ((fd = open(DEVURANDOM, O_RDONLY)) < 0) {
		perror("open");
		return -1;
	}
	
	/* this ioctl call is bounded to the entropy pool connected to /dev/urandom */
	/* meaning: is the call is a success, we're dealing with /dev/urandom*/ 
	if (!ioctl(fd, RNDGETENTCNT, &entropy) && (entropy >= (string_len * 10))) {
		return fd;
	}
	return -1;
}

/*
 * reads from /dev/urandom.
 * returns the number of bytes read
 * fill buff with data from /dev/urandom
 */
static ssize_t read_urandom(const int fd, void *buff, const size_t count) {
	/* /dev/urandom will always give the asked number of bytes */
	ssize_t res = read(fd, (char *)buff, count);
	if (res < 0) {
		perror("read");
		return -1;
	}
	return res;
}

static char *generate_key(unsigned char *random_data, const ssize_t string_len) {
	char *key = NULL;
	int i = 0, j = 0;
	
	if ((key = calloc((string_len + 1), sizeof *key)) == NULL) {
		perror("calloc");
		return NULL;
	}
	for (i = 0; i < string_len; i++) {
		int char_key = 0;
		size_t k = 0;
		for (j = 0; j != random_data[i]; j++) {
			if (k > strlen(KEYCHAR)) {
				k = 0;
			}
			char_key = KEYCHAR[k];
			k++;
		}
		key[i] = char_key;
	}
	key[string_len] = '\0';
	printf("generated key is:\t %s\n", key);
	return key;
}

int main(int argc, char *argv[]) {
	int random_fd;
	char *string_to_process = NULL;
	size_t string_len;
	ssize_t data_read;
	unsigned char *random_data;
	char *key = NULL;
	char *encrypted = NULL;
	char *decrypted = NULL;
	int i = 0;
	
	if (argc < 2) {
		printf("usage: %s [message]\n", argv[0]);
		return -1;
	}

	string_to_process= strdup(argv[1]);
	string_len = strlen(string_to_process);
	if ((encrypted = calloc((string_len + 1), sizeof *encrypted)) == NULL) {
		perror("calloc");
		free(string_to_process);
		return -1;
	}		
	if ((random_data = calloc((string_len + 1), sizeof *random_data)) == NULL) {
		perror("calloc");
		free(encrypted);
		free(string_to_process);
		return -1;
	}
	if ((decrypted = calloc((string_len + 1), sizeof *encrypted)) == NULL) {
		perror("calloc");
		free(encrypted);
		free(random_data);
		free(string_to_process);
		return -1;
	}
	
	printf("unencrypted string is:\t '%s'\n", string_to_process);
	if ((random_fd = open_urandom(string_len)) >= 0) {
		data_read = read_urandom(random_fd, random_data, string_len);
		if (data_read > 0) {
			key = generate_key(random_data, string_len);

			/* encrypt */
			for (i = 0; i < (int)string_len; i++) {
				encrypted[i] = key[i] ^ string_to_process[i];
			}
			printf("encrypted string:\t %s\n", encrypted);

 			/* decrypt */
			for (i = 0; i < (int)string_len; i++) {
				decrypted[i] = key[i] ^ encrypted[i];
			}
 			decrypted[string_len] = '\0';
 			printf("unencrypted string is:\t %s\n", decrypted);
		}
	}
	close(random_fd);
	free(string_to_process);
	free(encrypted);
	free(random_data);
	free(decrypted);
	free(key);
	return 0;
}
