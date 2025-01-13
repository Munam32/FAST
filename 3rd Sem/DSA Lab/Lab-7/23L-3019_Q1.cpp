//#include <iostream>
//using namespace std;
//
//
//class BST {
//
//	struct Node {
//		int Data;
//		Node* Left;
//		Node* Right;
//
//		Node(int _d, Node* _l, Node* _R) {
//			Data = _d;
//			Left = _l;
//			Right = _R;
//		}
//	};
//
//	Node* root = NULL;
//
//
//public:
//
//	BST(int _d, Node* _l, Node* _R) {
//		root = new Node(_d, _l, _R);
//	}
//
//	BST(BST& obj) {
//		DeepCopy(obj.root);
//		
//	}
//
//
//	void DeepCopy(Node* r) {
//
//		if (root == NULL) {
//			cout << "Tree is empty\n";
//		}
//		else if()
//
//	}
//
//	
//	
//	bool Insert(int d) {
//
//		return Insert(d, root);
//	}
//
//	bool Insert(int d, Node* r) {
//
//
//		if (r == NULL) {
//
//			r = new Node(d, NULL, NULL);
//			return true;
//
//		}
//		else if (d == r->Data)
//			return false;
//
//		else if (d < r->Data)
//			Insert(d, r->Left);
//		else
//			Insert(d, r->Right);
//
//		
//
//
//	}
//
//
//
//
//		
//
//	
//
//};
//
//
//
//
//
//
//
//
//void main() {
//
//
//	BST Tree(5,NULL,NULL);
//
//	cout<<Tree.Insert(5);
//
//	cout << "\n";
//	system("pause");
//}



#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(NULL), right(NULL){}
};

class BST {
private:
    Node* root;

    bool insert(Node*& node, int v) {

        if (node == NULL) {
            node = new Node(v);
            return true;
        }

        if (v < node->data) {
            return insert(node->left, v);
        }

        else if (v > node->data) {
            return insert(node->right, v);
        }

        else {
            return false; // Value already exists
        }
    }

    Node* copy(Node* node) {
        if (node == NULL) {
            return NULL;
        }

        Node* newNode = new Node(node->data);
        
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        
        return newNode;
    }

    
    void inorderPrint(Node* node) const {
        if (node != NULL) {

            inorderPrint(node->left);
            
            cout << node->data << " ";
            
            inorderPrint(node->right);
        }
    }

    
    void printLevel(Node* node, int level) const {
        if (node == NULL) return;
        if (level == 0) {
            cout << node->data << " ";
        }
        else if (level > 0) {

            printLevel(node->left, level - 1);
            printLevel(node->right, level - 1);

        }
    }

    void levelorderPrint(Node* node) const {
        
        int height = getHeight(node);

        for (int i = 0; i < height; i++) {
            printLevel(node, i);
            cout << "\n";
        }
    }

  
    int getHeight(Node* node) const {
        if (node == NULL) {
            return 0;
        }

        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        return max(leftHeight, rightHeight) + 1;
    }


    Node* search(Node* node, int val) {
        if (node == NULL || node->data == val) {
            return node;
        }
        if (val < node->data) {
            return search(node->left, val);
        }
        else {
            return search(node->right, val);
        }
    }

   
    int countNodes(Node* node) const {
        if (node == NULL) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

   
    int leafCount(Node* node) const {
        if (node == NULL) {
            return 0;
        }
        if (node->left == NULL && node->right == NULL) {
            return 1;
        }
        return leafCount(node->left) + leafCount(node->right);
    }


    void destroy(Node* node) {
        if (node != NULL) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }
   

// setting wrapper funcs
public:
    BST() : root(NULL) {}

    
    bool insert(int v) {
        return insert(root, v);
    }

 
    BST(const BST& other) {
        root = copy(other.root);
    }

    
    void inorderPrint() const {
        inorderPrint(root);
        cout << endl;
    }

    
    void levelorderPrint() const {
        levelorderPrint(root);
    }

    
    Node* search(int key) {
        return search(root, key);
    }

    
    int countNodes() const {
        return countNodes(root);
    }

    
    int leafCount() const {
        return leafCount(root);
    }

    
    ~BST() {
        destroy(root);
    }

};

// Example usage
void main() {
    BST tree;
    tree.insert(52);
    tree.insert(48);
    tree.insert(32);
    tree.insert(5);
    tree.insert(8);
    tree.insert(-1);
    bool val = tree.insert(2);

    if (!val) {
        cout << "Value already exists\n";
    }
    

    cout << "Inorder print: ";
    tree.inorderPrint();

    cout << "Level order print: " << endl;
    tree.levelorderPrint();

    cout << "Total nodes: " << tree.countNodes() << endl;
    cout << "Leaf nodes: " << tree.leafCount() << endl;

    Node* found = tree.search(7);
    cout << (found ? "7 Found" : "Not found") << endl;

    
    cout << "\n";
    system("pause");

    
}
