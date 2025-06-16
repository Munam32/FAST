#include <stdio.h>
#include <stdlib.h>

void removeCapitalAlphabets(char *inputFileName, char *outputFileName) {
    FILE *fin = fopen(inputFileName, "r");
    if (fin == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }
    
    FILE *fout = fopen(outputFileName, "w");
    if (fout == NULL) {
        perror("Error opening output file");
        fclose(fin);
        exit(EXIT_FAILURE);
    }
    
    int ch;
    // Read the input file character by character tiil end of file.
    while ((ch = fgetc(fin)) != EOF) {
        // If the character is a capital letter (A-Z), skip writing it.
        if (ch >= 'A' && ch <= 'Z') {
            continue;
        }
        fputc(ch, fout);
    }
    
    // Close both files.
    fclose(fin);
    fclose(fout);
}

int main(int argc, char *argv[]) {
    // Ensure that exactly two command line arguments are provided (input and output file names).
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <inputFile> <outputFile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    // Remove capital alphabets from the input file and write to the output file.
    removeCapitalAlphabets(argv[1], argv[2]);
    
    printf("Successfully removed capital alphabets from '%s' and saved the result to '%s'.\n", argv[1], argv[2]);
    return 0;
}
