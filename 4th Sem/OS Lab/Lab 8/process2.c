#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "shared.h"

int main() {
    int shmid = shmget(SHM_KEY, sizeof(ProcessData) * NUM_PROCESSES + sizeof(float), 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    void* shm_ptr = shmat(shmid, NULL, 0);
    if (shm_ptr == (void*)-1) {
        perror("shmat failed");
        exit(1);
    }

    ProcessData* data = (ProcessData*)shm_ptr;
    float* avg_ptr = (float*)(data + NUM_PROCESSES);

    FILE* file = fopen("file2.txt", "r");
    if (!file) {
        perror("file2.txt");
        exit(1);
    }

    int sum = 0, count = 0, val;
    while (fscanf(file, "%d", &val) != EOF) {
        sum += val;
        count++;
    }
    fclose(file);

    data[1].sum = sum;
    data[1].count = count;

    while (*avg_ptr == 0.0f) sleep(1);

    printf("Process 2 sum: %d, count: %d, average: %.2f\n", sum, count, *avg_ptr);

    shmdt(shm_ptr);
    return 0;
}
