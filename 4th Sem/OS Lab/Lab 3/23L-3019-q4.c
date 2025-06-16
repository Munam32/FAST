
// q4.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char *input = argv[1];

    pid_t pid1 = fork();
    if (pid1 == 0) {
        printf("Child 1 [PID: %d]: Vowels: ", getpid());
        for (int i = 0; input[i] != '\0'; ++i) {
            if (isVowel(input[i]))
                putchar(input[i]);
        }
        printf("\n");
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        printf("Child 2 [PID: %d]: Concatenated String: %s%s\n", getpid(), input, input);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    return 0;
}
