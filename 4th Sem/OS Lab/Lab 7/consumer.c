#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_SIZE 21
#define SEM_PRODUCER 0
#define SEM_CONSUMER 1

// Semaphore operation function
void semOp(int semid, int sem_num, int op) {
    struct sembuf sops = {sem_num, op, 0};
    semop(semid, &sops, 1);
}

int main() {
    // Access shared memory
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666);
    char *shm = (char *)shmat(shmid, NULL, 0);

    // Access semaphores
    int semid = semget(key, 2, 0666);

    while (1) {
        // Wait for producer to write data
        semOp(semid, SEM_CONSUMER, -1);

        if (shm[0] == '$') break; // End of file reached

        // Display data
        printf("Received: %s", shm);
        printf("\nPress ENTER to continue...");
        getchar();

        // Signal the producer
        semOp(semid, SEM_PRODUCER, 1);
    }

    // Cleanup
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL); // Remove shared memory
    semctl(semid, 0, IPC_RMID);    // Remove semaphores

    return 0;
}
