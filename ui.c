#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>


int main() {
	printf("ui: creating pipes...\n");

    int p1 = mkfifo("uno", 0644);
    if (p1) {
        printf("ui: couldn't create pipes (%s, %d), exiting...\n", strerror(errno), errno);
        printf("ui: hint: did you remove existing files/pipes named \"uno\" and \"dos\"?\n");
        return EXIT_FAILURE;
    }
    int p2 = mkfifo("dos", 0644);
    if (p2) {
        printf("ui: couldn't create pipes (%s, %d), exiting...\n", strerror(errno), errno);
        printf("ui: hint: did you remove existing files/pipes named \"uno\" and \"dos\"?\n");
        return EXIT_FAILURE;
    }
    
    printf("ui: pipes created, open ./worker now.\n");

    int p_to_child = open("uno", O_WRONLY);
    int child_to_p = open("dos", O_RDONLY);

	printf("ui: all done. ready.\n");
    printf("ui: hint: use ctrl+c to exit\n");

    char input[500];

    while (1) {
        printf(">>> ");
        
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = 0;
        write(p_to_child, input, strlen(input));

        int r = read(child_to_p, input, sizeof(input));
        input[r] = 0;
        
        printf("%s\n", input);
    }

    return 0;
}
