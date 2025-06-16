#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to compare integers for sorting
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Function to merge sorted odd and even indexed elements
void merge_sorted_arrays(int *arr, int *sorted_evens, int *sorted_odds, int size) {
    int even_index = 0, odd_index = 0;
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            arr[i] = sorted_evens[even_index++];
        } 
        else {
            arr[i] = sorted_odds[odd_index++];
        }
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <space-separated integers>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int size = argc - 1;
    int arr[size];

    // Convert command-line arguments to integer array
    for (int i = 0; i < size; i++) {
        arr[i] = atoi(argv[i + 1]);
    }

    // Pipes for communication
    int pipefd1[2], pipefd2[2];
    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        
        close(pipefd1[1]); 
        close(pipefd2[0]); 

        char read_fd_str[10], write_fd_str[10];
        sprintf(read_fd_str, "%d", pipefd1[0]);
        sprintf(write_fd_str, "%d", pipefd2[1]);

        execl("./q2child", "q2child", read_fd_str, write_fd_str, NULL);

        perror("execl");
        exit(EXIT_FAILURE);
        
    } else {  // Parent process
        close(pipefd1[0]);
        close(pipefd2[1]);

        // retrieve odd indexed elements
        int odd[size / 2 + 1], odd_count = 0;
        int even[size / 2 + 1], even_count = 0;

        for (int i = 0; i < size; i++) {
            if (i % 2 == 0) {
                even[even_count++] = arr[i];
            } else {
                odd[odd_count++] = arr[i];
            }
        }

        // Send odd indexed elements to the child
        write(pipefd1[1], odd, odd_count * sizeof(int));
        close(pipefd1[1]); // Close write end after sending data

        
        wait(NULL);

        // Receive sorted odd indexed elements from the child
        read(pipefd2[0], odd, odd_count * sizeof(int));
        close(pipefd2[0]); // Close read end after receiving data

        // Sort even indexed elements
        qsort(even, even_count, sizeof(int), compare);

        
        merge_sorted_arrays(arr, even, odd, size);

        // Print original and sorted arrays
        printf("Original Array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", atoi(argv[i + 1]));
        }
        printf("\n");

        printf("Sorted Array: ");
        for (int i = 0; i < size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        return 0;
    }
}
