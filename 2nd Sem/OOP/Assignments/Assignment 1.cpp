# include <iostream>
#include<fstream>
using namespace std;

// Creates new array of distinct elements only and updates size of the original array and returns the starting pointer of the new array + de allocates memmory
int* RemoveDuplicates(int* myArray, int& size)
{
	int* endPtr = myArray + size-1;
	int distinctCount = 0;
	bool check = true;	//checks for handling repeating elements case

	
	//counts number of distinct elements in the array
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
	


	//feeds distinct elements into new array on heap
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


// Sorts array in ascending order
void SortArray(int* myArray, const int& size)
{
	int* endPtr = myArray + size;


	// bubble Sort for sorting in ascending order

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


// Prints Array On console
void OutputArray(int* myArray, const int& size)
{
	int* endPtr = myArray + size;


	// Prints Array on Console

	for (int* iPtr = myArray; iPtr < endPtr; iPtr++)
		cout << *iPtr<<" ";


	cout << "\n\n";

}


// Performs union operation on 2 arrays + deallocates memmory
void UnionArray(int* myArray1, int* myArray2, const int& myArray1size, const int& myArray2size)
{
	int* endPtrArray1 = myArray1 + myArray1size;
	int* endPtrArray2 = myArray2 + myArray2size;
	int duplicateCount = 0;


	//finds number of duplicate elements in both arrays
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


	int* endPtr = newArray; // used to traverse array 1 + acts as an end pointer for array 1



	//feeds contents of array 1 in new array
	for (int* iPtr = myArray1; iPtr < endPtrArray1; iPtr++)
	{
		*endPtr = *iPtr;
		endPtr++;
	}



	delete[] myArray1;	

	int* temp = endPtr; // used to traverse next half of new array
	bool flag = false;	// check for not including common elements more than once



	// accesses one element of array2 at a time and stores distinct elements
	for (int* iPtr = myArray2; iPtr < endPtrArray2; iPtr++)
	{

		// searches for common elements in both arrays
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


// Feeds data from file into arrays + calls other functions
void InputArray(ifstream& infile)
{	

	if (infile.is_open())	
	{
		
		while ( !infile.eof() ) 
		{

			int size1 = 0, size2 = 0;	
			int number = 0;
			

			infile >> size1;		


			if (size1 <= 0)
			{
				cout << "Size can not be 0 or negative";
				break;
			}


			int* Array1 = new int[size1];
			int* temp = Array1;	// used to access arrays



			// reading into array from file
			for (int i = 0; i < size1; i++)		
			{
				infile >> number;
				*temp = number;
				 temp++;
			}
			
			infile >> size2;			


			if (size2 <= 0)	// checks for negative size value
			{
				
				delete[] Array1;

				cout << "Size can not be 0 or negative";
				break;

			}


			int* Array2 = new int[size2];	
			temp = Array2;					


			//feeds 2nd array contents
			for (int i = 0; i < size2; i++)
			{
				infile >> number;
				*temp = number;
				 temp++;
				
			}

			cout << "Input Array 1" << ": " << endl;
			OutputArray(Array1, size1);
			
			
			SortArray(Array1, size1);
			cout << "Sorted Array: " << endl;
			OutputArray(Array1, size1);


			Array1 = RemoveDuplicates(Array1, size1);


			cout << "Distinct Array: " << endl;
			OutputArray(Array1, size1);



			cout <<"Input Array 2"<< ": "<<endl;
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

		infile.close();	

	}
	else
		cout << "Cannot open file!!\n";
	

}
	

void main()
{
	ifstream input("Data1.txt");	

	InputArray(input);

	cout << '\n';
	system("pause");
}

