#include <iostream>
using namespace std;

int main() {

    // Toddler age : 2
    // Child 1-12
    // Teenager 13 - 17
    // adult 18

    float age;

    cout<<"Enter age: ";
    cin>>age;

    if (age<=2) cout<<"It is a Toddler";
    else if(age>2 && age<=12) cout<<"It is a child";
    else if(age>12 && age<=17) cout<<"It is a Teenager";
    else cout<<"It is an adult";

    cout<<endl;
    system("pause");
    return 0;
}