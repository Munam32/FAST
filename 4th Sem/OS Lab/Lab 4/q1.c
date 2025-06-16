
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//printing grandchild first if it is made, then child
void forkChild(const char* processType, int childIndex) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
        
    } 
    else if (pid == 0) {
        
        
        if (childIndex == 1 || childIndex == 4) {
            pid_t grandchild_pid = fork();
            
            if (grandchild_pid < 0) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
                
            } 
            
            else if (grandchild_pid == 0) {
                printf("I am grandchild %d process with PID %d, parent PID %d\n", childIndex, getpid(), getppid());
                printf("I am %s %d process with PID %d, parent PID %d\n", processType, childIndex, getpid(), getppid());
                exit(EXIT_SUCCESS);
            } 
            else {
                wait(NULL);
                exit(EXIT_SUCCESS);
            }
       } 
        else {
            printf("I am %s %d process with PID %d, parent PID %d\n", processType, childIndex, getpid(), getppid());
            exit(EXIT_SUCCESS);
        }
    
    }
    else
        wait(NULL);
}

void main() {

    printf("I am the parent process with PID %d\n", getpid());

    for (int i = 1; i <= 4; i++) {
        forkChild("child", i);
    }

    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    printf("Parent process (PID %d) is the last process to exit\n", getpid());
   
}

