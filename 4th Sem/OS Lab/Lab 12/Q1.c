#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void fork_tree(int level, int max_level) {
    if (level >= max_level) {
        // We've reached the maximum depth; no further forks.
        return;
    }

    // Create two child processes.
    for (int i = 0; i < 2; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            // Fork failed, print an error message and exit.
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // In the child process: print information and recursively fork further.
            printf("Process at level %d: PID = %d, Parent PID = %d\n", level + 1, getpid(), getppid());
            // Recursively create the subtree from this child.
            fork_tree(level + 1, max_level);
            // Child exits after finishing its branch.
            exit(EXIT_SUCCESS);
        }
        // If pid > 0, we are in the parent process; continue to create the next child.
    }

    // Parent process waits for its two children to terminate.
    for (int i = 0; i < 2; ++i) {
        int status;
        if (wait(&status) < 0) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    const int max_level = 3;  // Set the desired height of the binary fork tree.
    
    printf("Root process: PID = %d\n", getpid());
    
    // Start at level 1 (the root is already running in main)
    fork_tree(0, max_level);
    
    return 0;
}
