#include <iostream>
using namespace std;    

int main(){        

    float miles,gallons,mile_average;

    
    cout<<"Enter Miles Driven: ";
    cin>>miles;
    cout<<"Enter Gallons Used: ";
    cin>>gallons;
    cout<<endl;

    mile_average = float(miles/gallons);

    cout<<"Mile Average: "<<mile_average;


    return 0;
}