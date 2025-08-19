#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Global variables
int* array;
int ARRAY_SIZE;
int min1, max1, min2, max2, min3, max3;

// Function executed by each thread
void* find_min_max(void* arg) {
    int thread_id = *((int*)arg);
    int segment_size = ARRAY_SIZE / 3;
    int start = thread_id * segment_size;
    int end = (thread_id == 2) ? ARRAY_SIZE : (thread_id + 1) * segment_size;
    int local_min = array[start];
    int local_max = array[start];

    for (int i = start; i < end; i++) {
        if (array[i] < local_min) {
            local_min = array[i];
        }
        if (array[i] > local_max) {
            local_max = array[i];
        }
    }

    // Store results in global variables (thread-specific)
    if (thread_id == 0) {
        min1 = local_min;
        max1 = local_max;
    } else if (thread_id == 1) {
        min2 = local_min;
        max2 = local_max;
    } else {
        min3 = local_min;
        max3 = local_max;
    }

    pthread_exit(NULL);
}

int main() {
    // Manual Assignment of thread id for segment allocation
    pthread_t threads[3];
    int thread_ids[3] = {0, 1, 2};
    int result;

    // Get array size from user
    printf("Enter the size of the array: ");
    scanf("%d", &ARRAY_SIZE);

    // Validate array size
    if (ARRAY_SIZE < 3) {
        printf("Array size must be at least 3 for 3 threads\n");
        return 1;
    }

    // Allocate dynamic array
    array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    if (array == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Get array elements from user
    printf("Enter %d integers:\n", ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        scanf("%d", &array[i]);
    }

    // Create all threads first
    for (int i = 0; i < 3; i++) {
        result = pthread_create(&threads[i], NULL, find_min_max, &thread_ids[i]);
        if (result != 0) {
            perror("Failed to create thread");
            free(array);
            return 1;
        }
    }

    // Join all threads
    for (int i = 0; i < 3; i++) {
        result = pthread_join(threads[i], NULL);
        if (result != 0) {
            perror("Failed to join thread");
            free(array);
            return 1;
        }
    }

    // Find global min and max from thread results
    int global_min = (min1 < min2) ? min1 : min2;
    global_min = (global_min < min3) ? global_min : min3;
    
    int global_max = (max1 > max2) ? max1 : max2;
    global_max = (global_max > max3) ? global_max : max3;

    // Print results
    printf("Original array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("Global Minimum: %d\n", global_min);
    printf("Global Maximum: %d\n", global_max);

    // Free allocated memory
    free(array);
    return 0;
}