#include <iostream>
using namespace std;

int main(){
    int n,Length=1;
    cout<<"Enter value of n: ";
    cin>>n;

    if(n>0){
    cout<<n<<" -> ";

    while(n!=1){

        if(n%2==0){
            n/=2;
        }
        else{
            n = 3*n + 1;
        }
        Length++;
        cout<<n;

        if(n>1){
            cout<<" -> ";
        }

    }
        cout<<"; Length = "<<Length;
    }
    cout<<endl;
    system("pause");
    return 0;
}