# include<iostream>
#include<cmath>
using namespace std;

int main(){
    
    double L1,L2,Area,h;

    cout<<"Enter parallel Length 1: ";
    cin>>L1;
    cout<<"Enter parallel Length 2: ";
    cin>>L2;
    cout<<"Enter parallel Height: ";
    cin>>h;

    Area = (L1+L2) * (h/2.0);

    cout<<"Area Of Trapeziod: "<<Area;

    return 0;
}