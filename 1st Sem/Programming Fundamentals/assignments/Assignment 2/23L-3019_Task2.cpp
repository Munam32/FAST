#include <iostream>
using namespace std;

int main() {
    int lower_bound = 0, upper_bound=100,result;
    char response;
    

    cout << "Think of a number between 1 and 100." << endl;
    cout<<"Is your number 50?: (y/n) :  ";
    cin>>response;

    if(response=='y'){
        result = 50;
    }
    else{
        cout << "Is your number greater than 50? (y/n): ";
        cin >> response;

        if (response == 'y') {
            lower_bound = 51;
        }
        else {
            upper_bound = 50;
        }

        result = (lower_bound + upper_bound) / 2;

        cout << "Is your number " << result << "? (y/n): ";
        cin >> response;

        if (response == 'n') {
            cout << "Is your number greater than " << result << "? (y/n): ";
            cin >> response;

            if (response == 'y') {
                lower_bound = result + 1;
            }
            else {
                upper_bound = result - 1;
            }

            result = (lower_bound + upper_bound) / 2;
            
            cout << "Is your number " << result << "? (y/n): ";
            cin >> response;
            if (response == 'n') {
                cout << "Is your number greater than " << result << "? (y/n): ";
                cin >> response;
                if (response == 'y') {
                    lower_bound = result + 1;
                }
                else {
                    upper_bound = result - 1;
                }
                result = (lower_bound + upper_bound) / 2;
                cout << "Is your number " << result << "? (y/n): ";
                cin >> response;
                if (response == 'n') {
                    cout << "Is your number greater than " << result << "? (y/n): ";
                    cin >> response;
                    if (response == 'y') {
                        lower_bound = result + 1;
                    }
                    else {
                        upper_bound = result - 1;
                    }
                    result = (lower_bound + upper_bound) / 2;
                    cout << "Is your number " << result << "? (y/n): ";
                    cin >> response;
                    if (response == 'n') {
                        cout << "Is your number greater than " << result << "? (y/n): ";
                        cin >> response;
                        if (response == 'y') {
                            lower_bound = result + 1;
                        }
                        else {
                            upper_bound = result - 1;
                        }
                        result = (lower_bound + upper_bound) / 2;
                        cout << "Is your number " << result << "? (y/n): ";
                        cin >> response;
                        if (response == 'n') {
                            cout << "Is your number greater than " << result << "? (y/n): ";
                            cin >> response;
                            if (response == 'y') {
                                lower_bound = result + 1;
                            }
                            else {
                                upper_bound = result - 1;
                            }
                            result = (lower_bound + upper_bound) / 2;
                        }
                    }
                }
            }
        }
    }
    cout << "Your number is " << result << "!" << endl;
    return 0;
}