#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void sort_words(char *words[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(words[i], words[j]) > 0) {
                char *temp = words[i];
                words[i] = words[j];
                words[j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        perror("open FIFO");
        exit(EXIT_FAILURE);
    }

    char *words[argc - 2];
    int count = argc - 2;

    for (int i = 0; i < count; i++) {
        words[i] = argv[i + 2];
    }

    sort_words(words, count);

    char result[1024] = "";
    for (int i = 0; i < count; i++) {
        strcat(result, words[i]);
        strcat(result, " ");
    }

    write(fd, result, strlen(result) + 1);
    close(fd);
    return 0;
}
