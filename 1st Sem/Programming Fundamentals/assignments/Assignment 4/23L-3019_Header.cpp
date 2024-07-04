# include <iostream>
using namespace std;

void menu() {
	cout << "String Manipulation" << endl;
	cout << '\t' << "1 - String Length" << endl;
	cout << '\t' << "2 - String Concatenation" << endl;
	cout << '\t' << "3 - String Copy" << endl;
	cout << '\t' << "4 - String Edit" << endl << endl;

	cout << "Calculator" << endl;
	cout << '\t' << "5 - Addition" << endl;
	cout << '\t' << "6 - Subtraction" << endl;
	cout << '\t' << "7 - Multiplication" << endl;
	cout << '\t' << "8 - Division" << endl;
	cout << '\t' << "9 - Power" << endl;
	cout << '\t' << "10 - Power (babylonian)" << endl << endl;

	cout << "Sorting In An Array" << endl;
	cout << '\t' << "11 - Bubble Sort" << endl;
	cout << '\t' << "12 - Insertion Sort" << endl;
	cout << '\t' << "13 - Selection Sort" << endl << endl;

	cout << "Searching in An array" << endl;
	cout << '\t' << "14 - Linear Search" << endl;
	cout << '\t' << "15 - Binary Search" << endl << endl;
}

int string_length(char arr[]) {

	int count=0,index =0;

	while (arr[index] != '\0') {

		count++;
		index++;

	}

	return count;

	
}

void string_concat(char first_arr[], char second_arr[], char combined_arr[]) {
	int index = 0,combined_index=0;
	
	while (first_arr[index] != '\0') {
		combined_arr[index] = first_arr[index];
		index++;
		combined_index++;
	}
	index = 0;

	while (second_arr[index] != '\0') {
		combined_arr[combined_index] = second_arr[index];
		combined_index++;
		index++;
	}
	combined_arr[combined_index] = '\0';
}

void string_copy(char source_arr[], char dest_arr[]) {
	int index = 0;

	while (source_arr[index] != '\0') {
		dest_arr[index] = source_arr[index];
		index++;
	}
	dest_arr[index] = '\0';
	
}

void string_edit(char arr[], char ch, char ch_add) {
	int index = 0;

	while (arr[index] != '\0') {

		if (arr[index] == ch) {
			arr[index] = ch_add;
		}
		index++;

	}

}

float add(float num1, float num2) {
	return num1 + num2;
}

float sub(float num1, float num2) {
	return num1 - num2;
}

float mul(float num1, float num2) {
	return num1 * num2;
}

float div(float num1, float num2) {
	return num1 / num2;
}

void BubbleSort(float arr[], int size,char ch) {
	int temp;

	if (ch == 'A') {
		for (int i = 0; i < size - 1; i++) {

			for (int j = 0; j < size - i - 1; j++) {

				if (arr[j] > arr[j + 1]) {

					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;

				}

			}
		}

	}
	else {
		for (int i = 0; i < size - 1; i++) {

			for (int j = 0; j < size - i - 1; j++) {

				if (arr[j] < arr[j + 1]) {

					temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;

				}

			}
		}

	}
}

void InsertionSort(float arr[], int size,char ch) {

	int value_to_insert,hole_position;

	if (ch == 'A') {

		for (int pointer = 1; pointer < size; pointer++) {

			value_to_insert = arr[pointer];
			hole_position = pointer;

			while (hole_position > 0 && arr[hole_position - 1] > value_to_insert) {
				arr[hole_position] = arr[hole_position - 1];
				hole_position -= 1;
			}
			arr[hole_position] = value_to_insert;
		}

	}
	else {
		for (int pointer = 1; pointer < size; pointer++) {

			value_to_insert = arr[pointer];
			hole_position = pointer;

			while (hole_position > 0 && arr[hole_position - 1] < value_to_insert) {
				arr[hole_position] = arr[hole_position - 1];
				hole_position -= 1;
			}
			arr[hole_position] = value_to_insert;
		}

	}
}

int LinearSearch(float arr[], int size, float value) {

	for (int i = 0; i < size; i++) {
		if (arr[i] == value) {
			return i;
		}

	}
	return -1;

}

int BinarySearch(float arr[], int size, float target) {
	int low = 0;
	int high = size - 1;
	int mid;
	int value_to_insert;
	int hole_position;

	for (int pointer = 1; pointer < size; pointer++) {

		value_to_insert = arr[pointer];
		hole_position = pointer;

		while (hole_position > 0 && arr[hole_position - 1] > value_to_insert) {
			arr[hole_position] = arr[hole_position - 1];
			hole_position -= 1;
		}
		arr[hole_position] = value_to_insert;
	}

	while (low <= high) {
		mid = (low + high) / 2;

		if (target == arr[mid]) {
			return mid;
		}
		if (target > arr[mid]) {
			low = mid + 1;
		}
		if (target < arr[mid]) {
			high = mid - 1;
		}
	}
	return -1;
}

float simp_power(float num, int power) {
	float result=num;

	if (power < 0) {

		power *= -1;
		for (int i = 1; i <= power - 1; i++) {
			result *= num;
		}
		return (1/result);
	}
	else if (power == 0) {
		return 1;
	}
	else{
		for (int i = 1; i <= power - 1; i++) {
			result *= num;
		}
		return result;
	}

	
}

void SelectionSort(float arr[], int size, char ch) {

	if (ch == 'A') {
		bool swap;
		int min, index;

		for (int i = 0; i < size; i++) {
			swap = false;
			min = arr[i];
			for (int j = i + 1; j < size; j++) {
				if (arr[j] < min) {
					min = arr[j];
					index = j;
					swap = true;
				}
			}
			if (swap == true) {
				arr[index] = arr[i];
				arr[i] = min;
			}
		}

	}
	else {
		bool swap;
		int max, index;

		for (int i = 0; i < size; i++) {
			swap = false;
			max = arr[i];
			for (int j = i + 1; j < size; j++) {
				if (arr[j] > max) {
					max = arr[j];
					index = j;
					swap = true;
				}
			}
			if (swap == true) {
				arr[index] = arr[i];
				arr[i] = max;
			}
		}
	}
}

float power_frac(float num, float power) {

		if (power == 0) {
			return 1.0;
		}

		bool isNegative = false;

		if (power < 0) {
			isNegative = true;
			power=-power;
		}

		double x = 1.0;
		for (int i = 0; i < 100; i++) {  
			x = 0.5 * (x + num / x);  
		}

		
		for (int j = 1; j < power; j++) {
			x = power_frac(x, 2);  
		}

		if (isNegative) {
			return 1.0 / x;
		}

		return x;
	}