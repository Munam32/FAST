#include<iostream> 
using namespace std;
#include<cmath>

int main(){

    double x1,x2,y1,y2,x3,y3,DisAB,DisAC,DisBC,p;

    cout<<"Enter X1: ";
    cin>>x1;
    cout<<"Enter y1: ";
    cin>>y1;
    cout<<"Enter X2: ";
    cin>>x2;
    cout<<"Enter Y2: ";
    cin>>y2;
    cout<<"Enter X3: ";
    cin>>x3;
    cout<<"Enter Y3: ";
    cin>>y3;

    DisAB = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    DisAC = sqrt(pow(x3-x1,2)+pow(y3-y1,2));
    DisBC = sqrt(pow(x2-x3,2)+pow(y2-y3,2));


    p = (DisAB+DisAC+DisBC) / 2;

    double Area;

    Area = sqrt( p*(p-DisAB)*(p-DisAC)*(p-DisBC));

    cout<<"Area: "<<Area;


    return 0;
}


