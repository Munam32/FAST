// used forks instead of threads
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <cstdlib>
#include <ctime>
using namespace std;

class PrintShop {
private:
    sem_t* machineSemaphore; // Binary semaphore for machine access
    sem_t* inkSemaphore;     // Counting semaphore for ink cartridges

public:
    PrintShop() {
        machineSemaphore = sem_open("/machine_semaphore", O_CREAT, 0644, 1);
        inkSemaphore = sem_open("/ink_semaphore", O_CREAT, 0644, 2);
    }

    ~PrintShop() {
        sem_close(machineSemaphore);
        sem_close(inkSemaphore);
        sem_unlink("/machine_semaphore");
        sem_unlink("/ink_semaphore");
    }

    void print(int machineId) {
        cout << "Machine " << machineId << " is waiting to print.\n";

        // Acquire binary semaphore for machine access
        sem_wait(machineSemaphore);
        cout << "Machine " << machineId << " has acquired the machine access.\n";

        // Acquire ink cartridge if available
        if (sem_trywait(inkSemaphore) == 0) {
            cout << "Machine " << machineId << " acquired an ink cartridge and is printing.\n";
            sleep(rand() % 3 + 1); // Simulate printing time
            cout << "Machine " << machineId << " has finished printing.\n";

            // Release the ink cartridge
            sem_post(inkSemaphore);
        } else {
            cout << "Machine " << machineId << " could not acquire an ink cartridge and is waiting.\n";
        }

        // Release the machine access
        sem_post(machineSemaphore);
    }
};

int main() {
    srand(time(0));
    PrintShop printShop;

    for (int i = 1; i <= 5; ++i) {
        pid_t pid = fork();

        if (pid == 0) { // Child process
            printShop.print(i);
            exit(0);
        }
    }

    for (int i = 1; i <= 5; ++i) {
        wait(NULL); // Wait for all child processes to finish
    }

    return 0;
}






// Using Threads
// #include <stdio.h>
// #include <pthread.h>
// #include <semaphore.h>
// #include <unistd.h>      // For sleep()
// #include <stdlib.h>      // For rand()

// // Semaphores
// sem_t machineSemaphore; // Binary semaphore for machine access
// sem_t inkSemaphore;     // Counting semaphore for ink cartridges (2 slots)

// // PrintShop function
// void* print(void* arg) {
//     int machineId = *((int*)arg);

//     printf("Machine %d is waiting to print.\n", machineId);

//     // Acquire machine access
//     sem_wait(&machineSemaphore);
//     printf("Machine %d acquired machine access.\n", machineId);

//     // Check ink cartridge availability
//     if (sem_trywait(&inkSemaphore) == 0) {
//         printf("Machine %d acquired an ink cartridge. Printing...\n", machineId);

//         // Simulate printing with random delay
//         sleep(rand() % 3 + 1);

//         printf("Machine %d finished printing.\n", machineId);

//         // Release ink cartridge
//         sem_post(&inkSemaphore);
//     } else {
//         printf("Machine %d could not print (no ink cartridge available).\n", machineId);
//     }

//     // Release machine access
//     sem_post(&machineSemaphore);

//     return NULL;
// }

// int main() {
//     pthread_t machines[5];
//     int machineIds[5];

//     // Initialize semaphores
//     sem_init(&machineSemaphore, 0, 1);  // Binary semaphore for machine access
//     sem_init(&inkSemaphore, 0, 2);      // Counting semaphore for 2 ink cartridges

//     // Create machine threads
//     for (int i = 0; i < 5; i++) {
//         machineIds[i] = i + 1;
//         pthread_create(&machines[i], NULL, print, &machineIds[i]);
//     }

//     // Wait for all threads to finish
//     for (int i = 0; i < 5; i++) {
//         pthread_join(machines[i], NULL);
//     }

//     // Clean up
//     sem_destroy(&machineSemaphore);
//     sem_destroy(&inkSemaphore);

//     printf("All machines have finished their tasks.\n");

//     return 0;
// }
