# include <iostream>
#include <fstream>
using namespace std;

int digits(int num)
{
	int count = 0;

	while (num > 10)
	{
		num /= 10;
		count++;
	}

	return ++count;

}

void main()
{
	ifstream input("Cases.txt");


	if (input.is_open())
	{

		int cases, num;

		input >> cases;


		for (int i = 1; i <= cases; i++)
		{
			input >> num;

			int numDigits = digits(num);
			int* numArray = new int[numDigits];

			int temp = num;

			if (numDigits == 1)
			{
				numArray[0] = num;

			}

			else
			{
				for (int j = 0; j < numDigits; j++)
				{

					for (int k = 0; k < numDigits - j - 1; k++)
					{
						temp /= 10;
					}

					if (j > 0)
					{

						for (int z = 0; z < j; z++)
						{
							temp %= 10;
						}
					}

					numArray[j] = temp;
					temp = num;

				}

			}

			cout << "\nCase # " << i << "\n";

			for (int j = 0; j < numDigits; j++)
			{
				cout << numArray[j] << endl;
			}

			delete[] numArray;
		}

		input.close();
	}
	else
		cout << "File can not be opened";


	cout << '\n';
	system("pause");

}