#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

int main(int argc,char*argv[]){
  int size = argc-3;
  int array[size];
  for(int i=0;i<size;i++){
    array[i] = atoi(argv[i+1]);
  }
  
  bool order = atoi(argv[size+1]) == 1;
  int nth = atoi(argv[size+2]);
  
  printf("Array Elements ");
  print(array,size);
  sort(array,size,order);
  printf("Sorted Elements: ");
  print(array,size);
  findHighest(array,size,nth);
  return 0;
  
}




