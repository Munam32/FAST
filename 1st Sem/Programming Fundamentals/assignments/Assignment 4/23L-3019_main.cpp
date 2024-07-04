#include <iostream>
#include "23L-3019_header.h"
using namespace std;

int main() {
	float choice=0;

	while (1) {
		
		menu();

		
		cout << "Enter choice (-1 to exit): ";
		cin >> choice;

		if (choice != -1 && (choice < 1 || choice > 15))
			continue;

		if (choice == -1) {
			break;
		}

		cin.ignore();



		if (choice == 1) {

			const int arr_size=100;
			char arr[arr_size];
			int size;

			cout << "Enter String: ";
			cin.getline(arr,arr_size);

			size = string_length(arr);
			cout << "Length Of string: " << size;
		}
		else if (choice == 2) {
			const int first_size = 100, second_size = 100, combined_size = 200;

			char first_string[first_size], second_string[second_size], combined_string[combined_size];
			int index = 0;

			cout << "Enter first String: ";
			cin.getline(first_string, first_size);
			cout << "Enter Second String: ";
			cin.getline(second_string, second_size);

			string_concat(first_string, second_string, combined_string);
			cout << "Combined String: ";

			while (combined_string[index] != '\0') {
				cout << combined_string[index];
				index++;
			}
			


		}
		else if (choice == 3) {

			const int source_size = 100, dest_size = 100;
			char source[source_size], dest[dest_size];
			int index = 0;

			cout << "Enter Source String: ";
			cin.getline(source, source_size);

			string_copy(source, dest);

			cout << "Destination Array: ";
			while (dest[index] != '\0') {
				cout << dest[index];
				index++;
			}
		}
		else if (choice == 4) {
			const int size = 100;
			int index = 0;
			char ch,ch_add; 
			char string[size];

			cout << "Enter character to replace in string: ";
			cin >> ch;
			cout << "Enter Character to add: ";
			cin >> ch_add;
			cin.ignore();

			cout << "Enter String: ";
			cin.getline(string, size);

			string_edit(string, ch, ch_add);

			cout << "New String: ";
			while (string[index] != '\0') {
				cout << string[index];
				index++;
			}
			


		}
		else if (choice == 5) {

			float num1, num2;
			cout << "Enter first Number: ";
			cin >> num1;
			cout << "Enter Second Number: ";
			cin >> num2;
			cout << "Result: " << add(num1, num2);
		}
		else if (choice == 6) {
			float num1, num2;
			cout << "Enter first Number: ";
			cin >> num1;
			cout << "Enter Second Number: ";
			cin >> num2;
			cout << "Result: " << sub(num1, num2);

		}
		else if (choice == 7) {
			float num1, num2;
			cout << "Enter first Number: ";
			cin >> num1;
			cout << "Enter Second Number: ";
			cin >> num2;
			cout << "Result: " << mul(num1, num2);
		}
		else if (choice == 8) {
			float num1, num2;

			cout << "Enter numerator: ";
			cin >> num1;
			cout << "Enter denominator: ";
			cin >> num2;

			if (num2 == 0) {
				cout << "Math Error";
			}
			else {
				cout << "Result: " << div(num1, num2);
			}

			
		}
		else if (choice == 9) {

			float num;
			int power;
			cout << "Enter Number: ";
			cin >> num;
			cout << "Enter Power: ";
			cin >> power;

			cout << "Result: " << simp_power(num, power);
		}
		else if (choice == 10){
			float num;
			float power;

			cout << "Enter Number: ";
			cin >> num;  

			cout << "Answer: " << power_frac(num,2);


		}
		else if (choice == 11) {

			char choice;

			const int size = 10;
			float arr[size];

			while (1) { 
				cout << "Ascending or Descending Sort (A/D) : ";
				cin >> choice;
				if (choice == 'A' || choice == 'D') {
					break;
				}
			}

			cout << "Enter Elements:\n";
			for (int i = 0; i < size; i++) {
				cin >> arr[i];
			}


			BubbleSort(arr, size,choice);
			cout << "Sorted Array: ";
			for (int i = 0; i < size; i++) {
				cout << arr[i]<<" ";
			}

		}
		else if (choice == 12) {
			char choice;

			const int size = 10;
			float arr[size];
			while (1) { 
				cout << "Ascending or Descending Sort (A/D) : ";
				cin >> choice;
				if (choice == 'A' || choice == 'D') {
					break;
				}
			}

			cout << "Enter Elements:\n";
			for (int i = 0; i < size; i++) {
				cin >> arr[i];
			}


			InsertionSort(arr, size, choice);
			cout << "Sorted Array: ";
			for (int i = 0; i < size; i++) {
				cout << arr[i] << " ";
			}

		}
		else if (choice == 13) {
			char choice;

			const int size = 10;
			float arr[size];
			while (1) {
				cout << "Ascending or Descending Sort (A/D) : ";
				cin >> choice;
				if (choice == 'A' || choice == 'D') {
					break;
				}
			}

			cout << "Enter Elements:\n";
			for (int i = 0; i < size; i++) {
				cin >> arr[i];
			}


			SelectionSort(arr, size,choice);
			cout << "Sorted Array: ";
			for (int i = 0; i < size; i++) {
				cout << arr[i] << " ";
			}

			
		}
		else if (choice == 14) {

			cout << "Enter Array Elements:\n";

			const int size = 10;
			float arr[size];

			for (int i = 0; i < size; i++) {
				cin >> arr[i];
			}
			float value;

			cout << "Enter the value to be searched: ";
			cin >> value;

			int result = LinearSearch(arr, size, value);

			if (result != -1) {
				cout << "Element is present at position "<<result;
			}
			else {
				cout << "Element is not present in array";
			}

		}
		else if (choice == 15) {
			cout << "Enter Array Elements:\n";
			const int size = 10;
			float arr[size];
			for (int i = 0; i < size; i++) {
				cin >> arr[i];
			}
			cout << "Enter the value to be searched: ";
			float value;
			cin >> value;
			int result;

			result = BinarySearch(arr, size, value);

			if (result != -1) {
				cout << "Element is present at position "<<result;
			}
			else {
				cout << "Element is not present in array";
			}

		}


		cout<<'\n';
		system("pause");
		cout << "\n\n";
	}


	return 0;
}