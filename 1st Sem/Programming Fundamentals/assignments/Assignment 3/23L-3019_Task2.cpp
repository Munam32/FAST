#include <iostream>
using namespace std;

int main() {

	int factor;
	cout << "Prime numbers: ";

	for (int i = 2; i <= 300; i++) {
		factor = 0;
		for (int j = 1; j <= i; j++) {
			
			if (i % j == 0) factor++;
			if (factor > 2) break;


		}

		if (factor == 2) {
			cout << i << " ";

		}

	}	

	cout << endl;
	system("pause");
	return 0;
}
