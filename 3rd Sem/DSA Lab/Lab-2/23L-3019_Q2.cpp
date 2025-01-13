
#include <iostream>
using namespace std;

template <class T>
class List
{
private:

	class node
	{
	public:
		T data;
		node* next;

		node()
		{
			data = 0;
			next = NULL;
		}

		node(int d)
		{
			data = d;
			next = NULL;
		}
	};

	node* head, * tail;

public:
	List()
	{
		head = NULL;
		tail = NULL;
	}

	void InsertatHead(T d)
	{
		node* temp = new node(d);
		if (head == NULL)
		{
			tail = temp;
		}
		else
		{
			temp->next = head;

		}
		head = temp;
	}

	bool SearchNode(T d)
	{
		node* temp = head;
		while (temp != tail)
		{
			if (temp->data == d)
			{
				return 1;
			}
			temp = temp->next;
		}
		return 0;
	}

	void ReverseList()
	{
		node* current = head;
		node* prev = NULL;
		node* next = NULL;

		while (current != NULL)
		{
			next = current->next;
			current->next = prev;
			prev = current;
			current = next;
		}

		tail = head;
		head = prev;
	}

	void DeleteElement(T d) 
	{
		node* temp = head;
		node* current = NULL;
		node* prev = NULL;
		node* nxt = NULL;
		while (temp != tail)
		{
			if (temp->next->data == d)
			{
				prev = temp;
				current = temp->next;
				nxt = temp->next->next;
			}
			temp = temp->next;
		}
		prev->next = nxt;
		delete current;
	}


	void print()
	{
		cout << "List: ";
		node* temp = head;
		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
};



void main()
{
	List <int>LL;

	LL.InsertatHead(5);
	LL.InsertatHead(4);
	LL.InsertatHead(3);
	LL.InsertatHead(2);
	LL.InsertatHead(1);

	LL.print();

	int value = 0;

	cout << "Enter a value to search for: ";
	cin >> value;

	if (LL.SearchNode(value))
	{
		cout << value << " found in the list!\n";
	}
	else
	{
		cout << "Value not found!\n";
	}


	cout << "Enter a value to delete: ";
	cin >> value;

	LL.ReverseList();
	LL.print();

	LL.DeleteElement(value);
	cout << "Reverse";
	LL.print();


	cout << "\n";
	system("pause");

}