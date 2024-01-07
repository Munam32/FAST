#include <iostream>
using namespace std;

int main() {
    int num;

    cout<<"Enter Number: ";
    cin>>num;

    if(num!=0){
    if (num%2==0){
        if(num>0) cout<<"Positive Even Number";
        else if(num<0) cout<<"Negative Even Number";
    }

    else if(num>0) cout<<"Positive odd Number";
    else cout<<"Negative odd number";

    }
    cout<<endl;
    system("pause");

    return 0;
}