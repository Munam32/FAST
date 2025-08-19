#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_WRONLY); // O_WRONLY-> flag - open for writing only
    if (fd == -1) {
        perror("open FIFO");
        exit(EXIT_FAILURE);
    }

    char *smallest = argv[2];
    for (int i = 3; i < argc; i++) {
        if (strlen(argv[i]) < strlen(smallest)) {
            smallest = argv[i];
        }
    }

    write(fd, smallest, strlen(smallest) + 1);
    close(fd);
    return 0;
}
