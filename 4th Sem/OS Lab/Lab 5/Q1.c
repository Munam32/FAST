#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
# define N 5


void* print(){
  printf("--- Thread ID= %d ProcessID: %d  ---\n",(int)pthread_self(),(int)getpid());
  pthread_exit(NULL);
}



void main(){
  pthread_t threadID[N];

  for(int i=0;i<N;i++){
    pthread_create(&threadID[i],NULL,print,NULL);
    pthread_join(threadID[i],NULL);
  }

  


}
