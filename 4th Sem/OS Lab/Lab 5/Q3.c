/*
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
# include <signal.h>


int fibonacci(int n){
    // Base case: if n is 0 or 1, return n
    if (n <= 1){
        return n;
    }
    // Recursive case: sum of the two preceding Fibonacci numbers
    return fibonacci(n - 1) + fibonacci(n - 2);
}

void* fibonacciSeq(void*n){
  int num = *(int*)n;
  int *ans = (int*)malloc( num * sizeof(int));
  
  for(int i=0;i<num;i++){
    ans[i] = fibonacci(i);
  
  }
  pthread_exit(ans);
  
  
  
}


void* even(void* args) {
    int** data = (int**)args;  // Cast to int**
    int* array = data[0];      // First element is the array
    int size = *(data[1]);     // Second element is the size

    int* count = (int*)malloc(sizeof(int));
    
    if (count == NULL) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }

    *count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0)
            (*count)++;
    }
    
    pthread_exit(count);
}


void* odd(void* args) {
    int** data = (int**)args;  // Cast to int**
    int* array = data[0];      // First element is the array
    int size = *(data[1]);     // Second element is the size

    int* count = (int*)malloc(sizeof(int));
    
    if (count == NULL) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }

    *count = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 != 0)
            (*count)++;
    }
    

    pthread_exit(count);
}


void* Total(void* args){
  int** data = (int**)args;  // Cast to int**
  int* array = data[0];      // First element is the array
  int size = *(data[1]);     // Second element is the size
  int* sum = (int*)malloc(sizeof(int));  
  
  *sum=array[0];
  
  for (int i = 1; i < size; i++) {
          *sum += array[i];
    }
  
  pthread_exit(sum);



}

void main(int argc, char* argv[]){
  int num = atoi(argv[1]);
  
  pthread_t fibgen,oddCount,evenCount,Sum;
  
  int* series;
  pthread_create(&fibgen,NULL,fibonacciSeq,&num);
  
  
  pthread_join(fibgen,(void**) &series);
  printf("Main ThreadID = %lu",(unsigned long)fibgen);
  
  //printing sequence and first thread ID
  
  
  
  printf("  Sequence: ");
  for(int i=0;i<num;i++){
    printf("%d ",series[i]);
  }
  printf("\n");
  
 
 
  
  int* sizePtr = &num;
  int* args[] = {series, sizePtr}; // Pass array and size as an int* array
  int* countE;
  pthread_create(&evenCount, NULL, even, args);
  pthread_join(evenCount, (void**)&countE);

  printf("2nd ThreadID = %lu  Even Numbers Count = %d\n",(unsigned long)evenCount, *countE);
  
  
  int* countO;
  pthread_create(&oddCount, NULL, odd, args);
  pthread_join(oddCount, (void**)&countO);  
  
  printf("3rd ThreadID = %lu  Odd Numbers Count = %d\n",(unsigned long)oddCount, *countO);
  
  
  int* result;
  pthread_create(&Sum,NULL,Total,args);
  pthread_join(Sum,(void**)&result);
  
  printf("4th ThreadID = %lu  Sum Fibonnacci = %d\n",(unsigned long)Sum, *result);
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>

// Function to compute Fibonacci number
int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Thread function to generate Fibonacci sequence
void* fibonacciSeq(void* n) {
    pid_t tid = syscall(SYS_gettid);
    int num = *(int*)n;
    int* ans = (int*)malloc((num + 1) * sizeof(int));

    if (ans == NULL) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }

    for (int i = 0; i < num; i++) {
        ans[i] = fibonacci(i);
    }

    // Store the thread ID in the last index
    ans[num] = (unsigned long)tid;
    
    pthread_exit(ans);
}

// Thread function to count even numbers
void* even(void* args) {
    int** data = (int**)args;
    int* array = data[0];
    int size = *(data[1]);

    int* result = (int*)malloc(2 * sizeof(int));
    pid_t tid = syscall(SYS_gettid);
    if (result == NULL) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }

    result[0] = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0)
            result[0]++;
    }

    // Store the thread ID
    result[1] = (unsigned long)tid;
    
    pthread_exit(result);
}

//Thread for calculating odd numbers
void* odd(void* args) {
    int** data = (int**)args;
    int* array = data[0];
    int size = *(data[1]);
    int* result = (int*)malloc(2 * sizeof(int));
    
    pid_t tid = syscall(SYS_gettid);
    
    if (result == NULL) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }

    result[0] = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 != 0)
            result[0]++;
    }

    // Store the thread ID
    result[1] = (unsigned long)tid;
    
    pthread_exit(result);
}


// Thread function to calculate sum
void* sumFibonacci(void* args) {
    pid_t tid = syscall(SYS_gettid);
    int** data = (int**)args;
    int* array = data[0];
    int size = *(data[1]);

    int* result = (int*)malloc(2 * sizeof(int));
    if (result == NULL) {
        perror("Memory allocation failed");
        pthread_exit(NULL);
    }

    result[0] = 0;
    for (int i = 0; i < size; i++) {
        result[0] += array[i];
    }

    // Store the thread ID
    result[1] = (unsigned long)tid;
    
    pthread_exit(result);
}

void main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <num>\n", argv[0]);
        return;
    }

    int num = atoi(argv[1]);

    // Create threads
    pthread_t fibgen, evenCount, sumThread, oddCount;
    int* series;

    pthread_create(&fibgen, NULL, fibonacciSeq, &num);
    pthread_join(fibgen, (void**)&series);

    // Print Fibonacci thread ID
    printf("Fibonacci Thread ID = %lu", (unsigned long)series[num]);

    // Print Fibonacci sequence
    printf("  Sequence: ");
    for (int i = 0; i < num; i++) {
        printf("%d ", series[i]);
    }
    printf("\n");

    // Create even count thread
    int* sizePtr = &num;
    int* args[] = {series, sizePtr};
    int* countE;
    int* countO;

    pthread_create(&evenCount, NULL, even, args);
    pthread_join(evenCount, (void**)&countE);

    // Print even count thread ID
    printf("Even Count Thread ID = %lu  ", (unsigned long)countE[1]);
    printf("Even Numbers Count = %d\n", countE[0]);

    //Creating Odd Count Thread
    pthread_create(&oddCount, NULL, odd, args);
    pthread_join(oddCount, (void**)&countO);

    // Print Odd count thread ID
    printf("Odd Count Thread ID = %lu  ", (unsigned long)countO[1]);
    printf("Odd Numbers Count = %d\n", countO[0]);

    // Create sum calculation thread
    int* sumResult;
    pthread_create(&sumThread, NULL, sumFibonacci, args);
    pthread_join(sumThread, (void**)&sumResult);

    // Print sum thread ID
    printf("Sum Thread ID = %lu  ", (unsigned long)sumResult[1]);
    printf("Sum of Fibonacci Sequence = %d\n", sumResult[0]);

    // Free allocated memory
    free(series);
    free(countE);
    free(sumResult);

}




