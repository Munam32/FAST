# include <iostream>
#include <cmath>
using namespace std;

int main(){

    double a,b,c,Root1,Root2,discriminant;

    cout<<"Enter a: ";
    cin>>a;
    cout<<"Enter b: ";
    cin>>b;
    cout<<"Enter c: ";
    cin>>c;

    discriminant = sqrt((pow(b,2))-(4*a*c));        // remember semi colon

    if (discriminant>=0){

    Root1 = (-b + discriminant) / 2*a;
    Root2 = (-b-discriminant)/ 2*a;

    cout<<"Root 1: "<<Root1<<endl;
    cout<<"Root 2: "<<Root2;
    }

     
    else cout<<"Roots are complex";

    return 0;
}