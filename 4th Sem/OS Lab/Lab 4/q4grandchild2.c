#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        perror("open FIFO");
        exit(EXIT_FAILURE);
    }

    char *largest = argv[2];
    for (int i = 3; i < argc; i++) {
        if (strlen(argv[i]) > strlen(largest)) {
            largest = argv[i];
        }
    }

    write(fd, largest, strlen(largest) + 1);
    close(fd);
    return 0;
}
