#include <iostream>

using namespace std;

template<class T>
class Stack {

	class Node {
	public:
		T data;
		Node* next;

	
		Node(T _data, Node* _next) {
			data = _data;
			next = _next;
		}

	};

	int TotalItems = 0;
	Node* head = NULL;
	Node* tail = NULL;

public:
	
	~Stack() {
		if (!IsEmpty()) {
			Node* temp = head->next;
			Node* curr = head;
			while (temp != NULL) {
				delete curr;
				curr = temp;
				temp = temp->next;
			}
			delete curr;
		}
	}

	void Push(const T& item) {

		if (head == NULL & tail == NULL) {
			tail = new Node(item, NULL);
			head = tail;
		}
		else {
			tail->next = new Node(item, NULL);
			tail = tail->next;

		}
		TotalItems++;

		
	}
	
	T Pop() {
		if (!IsEmpty()) {
			
			if (head == tail) {
				T temp_data = tail->data;
				head = NULL;
				tail = NULL;
				
				TotalItems--;

				return temp_data;
					
			}
			else {


				Node* temp = head;

				while (temp->next != tail) temp = temp->next;

				T temp_data = tail->data;

				delete tail;

				tail = temp;
				tail->next = NULL;

				TotalItems--;
				return temp_data;
			}

		}
		
	}

	T TopItem() const {

		if (!IsEmpty())
			return tail->data;
		else
			cout << "No Element Present\n";

	}

	bool IsEmpty() const {
		return TotalItems == 0;
	}

	void Clear() {
		Clear (head);
	}


	void Clear(Node* ptr){
		
		if (IsEmpty()) {

			if (ptr == tail) {
				return;
			}
			else {
				Clear(ptr->next);
				delete ptr;
			}

		}
		TotalItems = 0;
		head = NULL;
		tail = NULL;




	}

	int Size() const {
		return TotalItems;
	}

	void Print() {

		if (head != NULL) {

			Node* temp = head;

			while (temp != NULL) {
				cout << temp->data<<" ";
				temp = temp->next;
			}

			cout << endl;
		}
		else {
			cout << "Stack is empty\n";
		}
	}

	bool IsFullyParenthesized(const string& expression, int index, Stack<char>& bracketStack) {
		// Base case: if we've processed the entire string
		if (index == expression.length()) {
			return bracketStack.IsEmpty();
		}

		char currentChar = expression[index];

		// If the current character is an opening bracket, push it onto the stack
		if (currentChar == '(' || currentChar == '[' || currentChar == '{') {
			bracketStack.Push(currentChar);
		}
		// If the current character is a closing bracket, check if it matches the top of the stack
		else if (currentChar == ')' || currentChar == ']' || currentChar == '}') {
			if (bracketStack.IsEmpty()) {
				return false;  // There's no matching opening bracket
			}

			char top = bracketStack.TopItem();
			if ((currentChar == ')' && top == '(') ||
				(currentChar == ']' && top == '[') ||
				(currentChar == '}' && top == '{')) {
				bracketStack.Pop();  // Matching pair, pop from stack
			}
			else {
				return false;  // Mismatched brackets
			}
		}

		// Move to the next character
		return IsFullyParenthesized(expression, index + 1, bracketStack);
	}

	bool IsFullyParenthesized(const string& expression) {
		Stack<char> bracketStack;
		return IsFullyParenthesized(expression, 0, bracketStack);

	}
};



void main() {

	Stack<int> Stack;

	/*Stack.Push(5);
	Stack.Push(6);
	Stack.Push(7);
	Stack.Push(8);
	Stack.Push(9);


	cout << "Size Of Stack: " << Stack.Size()<<endl;

	cout << "Top Element: " << Stack.TopItem()<<endl;

	cout << "Original Stack: ";
	Stack.Print();



	cout << "Removing Top 2 elements: ";
	int data = Stack.Pop();
	cout << data<<" ";
	data = Stack.Pop();
	cout << data << endl;

	cout << "Modified Stack: ";
	Stack.Print();

	cout << "Calling Clear Method\n";
	Stack.Clear();
	Stack.Print();

	bool flag = Stack.IsEmpty() ? true : false;

	if (flag) {
		cout << "Stack Empty\n";
	}
	else
		cout << "Stack Not Empty\n";

	cout << "Size Of Stack: " << Stack.Size() << endl;
*/


	string expression;

	cout << "Enter String: ";
	cin >> expression;

	bool flag = Stack.IsFullyParenthesized(expression);

	flag ? cout << "Is Parenthesized" : cout << "Is Not Parenthesized";

	




	cout << "\n";
	system("pause");
}