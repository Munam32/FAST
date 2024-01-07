#include <iostream> 
#include <string>
using namespace std; 

int main() { 

    string stream; 

    bool isPalindrome = true; 

    cout<<"Enter String: ";
    cin >> stream; 

    int textLength = stream.size(); 

    for (int i = 0; i < textLength / 2; i++) { 

        if (stream[i] != stream[textLength - i - 1]) { 
            isPalindrome = false; 

        } 

    } 

    if (isPalindrome == true) cout << "Input is a Palindrome."; 

    else cout << "Input is not a Palindrome";

    cout<<"\n";
    system("pause");
    return 0;
}