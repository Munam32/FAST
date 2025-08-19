#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

void to_uppercase() {
    char ch;
    while (scanf("%c", &ch) != EOF) { // Read characters from stdin
        if (islower(ch)) {
            ch = toupper(ch); // Convert to uppercase
        }
        printf("%c", ch); // Print to stdout
    }
}

int main() {
    int fd = open("original.txt", O_RDWR); // Open file for read/write
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Duplicate the file descriptor for reading (stdin)
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("Error duplicating file descriptor to stdin");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Redirect stdout to a temporary file
    int temp_fd = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp_fd == -1) {
        perror("Error creating temporary file");
        close(fd);
        exit(EXIT_FAILURE);
    }

    if (dup2(temp_fd, STDOUT_FILENO) == -1) {
        perror("Error duplicating file descriptor to stdout");
        close(fd);
        close(temp_fd);
        exit(EXIT_FAILURE);
    }

    to_uppercase(); // Process and convert content

    close(fd);
    close(temp_fd);

    // Replace original file with the temporary file
    if (rename("temp.txt", "original.txt") == -1) {
        perror("Error replacing original file with temporary file");
        exit(EXIT_FAILURE);
    }

    printf("File content updated to uppercase successfully.\n");
    return 0;
}

