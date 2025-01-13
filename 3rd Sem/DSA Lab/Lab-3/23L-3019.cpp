#include <iostream>
using namespace std;

template <class T>
class List {

public:
	class node {
	public:
		T data;
		node* next;
		node* prev;

	
		node() {
			prev = 0;
			next = 0;
		}
		node(T d, node*_prev=0, node* _next=0) {
			data = d;
			prev = _prev;
			next = _next;

		}


	};

	node* head;
	node* tail;


	
	List() {
		head = new node();
		tail = new node();
		head->next = tail;
		head->prev = nullptr;
		tail->next = nullptr;
		tail->prev = head;
	}
	void insertAtStart(T const element) {
		node* temp = new node(element,head , head->next);
		head->next->prev = temp;
		head->next = temp;
	
	
	}
	void insertAtEnd(T const element) {
		node* temp = new node(element, tail->prev, tail);
		tail->prev->next = temp;
		tail->prev = temp;
	}
	void insertAfter(T aft, T val) {
		node* temp = head;
		while (temp->data != aft) { // whatif element not present
			temp = temp->next;

		}
		node* temp_data = new node(val, temp, temp->next);
		temp->next->prev = temp_data;
		temp->next = temp_data;
		
	
	}
	void print() {
		node* temp = head->next;

		while (temp->next != nullptr) {
			cout << temp->data <<"\t";
			temp = temp->next;

		}
		cout << endl;
		
	}

	void DeleteStart() {
		if (head->next != tail) { // head =0 or tail =0
			node* temp = head->next;
			head->next = temp->next;
			temp->next->prev = head;
			delete temp;
		}

	}
	void DeleteEnd() {
		if (tail->prev != head) {
			node* temp = tail->prev;
			tail->prev = temp->prev;
			tail->prev->next = tail;
			delete temp;
		}
	}
	void DeleteElement(const T& element) {
		node* temp = head->next;
		while (temp->data != element) {
			temp = temp->next;
		}
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
	}

	void RemoveDuplicates() {
		node* temp = head;
		while (temp->next != 0) {
			T Data = head->data;
			node* temp2 = temp->next;
			while (temp2->next != 0) {
				if (temp2->data == Data) {
					temp2->prev->next = temp2->next;
					temp2->next->prev = temp2->prev;
				}
				temp2 = temp2->next;
			}
			temp = temp->next;
		}
	}

	void Mean() {
		node* temp = head;
		int sum=0;
		int count = 0;

		while (temp != tail) {
			sum+= temp->data;
			count++;
			temp = temp->next;
		}
		count--;
		cout << "Mean: " << (sum / count * 1.0) << endl;

	}
	
	void Middle() {
		node* temp = head;
		int middle;
		int count = 0;

		while (temp != tail) {
			count++;
			temp = temp->next;
		}
		count--;
		
		
		middle = count / 2;
		for (int i = 0; i < middle; i++) {
			temp = temp->prev;
		}
		cout << "Middle element: " << temp->data << endl;
		
	}
	node* Sort(node* head) {
		if (head == 0 || head->next == 0) {
			return head;
		}
		node* curr = head->next;
		node* key=0;
		node* prevNode=0;

		while (curr != 0) {
			key = curr;
			curr = curr->prev;
		}
		while (prevNode != NULL && prevNode->data>key->data) {
			prevNode->next->data = prevNode->data;
			prevNode = prevNode->prev;

			if (prevNode == 0) {
				head->data = key->data;
			}
			else {
				prevNode->next->data = key->data;
			}
			curr = curr->next;
		}
		node* temp = head->next;
		while (temp->next != NULL) {
			cout << temp->data << "\t";
			temp = temp->next;
		}
		cout << endl;
	}
	void MinMax() {
		cout << "Minimum Value: " << head->next->data<<endl;
		cout << "Maximum Value: " << tail->prev->data<<endl;
	 }
	
	~List() {
		while (head->next != tail) {
			DeleteStart();
		}
		delete head;
		delete tail;
	}

};













void main() {
	List <int> l;

	l.insertAtEnd(10);
	l.insertAtEnd(20);
	l.print();

	l.insertAtStart(5);
	l.print();
	l.insertAtEnd(30);
	l.print();
	l.insertAfter(10, 15);
	l.Sort(l.head);
	l.MinMax();
	l.print();

	
	l.DeleteStart();
	l.print();
	l.DeleteEnd();
	l.print();
	l.DeleteElement(15);
	l.print();

	l.RemoveDuplicates();
	l.print();

	l.Mean();
	l.Middle();

	cout << "\n";
	system("pause");
}	