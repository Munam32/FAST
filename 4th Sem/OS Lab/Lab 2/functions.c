# include "header.h"
#include <stdio.h>

void sort(int array[],bool order,int size){
  
  for(int i=0;i<size;i++){
    for(int j=0;j<size-i-1;j++){
      if(order && array[j]>array[j+1]){
        int temp = array[j];
        array[j]=array[j+1];
        array[j+1] = temp;
      }
      else if(!order && array[j]<array[j+1]){
        int temp = array[j];
        array[j]=array[j+1];
        array[j+1]=temp;
      }
    
    }
  }
return;
}


void findHighest(int array[] , int position,int size){
    if(position < size && position>1){
      sort(array,true,size);
      
      printf("%d Highest: %d",position,array[size-position-2]);
      
    }
    else
        printf("incorrect position");
    
    return;

}


void print(int array[],int size){
  for(int i=0;i<size;i++){
    printf("%d \t",array[i]);
  }
  return;
  
}









