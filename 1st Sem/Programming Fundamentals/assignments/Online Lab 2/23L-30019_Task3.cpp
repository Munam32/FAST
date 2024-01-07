#include<iostream>
using namespace std;

int main(){
    int count=0,sum,num,temp;

    cout<<"Enter Number: ";
    cin>>num;

    temp = num;

    while(temp>10){
        temp = temp /10;
        count++;
    }
    count++;

    if(count==4){

        sum = num/1000;

        sum = sum + (num%1000)/100;
    
        sum = sum + (num%100)/10;

        sum = sum + num%10;
        
        cout<<"Sum of the digits: "<<sum<<endl;
    }
    
    system("pause");
    return 0;
}