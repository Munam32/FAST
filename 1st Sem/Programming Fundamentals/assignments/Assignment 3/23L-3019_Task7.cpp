#include <iostream>
using namespace std;

int main(){
    float fact=1,ans=0;

    for(float i=1 ; i<=7; i++){

        fact*=i;
        ans += i/fact;
    }

    cout<<"Answer: "<<ans;
    cout<<endl;
    system("pause");
    return 0;
}