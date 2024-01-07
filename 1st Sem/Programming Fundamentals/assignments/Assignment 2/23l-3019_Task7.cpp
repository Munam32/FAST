#include <iostream>
using namespace std;

int main() {
    char ch;

    cout<<"Enter character: ";
    cin>>ch;
    
    if (ch=='a' || ch=='A' || ch=='e' || ch=='E' || ch=='i' || ch=='I' || ch=='o' || ch=='O' || ch=='u' || ch=='U' ) cout<<"It is a vowel";
    else cout<<"It is a consonant";
    
    cout<<endl;
    system("pause");

    return 0;
}