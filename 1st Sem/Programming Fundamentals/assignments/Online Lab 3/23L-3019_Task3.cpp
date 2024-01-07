#include <iostream>
using namespace std;

int main() {
    const int maxArraySize = 100;
    int input[maxArraySize];
    int size = 0; 

    cout << "Enter the elements of the array (enter -1 to finish):" << endl;

    int element;
    while (true) {
        cin >> element;
        if (element == -1 || size >= maxArraySize) {
            break;
        }
        input[size] = element;
        size++;
    }

    for (int i = 0; i < size; i++) {
        int sum = 0;
        for (int j = 1; j <= input[i]; j++) {
            sum += j;
        }
        input[i] = sum;
    }

    cout << "Output Array:" << endl;
    for (int i = 0; i < size; i++) {
        cout << input[i] << " ";
    }

    return 0;
}
