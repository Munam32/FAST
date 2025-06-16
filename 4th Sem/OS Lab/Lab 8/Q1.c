#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#define NUM_THREADS 3

typedef struct {
    char ch;
    int count;
    int order_index;
} ThreadInfo;

sem_t sems[NUM_THREADS];
ThreadInfo threadInfos[NUM_THREADS];
int repeat;

void* thread_func(void* arg) {
    ThreadInfo* info = (ThreadInfo*)arg;

    for (int r = 0; r < repeat; r++) {
        sem_wait(&sems[info->order_index]);

        for (int i = 0; i < info->count; i++) {
            printf("%c", info->ch);
            fflush(stdout);
        }

        int next = (info->order_index + 1) % NUM_THREADS;
        sem_post(&sems[next]);
    }

    return NULL;
}

int char_to_index(char ch) {
    return ch - 'a'; // a -> 0, b -> 1, c -> 2
}

int main(int argc, char* argv[]) {
    if (argc != 8) {
        printf("Usage: ./q1 <char1> <count1> <char2> <count2> <char3> <count3> <repeat>\n");
        return 1;
    }

    repeat = atoi(argv[7]);

    int used[NUM_THREADS] = {0};
    for (int i = 0; i < NUM_THREADS; i++) {
        char ch = argv[1 + i * 2][0];
        int count = atoi(argv[2 + i * 2]);
        int index = char_to_index(ch);

        if (used[index]) {
            fprintf(stderr, "Duplicate character in arguments.\n");
            return 1;
        }
        used[index] = 1;

        threadInfos[index].ch = ch;
        threadInfos[index].count = count;
        threadInfos[index].order_index = i; // order according to appearance
    }

    for (int i = 0; i < NUM_THREADS; i++)
        sem_init(&sems[i], 0, i == 0 ? 1 : 0); // first in order gets to start

    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, thread_func, &threadInfos[i]);

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < NUM_THREADS; i++)
        sem_destroy(&sems[i]);

    return 0;
}

