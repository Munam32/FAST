# include <iostream>
using namespace std;
int main(){

    int num;
    cout<<"Enter Number: ";
    cin>>num;

    cout<<"Factors of "<<num<<" are: ";
    for(int i = 1; i<=num;i++){
        if(num % i==0) cout<<i<<" ";

    }
    cout<<endl;

    system("pause");
    return 0;
}

