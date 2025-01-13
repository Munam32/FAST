# include <iostream>
# include <list>
using namespace std;

template <class T>
class User {

	class UserList {
	public:
		int UserID;
		string UserName;
		string Email;
		string Country;
		string Type;

		UserList* next;
		UserList* prev;


		UserList(int _UserID = 0, string _UserName = "", string _Email = "", string _Country = "", string _Type = "", UserList* _next = NULL, UserList* _prev = NULL) {
			UserID = _UserID;
			UserName = _UserName;
			Email = _Email;
			Country = _Country;
			Type = _Type;
			next = _next;
			prev = _prev;
		}
	};

	class AVL_Index {
	public:
		int height;
		T UserID;
		UserList* list = NULL;
		AVL_Index* left = NULL;
		AVL_Index* right = NULL;

		AVL_Index(T _UserID, UserList* _list, AVL_Index* _left, AVL_Index* _right) {
			UserID = _UserID;
			list = _list;
			left = _left;
			right = _right;
		}

	};

	class AVL_Index_UserName {
	public:
		int height;
		string UserName = "";
		UserList* list = NULL;
		AVL_Index_UserName* left = NULL;
		AVL_Index_UserName* right = NULL;

		AVL_Index_UserName(string _UserName, UserList* _list, AVL_Index_UserName* _left, AVL_Index_UserName* _right) {
			UserName = _UserName;
			list = _list;
			left = _left;
			right = _right;
		}


	};

	class AVL_Index_Email {
	public:
		int height;
		string Email = "";
		UserList* list = NULL;
		AVL_Index_Email* left = NULL;
		AVL_Index_Email* right = NULL;

		AVL_Index_Email(string _Email, UserList* _list, AVL_Index_Email* _left, AVL_Index_Email* _right) {
			Email = _Email;
			list = _list;
			left = _left;
			right = _right;
		}


	};


	class Group { 
	public:
		string Index;
		list<UserList*> Users;
		Group* left = NULL;
		Group* right = NULL;
		int height;

		Group(string _Index, Group* _left, Group* _right) {
			Index = _Index;
			left = _left;
			right = _right;
			

			
		}

	};


	UserList* head = NULL;
	UserList* tail = NULL;
	AVL_Index* root_ID = NULL;
	AVL_Index_UserName* root_UserName = NULL;
	AVL_Index_Email* root_Email = NULL;
	Group* root_Country = NULL;
	Group* root_Type = NULL;


	void DeleteInGroups(UserList* ptr) {
		
		Group* temp = GetGroupIndex(ptr->Country, root_Country);
		
		if (!((temp->Users).empty())) {

			for (auto it = (temp->Users).begin(); it != (temp->Users).end(); ) {

				if ((*it)->UserID == ptr->UserID) {
					it = (temp->Users).erase(it);
				}
				else {
					++it; // Increment the iterator only if no removal
				}
			}

		}

		if ((temp->Users).empty()) {
			DeleteGroup(root_Country, ptr->Country);
		}

		
		temp = GetGroupIndex(ptr->Type, root_Type);

		if (!((temp->Users).empty())) {

			for (auto it = (temp->Users).begin(); it != (temp->Users).end(); ) {

				if ((*it)->UserID == ptr->UserID) {
					it = (temp->Users).erase(it);
				}
				else {
					++it; // Increment the iterator only if no removal
				}
			}

		}

		if ((temp->Users).empty()) {
			DeleteGroup(root_Type, ptr->Type);
		}



			
	}
	void DeleteInUserNameTree(AVL_Index_UserName*& root,string value) {
		
		if (root == NULL) {
			return;
		}


		if (value < root->UserName) {
			DeleteIndexUserName(root->left, value);
		}


		else if (value > root->UserName) {
			DeleteIndexUserName(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				//DeleteInList(root->list);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				AVL_Index_UserName* temp = root;
				root = root->right;
				//DeleteInList(temp->list);
				delete temp;
			}
			else if (root->right == NULL) {
				AVL_Index_UserName* temp = root;
				root = root->left;
				//DeleteInList(temp->list);
				delete temp;
			}

			else {
				AVL_Index_UserName* temp = findMin(root->right);
				root->UserName = temp->UserName;
				root->list = temp->list;
				root->height = temp->height; // check
				DeleteIndexUserName(root->right, temp->UserName);
			}
		}

		balance(root);

	}
	void DeleteInEmailTree(AVL_Index_Email*& root,string value) {
		
		if (root == NULL) {
			return;
		}


		if (value < root->Email) {
			DeleteIndexEmail(root->left, value);
		}


		else if (value > root->Email) {
			DeleteIndexEmail(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				//DeleteInList(root->list);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				AVL_Index_Email* temp = root;
				root = root->right;
				//DeleteInList(temp->list);
				delete temp;
			}
			else if (root->right == NULL) {
				AVL_Index_Email* temp = root;
				//DeleteInList(temp->list);
				root = root->left;
				delete temp;
			}

			else {
				AVL_Index_Email* temp = findMin(root->right);
				root->Email = temp->Email;
				root->list = temp->list;
				root->height = temp->height; // check
				DeleteIndexEmail(root->right, temp->Email);
			}
		}

		balance(root);
	}
	
