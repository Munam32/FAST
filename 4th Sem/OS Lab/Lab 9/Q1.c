#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define WAITING_CHAIRS 5


sem_t customers;        // Signals when customers are waiting
sem_t barber;          // Signals when barber is ready
sem_t mutex;           // Protects access to waiting_chairs
int waiting_chairs = 0; // Number of customers waiting

void* barber_thread(void* arg) {
    while (1) {
        sem_wait(&customers); // Wait for a customer
        sem_wait(&mutex);    // Acquire mutex to update waiting_chairs
        waiting_chairs--;    // Customer is being served
        sem_post(&barber);   // Signal barber is ready
        sem_post(&mutex);    // Release mutex

        printf("Barber is cutting hair\n");
        sleep(2); // Simulate haircut time
        printf("Barber finished cutting hair\n");
    }
    return NULL;
}

void* customer_thread(void* arg) {
    long id = (long)arg;
    sem_wait(&mutex); // Acquire mutex to check waiting_chairs
    
    if (waiting_chairs < WAITING_CHAIRS) {
        waiting_chairs++; // Occupy a waiting chair
        printf("Customer %ld is waiting (%d waiting)\n", id + 1, waiting_chairs);
        
        sem_post(&customers); // Signal a customer is waiting
        sem_post(&mutex);     // Release mutex
        sem_wait(&barber);    // Wait for barber
        
        printf("Customer %ld is getting haircut\n", id + 1);
    } else {
        sem_post(&mutex); // Release mutex
        printf("Customer %ld left (no chairs available)\n", id + 1);
    }
    return NULL;
}

int main() {
    long i,MAX_CUSTOMERS;
    
    printf("Enter Maximum Customers: ");
    scanf("%ld",&MAX_CUSTOMERS);
    printf("\n");
    

    pthread_t barber_t;
    pthread_t customers_t[MAX_CUSTOMERS];
    
    
    // Initialize semaphores
    sem_init(&customers, 0, 0);
    sem_init(&barber, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create barber thread
    pthread_create(&barber_t, NULL, barber_thread, NULL);

    // Create customer threads
    for (i = 0; i < MAX_CUSTOMERS; i++) {
        pthread_create(&customers_t[i], NULL, customer_thread, (void*)i);
        sleep(1); // Simulate customers arriving at intervals
    }

    // Join customer threads
    for (i = 0; i < MAX_CUSTOMERS; i++) {
        pthread_join(customers_t[i], NULL);
    }

    // Cleanup
    sem_destroy(&customers);
    sem_destroy(&barber);
    sem_destroy(&mutex);

    return 0;
}
