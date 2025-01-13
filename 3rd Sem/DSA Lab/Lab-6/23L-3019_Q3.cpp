#include <iostream>
using namespace std;

void generateSubsequences(string str, string current, int index) {
	if (index == str.length()) {
		cout << current << endl;
		return;
	}

	generateSubsequences(str, current, index + 1);
	generateSubsequences(str, current.append(1, str[index]), index + 1);

}





void main() {

	string a = "abc";
	string c = "";

	generateSubsequences(a, c, 0);

	cout << "\n";
	system("pause");
}