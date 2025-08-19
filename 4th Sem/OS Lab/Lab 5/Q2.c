#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void* summation(void* N){
  int num = *(int*)N;
  int sum=0;
  
  for(int i=0;i<=num;i++){
    sum+= i*i;
  
  }
    
  printf("Sum of squared integers from 0 to %d: %d\n",num,sum);
  pthread_exit(0);
  



}



void main(int argc, char* argv[]){
  int N = atoi(argv[1]);

  pthread_t threadID;
  pthread_create(&threadID,NULL,summation,&N);
  pthread_join(threadID,NULL);

}
