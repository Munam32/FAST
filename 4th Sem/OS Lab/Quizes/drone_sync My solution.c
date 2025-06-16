#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

#define NUM_DRONES 5
#define MAX_CYCLES 5

// changing Initialization for effective usage
typedef enum { WRENCH, SCREWDRIVER, CHARGER } Tool;
const char* tool_names[] = { "Wrench", "Screwdriver", "Battery Charger" };

typedef struct {
    int id;
    Tool tool1;
    Tool tool2;
} Drone;

// Semaphores for the shared tools
sem_t tool_semaphores[3];

// Mutex for queue-based fairness
pthread_mutex_t queue_lock;

void* drone_routine(void* arg) {
    Drone* drone = (Drone*) arg;
    int cycles = 0;

    //using MAX_CYCLES in order to remove infinite looping + implemented picka nad release tools in the loop
    while (cycles < MAX_CYCLES) {
        printf("Drone %d needs %s and %s\n", (drone->id) + 1,
               tool_names[drone->tool1], tool_names[drone->tool2]);


        // Lock queue to ensure fairness in picking tools
        pthread_mutex_lock(&queue_lock);

        // Acquire tools in any order, but guarantee fairness
        sem_wait(&tool_semaphores[drone->tool1]);
        sem_wait(&tool_semaphores[drone->tool2]);

        //releasing 
        pthread_mutex_unlock(&queue_lock);

        // Perform maintenance 
        printf("Drone %d acquired %s and %s, performing maintenance...\n",
               (drone->id)+1, tool_names[drone->tool1], tool_names[drone->tool2]);
        
        sleep(2); // Simulate maintenance work for drones

        // Release tools for other drones
        sem_post(&tool_semaphores[drone->tool1]);
        sem_post(&tool_semaphores[drone->tool2]);
        printf("Drone %d finished maintenance cycle %d.\n", (drone->id)+1, cycles + 1);

        sleep(rand() % 3 + 1);
        cycles++;
    }

    printf("Drone %d completed all cycles and is exiting.\n", (drone->id)+1);
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t drones[NUM_DRONES];
    Drone drone_info[NUM_DRONES];

    // Initialize semaphores (1 tool available at a time)
    for (int i = 0; i < 3; i++) {
        sem_init(&tool_semaphores[i], 0, 1);
    }

    // Initialize queue fairness lock
    pthread_mutex_init(&queue_lock, NULL);

    // Assign drones random but distinct tool pairs
    for (int i = 0; i < NUM_DRONES; i++) {
        drone_info[i].id = i;
        drone_info[i].tool1 = rand() % 3;
        
        do {
            drone_info[i].tool2 = rand() % 3;
        } while (drone_info[i].tool2 == drone_info[i].tool1);
    }

    // Create drone threads
    for (int i = 0; i < NUM_DRONES; i++) {
        if (pthread_create(&drones[i], NULL, drone_routine, &drone_info[i]) != 0) {
            fprintf(stderr, "Error creating thread for drone %d.\n", i+1);
            exit(1);
        }
    }

    // Wait for all drones to finish
    for (int i = 0; i < NUM_DRONES; i++) {
        pthread_join(drones[i], NULL);
    }

    // Clean up semaphores and mutexes
    for (int i = 0; i < 3; i++) {
        sem_destroy(&tool_semaphores[i]);
    }
    pthread_mutex_destroy(&queue_lock);

    printf("Main thread Exiting...\n");
    return 0;
}
