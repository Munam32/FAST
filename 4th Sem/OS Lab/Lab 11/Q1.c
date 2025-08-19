# include <stdio.h>
# include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

# define FILE_SIZE 100
# define HALF_SIZE 50


void* convert (void * arg){
    char* map = (char*)arg;

    for(size_t i = 0; i<HALF_SIZE;i++){
        if(islower(map[i]))
            map[i] = toupper(map[i]);
        else if(isupper(map[i]))
            map[i] = tolower(map[i]);
    }

    pthread_exit(EXIT_SUCCESS);
}



void main(int argc, char* argv[] ){
    
    if (argc != 2){
        printf("Insufficent parameters passed to %s \n",argv[0]);
        return;
    }

    // Creating File descriptors
    int fd = open(argv[1], O_RDWR);
    if( fd == -1 ){
        printf("%s can not be opened successfully\n", argv[1] );
        return;
    }

    // Creating map
    char* map = mmap(NULL,FILE_SIZE, PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0);
    if(map == MAP_FAILED){
        perror("Mapping failed\n");
        close(fd);
        return;
    }

    // Creating threads
    pthread_t thread1,thread2;

    if(pthread_create(&thread1,NULL,convert,map) != 0 ){
        printf("Error Creating Thread1\n");
        munmap(map,FILE_SIZE);
        return;
    }

    if(pthread_create(&thread2,NULL,convert, map + HALF_SIZE) != 0){
        printf("Error Creating thread2\n");
        munmap(map,FILE_SIZE);
        return;
    }


    // Wait for threads Completion
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);


    // Syncing changes to disk
    if(msync(map, FILE_SIZE, MS_SYNC) == -1)
        perror("Error syncing file\n");


    //Unmap memory
    if(munmap(map,FILE_SIZE) == -1){
        perror("Error unmapping the file\n");
    }


    // closing file descriptors
    close(fd);

    // Termination
    printf("Completed\n");



}