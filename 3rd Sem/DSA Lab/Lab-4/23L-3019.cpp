#include <iostream>
using namespace std;

template <class T>
class List {

private:
	
	class Node {
	public:
		T Data;
		Node* next;
		Node* prev;

		Node() {
			next = NULL; 
			prev = NULL;
		}
		Node(T _data, Node* _next, Node* _prev) {
			next = _next;
			prev = _prev;
			Data = _data;
		}

	};

	Node* head;
	Node* tail;
	int size;

public:

	class Iterator {
	
		Node* current;
		friend class List;
		

	public:

		Iterator() {
			current = NULL;
		}

		Iterator(Node* ptr) {
			current = ptr;
		}
		
		Node* getCurrent() {
			return current;
		}

		int getSize() {
			return size;
		}

		Iterator& operator++() { // pre increment
			current = current->next;
			return *this;
		}

		Iterator operator++(int) { // post increment
			Iterator old = *this;
			current = current->next;
			return old;
		}
		Iterator& operator--() { // pre decrement
			current = current->prev;
			return *this;
		}

		Iterator operator--(int) { // post decrement
			Iterator old = *this;
			current = current->prev;
			return old;
		}
		
		T& operator*() const {
			return current->Data;
		}

		bool operator==(const Iterator& rhs) const {
			return current = rhs.current;

		}

		bool operator!=(const Iterator& rhs) const {
			return current != rhs.current;

		}
		




	};

	List() {
		head = new Node;
		tail = new Node;
		head->next = tail;
		head->prev = NULL;
		tail->prev = head;
		tail->next = NULL;
		size = 0;
	}

	~List() {
		Node* temp;
		temp = head->next;
		
		while (temp != tail) {
			temp = temp->next;
			delete temp->prev;
			
		}
		

	}

	Iterator begin() const {
		Iterator it(head->next);
		return it;
	}

	Iterator end() const {
		Iterator it(tail->prev);
		return it;
	}

	// inserting at end
	void Insert(T value) { 
		Node* temp = new Node(value, tail, tail->prev);

		tail->prev->next = temp;
		tail->prev = temp;

		size++;
		

	}

	void printForwad() {
		
		Iterator it;

		for (it = begin(); it != end(); it++) {
			cout << *it << " ";
		}
		cout << *it << endl;

	}

	void printBackward() {
		Iterator it;

		for (it = end(); it != begin(); it--) {
			cout << *it << " ";
		}
		cout <<*it<<endl;

	}
	
	int getSize() {
		return size;
	}

	bool Search(T value) const {
		
		Iterator bottom = begin();
		Iterator top = end();
		
		int low = 0;
		int high = size - 1;

		while (low <= high)
		{
			int midIndex = low + (high - low) / 2;
			
			Iterator mid = bottom;

			for (int i = 0; i < midIndex; ++i)
			{
				++mid;
			}
			if (*mid == value)
			{
				Iterator it = mid;
				return true;
			}
			else if (*mid < value)
			{
				low = midIndex + 1;
				bottom = ++mid;
			}
			else
			{
				high = midIndex - 1;
				top = mid;
			}
		}

		return false;


		
	}

	void erase(T value) {

		for (Iterator it = begin(); it != end(); it++) {
			
			if (*it == value) {

				Node* temp = it.getCurrent();

				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;

				delete temp;
				break;

			}


		}

	}




};

template <typename T>
void printList(List<T>& a)
{
	typename List<T>::Iterator it = a.begin();

	for (; it != a.end(); it++) {

		cout << *it << " ";

	}
	

	cout << *it<<endl;
}






template <typename T>
void UnionList(List<T>& a, List<T>& b, List<T>& c) //testing
{
	typename List<T>::Iterator it = a.begin();
	
	for(; it!=a.end();it++)
	{
		c.Insert(*it);
		
	}

	it = b.begin();

	for (; it != b.end(); it++)
	{
		c.Insert(*it);
		
	}
}




template <typename T>
void IntersectList(List<T>& a, List<T>& b, List<T>& c)
{
	typename List<T>::Iterator tempA = a.begin();
	

	while (tempA != a.end())
	{
		typename List<T>::Iterator tempB = b.begin();

		while (tempB != b.end())
		{
			if (*tempA == *tempB)
			{
				c.Insert(*tempA);
				break;
			}
			++tempB;
		}
		++tempA;
	}
}



template <typename T>
void DifferenceList(List<T>& a, List<T>& b, List<T>& c)
{
	typename List<T>::Iterator tempA = a.begin();

	while (tempA != a.end())
	{
		bool found = false;
		typename List<T>::Iterator tempB = b.begin();
		
		while (tempB != b.end())
		{
			if (*tempA == *tempB)
			{
				found = true;
				break;
			}
			++tempB;
		}
		if (!found)
		{
			c.Insert(*tempA);
		}
		++tempA;
	}
}



void main() {

	List<int> l , w , x,y,z;

	l.Insert(5);
	l.Insert(6);
	l.Insert(7);
	l.Insert(8);
	l.Insert(9);
	l.Insert(10);

	w.Insert(10);
	w.Insert(5);
	w.Insert(6);
	w.Insert(7);
	w.Insert(14);
	w.Insert(15);

	
	
	cout << "Printing Forward: ";
	l.printForwad();
	
	cout << "\n";

	cout << "Printing Backward: ";
	l.printBackward();

	cout << "\n";



	// hardcoding the value 5

	if (l.Search(5))
		cout << "value found";
	else
		cout << "value not found";

	cout << "\n\n";

	cout << "Erasing value 5\n";
	l.erase(5);

	cout << "\n";

	cout << "New List: ";
	l.printForwad();

	DifferenceList(l, w, x);
	
	cout << "Difference: ";
	printList(x);

	UnionList(l, w, y);
	cout << "Union: ";
	printList(y);

	cout << "2nd List: ";
	printList(w);


	IntersectList(l, w, z);
	cout << "Intersection: ";
	printList(z);


	cout << "\n";
	system("pause");
}