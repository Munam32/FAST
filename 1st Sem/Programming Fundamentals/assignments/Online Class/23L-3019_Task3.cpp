#include <iostream>
using namespace std;


int main(){

    int DecNum,quotient,remainder,BinNum=0;

    cout<<"Enter Decimal Number: ";
    cin>>DecNum;

    quotient = DecNum;

    for(; quotient!=0; quotient = quotient/2){


        remainder = quotient % 2;
        BinNum = (BinNum*10) + remainder;
    }
    cout<<"Binary Number: "<<BinNum;




    return 0;
}