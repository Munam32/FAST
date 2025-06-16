#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include "shared.h"

int main() {
    int shmid = shmget(SHM_KEY, sizeof(ProcessData) * NUM_PROCESSES + sizeof(float), IPC_CREAT | 0666);
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

    printf("Server waiting for both processes...\n");

    while (data[0].count == 0 || data[1].count == 0) {
        sleep(1);
    }

    int totalSum = data[0].sum + data[1].sum;
    int totalCount = data[0].count + data[1].count;
    float average = (float)totalSum / totalCount;

    *avg_ptr = average;

    printf("Server computed average: %.2f\n", average);

    shmdt(shm_ptr);
    // Remove shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
