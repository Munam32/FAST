#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    // Check if a course code was provided as a command-line argument
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <CourseCode>\n", argv[0]);
        return 1;
    }
    
    // Print the welcome message with the provided course code
    printf("Welcome to %s Operating System Lab Course\n", argv[1]);
    
    return 0;
}
