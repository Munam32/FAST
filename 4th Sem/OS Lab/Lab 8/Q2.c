#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 100

int buffer[SIZE], in = 0, out = 0, count = 0;
int done = 0;

sem_t empty, full, mutex;

void* producer(void* arg) {
    for (int i = 0; i < SIZE; i++) {
        int num = rand() % 6 + 1;
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = num;
        in = (in + 1) % SIZE;
        count++;

        printf("Number %d\n", num);

        sem_post(&mutex);
        sem_post(&full);
        usleep(10000); // simulate work
    }
    done = 1;
    return NULL;
}

void* consumer(void* arg) {
    int sum = 0, nonSix = 0;
    while (!done || count > 0) {
        sem_wait(&full);
        sem_wait(&mutex);

        int num = buffer[out];
        out = (out + 1) % SIZE;
        count--;

        if (num == 6) {
            printf("Sum %d\n", sum);
            sum = 0;
            nonSix = 0;
        } else {
            sum += num;
            nonSix++;
            if (nonSix == 10) {
                printf("Sum %d\n", sum);
                nonSix = 0;
            }
        }

        sem_post(&mutex);
        sem_post(&empty);
        usleep(10000);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    return 0;
}
