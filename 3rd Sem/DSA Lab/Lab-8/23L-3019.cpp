#include <iostream>
using namespace std;


class LibrarySystem {

	class BookNode {
	public:
		int bookId;
		string title;
		BookNode* left;
		BookNode* right;
		int height;


	

		BookNode(int _bookId, string _title,BookNode* _left, BookNode* _right,int _height=0) {
			bookId = _bookId;
			title = _title;
			left = _left;
			right = _right;
			height = _height;
		}
		BookNode() {
			bookId = 0;
			title = "";
			left = 0;
			right = 0;
			height = 0;
		}


	};
	BookNode* root;

public:
	LibrarySystem() {
		root = new BookNode();
	}

	int CalcHeight(BookNode*& ptr) {
		return ptr == NULL ? -1 : ptr->height;

	}


	void addBook(int ID, string title){
		addBook(ID, title, root);
	}

	void addBook(int& ID, string& title,BookNode*& ptr) {
		if (ptr == NULL)
			ptr = new BookNode(ID, title, NULL, NULL);
		
		else if (ID < ptr->bookId) {
			addBook(ID, title, ptr->left);
		}
		else if (ID > ptr->bookId) {
			addBook(ID, title, ptr->right);
		}

		balance(ptr);
	}

	void balance(BookNode*& ptr) {
		if (ptr == NULL) {
			return;
		}
		
		if (CalcHeight(ptr->left) - CalcHeight(ptr->right) > 1) {
			if (CalcHeight(ptr->left->left) >= CalcHeight(ptr->right->left)) {
				rotateWithleftChild(ptr);
			}
			else {
				doubleWithleftChild(ptr);
			}
		}

		else if (CalcHeight(ptr->right) - CalcHeight(ptr->left) > 1) {
			if (CalcHeight(ptr->right->right) >= CalcHeight(ptr->right->left)) {
				rotateWithrightChild(ptr);
			}
			else
				doubleWithrightChild(ptr);
		}
		ptr->height = max(CalcHeight(ptr->left), CalcHeight(ptr->right));
	}

	void rotateWithleftChild(BookNode*& k2) {
		BookNode* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(CalcHeight(k2->left), CalcHeight(k2->right)) + 1;
		k1->height = max(CalcHeight(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void rotateWithrightChild(BookNode*& k1) {
		BookNode* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;

		k1->height = max(CalcHeight(k1->left), CalcHeight(k1->right)) + 1;
		k2->height = max(CalcHeight(k2->left), k2->height) + 1; //calcHeight(k2->right)
		k1 = k2;
	}

	void doubleWithleftChild(BookNode*& k3) {
		rotateWithrightChild(k3->left);
		rotateWithleftChild(k3);
	}

	void doubleWithrightChild(BookNode*& k3) {
		rotateWithrightChild(k3->right);
		rotateWithleftChild(k3);
	}


	int getTotalBooks() {
		return getTotalBooks(root);
	}


	int getTotalBooks(BookNode*& ptr) {
		if (ptr == NULL) {
			return 0;
		}
		else
			return 1 + getTotalBooks(ptr->left) + getTotalBooks(ptr->right);



	}

	void inorderPrint() {
		inorderPrint(root);
	}

	void inorderPrint(BookNode* node) const {
		if (node != NULL) {

			inorderPrint(node->left);
			
			if(node!=root)
				cout << node->bookId << " " << node->title<<"\n";

			inorderPrint(node->right);
		}
	}



};











void main() {

	LibrarySystem L1;
	L1.addBook(10, "pata nhi");
	L1.addBook(20, "pata nhi");
	L1.addBook(30, "pata nhi");
	L1.addBook(40, "pata nhi");
	L1.addBook(50, "pata nhi");

	
	L1.inorderPrint();

	cout << "Total books: " << L1.getTotalBooks()-1;

	cout << "\n";
	system("pause");
}