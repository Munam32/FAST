#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define NUM_DRONES 5

// Shared tools (1 of each)
pthread_mutex_t wrench = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t screwdriver = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t charger = PTHREAD_MUTEX_INITIALIZER;

// Enum to identify tools
typedef enum { WRENCH, SCREWDRIVER, CHARGER } Tool;

// Tool names for printing
const char* tool_names[] = {"Wrench", "Screwdriver", "Charger"};

// Structure to assign tools to a drone
typedef struct {
    int id;
    Tool tool1;
    Tool tool2;
} Drone;

pthread_mutex_t tool_mutexes[3];

// Tool acquisition order not fixed — can cause deadlock
void pick_tool(Tool t) {
    pthread_mutex_lock(&tool_mutexes[t]);
    printf("Tool %s acquired\n", tool_names[t]);
}

void release_tool(Tool t) {
    pthread_mutex_unlock(&tool_mutexes[t]);
    printf("Tool %s released\n", tool_names[t]);
}

void* drone_routine(void* arg) {
    Drone* drone = (Drone*) arg;
    printf("Drone %d needs %s and %s\n", drone->id,
           tool_names[drone->tool1], tool_names[drone->tool2]);

    while (1) {
        // POTENTIAL DEADLOCK: No enforced ordering of locks
        pick_tool(drone->tool1);
        sleep(1);  // Simulate delay between tool acquisitions
        pick_tool(drone->tool2);

        printf("Drone %d performing maintenance...\n", drone->id);
        sleep(2);  // Simulate work

        release_tool(drone->tool1);
        release_tool(drone->tool2);

        printf("Drone %d finished maintenance\n", drone->id);
        sleep(rand() % 3 + 1);  // Random delay before next cycle
    }

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t drones[NUM_DRONES];
    Drone drone_info[NUM_DRONES];

    // Initialize tool mutexes
    tool_mutexes[WRENCH] = wrench;
    tool_mutexes[SCREWDRIVER] = screwdriver;
    tool_mutexes[CHARGER] = charger;

    // Assign random tools to each drone (two different tools)
    for (int i = 0; i < NUM_DRONES; i++) {
        drone_info[i].id = i;
        drone_info[i].tool1 = rand() % 3;
        do {
            drone_info[i].tool2 = rand() % 3;
        } while (drone_info[i].tool2 == drone_info[i].tool1);
    }

    // Create drone threads
    for (int i = 0; i < NUM_DRONES; i++) {
        pthread_create(&drones[i], NULL, drone_routine, &drone_info[i]);
    }

    // Let the drones run for some time
    sleep(20);

    // Not joining threads or cleaning up — not ideal
    printf("Main thread exiting...\n");
    return 0;
}

