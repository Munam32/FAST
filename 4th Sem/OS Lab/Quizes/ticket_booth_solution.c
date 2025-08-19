// Compile with: gcc -std=c11 -pthread ticket_booth_fixed.c -o ticket_booth_fixed

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <errno.h>

#define MAX_CUSTOMERS 20
#define MAX_INSIDE     5

/* Shared state */
int current_ticket     = 1;
int served_customers   = 0;
int served_concessions = 0;
int total_revenue      = 0;

/* Semaphores */
sem_t sem_entry;       // limits customers inside
sem_t sem_seller;      // limits concurrent ticket sellers
sem_t sem_concession;  // limits concurrent concession service

/* Mutex to protect all shared counters */
pthread_mutex_t revenue_lock = PTHREAD_MUTEX_INITIALIZER;

/* Utility to check return codes */
static void check(int ret, const char *msg) {
    if (ret != 0) {
        errno = ret;
        perror(msg);
        exit(EXIT_FAILURE);
    }
}

void* customer_thread(void* arg) {
    int id = *(int*)arg;
    free(arg);

    /* 1) Limit number of customers inside */
    check(sem_wait(&sem_entry), "sem_wait entry");

    /*
     * 2) Consistent acquisition order to avoid deadlock:
     *    ALWAYS seller → concession
     */
    check(sem_wait(&sem_seller), "sem_wait seller");
    check(sem_wait(&sem_concession), "sem_wait concession");

    /* 3) Critical section: assign ticket and update revenue */
    check(pthread_mutex_lock(&revenue_lock), "pthread_mutex_lock");
    {
        int ticket = current_ticket++;
        total_revenue += 10;
        served_customers++;
        printf("Customer %2d got ticket %3d (+$10)\n", id, ticket);
    }
    check(pthread_mutex_unlock(&revenue_lock), "pthread_mutex_unlock");

    /* 4) Concession for even‐ID customers */
    if (id % 2 == 0) {
        /* Already hold sem_concession; now update shared state */
        check(pthread_mutex_lock(&revenue_lock), "pthread_mutex_lock");
        {
            served_concessions++;
            total_revenue += 5;
            printf("    Customer %2d bought concession (+$5)\n", id);
        }
        check(pthread_mutex_unlock(&revenue_lock), "pthread_mutex_unlock");
    }

    /* 5) Release in reverse order */
    check(sem_post(&sem_concession), "sem_post concession");
    check(sem_post(&sem_seller),    "sem_post seller");
    check(sem_post(&sem_entry),     "sem_post entry");

    return NULL;
}

int main() {
    pthread_t threads[MAX_CUSTOMERS];

    /* 6) Initialize semaphores and check errors */
    check(sem_init(&sem_entry,      0, MAX_INSIDE), "sem_init entry");
    check(sem_init(&sem_seller,     0, 2),          "sem_init seller");
    check(sem_init(&sem_concession, 0, 1),          "sem_init concession");

    /* 7) Spawn customer threads */
    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        int *pid = malloc(sizeof(int));
        if (!pid) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *pid = i + 1;
        check(pthread_create(&threads[i], NULL, customer_thread, pid),
              "pthread_create");
    }

    /* 8) Join all threads */
    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        check(pthread_join(threads[i], NULL), "pthread_join");
    }

    /* 9) Final report */
    printf("\nFINAL COUNTS:\n");
    printf("  Served customers:   %d (expected %d)\n",
           served_customers,   MAX_CUSTOMERS);
    printf("  Served concessions: %d (expected %d)\n",
           served_concessions, MAX_CUSTOMERS/2);
    printf("  Total revenue:      $%d\n", total_revenue);

    /* 10) Clean up */
    check(sem_destroy(&sem_entry),      "sem_destroy entry");
    check(sem_destroy(&sem_seller),     "sem_destroy seller");
    check(sem_destroy(&sem_concession), "sem_destroy concession");
    check(pthread_mutex_destroy(&revenue_lock), "pthread_mutex_destroy");

    return 0;
}

