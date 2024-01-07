#include <iostream>
using namespace std;

int main(){
    int num1,num2,count;

    cout<<"enter number 1: ";
    cin>>num1;
    cout<<"Enter number 2: ";
    cin>>num2;

    cout<<"Prime Numbers: ";

    if (num1<num2){

    for (int i = num1+1; i<num2;i++){
        count=0;
        for(int j =1; j<=i;j++){
            if(i%j ==0) count++;

        }

        if(count==2)
        cout<<i<<" ";
    }

    }
    cout<<endl;
    system("pause");
    return 0;
}