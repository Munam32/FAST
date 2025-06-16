#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if at least one number is provided.
    if (argc < 2) {
        fprintf(stderr, "Usage: %s num1 num2 ...\n", argv[0]);
        return 1;
    }
    
    // Use a long long for multiplication to handle larger numbers.
    long long product = 1;
    int num = 0;

    // Iterate through each argument (starting from argv[1])
    for (int i = 1; i < argc; i++) {

        // Convert the argument to an integer.
        // Using atoi function to return 0 if the conversion fails,
        // which might be ambiguous if the user passes "0".)
        num = atoi(argv[i]);
        product *= num;
    }
    
    // Print the multiplication result
    printf("Result: %lld\n", product);
    
    return 0;
}
