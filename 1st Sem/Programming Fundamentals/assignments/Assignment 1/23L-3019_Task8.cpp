# include<iostream>
#include <cmath>
#include <iomanip>     // use to control sfgs
using namespace std;

int main(){

    double x,Ans;

    cout<<"Enter value of x: ";
    cin>>x;

    Ans = x - (pow(x,3) / 6) - (pow(x,5) / 120) -  (pow(x,7) / 5040) ;  //floating point arithmetic

    cout<<"Answer: "<<setprecision(3)<<Ans;

    return 0;
}