	void DeleteUserID(T ID) {

	}

public:
	~User() {
		// List deallocation
		if (head != NULL && tail != NULL) {

			if (head == tail) {
				delete head;
			}
			else {
				UserList* temp = head->next;
				UserList* curr = head;
				
				while (temp!= NULL) {
					
					delete curr;
					curr = temp;
					temp = temp->next;
				}
				delete curr;
				

			}
		}
		// Tree Deallocation + GROUP trees de allocatioon
		DeAllocateTree(root_ID);
		DeAllocateTree(root_UserName);
		DeAllocateTree(root_Email);
		DeAllocateTree(root_Type);
		DeAllocateTree(root_Country);
	
	}
	void DeAllocateTree(AVL_Index*& root) {
		if (root == NULL) {
			return;
		}
		else {
			DeAllocateTree(root->left);
			DeAllocateTree(root->right);

			delete root;
		}
	}
	void DeAllocateTree(AVL_Index_UserName*& root) {
		if (root == NULL) {
			return;
		}
		else {
			DeAllocateTree(root->left);
			DeAllocateTree(root->right);

			delete root;
		}
	}
	void DeAllocateTree(AVL_Index_Email*& root) {
		if (root == NULL) {
			return;
		}
		else {
			DeAllocateTree(root->left);
			DeAllocateTree(root->right);

			delete root;
		}
	}
	void DeAllocateTree(Group*& root) {
		if (root == NULL) {
			return;
		}
		else {
			DeAllocateTree(root->left);
			DeAllocateTree(root->right);

			delete root;
		}
	}
	


	// LIST FUNCS
	void InsertListAtStart(int UserID, string UserName, string Email, string Country, string Type) {
		if (!head) {
			UserList* temp = new UserList(UserID, UserName, Email, Country, Type, NULL, NULL);
			head= temp;
			tail= temp;
			InsertInAvlIndex(UserID, temp, root_ID);
			InsertInAvlIndexUserName(UserName, temp, root_UserName);
			InsertInAvlIndexEmail(Email, temp, root_Email);
		}
		else {
			UserList* temp = new UserList(UserID, UserName, Email, Country, Type, head, NULL);
			head->prev = temp;
			head = temp;
			InsertInAvlIndex(UserID, temp, root_ID);
			InsertInAvlIndexUserName(UserName, temp, root_UserName);
			InsertInAvlIndexEmail(Email, temp, root_Email);
		}
	}
	void InsertListAtEnd(int UserID, string UserName, string Email, string Country, string Type) {
		if (!head) { // checks if there is no element in the list

			UserList* temp = new UserList(UserID, UserName, Email, Country, Type, NULL, tail);
			tail->next = temp;
			tail = temp;
			InsertInAvlIndex(UserID, temp, root_ID);
			InsertInAvlIndexUserName(UserName, temp, root_UserName);
			InsertInAvlIndexEmail(Email, temp, root_Email);
		}
		else {
			UserList* temp = new UserList(UserID, UserName, Email, Country, Type, NULL, tail);
			tail->next = temp;
			tail = temp;
			InsertInAvlIndex(UserID, temp, root_ID);
			InsertInAvlIndexUserName(UserName, temp, root_UserName);
			InsertInAvlIndexEmail(Email, temp, root_Email);
		}
	}
	void InsertInList(int UserID, string UserName, string Email, string Country, string Type) {

		if (head && tail) { // checks if there are multple nodes in list

			if (UserID < head->UserID) {
				InsertListAtStart(UserID, UserName, Email, Country, Type);
			}
			else if (UserID > tail->UserID) {
				InsertListAtEnd(UserID, UserName, Email, Country, Type);
			}
			else {
				UserList* temp = head->next;

				while (temp->UserID < UserID) {
					temp = temp->next;
				}

				UserList* temp2 = new UserList(UserID, UserName, Email, Country, Type, temp, temp->prev);
				temp->prev->next = temp2;
				temp->prev = temp2;

				InsertInAvlIndex(UserID, temp2, root_ID);	
				InsertInAvlIndexUserName(UserName, temp2, root_UserName);
				InsertInAvlIndexEmail(Email, temp2, root_Email);
			}

		}
		else
			InsertListAtStart(UserID, UserName, Email, Country, Type);

		


	}
	
