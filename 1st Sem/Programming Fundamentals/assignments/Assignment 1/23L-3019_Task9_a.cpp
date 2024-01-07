#include<iostream> 
using namespace std;
#include<cmath>

int main(){

    double x1,x2,y1,y2,distance;

    cout<<"Enter X1: ";
    cin>>x1;
    cout<<"Enter X1: ";
    cin>>y1;
    cout<<"Enter X2: ";
    cin>>x2;
    cout<<"Enter Y2: ";
    cin>>y2;

    distance = sqrt(pow(x2-x1,2)+pow(y2-y1,2));

    cout<<"Distance Between points: "<<distance;
    return 0;

}


