#include <iostream>
using namespace std;

int main() {

    float sum=0,num1;
    int num2;

    cout<<"Enter Numbers you want to input: ";
    cin>>num2;

    for(int i=0; i<num2; i++){

        cout<<"Enter Number: ";
        cin>>num1;

        if(num1>0) sum =sum+num1;

    }
    cout<<"Sum of positive numbers is: "<<sum<<endl;
    
    system("pause");
    return 0;
}