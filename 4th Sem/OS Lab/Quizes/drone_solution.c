#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_DRONES 5
#define NUM_TOOLS 3

// Tool identifiers
typedef enum { WRENCH = 0, SCREWDRIVER = 1, CHARGER = 2 } Tool;
const char* tool_names[] = { "Wrench", "Screwdriver", "Charger" };

// Mutex for each tool
pthread_mutex_t tool_mutexes[NUM_TOOLS];

// Structure for each drone
typedef struct {
    int id;
    Tool tool1;
    Tool tool2;
} Drone;

// Drone routine
void* drone_routine(void* arg) {
    Drone* d = (Drone*)arg;

    // Determine acquisition order to prevent deadlock
    Tool first = (d->tool1 < d->tool2) ? d->tool1 : d->tool2;
    Tool second = (d->tool1 < d->tool2) ? d->tool2 : d->tool1;

    for (int i = 0; i < 3; ++i) {  // Each drone runs 3 times
        printf("Drone %d wants tools %s and %s\n", d->id, tool_names[d->tool1], tool_names[d->tool2]);

        // Lock in fixed order (lower tool ID first)
        pthread_mutex_lock(&tool_mutexes[first]);
        printf("Drone %d acquired %s\n", d->id, tool_names[first]);

        sleep(1); // Simulate delay — safe due to ordering

        pthread_mutex_lock(&tool_mutexes[second]);
        printf("Drone %d acquired %s\n", d->id, tool_names[second]);

        // Perform maintenance
        printf("Drone %d is performing maintenance...\n", d->id);
        sleep(2);

        // Release both tools
        pthread_mutex_unlock(&tool_mutexes[second]);
        pthread_mutex_unlock(&tool_mutexes[first]);
        printf("Drone %d released both tools\n", d->id);

        sleep(rand() % 3 + 1); // Random delay before next cycle
    }

    printf("Drone %d completed all maintenance tasks.\n", d->id);
    return NULL;
}

int main() {
    srand(time(NULL));

    pthread_t drones[NUM_DRONES];
    Drone drone_info[NUM_DRONES];

    // Initialize tool mutexes
    for (int i = 0; i < NUM_TOOLS; ++i) {
        pthread_mutex_init(&tool_mutexes[i], NULL);
    }

    // Assign random tool pairs to drones (2 different tools)
    for (int i = 0; i < NUM_DRONES; ++i) {
        Tool t1 = rand() % NUM_TOOLS;
        Tool t2;
        do {
            t2 = rand() % NUM_TOOLS;
        } while (t2 == t1);

        drone_info[i].id = i;
        drone_info[i].tool1 = t1;
        drone_info[i].tool2 = t2;

        pthread_create(&drones[i], NULL, drone_routine, &drone_info[i]);
    }

    // Wait for drones to complete
    for (int i = 0; i < NUM_DRONES; ++i) {
        pthread_join(drones[i], NULL);
    }

    // Cleanup
    for (int i = 0; i < NUM_TOOLS; ++i) {
        pthread_mutex_destroy(&tool_mutexes[i]);
    }

    printf("All drones completed maintenance.\n");
    return 0;
}

