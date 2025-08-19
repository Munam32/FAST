#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

// defining for ease

#define MAX_WORDS 10
#define MAX_LENGTH 100
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"
#define FIFO3 "fifo3"
#define FIFO4 "fifo4"


// creating named pipes
void create_fifo(const char *fifo_name) {
    mkfifo(fifo_name, 0666); 
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > MAX_WORDS + 1) {
        fprintf(stderr, "Usage: %s <word1> <word2> ... (up to 10 words)\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    create_fifo(FIFO1);
    create_fifo(FIFO2);
    create_fifo(FIFO3);
    create_fifo(FIFO4);

    pid_t pid1 = fork();
    if (pid1 == 0) { // First child
        if (fork() == 0) { // First grandchild (find shortest word)
            execl("./q4grandchild1", "q4grandchild1", FIFO1, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], NULL);
            perror("execl q4grandchild1");
            exit(EXIT_FAILURE);
        }
        if (fork() == 0) { // Second grandchild (find longest word)
            execl("./q4grandchild2", "q4grandchild2", FIFO2, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], NULL);
            perror("execl q4grandchild2");
            exit(EXIT_FAILURE);
        }
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) { // Second child
        if (fork() == 0) { // Third grandchild
            execl("./q4grandchild3", "q4grandchild3", FIFO3, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], NULL);
            perror("execl q4grandchild3");
            exit(EXIT_FAILURE);
        }
        if (fork() == 0) { // Fourth grandchild
            execl("./q4grandchild4", "q4grandchild4", FIFO4, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7], argv[8], argv[9], argv[10], NULL);
            perror("execl q4grandchild4");
            exit(EXIT_FAILURE);
        }
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    // Read results from FIFO pipes
    char buffer[MAX_LENGTH];

    int fd1 = open(FIFO1, O_RDONLY);
    read(fd1, buffer, MAX_LENGTH);
    printf("Smallest word: %s\n", buffer);
    close(fd1);

    int fd2 = open(FIFO2, O_RDONLY);
    read(fd2, buffer, MAX_LENGTH);
    printf("Largest word: %s\n", buffer);
    close(fd2);

    int fd3 = open(FIFO3, O_RDONLY);
    read(fd3, buffer, MAX_LENGTH);
    printf("Sorted words: %s\n", buffer);
    close(fd3);

    // removing named pipes
    unlink(FIFO1);
    unlink(FIFO2);
    unlink(FIFO3);
    unlink(FIFO4);

    return 0;
}
