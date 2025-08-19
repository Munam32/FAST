#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void find_even_numbers() {
    int start, end;

    // Read the range from standard input (redirected from pipe's read end)
    if (scanf("%d %d", &start, &end) != 2) {
        fprintf(stderr, "Error reading range\n");
        exit(1);
    }

    // Print even numbers within the range
    for (int i = start; i <= end; i++) {
        if (i % 2 == 0) {
            printf("%d\n", i);
        }
    }
    fflush(stdout); // Ensure output is flushed
}

int main() {
    int input_fd = open("input.txt", O_RDONLY);
    if (input_fd < 0) {
        perror("Error opening input file");
        return 1;
    }

    int output_fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_fd < 0) {
        perror("Error opening output file");
        close(input_fd);
        return 1;
    }

    int pipe_fd[2];
    if (pipe(pipe_fd) < 0) {
        perror("Pipe creation failed");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    if (pid == 0) { // Child process
        close(pipe_fd[1]);            // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe's read end
        dup2(output_fd, STDOUT_FILENO); // Redirect stdout to output.txt
        close(pipe_fd[0]);
        close(output_fd);

        find_even_numbers(); // Perform the task
        exit(0);
    } else { // Parent process
        close(pipe_fd[0]);             // Close read end of the pipe
        dup2(input_fd, STDIN_FILENO);  // Redirect stdin to input.txt
        close(input_fd);

        // Pass the range from input.txt to the child process through the pipe
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            dprintf(pipe_fd[1], "%s", buffer); // Write to pipe using standard I/O
        }

        close(pipe_fd[1]); // Close write end of the pipe after sending data

        wait(NULL); // Wait for the child process to finish
        close(output_fd); // Close the output file descriptor
    }

    return 0;
}
