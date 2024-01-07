#include <iostream>
using namespace std;

int main() {

    for(int i =1; i<=5;i++){

        if(i==1){
            for(int spaces=1 ; spaces<=8; spaces++){
                cout<<" ";
                
            }
            cout<<"1";
        }
        else if(i==2){
            for(int spaces=1 ; spaces<=6; spaces++){
                cout<<" ";
                
                
            }
            cout<<"1   1";
        }
        else if(i==3){
            for(int spaces=1 ; spaces<=4; spaces++){
                cout<<" ";
                
            }
            cout<<"1   2   1";
        }
        else if(i==4){
            cout<<"  ";
            cout<<"1   3   3   1";
        }

        else{
            cout<<"";
            cout<<"1   4   6   4   1";
    
            
        }       
        cout<<endl;
    }
    cout<<endl;
    system("pause");
    return 0;
}
