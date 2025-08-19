// #include <unistd.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>
// #include <sys/mman.h>
// #include <sys/stat.h>
// #include <pthread.h>
// #include <string.h>
// #include <ctype.h>

// struct stat sb;

// #define OUT 0
// #define IN 1

// // Function to count the number of words in a string
// void* countWords(void* arg) {
//   char* map = (char*) arg;

//   int wordCount = 0;
//   int state = OUT; 

//   // Traverse all characters of the input string
//   for (int i = 0; i < sb.st_size/4; i++) {
    
//     // Check for backslash first
//     if (map[i] == '\\') {
//       i++; // Skip next character (after backslash)
//       continue;
//     }

//     // If the current character is a word character
//     if (isalnum(map[i])) {
//       // If previous state was OUT, increment word count and change state to IN
//       if (state == OUT) {
//         wordCount++;
//         state = IN;
//       }
//     }
//     // If the current character is not a word character
//     else {
//       // Change state to OUT
//       state = OUT;
//     }
//   }

//   pthread_exit(&wordCount);
// }

// int main(int argc,char*argv[]){

//     if (argc!=2 ){
//         printf("Less Number Of Arguements for %s\n",argv[1]);
//         return EXIT_FAILURE;
//     }

//     int fd = open(argv[1],O_RDONLY);
//     if(fd == -1){
//         printf("Error opening file %s\n",argv[1]);
//         return EXIT_FAILURE;
//     }

//     //creating stat for file size computation
    
        
//     if (fstat(fd, &sb) == -1) {
//         perror("fstat");
//         close(fd);
//         return EXIT_FAILURE;
//     }

//     // Creating Map
//     char* map = mmap(NULL , sb.st_size, PROT_READ , MAP_SHARED, fd, 0);
//     if (map == MAP_FAILED){
//         perror("Mapping Failed");
//         close(fd);
//         return EXIT_FAILURE;
//     }

//     pthread_t thread1,thread2,thread3,thread4;
//     int size1 = sb.st_size / 4;
    

//     int** temp;
//     int count = 0;


//     if(pthread_create(&thread1,NULL,countWords,map) !=0 ){
//         printf("Error Creating thread 1\n ");
//         close(fd);
//         munmap(map,sb.st_size);
//     }

//     if(pthread_create(&thread2,NULL,countWords,map+size1) !=0 ){
//         printf("Error Creating thread 2\n ");
//         close(fd);
//         munmap(map,sb.st_size);
//     }

//     if(pthread_create(&thread3,NULL,countWords,map+ 2*size1) !=0 ){
//         printf("Error Creating thread 3\n ");
//         close(fd);
//         munmap(map,sb.st_size);
//     }


//     if(pthread_create(&thread4,NULL,countWords,map+ 3*size1) !=0 ){
//         printf("Error Creating thread 4\n ");
//         close(fd);
//         munmap(map,sb.st_size);
//     }


//     // Wait for threads Completion
//     pthread_join(thread1,temp);
//     count = **temp;

//     pthread_join(thread2,temp);

//     count+=**temp;

//     pthread_join(thread3,temp);

//     count+=**temp;

//     pthread_join(thread4,temp);

//     count+=**temp;

//     // Syncing changes to disk
//     if(msync(map, sb.st_size, MS_SYNC) == -1)
//         perror("Error syncing file\n");
    


//     //Unmap memory
//     if(munmap(map,sb.st_size) == -1){
//         perror("Error unmapping the file\n");
//     }


//     // closing file descriptors
//     close(fd);

//     // Termination
//     printf("Completed\n");

//     return 1;
// }

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#define THREAD_COUNT 4

typedef struct {
    char *start;       // Pointer to the start of the chunk
    size_t length;     // Length of this chunk
    int index;         // Thread index
    int *results;      // Shared results array
} ThreadData;

void *count_words(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int count = 0;
    char *ptr = data->start;
    char *end = data->start + data->length;

    // For threads other than the first, if the previous character (outside this chunk)
    // is not a delimiter then we are mid-word. In that case, skip until a delimiter.
    if (data->index != 0) {
        if (*(data->start - 1) != ' ' && *(data->start - 1) != '\n' && *(data->start - 1) != '\t') {
            while (ptr < end && (*ptr != ' ' && *ptr != '\n' && *ptr != '\t'))
                ptr++;
        }
    }

    // Now count words in the adjusted portion of the chunk.
    while (ptr < end) {
        // Skip any delimiters.
        while (ptr < end && (*ptr == ' ' || *ptr == '\n' || *ptr == '\t'))
            ptr++;
        if (ptr < end) {  // Found the start of a word.
            count++;
            // Skip until the next delimiter.
            while (ptr < end && (*ptr != ' ' && *ptr != '\n' && *ptr != '\t'))
                ptr++;
        }
    }
    data->results[data->index] = count;
    return NULL;
}

int main() {
    const char *filename = "sample.txt";
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    // Determine the file size.
    size_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == 0) {
        printf("The file is empty.\n");
        close(fd);
        return EXIT_SUCCESS;
    }
    lseek(fd, 0, SEEK_SET);

    // Memory-map the file.
    char *mapped = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped == MAP_FAILED) {
        perror("mmap failed");
        close(fd);
        return EXIT_FAILURE;
    }

    size_t chunk_size = file_size / THREAD_COUNT;
    pthread_t threads[THREAD_COUNT];
    ThreadData thread_data[THREAD_COUNT];
    int results[THREAD_COUNT] = {0};

    // Create threads and assign each a chunk of the file.
    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_data[i].start = mapped + i * chunk_size;
        thread_data[i].length = (i == THREAD_COUNT - 1) ? (file_size - i * chunk_size) : chunk_size;
        thread_data[i].index = i;
        thread_data[i].results = results;
        pthread_create(&threads[i], NULL, count_words, &thread_data[i]);
    }

    // Wait for all threads to complete.
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    // Sum the results from all threads.
    int total_words = 0;
    for (int i = 0; i < THREAD_COUNT; i++) {
        total_words += results[i];
    }

    printf("Total words in the file: %d\n", total_words);

    munmap(mapped, file_size);
    close(fd);
    return EXIT_SUCCESS;
}
