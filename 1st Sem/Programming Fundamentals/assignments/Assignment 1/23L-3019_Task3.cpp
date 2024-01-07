# include <iostream>
using namespace std;

int main(){

    float PerNightRate=0,Bill=0,R_ServiceCharge=0,T_ServiceCharge=0;
    int NumNights=0;
    char confirm;

    cout<<"Enter Per Night rate: ";
    cin>>PerNightRate;
    cout<<"Enter Number Of Nights stayed: ";
    cin>>NumNights;

    Bill = NumNights * PerNightRate; 
    
    cout<<"Is there are any One-Time room service charge (y/n) : ";
    cin>>confirm;

   
    if (confirm =='y'){                                         //use single quotes
        cout<<"Enter Room Service Charge: ";
        cin>>R_ServiceCharge;
    }

    cout<<"Is there any One-Time Telephone Charge (y/n) : ";
    cin>>confirm;

    if(confirm=='y'){
        cout<<"Enter Telephone charge: ";
        cin>>T_ServiceCharge;
    }
    
    Bill = Bill + T_ServiceCharge + R_ServiceCharge;

    cout<<"Customer Bill: "<<"$"<<Bill;

    return 0;
}
