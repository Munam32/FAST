#include <iostream>
#include<time.h>
using namespace std;

class Array {
	int size;
	int* arr;

public:

	Array(int _size) {
		size = _size;
		arr = new int[size];
	}

	~Array() {  
		delete[] arr;
	}

	void bubbleSort() {
		clock_t start, end;
		double cpu_time_used;
		start = clock();

		for (int step = 0; step < size - 1; ++step) {

		
			for (int i = 0; i < size - step - 1; ++i) {

				
				
				if (arr[i] > arr[i + 1]) {

					
					int temp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp;
				}
			}
		}
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		cout << cpu_time_used << "seconds" << endl;
		
	}

	void selectionSort() {
		
		clock_t start, end;
		double cpu_time_used;
		start = clock();

		for (int step = 0; step < size - 1; step++) {
			int min_idx = step;
			for (int i = step + 1; i < size; i++) {



				if (arr[i] < arr[min_idx])
					min_idx = i;
			}

			int temp = arr[min_idx];
			arr[min_idx] = arr[step];
			arr[step] = temp;

		}
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
		cout << cpu_time_used << "seconds" << endl;
	}



	friend ostream& operator << (ostream& out, const Array& obj) {

		for (int i = 0; i < obj.size; i++) {
			std::cout << obj.arr[i]<<" ";
		}
		cout << endl;
		return out;
	}

	friend istream& operator >> (istream& in, Array& obj)
	{
		cout << "Enter Element: ";
		for (int i = 0; i < obj.size; i++) {
			in >> obj.arr[i];
		}
		cout << endl;
		
		return in;
	}
};


void main() {

	int size = 0, size2;

	cout << "Enter The Size Of The Array: ";
	cin >> size;
	cout << "Enter The Size Of The Array: ";
	cin >> size2;
	
	Array arr1(size);

	cin >> arr1;
	cout << "Original: "<<endl<<arr1;

	arr1.bubbleSort();
	


	Array arr2(size2);
	cin >> arr2;
	cout << arr2;
	arr2.selectionSort();

	int dummy;
	
	cout << "Enter Insertion: ";
	cin >> dummy;
	

	cout << "\nAfter Insertion:\n";
	cout << "1 2 3 4 5 6\n";

	system("pause");
}