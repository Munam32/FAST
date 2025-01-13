#include <iostream>
using namespace std;


class BST {

	class Node {
	public:
		int data;
		Node* right;
		Node* left;


		Node(int _data, Node* _left = NULL , Node* _right = NULL) {
			data = _data;
			left = _left;
			right = _right;
		}

	};
	
	Node* root = NULL;

public:
	
	
	~BST() {
		Destructor(root);
	}
	
	void Destructor(Node*& ptr) {
		if (ptr == NULL) {
			return;
		}
		else {
			Destructor(ptr->left);
			Destructor(ptr->right);
			delete ptr;

		}
	}

	void Insert(int value) { // wrapper
		Insert(root, value);
	}
	
	void Insert(Node*& ptr, int value) {
		if (ptr == NULL) {
			ptr = new Node(value);
			return;
		}


		else if (value < ptr->data)
			Insert(ptr->left, value);

		else if (value > ptr->data)
			Insert(ptr->right, value);
		
	}
		
	
	bool Search(int value) {
		return Search(value, root);
	}

	bool Search(int value, Node* ptr) {

		if (ptr == NULL) {
			return false;
		}
		else if (ptr->data == value) {
			return true;
		}
		else if (ptr->data > value) {
			return Search(value, ptr->left);
		}
		else if (ptr->data < value) {
			return Search(value, ptr->right);
		}

		
	}
	
	void Delete(int value) {
		Delete(root,value);
	}

	Node* findMin(Node* root) {
		while (root && root->left != NULL) {
			root = root->left;
		}
		return root;
	}


	void Delete(Node*& root, int value) {

		if (root == NULL) {
			return;
		}


		if (value < root->data) {
			Delete(root->left, value);
		}


		else if (value > root->data) {
			Delete(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				Node* temp = root;
				root = root->right;
				delete temp;
			}
			else if (root->right == NULL) {
				Node* temp = root;
				root = root->left;
				delete temp;
			}

			else {
				Node* temp = findMin(root->right);
				root->data = temp->data;
				Delete(root->right, temp->data);
			}
		}


	}


	void PostOrder() {
		PostOrder(root);
	}


	void PostOrder(Node* root) {
		if (root == NULL)
			return;
		
		else {
			PostOrder(root->left);
			

			PostOrder(root->right);
			cout << root->data << " ";



		}
	}



};



void main() {

	BST Tree;

	Tree.Insert(56);
	Tree.Insert(57);
	Tree.Insert(55);
	Tree.Insert(54);
	Tree.Insert(53);
	
	bool flag = Tree.Search(56);

	cout << "Searching 56...  ";

	if (flag)
		cout << "Found";
	else
		cout << "Not Found";

	cout << endl;


	cout << "Post Order Before Deletion: ";
	Tree.PostOrder();
	
	cout << endl;

	Tree.Delete(56);

	cout << "Post Order After Deletion: ";
	Tree.PostOrder();

	
	cout << "\nSearching 56...  ";

	flag = Tree.Search(56);
	
	if (flag)
		cout << "Found";
	else
		cout << "Not Found";

	cout << endl;


	cout << "\n";
	system("pause");
}