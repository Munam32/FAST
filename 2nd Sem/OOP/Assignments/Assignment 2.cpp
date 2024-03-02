#include <iostream>
#include <fstream>
using namespace std;

// destroys 2D Array on Heap
void DeallocateMemory(int** matrix, const int& rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}


//swaps addresses of 2 rows
void InterchangeRows(int*& row1, int*& row2)
{
	int* temp = row1;
	row1 = row2;
	row2 = temp;
}


//Calls Interchange rows to swap rows
void InterchangeRows(int** matrix, const int& ROWS1, const int& ROWS2)
{
	

	InterchangeRows(*(matrix + ROWS1 - 1), *(matrix + ROWS2 - 1));



}


//Creates a Transpose matrix and returns its pointer
int** TransposeMatrix(int** matrix, const int& ROWS, const int& COLS)
{

	//swapping rows with cols
	int rows = COLS, cols = ROWS;

	//creating new 2D Array
	int** matrixT = new int* [rows];

	for (int** i = matrixT; i < (matrixT + rows); i++)
	{
		*i = new int[cols];
	}
	
	//storing elements in transpose matrix
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			*(*(matrixT + j) + i) = *(*(matrix + i) + j);
		}
	}

	return matrixT;
}


// Checks if a matrix is symmetric
bool IsSymmetric(int** matrix, const int& ROWS, const int& COLS)
{
	int** newMatrix = TransposeMatrix(matrix, ROWS, COLS);

	// checking for unequal elements in transpose and original matrix
	if (ROWS == COLS)
	{
		for (int i = 0; i < ROWS; i++)
		{
			for (int j = 0; j < COLS; j++)
			{
				if (*(*(newMatrix + i) + j) != *(*(matrix + i) + j))
				{
					DeallocateMemory(newMatrix, ROWS);
					return false;
				}
			}
		}
	}
	else 
	{
		DeallocateMemory(newMatrix, ROWS);
		return false;
	}

	DeallocateMemory(newMatrix, ROWS);
	return true;
	
}



//Adds 2 matrices
int** AddMatrix(int** matrixA, int** matrixB, const int& rows, const int& cols, const int& ROWS, const int& COLS)
{	
	int** matrixR = new int* [rows];

	//creating resulting matrix
	for (int i = 0; i < rows; i++)
	{
		*(matrixR + i) = new int[cols];
	}

	//storing results in resulting matrix
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			*(*(matrixR + i) + j) = (*(*(matrixA + i) + j)) + (*(*(matrixB + i) + j));
		}

	}

	return matrixR;


	
	
}



void OutputMatrix(int** matrix, const int& rows, const int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << *(*(matrix + i) + j) << " ";
		}
		cout << endl;
	}
	cout << endl;
}


//reads file, stores data into arrays and returns array pointer
int** InputMatrix(ifstream& fin,int&rows,int&cols)
{

	fin >> rows;
	fin >> cols;	


	// creating 2D Array on heap
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++)
		*(matrix + i) = new int[cols];
		
	
	// feeding numbers into array
	int num;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{	
			fin >> num;
			*(*(matrix + i) + j) = num;

		}
	}

	
	
	return matrix;

}


// assuming file has 3 matrices

void main()
{

	ifstream input("InputFile.txt");

	if (input.is_open())
	{
		int rowsA, colsA, rowsB, colsB, rowsC, colsC;


		int** matrixA = InputMatrix(input, rowsA, colsA);

		cout << "Matrix A:" << endl;
		OutputMatrix(matrixA, rowsA, colsA);



		int** matrixB = InputMatrix(input, rowsB, colsB);

		cout << "Matrix B:" << endl;
		OutputMatrix(matrixB, rowsB, colsB);



		int** matrixC = InputMatrix(input, rowsC, colsC);

		cout << "Matrix C:" << endl;
		OutputMatrix(matrixC, rowsC, colsC);



		if (rowsA == rowsB && colsA == colsB)
		{

			cout << "A+B: " << endl;
			int** addMatrix = AddMatrix(matrixA, matrixB, rowsA, colsA, rowsB, colsB);
			OutputMatrix(addMatrix, rowsA, colsA);
			DeallocateMemory(addMatrix, rowsA);

		}
		else
			cout << "A+B:" << endl << "Addition is not possible" << endl << endl;;




		if (rowsA == rowsC && colsA == colsC)
		{
			cout << "A+C: " << endl;
			int** addMatrix = AddMatrix(matrixA, matrixC, rowsA, colsA, rowsC, colsC);
			OutputMatrix(addMatrix, rowsA, colsA);
			DeallocateMemory(addMatrix, rowsA);
		}
		else
			cout << "A+C:" << endl << "Addition is not possible"<<endl<<endl;




		if (rowsB == rowsC && colsB == colsC)
		{
			cout << "B+C: " << endl;
			int** addMatrix = AddMatrix(matrixB, matrixC, rowsB, colsB, rowsC, colsC);
			OutputMatrix(addMatrix, rowsB, colsB);
			DeallocateMemory(addMatrix, rowsB);
		}
		else
			cout << "B+C:" << endl << "Addition is not possible"<<endl<<endl;




		cout << "Transpose Of Matrix A:\n";

		int** transposeMatrix = TransposeMatrix(matrixA, rowsA, colsA);
		OutputMatrix(transposeMatrix, colsA, rowsA);
		DeallocateMemory(transposeMatrix, colsA);



		cout << "Transpose Of Matrix B:\n";

		transposeMatrix = TransposeMatrix(matrixB, rowsB, colsB);
		OutputMatrix(transposeMatrix, colsB, rowsB);
		DeallocateMemory(transposeMatrix, colsB);




		cout << "Transpose Of Matrix C:\n";

		transposeMatrix = TransposeMatrix(matrixC, rowsC, colsC);
		OutputMatrix(transposeMatrix, colsC, rowsC);
		DeallocateMemory(transposeMatrix, colsC);




		if (IsSymmetric(matrixA, rowsA, colsA))
			cout << "Matrix A is symmetric"<<"\n\n";
		else
			cout << "Matrix A is not symmetric"<< "\n\n";



		if (IsSymmetric(matrixB, rowsB, colsB))
			cout << "Matrix B is symmetric"<< "\n\n";
		else
			cout << "Matrix B is not symmetric"<< "\n\n";






		if (IsSymmetric(matrixC, rowsC, colsC))
			cout << "Matrix C is symmetric"<< "\n\n";
		else
			cout << "Matrix C is not symmetric"<< "\n\n";






		cout << "Changing row 1 and row 2 of Matrix A\n";
		InterchangeRows(matrixA, 1, 2);
		OutputMatrix(matrixA, rowsA, colsA);

		DeallocateMemory(matrixA, rowsA);


		cout << "Changing row 1 and row 2 of Matrix B\n";
		InterchangeRows(matrixB, 1, 2);
		OutputMatrix(matrixB, rowsB ,colsB);

		DeallocateMemory(matrixB, rowsB);


		cout << "Changing row 1 and row 2 of Matrix C\n";
		InterchangeRows(matrixC, 1, 2);
		OutputMatrix(matrixC, rowsC, colsC);

		DeallocateMemory(matrixC, rowsC);





		input.close();


	}
	else
		cout << "File is not accessible";


	cout << "\n";
	system("pause");
}