	// called when sure that element is present in list
	void DeleteInList(UserList*ptr) {
		
		if (ptr != NULL && head != NULL && tail != NULL) {


			if (ptr == head && ptr == tail) {
				delete ptr;
				head = NULL;
				tail = NULL;
			}

			else if (ptr == head && ptr != tail) {
				head = head->next;
				delete head->prev;
				head->prev = NULL;
			}
			else if (ptr == tail && ptr != head) {
				tail = tail->prev;
				delete tail->next;
				tail->next = NULL;
			}
			else {
				ptr->prev->next = ptr->next;
				ptr->next->prev = ptr->prev;
				delete ptr;
			}
		}
		else {
			cout << "List is Empty\n";
		}
	}  
	void PrintList() {

		if (head && tail) {
			UserList* temp = head;

			while (temp) {
				cout << "UserID: " << temp->UserID << endl;
				cout << "User Name: " << temp->UserName << endl;
				cout << "Email: " << temp->Email << endl;
				cout << "Country: " << temp->Country << endl;
				cout << "Member Type: " << temp->Type << endl;
				cout << "--------------------------------------------------------------" << endl;
				temp = temp->next;

			}
		}
		else {
			cout << "No User Entered\n";
		}

	}
	



	// AVL INDEX FUNCS

	void Search_Index(T ID) {
		Search_Index(root_ID, ID);
	}
	void Search_Index(AVL_Index* root, T ID) {


		if (root == NULL) {
			cout << "No User Found\n";
			return;
		}


		if (root->UserID == ID) {
			cout << "UserID: " << root->UserID << endl;
			cout << "User Name: " << root->list->UserName << endl;
			cout << "Email: " << root->list->Email << endl;
			cout << "Country: " << root->list->Country << endl;
			cout << "Member Type: " << root->list->Type << endl;
			cout << "--------------------------------------------------------------" << endl;
			return;
		}


		else if (ID > root->UserID)
			Search_Index(root->right, ID);
		else
			Search_Index(root->left, ID);



	}
	int CalcHeight(AVL_Index*& ptr) {
		return ptr == NULL ? -1 : ptr->height;

	}
	void InsertInAvlIndex(T UserID, UserList* list, AVL_Index*& ptr) {
		if (ptr == NULL)
			ptr = new AVL_Index(UserID, list, NULL, NULL);

		else if (UserID < ptr->UserID) {
			InsertInAvlIndex(UserID, list, ptr->left);
		}
		else if (UserID > ptr->UserID) {
			InsertInAvlIndex(UserID, list, ptr->right);
		}

		balance(ptr);

		
		
	}
	void balance(AVL_Index*& ptr) {
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
	void rotateWithleftChild(AVL_Index*& k2) {
		AVL_Index* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(CalcHeight(k2->left), CalcHeight(k2->right)) + 1;
		k1->height = max(CalcHeight(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void rotateWithrightChild(AVL_Index*& k1) {
		AVL_Index* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;

		k1->height = max(CalcHeight(k1->left), CalcHeight(k1->right)) + 1;
		k2->height = max(CalcHeight(k2->left), k2->height) + 1; //calcHeight(k2->right)
		k1 = k2;
	}
	void doubleWithleftChild(AVL_Index*& k3) {
		rotateWithrightChild(k3->left);
		rotateWithleftChild(k3);
	}
	void doubleWithrightChild(AVL_Index*& k3) {
		rotateWithrightChild(k3->right);
		rotateWithleftChild(k3);
	}
	AVL_Index* findMin(AVL_Index* root) {
		while (root && root->left != NULL) {
			root = root->left;
		}
		return root;
	}
	void DeleteIndex(T ID) {
		DeleteIndex(root_ID, ID);
	}
	void DeleteIndex(AVL_Index*& root, T value) {

		// works from in order successor


		if (root == NULL) {
			return;
		}


		if (value < root->UserID) {
			DeleteIndex(root->left, value);
		}


		else if (value > root->UserID) {
			DeleteIndex(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				DeleteInList(root->list);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				AVL_Index* temp = root;
				root = root->right;
				DeleteInList(temp->list);
				
				delete temp;

			}
			else if (root->right == NULL) {
				AVL_Index* temp = root;
				root = root->left;
				DeleteInList(temp->list);
				delete temp;
			}

			else {
				AVL_Index* temp = findMin(root->right);
				root->UserID = temp->UserID;
				root->list = temp->list;
				root->height = temp->height; // check
				DeleteIndex(root->right, temp->UserID);
			}
		}

		balance(root);




	}
	void PrintIndices(AVL_Index* root) {
		// Empty Tree
		if (root == NULL) {
			cout << "No Indice Found\n";
			return;
		}

		// Recur on the left subtree
		PrintIndices(root->left);

		// Visit the current node
		cout << root->UserID << endl;

		// Recur on the right subtree
		PrintIndices(root->right);
	}

	// AVL UserName Index Funcs

	void InsertInAvlIndexUserName(string UserName, UserList* list, AVL_Index_UserName*& ptr) {
		if (ptr == NULL)
			ptr = new AVL_Index_UserName(UserName, list, NULL, NULL);

		else if (UserName < ptr->UserName) {
			InsertInAvlIndexUserName(UserName, list, ptr->left);
		}
		else if (UserName > ptr->UserName) {
			InsertInAvlIndexUserName(UserName, list, ptr->right);
		}

		balance(ptr);



	}
	void SearchUserName(string Name) {
		SearchUserName(root_UserName, Name);
	}
	void SearchUserName(AVL_Index_UserName* root, string Name) {


		if (root == NULL) {
			return;
		}


		if (root->UserName == Name) {
			cout << "UserID: " << root->list->UserID << endl;
			cout << "User Name: " << root->list->UserName << endl;
			cout << "Email: " << root->list->Email << endl;
			cout << "Country: " << root->list->Country << endl;
			cout << "Member Type: " << root->list->Type << endl;
			cout << "--------------------------------------------------------------" << endl;
			return;
		}


		else if (Name > root->UserName)
			SearchUserName(root->right, Name);
		else
			SearchUserName(root->left, Name);



	}
	
	int CalcHeight(AVL_Index_UserName*& ptr) {
		return ptr == NULL ? -1 : ptr->height;

	}
	void balance(AVL_Index_UserName*& ptr) {
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
	void rotateWithleftChild(AVL_Index_UserName*& k2) {
		AVL_Index_UserName* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(CalcHeight(k2->left), CalcHeight(k2->right)) + 1;
		k1->height = max(CalcHeight(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void rotateWithrightChild(AVL_Index_UserName*& k1) {
		AVL_Index_UserName* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;

		k1->height = max(CalcHeight(k1->left), CalcHeight(k1->right)) + 1;
		k2->height = max(CalcHeight(k2->left), k2->height) + 1; //calcHeight(k2->right)
		k1 = k2;
	}
	void doubleWithleftChild(AVL_Index_UserName*& k3) {
		rotateWithrightChild(k3->left);
		rotateWithleftChild(k3);
	}
	void doubleWithrightChild(AVL_Index_UserName*& k3) {
		rotateWithrightChild(k3->right);
		rotateWithleftChild(k3);
	}
	
	AVL_Index_UserName* findMin(AVL_Index_UserName* root) {
		while (root && root->left != NULL) {
			root = root->left;
		}
		return root;
	}
	void DeleteIndexUserName(string Name) {
		DeleteIndexUserName(root_UserName, Name);
	}
	void DeleteIndexUserName(AVL_Index_UserName*& root, string value) {

		// works from in order successor


		if (root == NULL) {
			return;
		}


		if (value < root->UserName) {
			DeleteIndexUserName(root->left, value);
		}


		else if (value > root->UserName) {
			DeleteIndexUserName(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				DeleteInList(root->list);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				AVL_Index_UserName* temp = root;
				root = root->right;
				DeleteInList(temp->list);
				delete temp;
			}
			else if (root->right == NULL) {
				AVL_Index_UserName* temp = root;
				root = root->left;
				DeleteInList(temp->list);
				delete temp;
			}

			else {
				AVL_Index_UserName* temp = findMin(root->right);
				root->UserName = temp->UserName;
				root->list = temp->list;
				root->height = temp->height; // check
				DeleteIndexUserName(root->right, temp->UserName);
			}
		}

		balance(root);


	}
	void PrintUserNameIndices() {
		PrintUserNameIndices(root_UserName);
	}
	void PrintUserNameIndices(AVL_Index_UserName* root) {
		// Empty Tree
		if (root == nullptr) {
			cout << "No Indice Found\n";
			return;
		}

		// Recur on the left subtree
		PrintUserNameIndices(root->left);

		// Visit the current node
		cout << root->UserName << endl;

		// Recur on the right subtree
		PrintUserNameIndices(root->right);
	}


	// AVL Email Index FUNCS

	void InsertInAvlIndexEmail(string Email, UserList* list, AVL_Index_Email*& ptr) {
		if (ptr == NULL)
			ptr = new AVL_Index_Email(Email, list, NULL, NULL);

		else if (Email < ptr->Email) {
			InsertInAvlIndexEmail(Email, list, ptr->left);
		}
		else if (Email > ptr->Email) {
			InsertInAvlIndexEmail(Email, list, ptr->right);
		}

		balance(ptr);



	}
	void SearchEmail(string Email) {
		SearchEmail(root_Email, Email);
	}
	void SearchEmail(AVL_Index_Email* root, string Email) {


		if (root == NULL) {
			cout << "No User Found\n";
			return;
		}


		if (root->Email == Email) {
			cout << "UserID: " << root->list->UserID << endl;
			cout << "User Name: " << root->list->UserName << endl;
			cout << "Email: " << root->Email << endl;
			cout << "Country: " << root->list->Country << endl;
			cout << "Member Type: " << root->list->Type << endl;
			cout << "--------------------------------------------------------------" << endl;
			return;
		}


		else if (Email > root->Email)
			SearchEmail(root->right, Email);
		else
			SearchEmail(root->left, Email);



	}
	int CalcHeight(AVL_Index_Email*& ptr) {
		return ptr == NULL ? -1 : ptr->height;

	}
	void balance(AVL_Index_Email*& ptr) {
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
	
	void rotateWithleftChild(AVL_Index_Email*& k2) {
		AVL_Index_Email* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(CalcHeight(k2->left), CalcHeight(k2->right)) + 1;
		k1->height = max(CalcHeight(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void rotateWithrightChild(AVL_Index_Email*& k1) {
		AVL_Index_Email* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;

		k1->height = max(CalcHeight(k1->left), CalcHeight(k1->right)) + 1;
		k2->height = max(CalcHeight(k2->left), k2->height) + 1; //calcHeight(k2->right)
		k1 = k2;
	}
	void doubleWithleftChild(AVL_Index_Email*& k3) {
		rotateWithrightChild(k3->left);
		rotateWithleftChild(k3);
	}
	void doubleWithrightChild(AVL_Index_Email*& k3) {
		rotateWithrightChild(k3->right);
		rotateWithleftChild(k3);
	}
	AVL_Index_Email* findMin(AVL_Index_Email* root) {
		while (root && root->left != NULL) {
			root = root->left;
		}
		return root;
	}
	
	void DeleteIndexEmail(string Email) {
		DeleteIndexEmail(root_Email, Email);
	}
	void DeleteIndexEmail(AVL_Index_Email*& root, string value) {

		// works from in order successor


		if (root == NULL) {
			return;
		}


		if (value < root->Email) {
			DeleteIndexEmail(root->left, value);
		}


		else if (value > root->Email) {
			DeleteIndexEmail(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				DeleteInList(root->list);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				AVL_Index_Email* temp = root;
				root = root->right;
				DeleteInList(temp->list);
				delete temp;
			}
			else if (root->right == NULL) {
				AVL_Index_Email* temp = root;
				DeleteInList(temp->list);
				root = root->left;
				delete temp;
			}

			else {
				AVL_Index_Email* temp = findMin(root->right);
				root->Email = temp->Email;
				root->list = temp->list;
				root->height = temp->height; // check
				DeleteIndexEmail(root->right, temp->Email);
			}
		}

		balance(root);


	}
	void PrintEmailIndices() {
		PrintEmailIndices(root_Email);
	}
	void PrintEmailIndices(AVL_Index_Email* root) {
		// Empty Tree
		if (root == nullptr) {
			cout << "No Email Indices Found\n";
			return;
		}

		// Recur on the left subtree
		PrintEmailIndices(root->left);

		// Visit the current node
		cout << root->Email <<endl;

		// Recur on the right subtree
		PrintEmailIndices(root->right);
	}


	// Groupping

	void CreateGroupOnCountry(string Index) {
		
		if (GetGroupIndex(Index, root_Country)) {
			cout << "Group Already Exists\n";
		}
		else {
			UserList* temp = head;

			while (temp != NULL) {

				if (temp->Country == Index) {

					Group* temp2 = GetGroupIndex(Index, root_Country);

					if (temp2 != NULL) {
						(temp2->Users).push_back(temp);
					}
					else {
						InsertInAvlGroup(Index, root_Country);
						temp2 = GetGroupIndex(Index, root_Country);
						(temp2->Users).push_back(temp);
					}
				}

				temp = temp->next;
			}
		}
	}
	void DeleteIndexEmailByGroup(AVL_Index_Email*& root, string value) {

		// works from in order successor


		if (root == NULL) {
			return;
		}


		if (value < root->Email) {
			DeleteIndexEmailByGroup(root->left, value);
		}


		else if (value > root->Email) {
			DeleteIndexEmailByGroup(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				//DeleteInList(root->list);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				AVL_Index_Email* temp = root;
				root = root->right;
				//DeleteInList(temp->list);
				delete temp;
			}
			else if (root->right == NULL) {
				AVL_Index_Email* temp = root;
				//DeleteInList(temp->list);
				root = root->left;
				delete temp;
			}

			else {
				AVL_Index_Email* temp = findMin(root->right);
				root->Email = temp->Email;
				root->list = temp->list;
				root->height = temp->height; // check
				DeleteIndexEmailByGroup(root->right, temp->Email);
			}
		}

		balance(root);


	}
	void DeleteIndexUserNameByGroup(AVL_Index_UserName*& root, string value) {

		// works from in order successor


		if (root == NULL) {
			return;
		}


		if (value < root->UserName) {
			DeleteIndexUserNameByGroup(root->left, value);
		}


		else if (value > root->UserName) {
			DeleteIndexUserNameByGroup(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				//DeleteInList(root->list);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				AVL_Index_UserName* temp = root;
				root = root->right;
				//DeleteInList(temp->list);
				delete temp;
			}
			else if (root->right == NULL) {
				AVL_Index_UserName* temp = root;
				root = root->left;
				//DeleteInList(temp->list);
				delete temp;
			}

			else {
				AVL_Index_UserName* temp = findMin(root->right);
				root->UserName = temp->UserName;
				root->list = temp->list;
				root->height = temp->height; // check
				DeleteIndexUserNameByGroup(root->right, temp->UserName);
			}
		}

		balance(root);


	}
	void DeleteEntriesByGroupOnCountry(list<UserList*> head) {
		

		for (UserList* ptr : head) {
			
			string Name = ptr->UserName;
			string email = ptr->Email;
			string country = ptr->Country;

			

			Group* temp = GetGroupIndex(ptr->Type, root_Type);

			if (temp != NULL) {

				//list<UserList*> TypeList = temp->Users;
				
				if (! ( (temp->Users).empty()) ) {

					

					for (auto it = (temp->Users).begin(); it != (temp->Users).end(); ) {
						
						if ( (*it)->Country == country && (*it)->UserName == Name) { // Condition to remove
							it = (temp->Users).erase(it); // erase() returns the next iterator
						}
						else {
							++it; // Increment the iterator only if no removal
						}
					}
				}

				if ((temp->Users).empty()) {
					DeleteGroup(root_Type,ptr->Type);
				}
			}


			DeleteIndex(ptr->UserID);
			DeleteIndexEmailByGroup(root_Email, email);
			DeleteIndexUserNameByGroup(root_UserName, Name);
			
			
			// exception ka masla


			
		}
		
	}
	void DeleteEntriesByGroupOnType(list<UserList*> head) {
		
		for (UserList* ptr : head) {

			string Name = ptr->UserName;
			string email = ptr->Email;
			string type = ptr->Type;



			Group* temp = GetGroupIndex(ptr->Country, root_Country);

			if (temp != NULL) {

				//list<UserList*> CountryList = temp->Users;

				if (! ( (temp->Users).empty() ) ) {

					for (auto it = (temp->Users).begin(); it != (temp->Users).end(); ) {
						
						if ((*it)->Type == type && (*it)->UserName == Name) { // Condition to remove
							it = (temp->Users).erase(it); // erase() returns the next iterator
						}
						else {
							++it; // Increment the iterator only if no removal
						}
					}

					
				}

				if ((temp->Users).empty()) {
					DeleteGroup(root_Country, ptr->Country);
				}
			}
			


			DeleteIndex(ptr->UserID);
			//DeleteIndexEmailByGroup(root_Email, email);
			//DeleteIndexUserNameByGroup(root_UserName, Name);






		}
	}
	void CreateGroupOnType(string Type) {
		if (GetGroupIndex(Type, root_Type)) {
			cout << "Group Already Exists\n";
		}
		else {
			UserList* temp = head;

			while (temp != NULL) {

				if (temp->Type == Type) {

					Group* temp2 = GetGroupIndex(Type, root_Type);

					if (temp2 != NULL) {
						(temp2->Users).push_back(temp);
					}
					else {
						InsertInAvlGroup(Type, root_Type);
						temp2 = GetGroupIndex(Type, root_Type);
						(temp2->Users).push_back(temp);
					}
				}

				temp = temp->next;
			}
		}
	}
	Group* findMin(Group* root) {
		while (root && root->left != NULL) {
			root = root->left;
		}
		return root;
	}
	void DeleteGroup(Group*& root, string value) {
		// works from in order successor

		if (root == NULL) {
			return;
		}


		if (value < root->Index) {
			DeleteGroup(root->left, value);
		}


		else if (value > root->Index) {
			DeleteGroup(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				//DeleteEntriesByGroupOnType(root->Users);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				Group* temp = root;
				root = root->right;
				//DeleteEntriesByGroupOnType(temp->Users);
				delete temp;
			}
			else if (root->right == NULL) {
				Group* temp = root;
				//DeleteEntries(temp->Users);
				root = root->left;
				delete temp;
			}

			else {
				Group* temp = findMin(root->right);
				root->Index = temp->Index;
				root->Users = temp->Users;
				root->height = temp->height;
				DeleteGroup(root->right, temp->Index);
			}
		}

		balance(root);
	}
	void DeleteGroupOnCountry(string Index) {
		DeleteGroupOnCountry(root_Country, Index);
	}
	void DeleteGroupOnCountry(Group*& root, string value) {

		// works from in order successor


		if (root == NULL) {
			return;
		}


		if (value < root->Index) {
			DeleteGroupOnCountry(root->left, value);
		}


		else if (value > root->Index) {
			DeleteGroupOnCountry(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				DeleteEntriesByGroupOnCountry(root->Users);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				Group* temp = root;
				root = root->right;
				DeleteEntriesByGroupOnCountry(temp->Users);
				delete temp;
			}
			else if (root->right == NULL) {
				Group* temp = root;
				DeleteEntriesByGroupOnCountry(temp->Users);
				root = root->left;
				delete temp;
			}

			else {
				Group* temp = findMin(root->right);
				root->Index = temp->Index;
				root->Users = temp->Users;
				root->height = temp->height; 
				DeleteGroupOnCountry(root->right, temp->Index);
			}
		}

		balance(root);


	}
	void DeleteGroupOnType(string Type) {
		DeleteGroupOnType(root_Type, Type);
	}
	void DeleteGroupOnType(Group*& root, string value) {
		// works from in order successor


		if (root == NULL) {
			return;
		}


		if (value < root->Index) {
			DeleteGroupOnType(root->left, value);
		}


		else if (value > root->Index) {
			DeleteGroupOnType(root->right, value);
		}
		else {

			if (root->left == NULL && root->right == NULL) {
				DeleteEntriesByGroupOnType(root->Users);
				delete root;
				root = NULL;
			}

			else if (root->left == NULL) {
				Group* temp = root;
				DeleteEntriesByGroupOnType(temp->Users);
				root = root->right;
				
				delete temp;
			}
			else if (root->right == NULL) {
				Group* temp = root;
				DeleteEntriesByGroupOnType(temp->Users);
				root = root->left;
				delete temp;
			}

			else {
				Group* temp = findMin(root->right);
				root->Index = temp->Index;
				root->Users = temp->Users;
				root->height = temp->height;
				DeleteGroupOnType(root->right, temp->Index);
			}
		}

		balance(root);
	}

	void InsertInAvlGroup(string Index, Group*& ptr) {
		if (ptr == NULL)
			ptr = new Group(Index, NULL, NULL);

		else if (Index < ptr->Index) {
			InsertInAvlGroup(Index, ptr->left);
		}
		else if (Index > ptr->Index) {
			InsertInAvlGroup(Index, ptr->right);
		}

		balance(ptr);



	}
	Group* GetGroupIndex(string Index, Group* ptr) {
		if (ptr == NULL)
			return NULL;

		if (ptr->Index == Index)
			return ptr;

		if (ptr->Index > Index)
			return GetGroupIndex(Index, ptr->left);

		// No need for else
		return GetGroupIndex(Index, ptr->right);
	


	}
	int CalcHeight(Group*& ptr) {
		return ptr == NULL ? -1 : ptr->height;

	}
	void balance(Group*& ptr) {
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
	void rotateWithleftChild(Group*& k2) {
		Group* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(CalcHeight(k2->left), CalcHeight(k2->right)) + 1;
		k1->height = max(CalcHeight(k1->left), k2->height) + 1;
		k2 = k1;
	}
	void rotateWithrightChild(Group*& k1) {
		Group* k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;

		k1->height = max(CalcHeight(k1->left), CalcHeight(k1->right)) + 1;
		k2->height = max(CalcHeight(k2->left), k2->height) + 1; //calcHeight(k2->right)
		k1 = k2;
	}
	void doubleWithleftChild(Group*& k3) {
		rotateWithrightChild(k3->left);
		rotateWithleftChild(k3);
	}
	void doubleWithrightChild(Group*& k3) {
		rotateWithrightChild(k3->right);
		rotateWithleftChild(k3);
	}

	void PrintCountryDetails(string Index) {
		
		Group* temp = GetGroupIndex(Index, root_Country);
		
		if (temp != NULL) {
			
			for (UserList* val : temp->Users) {

				cout << "UserID: " << val->UserID << endl;
				cout << "User Name: " << val->UserName << endl;
				cout << "Email: " << val->Email << endl;
				cout << "Country: " << val->Country << endl;
				cout << "Member Type: " << val->Type << endl;
				cout << "--------------------------------------------------------------" << endl;
			}
		}
		else {
			cout << "Index Not Found So can not print\n";
		}
		
	}
	void PrintTypeDetails(string Type) {
		
		Group* temp = GetGroupIndex(Type, root_Type);

		if (temp != NULL) {

			for (UserList* val : temp->Users) {

				cout << "UserID: " << val->UserID << endl;
				cout << "User Name: " << val->UserName << endl;
				cout << "Email: " << val->Email << endl;
				cout << "Country: " << val->Country << endl;
				cout << "Member Type: " << val->Type << endl;
				cout << "--------------------------------------------------------------" << endl;
			}
		}
		else
			cout << "Index Not Found So can not print\n";
		
	}
	void PrintGroupOnTypeIndices() {
		PrintGroupOnTypeIndices(root_Type);
	}
	void PrintGroupOnTypeIndices(Group* root) {
		// Empty Tree
		if (root == nullptr) {
			return;
		}

		// Recur on the left subtree
		PrintGroupOnTypeIndices(root->left);

		// Visit the current node
		cout << root->Index << endl;

		// Recur on the right subtree
		PrintGroupOnTypeIndices(root->right);
	}
	
	
	void PrintGroupOnCountryIndices() {
		PrintGroupOnCountryIndices(root_Country);
	}
	void PrintGroupOnCountryIndices(Group* root) {
		// Empty Tree
		if (root == nullptr) {
			
			return;
		}

		// Recur on the left subtree
		PrintGroupOnCountryIndices(root->left);

		// Visit the current node
		cout << root->Index << endl;

		// Recur on the right subtree
		PrintGroupOnCountryIndices(root->right);
	}




	
};








void main() {

	User <int> BigBoss;

	BigBoss.InsertInList(25, "Munam32", "abdulmunam891@gmail.com", "Pakistan", "Platinum");    // Question 4
	BigBoss.InsertInList(42, "Munam12", "wasif891@gmail.com", "Pakistan", "Gold");
	BigBoss.InsertInList(77, "Munam568465", "afaq@gmail.com", "Pakistan", "Platinum");
	BigBoss.InsertInList(93, "Munamss8", "hassan@gmail.com", "Saudia", "Platinum");
	BigBoss.InsertInList(98, "Munamdd1", "Ahmad@gmail.com", "Saudia", "Platinum");

	BigBoss.CreateGroupOnCountry("Saudia");
	BigBoss.DeleteGroupOnCountry("Saudia");

	BigBoss.CreateGroupOnType("Gold");


	
	

	cout << "\n";
	system("pause");

}