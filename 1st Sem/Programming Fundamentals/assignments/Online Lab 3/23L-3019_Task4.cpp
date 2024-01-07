#include <iostream>
using namespace std;

int main(){
    int arr[5];
    cout<<"Enter 5 Numbers: "<<endl;

    for (int i=0;i<5;i++){
        cin>>arr[i];
    }

    int index=0,num,bitarr[5];

    for(int j=0; j<5;j++){

        num=arr[j];

        int count = 0;

        while (num > 0) {
            if (num % 2 == 0) {
                count++;
            }
            num /= 2;
        }

        bitarr[j] = count; 
    }

    cout<<"Output Array: ";

    for(int j=0;j<=4;j++){
        cout<<bitarr[j]<<" ";
    }

    cout<<endl;
    system("pause");
    return 0;
}