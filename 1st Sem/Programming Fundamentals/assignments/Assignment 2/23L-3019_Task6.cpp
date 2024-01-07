#include <iostream>
using namespace std;

int main() {
    int X,Y;

    cout<<"Enter X: ";
    cin>>X;
    cout<<"Enter Y: ";
    cin>>Y;

    if(Y%X==0) cout<<"True"; // if x==0 error
    else cout<<"False";
    
    cout<<endl;
    system("pause");
    return 0;
}