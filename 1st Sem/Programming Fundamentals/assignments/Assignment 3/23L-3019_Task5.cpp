#include<iostream>
#include<cmath>
using namespace std;

int main() {
	float x,result;
	cout << "Enter value of x: ";
	cin >> x;

	if(x>0){

		result = (x - 1) / x;

		for (int i = 2; i <= 7; i++) {
			result += 0.5 * pow( (x - 1) / x ,i);	
		}

		cout << "Log of " << x << " is: " << result;
	}

		


	cout << endl;
	system("pause");
	return 0;
}