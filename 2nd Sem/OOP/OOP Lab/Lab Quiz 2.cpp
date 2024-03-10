#include <iostream>

using namespace std;



void main()
{
	int quires,size,left,right;

	cout << "Enter Size of Array: ";
	cin >> size;

	int* arr = new int[size];

	for (int i = 0; i < size; i++)
		arr[i] = 0;

	cout << "Enter number of Quires: ";
	cin >> quires;

	for (int i = 0; i < quires; i++)
	{
		cout << "Enter left query: ";
		cin >> left;

		cout << "Enter left query: ";
		cin >> right;

		for (int i = left; i <= right; i++)
		{
			arr[i] += 1;
		}

		

	}

	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";

	delete[] arr;



	cout << "\n";
	system("pause");
}