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

    sem_wait(&sem_entry);

    if (id % 2 == 0) {
        sem_wait(&sem_concession);
        sem_wait(&sem_seller);
    } else {
        sem_wait(&sem_seller);
        sem_wait(&sem_concession);
    }

    int ticket = current_ticket++;
    total_revenue += 10;
    served_customers++;

    if (id % 2 == 0) {
        served_concessions++;
        total_revenue += 5;
    }

    sem_post(&sem_seller);
    sem_post(&sem_concession);
    sem_post(&sem_entry);

    return NULL;
}

int main() {
    pthread_t threads[MAX_CUSTOMERS];

    sem_init(&sem_entry,      0, MAX_INSIDE);
    sem_init(&sem_seller,     0, 2);
    sem_init(&sem_concession, 0, 1);

    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        int *pid = malloc(sizeof(int));
        *pid = i + 1;
        pthread_create(&threads[i], NULL, customer_thread, pid);
    }

    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Served: customers=%d  concessions=%d  revenue=$%d  next_ticket=%d\n",
           served_customers, served_concessions, total_revenue, current_ticket);

    return 0;
}

