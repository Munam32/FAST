#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CUSTOMERS 20
#define MAX_INSIDE    5

int current_ticket     = 1;
int served_customers   = 0;
int served_concessions = 0;
int total_revenue      = 0;

sem_t sem_entry;        
sem_t sem_seller;       
sem_t sem_concession;   

pthread_mutex_t revenue_lock = PTHREAD_MUTEX_INITIALIZER; 

void* customer_thread(void* arg) {
    int id = *(int*)arg;
    free(arg); 

    sem_wait(&sem_entry); // Ensure max 5 customers inside the booth

    // Enforce consistent acquisition order to prevent deadlock
    sem_wait(&sem_seller);
    sem_wait(&sem_concession);

    pthread_mutex_lock(&revenue_lock); // Protect shared counters
    int ticket = current_ticket++;
    total_revenue += 10;
    served_customers++;

    if (id % 2 == 0) { 
        served_concessions++;
        total_revenue += 5;
    }
    pthread_mutex_unlock(&revenue_lock);

    sem_post(&sem_concession); 
    sem_post(&sem_seller);     
    sem_post(&sem_entry);      

    pthread_exit(0);
}

int main() {
    pthread_t threads[MAX_CUSTOMERS];
    int *pid;

    
    sem_init(&sem_entry,      0, MAX_INSIDE);
    sem_init(&sem_seller,     0, 2);
    sem_init(&sem_concession, 0, 1);

    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        pid = malloc(sizeof(int));
        if (pid == NULL) { // Check return value of malloc
            perror("Failed to allocate memory");
            exit(EXIT_FAILURE);
        }
        *pid = i + 1;
        if (pthread_create(&threads[i], NULL, customer_thread, pid) != 0) { // Check thread creation
            perror("Failed to create thread");
            free(pid);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) { // Check thread joining
            perror("Failed to join thread");
            exit(EXIT_FAILURE);
        }
    }

    printf("Served: customers=%d  concessions=%d  revenue=$%d  next_ticket=%d\n",
           served_customers, served_concessions, total_revenue, current_ticket);

    // Clean up semaphores
    sem_destroy(&sem_entry);
    sem_destroy(&sem_seller);
    sem_destroy(&sem_concession);
    pthread_mutex_destroy(&revenue_lock);

    return 0;
}

