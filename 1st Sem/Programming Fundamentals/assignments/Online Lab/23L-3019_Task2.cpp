# include <iostream>
using namespace std;

int main(){
    int num;

    cout<<"Enter Number of the weekday (1-7): ";
    cin>>num;

    if(num<=0 || num >7) cout<<"Enter a valid number\n";
    else{
        if(num==1) cout<<"Monday\n";
        else if(num==2) cout<<"Tuesday\n";
        else if(num==3) cout<<"Wednesday\n";
        else if(num==4) cout<<"Thursday\n";
        else if(num==5) cout<<"Friday\n";
        else if(num==6) cout<<"Saturday\n";
        else if(num==7) cout<<"Sunday\n";
    }

    system("pause");
    return 0;
}