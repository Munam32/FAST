#include <iostream>
using namespace std;

int main(){
    char ch='A';
    int spaces,diff=2;

    for(int i=7;i>=1;i--){
        cout<<ch<<" ";
        ch++;
    }
    ch--;

    for(int j=6; j>=1;j--){
        ch--;
        cout<<ch<<" ";
    }
    cout<<endl;


    for(int i = 6; i>=1;i--){
        
        for(int j=1;j<=i;j++){
            cout<<ch<<" ";
            ch++;
        }
        
        for(int spaces=1; spaces<=diff;spaces++){
            cout<<" ";
        }
        diff+=4;
        ch--;
        

        for(int y=1; y<=i; y++){
            cout<<ch<<" ";
            ch--;
        }
        ch='A';
        cout<<endl;
        
    }
    cout<<endl;
    system("pause");
    return 0;
}