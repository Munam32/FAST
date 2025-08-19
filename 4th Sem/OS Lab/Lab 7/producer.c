#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <string.h>

#define SHM_SIZE 21  // 20 characters + null terminator
#define SEM_PRODUCER 0
#define SEM_CONSUMER 1

// Semaphore operation function
void semOp(int semid, int sem_num, int op) {
    struct sembuf sops = {sem_num, op, 0};
    semop(semid, &sops, 1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source_file>\n", argv[0]);
        return 1;
    }

    // Open the source file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Create shared memory
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    char *shm = (char *)shmat(shmid, NULL, 0);

    // Create semaphores
    int semid = semget(key, 2, IPC_CREAT | 0666);
    semctl(semid, SEM_PRODUCER, SETVAL, 1); // Producer starts first
    semctl(semid, SEM_CONSUMER, SETVAL, 0);  // Consumer waits

    char buffer[21];  // 20 characters + null terminator
    while (fgets(buffer, 21, file)) {
        // Producer waits for its turn
        semOp(semid, SEM_PRODUCER, -1);

        // Write data to shared memory
        strcpy(shm, buffer);

        // Signal the consumer
        semOp(semid, SEM_CONSUMER, 1);
    }

    // Indicate EOF with '$'
    semOp(semid, SEM_PRODUCER, -1);
    strcpy(shm, "$");
    semOp(semid, SEM_CONSUMER, 1);

    // Cleanup
    shmdt(shm);
    fclose(file);

    return 0;
}
