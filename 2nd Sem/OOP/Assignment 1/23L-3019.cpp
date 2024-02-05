# include <iostream>
#include<fstream>
using namespace std;

int* RemoveDuplicates(int* myArray, int& size)
{
	int* endPtr = myArray + size-1;
	int distinctCount = 0;
	bool check = true;
	

	for (int* iPtr = myArray; iPtr < endPtr; iPtr++)
	{	
		int* nextElement = iPtr + 1;


		if (*iPtr != *nextElement)
		{
			distinctCount++;
			
		}
		
	}
	distinctCount++;
	
	
	
	int *newArray = new int[distinctCount];
	int* temp = newArray;
	


	for (int* iPtr = myArray; iPtr < endPtr; iPtr++)
	{

		int* nextElement = iPtr + 1;


		if (*iPtr != *nextElement)
		{	
			if (check == false)
			{
				check = true;
				continue;
			}

			else
			{
				*temp = *iPtr;
				temp++;

				if (iPtr == endPtr - 1)
				{
					*temp = *nextElement;
					break;
				}
			}

		}

		else if(*iPtr == *nextElement && check)
		{
			*temp = *iPtr;
			temp++;
			check = false;
		}

	}


	delete[] myArray;
	size = distinctCount;

	return newArray;

	
}


void SortArray(int* myArray, const int& size)
{
	int* endPtr = myArray + size;

	for (int i = 0; i < size; i++)
	{
		int* arraySize = endPtr - i-1;
		
		for (int* jPtr = myArray; jPtr < arraySize; jPtr++)
		{
			int* nextElement = jPtr + 1;

			if (*jPtr > *nextElement)
			{
				int tempNum = *jPtr;
				*jPtr = *nextElement;
				*nextElement = tempNum;

			}
			
		}
	}
	
}


void OutputArray(int* myArray, const int& size)
{
	int* endPtr = myArray + size;

	for (int* iPtr = myArray; iPtr < endPtr; iPtr++)
		cout << *iPtr<<" ";

	cout << "\n\n";

}


void UnionArray(int* myArray1, int* myArray2, const int& myArray1size, const int& myArray2size)
{
	int* endPtrArray1 = myArray1 + myArray1size;
	int* endPtrArray2 = myArray2 + myArray2size;
	int duplicateCount = 0;


	for (int* iPtr = myArray1; iPtr < endPtrArray1; iPtr++)
	{
		for (int* jPtr = myArray2; jPtr < endPtrArray2; jPtr++)
		{
			if (*iPtr == *jPtr)
			{
				duplicateCount++;
				break;

			}
		}

	}


	int newSize = myArray1size + myArray2size - duplicateCount;
	int* newArray = new int[newSize];




	int* endPtr = newArray;





	for (int* iPtr = myArray1; iPtr < endPtrArray1; iPtr++)
	{
		*endPtr = *iPtr;
		endPtr++;
	}

	delete[] myArray1;

	int* temp = endPtr;
	bool flag = false;

	for (int* iPtr = myArray2; iPtr < endPtrArray2; iPtr++)
	{

		for (int* jPtr = newArray; jPtr < endPtr; jPtr++)
		{

			if (*iPtr == *jPtr)
			{
				flag = true;
				break;
			}
			else
				flag = false;

		}

		if (flag == false)
		{
			*temp = *iPtr;
			temp++;
		}
	}

	
	delete[] myArray2;
	
	SortArray(newArray, newSize);
	OutputArray(newArray, newSize);

	delete[] newArray;




}

void InputArray(ifstream& infile)
{	

	if (infile.is_open())	
	{
		int count = 1;			// keeps count of number of arrays

		while ( !infile.eof() ) 
		{

			int size1 = 0, size2 = 0;	
			int number = 0;
			

			infile >> size1;		

			if (size1 <= 0)
			{
				cout << "Array does not exist";
				break;
			}

			int* Array1 = new int[size1];		// Creating Array on heap
			int* temp = Array1;					// using temp var to traverse


			for (int i = 0; i < size1; i++)		
			{
				infile >> number;
				*temp = number;
				 temp++;
			}


			cout << "Input Array " << count << ": "<<endl;
			count++;


			OutputArray(Array1, size1);	
			SortArray(Array1, size1);


			cout << "Sorted Array: " << endl;
			OutputArray(Array1, size1);


			Array1 = RemoveDuplicates(Array1, size1);


			cout << "Distinct Array: " << endl;
			OutputArray(Array1, size1);


			infile >> size2;			

			if (size2 <= 0)
			{
				cout << "Array does not exist, 2 arrays needed minimum";
				break;
			}

			int* Array2 = new int[size2];	
			temp = Array2;


			for (int i = 0; i < size2; i++)
			{
				infile >> number;
				*temp = number;
				 temp++;
				
			}


			cout <<"Input Array " << count << ": "<<endl;
			count++;



			OutputArray(Array2, size2);
			SortArray(Array2, size2);


			cout << "Sorted Array: " << endl;
			OutputArray(Array2, size2);


			Array2 = RemoveDuplicates(Array2, size2);


			cout << "Distinct Array: " << endl;
			OutputArray(Array2, size2);

			cout << "Union Of 2 Arrays: \n";
			UnionArray(Array1, Array2, size1, size2);

		}

		cout << endl;

		infile.close();	

	}
	else
		cout << "Cannot open file.\n";
	

}
	

void main()
{
	ifstream fin("Data1.txt");	

	InputArray(fin);

	cout << '\n';
	system("pause");
}

