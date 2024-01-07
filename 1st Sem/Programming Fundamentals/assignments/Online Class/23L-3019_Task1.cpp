# include <iostream>
using namespace std;

int main(){

    int Num,fact;

    cout<<"Enter Number: ";
    cin>>Num;

    if(Num == 0) cout<<"Factorial: 1";

    else if(Num>0){

    fact = Num;
    Num--;

    for( ; Num>1 ; Num--){

        fact = Num * fact;
    }

    
    cout<<"Factorial: "<<fact;
    }

    else if(Num<0) cout<<"Factorial of a negative number does not exist";
    

    return 0;
}
