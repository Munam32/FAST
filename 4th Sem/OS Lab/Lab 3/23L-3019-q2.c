
// q2.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

bool isPrime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        printf("Child 1 [PID: %d]: Square of %d is %d\n", getpid(), num1, num1 * num1);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        if (isPrime(num2))
            printf("Child 2 [PID: %d]: %d is a prime number.\n", getpid(), num2);
        else
            printf("Child 2 [PID: %d]: %d is not a prime number.\n", getpid(), num2);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    return 0;
}
