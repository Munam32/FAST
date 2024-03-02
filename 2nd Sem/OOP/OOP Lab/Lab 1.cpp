#include <iostream>
using namespace std;


void AllocateAndCopyArray(int*& myArray,int& size)
{	
	int newsize = size * 2;
	int* newPtr = new int[newsize];

	for (int i = 0; i < size; i++)
	{
		*(newPtr + i) = *(myArray + i);
	}

	delete[]myArray;

	myArray = newPtr;
	size = newsize;


}




void OutputArray(int* myArray, const int& size)
{
	cout << "Elements: ";

	for (int i = size-1; i>=0; i--)
	{
		cout << *(myArray + i)<<" ";
	}

	
}


int* InputArray(int& size)
{
	int* startPtr = new int[size];

	int input,count=0;

	cout << "Enter Elements: ";


	while (cin >> input && input != -1)
	{
		*(startPtr + count) = input;
		count++;

		if (size == count);
			AllocateAndCopyArray(startPtr, size);
			
	}
	if (input == -1)
		size = count;


	return startPtr;
}

void main()
{
	int size = 5;
	int* startPtr = InputArray(size);

	OutputArray(startPtr, size);
	
	delete[] startPtr;

	
	

	cout << '\n';
	system("pause");
}