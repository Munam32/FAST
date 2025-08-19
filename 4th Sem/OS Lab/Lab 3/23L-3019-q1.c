
// q1.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) {
        if (num % 2 == 0)
            printf("Child: The number %d is even.\n", num);
        else
            printf("Child: The number %d is odd.\n", num);
    } else {
        printf("Parent: The number entered is %d\n", num);
    }
    return 0;
}
