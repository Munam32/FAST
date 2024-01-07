# include <iostream>
using namespace std;

int main(){

    int year;
    cout<<"Enter Year: ";
    cin>>year;

    if(year%4 ==0) cout<<"It is a Leap Year";
    else cout<<"It is not a Leap Year";
    
    cout<<endl;
    system("pause");
    return 0;
}