#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to remove special characters and numbers
void proofread_document(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i]) || isspace(input[i])) {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int pipefd1[2], pipefd2[2];
    pid_t pid;

    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Student process
        close(pipefd1[1]); // Close unused write end
        close(pipefd2[0]); // Close unused read end

        char buffer[BUFFER_SIZE];
        char cleaned_buffer[BUFFER_SIZE];
        
        read(pipefd1[0], buffer, BUFFER_SIZE);
        proofread_document(buffer, cleaned_buffer);
        write(pipefd2[1], cleaned_buffer, strlen(cleaned_buffer) + 1);

        close(pipefd1[0]);
        close(pipefd2[1]);
        
        
        exit(EXIT_SUCCESS);
    } 
    else {  // Teacher process
        close(pipefd1[0]); // Close unused read end
        close(pipefd2[1]); // Close unused write end

        FILE *file = fopen(argv[1], "r");
        
        if (file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE];
        
        fread(buffer, sizeof(char), BUFFER_SIZE, file);
        fclose(file);

        write(pipefd1[1], buffer, strlen(buffer) + 1);
        wait(NULL);

        char cleaned_buffer[BUFFER_SIZE];
        read(pipefd2[0], cleaned_buffer, BUFFER_SIZE);
        printf("Proofread Document:\n%s\n", cleaned_buffer);

        close(pipefd1[1]);
        close(pipefd2[0]);
    }

    return 0;
}
