#include <iostream>
using namespace std;
int main(){
    float Temp;
    cout<<"Enter Temperature: ";
    cin>>Temp;

    if(Temp<=0) cout<<"Freezing weather";
    else if(Temp>0 && Temp <= 10) cout<<"Very Cold Weather";
    else if(Temp>10 && Temp <= 20) cout<<"Cold Weather";
    else if(Temp>20 && Temp <= 30) cout<<"Normal In Temperature";
    else if(Temp>30 && Temp < 40) cout<<"Hot Weather";
    else cout<<"Very Hot Weather";

    cout<<endl;
    system("pause");
    return 0;
}