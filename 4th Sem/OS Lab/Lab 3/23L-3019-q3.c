
// q3.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <array of integers>\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int arr[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = atoi(argv[i + 1]);
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        int sum = 0;
        for (int i = 0; i < n; ++i) sum += arr[i];
        printf("Child 1 [PID: %d]: Sum = %d\n", getpid(), sum);
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        int sum = 0;
        for (int i = 0; i < n; ++i) sum += arr[i];
        printf("Child 2 [PID: %d]: Average = %.2f\n", getpid(), (float)sum / n);
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        int min = INT_MAX, max = INT_MIN;
        for (int i = 0; i < n; ++i) {
            if (arr[i] < min) min = arr[i];
            if (arr[i] > max) max = arr[i];
        }
        printf("Child 3 [PID: %d]: Min = %d, Max = %d\n", getpid(), min, max);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);
    return 0;
}
