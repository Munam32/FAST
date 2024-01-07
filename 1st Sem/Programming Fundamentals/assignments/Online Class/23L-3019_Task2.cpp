# include<iostream>
using namespace std;


int main(){

    int Num;

    cout<<"Enter Number of terms for the sequence: ";
    cin>>Num;

    if (Num<0) cout<<"Enter non-zero Values";

    else{

        int a=0,b=1,Nextterm = 0;

        for(int i=0;i<Num;i++){

            if(i<2){
                Nextterm = i;
            }
            else{
                Nextterm = a+b;
                a=b;
                b = Nextterm;
            }
            cout<<Nextterm<<" ";
        }

    }
    return 0;
}