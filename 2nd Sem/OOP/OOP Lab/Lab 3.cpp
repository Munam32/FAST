#include <iostream>
using namespace std;

void inline InputMatrix(int** matrix, const int& rows, const int& cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			cout << "Enter " << i+1 << " row " << "and " << j+1 << " column element: ";
			cin >> *(*(matrix + i) + j);

		}
}

void inline DisplayMatrix(int** matrix, const int& rows, const int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << *(*(matrix + i) + j) << " ";

		}
		cout << endl;
	}
}

int inline** AllocateMemory(int& rows, int& cols)
{
	while (1)
	{
		cout << "Enter Rows: ";
		cin >> rows;

		cout << "Enter columns: ";
		cin >> cols;

		if ( (rows == 0 && cols == 0) || rows != cols)
		{
			cout << "Enter Valid and same rows and colums"<<endl;
			continue;
		}
		else
			break;
	}

	int** matrix = new int* [rows];

	for (int i = 0; i < rows; i++)
	{
		*(matrix + i) = new int[cols];
	}

	return matrix;
}
 
void inline DeallocateMemory(int** matrix, const int& rows, const int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] *(matrix + i);
	}

	delete[] matrix;
}

int inline* MaxOfColumn(int** matrix, const int& rows, const int& cols)
{
	int* ColAddress = new int[cols];
	int* temp = ColAddress;

	
	int max;

	

	for (int i = 0; i < cols; i++)
	{
		max = *(*(matrix+i));

		for (int j = 0; j < rows; j++)
		{
			if ( (*(*(matrix + i) + j)) > max )
			{
				max = *(*(matrix + j) + i);
			}
		}

		*temp = max;
		temp++;
		
	}

	return ColAddress;

	
}

bool inline IsMatrixUpperTriangle(int** matrix, const int& rows, const int& cols)
{
	bool flag = true;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (i > j)
			{
				if ( *( *(matrix + i) + j) != 0)
				{
					flag = false;
					break;
				}
			}
			else
				break;
			

		}
		
	}
	return flag;
}



void main()
{
	int rows, cols;

	int** BaseAddress = AllocateMemory(rows, cols);

	InputMatrix(BaseAddress, rows, cols);

	DisplayMatrix(BaseAddress,rows, cols);

	int* MaxArray = MaxOfColumn(BaseAddress, rows, cols);


	cout << endl<<"Max numbers in each column: ";
	for (int i = 0; i < cols; i++)
		cout << *(MaxArray + i)<<" ";

	delete[] MaxArray;

	cout << endl;

	if (IsMatrixUpperTriangle(BaseAddress, rows, cols))
		cout << "matrix is upper triangle";
	else
		cout << "matrix is not upper triangle";


	DeallocateMemory(BaseAddress, rows, cols);


	cout << "\n";
	system("pause");
}