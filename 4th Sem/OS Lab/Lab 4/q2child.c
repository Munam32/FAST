#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Function to compare integers for sorting, using q sort so must type cast generic pointers to int and then de-reference them
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <read_pipe_fd> <write_pipe_fd>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int read_fd = atoi(argv[1]);
    int write_fd = atoi(argv[2]);

    int buffer[1024];
    int count = read(read_fd, buffer, sizeof(buffer));

    if (count < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    int num_elements = count / sizeof(int);

    // Sort odd-indexes
    qsort(buffer, num_elements, sizeof(int), compare);

    // Send sorted data back to parent
    write(write_fd, buffer, num_elements * sizeof(int));

    close(read_fd);
    close(write_fd);

    return 0;
}
