#ifndef SHARED_H
#define SHARED_H

#define SHM_KEY 1234
#define NUM_PROCESSES 2

typedef struct {
    int sum;
    int count;
} ProcessData;

#endif

