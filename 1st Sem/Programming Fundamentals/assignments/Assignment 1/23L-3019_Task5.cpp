# include <iostream>
# include <cmath>
using namespace std;


int main(){

    double a,b,c,p,Area;

    cout<<"Enter a: ";
    cin>>a;
    cout<<"Enter b: ";
    cin>>b;
    cout<<"Enter c: ";
    cin>>c;

    p = (a+b+c) / 2;

    Area = sqrt( p*(p-a)*(p-b)*(p-c));  // no bracket multiplication "(p-a)(p-b)" use multiplication sign. "(p-a)*(p-b)"

    if (Area>0) cout<<"Area: "<<Area;
    else cout<<"Triangle does not exist";


    return 0;
}
