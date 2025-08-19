#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;        // Protects read_count
sem_t wrt;          // Controls writer access
int read_count = 0; // Number of active readers
char data[100] = "Initial data"; // Shared data

void* writer_thread(void* arg) {
    while (1) {
        
        printf("Writer is waiting\n");
        sem_wait(&wrt); 
        
        printf("Writer is writing\n");
        snprintf(data, sizeof(data), "Written by writer at %ld", time(NULL));
        
        sleep(1); // Simulate writing time
        printf("Writer finished: %s\n", data);
        
        sem_post(&wrt); 
        sleep(2); // Wait before next write
    }
    return NULL;
}

void* reader_thread(void* arg) {
    long id = (long)arg;
    
    while (1) {
        sem_wait(&mutex); // Protect read_count
        read_count++;
        
        if (read_count == 1) {
            sem_wait(&wrt); // First reader locks writer
        }
        
        sem_post(&mutex); // Release read_count protection

        printf("Reader %ld is reading: %s\n", id, data);
        sleep(1); // Simulate reading time

        sem_wait(&mutex); // Protect read_count
        read_count--;
        if (read_count == 0) {
            sem_post(&wrt); // Last reader unlocks writer
        }
        sem_post(&mutex); // Release read_count protection

        sleep(2); // Wait before next read
    }
    return NULL;
}

int main() {
    pthread_t writer_t, reader_t1, reader_t2;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create threads
    pthread_create(&writer_t, NULL, writer_thread, NULL);
    pthread_create(&reader_t1, NULL, reader_thread, (void*)1);
    pthread_create(&reader_t2, NULL, reader_thread, (void*)2);

    // Join threads (unreachable in this example as threads run indefinitely)
    pthread_join(writer_t, NULL);
    pthread_join(reader_t1, NULL);
    pthread_join(reader_t2, NULL);

    // Cleanup
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
