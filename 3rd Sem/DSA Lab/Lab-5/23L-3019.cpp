# include <iostream>
using namespace std;
template <class T>
class List {
	friend class Queue;

	class Node {
	public:
		T data;
		Node* next;



		Node(T _data, Node* _next = 0) {
			data = _data;
			next = _next;


		}
		Node() {
			next = 0;

		}


	};

	Node* head;
	Node* tail;

public:
	List() {
		head = NULL;
		tail = NULL;


	}
	~List() {
		Node* temp = head->next;
		Node* temp_prev = head;

		while (temp != head) {
			delete temp_prev;
			temp_prev = temp;
			temp = temp->next;
		}
	
	}

	void Insert(T d) {
		Node* temp = new Node(d);

		if (head == NULL) {
			head = temp;
			temp->next = tail;
			tail = temp;
		}
		else {
			tail->next = temp;
			temp->next = head;
			tail = temp;

		}
	}

	Node* Search(T d) {
		Node* temp = head;
		Node* temp_prev = temp;

		if (temp->data == d)
			return head;

		temp = temp->next;


		while (temp != head) {

			if (temp->data == d)
				return temp_prev;

			temp = temp->next;
			temp_prev = temp_prev->next;
		}

		return 0;


	}
	

	void InsertBefore(T v1, T v2) {

		Node* temp2 = Search(v2);


		if (head == tail && temp2 != 0) {
			Node* temp = new Node(v1);
			temp->next = head;
			head = temp;
			tail->next = head;
		}
		else if (temp2 != 0) {
			Node* temp = new Node(v1);
			Node* ptr = temp2->next;

			temp2->next = temp;
			temp->next = ptr;



		}


	}

	void Update(T d_find, T d_add) {
		Node* temp = Search(d_find);

		if (temp == head) {
			temp->data = d_add;

		}
		else if (temp != 0)
			temp->next->data = d_add;
		else
			cout << "No value found , so can not add\n";

	}
		



	
	bool Check() {
		return (tail->next == head);

	}

	void print() {
		Node* temp = head;

		cout << temp->data << " ";

		temp = temp->next;

		while (temp != head) {
			cout << temp->data << " ";
			temp = temp->next;
		}

		cout << "\n";
		
	}
	

	

};



class Queue {
	
	
	List<int> Q;

	
	int size;

public:
	void enqueue(int d) {

		if (!(this->isFull())) {
			Q.Insert(d);
			size++;
		}
	}
	int dequeue() {
		// not empty condition
		int temp = Q.head->data;
		Q.head = Q.head->next;
		Q.tail->next = Q.head;
		size--;
		return temp;
	}
	bool isFull() {
		if (Q.tail == Q.head && Q.head != NULL && Q.tail != NULL && size!=1) {
			return true;
		}
		else
			return false;
	}
	int GetSize() {
		return size;
	}
	bool isEmpty() {
		if (Q.head != Q.tail)
			return true;
		else
			return false;

	}

	int front() {
		return Q.head->data;
	}

	int rear() {
		return Q.tail->data;
	}

	void print() {
		Q.print();
	}


	
	
	

};

void main() {

	List <int> CL;

	CL.Insert(5);
	CL.Insert(6);
	CL.Insert(7);

	CL.print();

	

	CL.InsertBefore(5, 7);
	CL.print();

	if (CL.Search(6) != 0) {
		cout << "Value Found\n";

	}
	else
		cout << "Value Not Found\n";

	
	
	CL.Update(5, 6);
	cout << CL.Check()<<endl;

	CL.print();



	Queue obj,obj2;

	/*obj.enqueue(1);
	obj.enqueue(2);
	obj.enqueue(3);
	obj.enqueue(4);

	obj.print();

	cout << endl;
	cout<<obj.dequeue()<<endl;

	obj.print();

	cout << obj.front() << endl;
	cout << obj.rear() << endl;
	cout << obj.isFull() << endl;
	cout << obj.isEmpty() << endl;*/



	/*obj.enqueue(3);
	obj.enqueue(2);
	obj.enqueue(5);
	obj.enqueue(6);
	obj.enqueue(7);
	obj.enqueue(9);
	obj.enqueue(8);
	obj.enqueue(4);

	int temp = obj.GetSize();
	

	for (int i = 0; i < temp/2; i++) {
		obj2.enqueue(obj.dequeue());
		
	}
	for (int i = 0; i < temp / 2; i++) {
		obj2.enqueue(obj2.dequeue());
		obj2.enqueue(obj.dequeue());

	}

	obj2.print();*/


	cout << "\n";
	system("pause");
}