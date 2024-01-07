#include <iostream>
using namespace std;

int main() {

    int total=500,NumAccidents,Age;

    cout<<"Enter Driver's Age: ";
    cin>>Age;
    cout<<"Enter Number Of Accidents: ";
    cin>>NumAccidents;
    

    if (Age<25) total+=100;
    
    
    if (NumAccidents == 1) total+=50;
    else if(NumAccidents ==2) total+=125;
    else if(NumAccidents ==3) total+=225;
    else if(NumAccidents ==4) total+=375;
    else if(NumAccidents ==5) total+=575;

    if(NumAccidents<6)
        cout<<"Total Insurance Charge: "<<total<<endl;
    else
        cout<<"No insurance\n";

    system("pause");
    return 0;
}