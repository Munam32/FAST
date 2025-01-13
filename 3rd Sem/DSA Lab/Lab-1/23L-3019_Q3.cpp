#include <iostream>
using namespace std;

template <typename T>
class Container {
	T* elements;
	int capacity;
	int size;
public:
	Container() {
		capacity = 0; 
		size = 0;
		elements = 0;
	}
	~Container() {
		size = 0;
		capacity = 0;
	}

	void addElement(const T& elm) {
		T* temp = new T[size++];
		for (int i = 0; i < size - 1; i++) {
			temp[i] = elements[i];
		}
		temp[size - 1] = elm;
		elements = temp;
	}
	void displayElements() const{
		for (int i = 0; i < size; i++) {
			cout << elements[i] << " ";
		}
		
	
	}
};

void main() {
	Container<int>vals;
	vals.addElement(2);
	vals.addElement(4);
	vals.addElement(6);
	vals.addElement(8);
	vals.displayElements();
	cout << endl;

	Container<char>val;
	val.addElement('H');
	val.addElement('E');
	val.addElement('L');
	val.addElement('L');
	val.addElement('O');
	val.displayElements();
	cout << endl;




	system("pause");
}

