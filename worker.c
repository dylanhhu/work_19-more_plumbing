#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


void reverse(char *str);


int main() {
	printf("worker: opening pipes...\n");
	
	int p_to_child = open("uno", O_RDONLY);
	if (p_to_child < 0) {
		printf("worker: couldn't open pipes (%s, %d)\n", strerror(errno), errno);
		printf("worker: hint: did you create the pipes using ./ui ?\n");
		return EXIT_FAILURE;
	}
	int child_to_p = open("dos", O_WRONLY);
	if (child_to_p < 0) {
		printf("worker: couldn't open pipes (%s, %d)\n", strerror(errno), errno);
		printf("worker: hint: did you create the pipes using ./ui ?\n");
		return EXIT_FAILURE;
	}

	printf("worker: pipes opened, ready.\n");
	printf("worker: hint: use ctrl-c to exit\n");

	char data[500];

	while (1) {
		int r = read(p_to_child, data, sizeof(data));
		data[r] = 0;

		reverse(data);
		write(child_to_p, data, strlen(data));
	}
	
	return 0;
}


void reverse(char *str) {
	int len = strlen(str);

	int i;
	for (i = 0; i < len / 2; i++) {
		int temp = str[len-i-1];
		str[len-i-1] = str[i];
		str[i] = temp;
	}
}
