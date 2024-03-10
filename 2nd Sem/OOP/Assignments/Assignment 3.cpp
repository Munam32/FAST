#include <iostream>
#include <fstream>
using namespace std;


//deallocates 2D char array
void deAllocate(char**& str, const int& rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] str[i];
	}
	delete[] str;
}


//calculates string length
int stringlength(char* str)
{
	int count = 0;

	for (int i=0 ;  str[i] != '\0'; i++)
		count++;

	return count;
}


//calculates words in a string
int wordCount(char* str)
{
	int rowCount = 0;

	for (int i = 0; str[i] != '\0'; i++)

		if (str[i] == ' ')
			rowCount++;

	rowCount++;

	return rowCount;
}


//rows taken as extra parameter in this function
void DisplayStringList(char**& list, const int& rows)
{

	for (int i = 0; i < rows; i++)
		cout << list[i] << endl;
}


char** stringTokens(char* str)
{
	int rows, colCount = 0;
	int index = 0, j = 0;

	rows = wordCount(str);


	char** Tokens = new char* [rows];


	//initializes rows with columns
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ')
		{
			colCount++;
		}

		if (str[i+1] == '\0')
		{
			Tokens[index] = new char[colCount + 1];
		}

		if(str[i] == ' ')
		{
			Tokens[index++] = new char[colCount + 1];
			colCount = 0;
		}

	}

	index = 0;

	//stores words in each row
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			Tokens[index][j] = '\0';
			j = 0;
			index++;
		}

		else
		{
			Tokens[index][j] = str[i];
			j++;
		}

		if (str[i+1] == '\0')
		{
			Tokens[index][j] = '\0';
		}
	}

	return Tokens;


}


char* reverseSentece(char* str)
{
	int index = 0, ReverseIndex = 0;
	bool flag = true;

	int rows = wordCount(str);
	char** Words = stringTokens(str);
	int length = stringlength(str);


	char* reverseStr = new char[length + 1];

	//stores characters in heap
	for (int i = rows - 1; i >= 0; i--)
	{
		flag = true;

		while (flag)
		{
			if (Words[i][index] != '\0')
			{
				reverseStr[ReverseIndex] = Words[i][index];
				ReverseIndex++;
				index++;
			}
			else
			{
				reverseStr[ReverseIndex] = ' ';
				index = 0;
				ReverseIndex++;
				flag = false;
			}
		}
	}

	reverseStr[ReverseIndex] = '\0';

	deAllocate(Words, rows);

	return reverseStr;

}


void stringConcatenate(char*& str1, char* str2)
{
	int size = stringlength(str1) + stringlength(str2);

	char* temp = new char[size + 2];

	int i = 0;
	for (; str1[i] != '\0'; i++)
	{
		temp[i] = str1[i];
	}

	temp[i++] = ' ';

	for (int j = 0; str2[j] != '\0'; j++,i++)
	{
		temp[i] = str2[j];

	}

	temp[i] = '\0';

	str1 = temp;
}


int compareString(char* str1, char* str2)
{


	for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++)
	{
		char temp1 = str1[i], temp2 = str2[i];

		if (str1[i] >= 'A' && str1[i] <= 'Z')
		{
			temp1 += 32;
		}

		if (str2[i] >= 'A' && str2[i] <= 'Z')
		{
			temp2 += 32;
		}

		

		if (temp1 < temp2)
			return 1;


		else if (temp2 < temp1)
			return -1;

	}

	//handles strings of shorter size
	if (stringlength(str1) > stringlength(str2))
		return 1;

	else if (stringlength(str1) < stringlength(str2))
		return -1;

	else
		return 0;

}


void bubbleSort(char** list, const int& size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - i - 1; j++)
		{
			if (compareString(list[j], list[j + 1]) == -1)
			{
				char* temp = list[j + 1];
				list[j + 1] = list[j];
				list[j] = temp;
			}
		}
}


void StudentList(ifstream& input)
{	
	int size = 0;

	input >> size;
	input.ignore();


	char** list = new char* [size];


	//stores names in "list" 2D Array
	for (int i = 0; i < size; i++)
	{
		char temp[81];
		input.getline(temp, 81);


		int length = stringlength(temp);

		list[i] = new char[length + 1];

		for (int j = 0; j < length; j++)

			list[i][j] = temp[j];

		list[i][length] = '\0';


	}
	input.close();

	cout << "Students List Functionality\n";
	cout << "-----------------------------------------\n";
	cout << "Before Sorting: \n\n";

	DisplayStringList(list, size);

	cout << "\n\n";

	bubbleSort(list, size);

	cout << "After Sorting:\n\n";
	DisplayStringList(list, size);

	deAllocate(list, size);




}



void main()
{
	ifstream input("Data.txt");

	if (input.is_open())
	{
		char* str1 = new char[81];
		input.getline(str1, 81);

		char* str2 = new char[81];
		input.getline(str2, 81);

		char* tempReverse = str1;

		cout << "Testing StringConcatenation\n";
		cout << "-----------------------------------------\n";
		cout << "String 1: " << str1 << endl;
		cout << "String 2: " << str2 << endl;
		cout << "After Concatenation: ";

		stringConcatenate(str1, str2);
		cout << str1;
		

		cout << "\n\n";

		cout << "Testing StringTokens\n";
		cout << "-----------------------------------------\n";
		cout << "Tokens of String 1:\n";

		int rows = wordCount(str1);
		char** temp = stringTokens(str1);


		DisplayStringList(temp, rows);


		cout << "\n\n";

		cout << "Tokens of String 2:\n";

		rows = wordCount(str2);
		temp = stringTokens(str2);
		DisplayStringList(temp, rows);



		cout << "\n";

		cout << "Testing ReverseSentence\n";
		cout << "-----------------------------------------\n";
		cout << "Reverse Sentence of String 1: " << reverseSentece(tempReverse)<<"\n\n";
		cout << "Reverse Sentence of String 2: " << reverseSentece(str2) << "\n\n";
		cout << "Reverse Sentence of Combined String: " << reverseSentece(str1)<<"\n\n";

		delete[] str1;
		delete[] str2;

		StudentList(input);

	}
	else
		cout << "File Can not be opened";
	

	cout << '\n';
	system("pause");
}