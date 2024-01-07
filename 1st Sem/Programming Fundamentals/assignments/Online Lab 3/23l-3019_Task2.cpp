#include <iostream>
using namespace std;
#include <cstring>

int main() {
    char input[100];
    cout << "Enter a character array: ";
    cin.getline(input, sizeof(input));

    int frequency[128] = {0}; 


    for (int i = 0; i < strlen(input); i++) {
        frequency[input[i]]++;
    }

    cout << "Frequency of each element of the array: " << endl;

    for (int i = 0; i < 128; i++) {
        if (frequency[i] > 0) {
            char character = i; 
            cout << frequency[i] << " " << character << endl;
        }
    }


    cout<<"\n";
    system("pause");
    return 0;
}
