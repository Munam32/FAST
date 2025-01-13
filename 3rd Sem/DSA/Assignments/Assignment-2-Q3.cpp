#include<iostream>
#include<vector>
#include<string>
using namespace std;
class UserList;
class LinkedList;
class AVL;
class AVlString;
class AVLGroup;
class avlGroup;
class linkedlist;
class Complaint;
class minHeap;
class User;

// DLL
class UserList
{
private:
    friend class AVL;
    friend class AVlString;
    friend class User;
    friend class LinkedList;
    friend class AVLGroup;
    class ListNode
    {
    public:
        int UserID;
        string Name;
        string Email;
        string Country;
        string Type;
        ListNode* next;
        ListNode* prev;

        ListNode(int id, string na, string em, string cou, string Ty, ListNode* n = nullptr, ListNode* p = nullptr)
        {
            UserID = id;
            Name = na;
            Email = em;
            Country = cou;
            Type = Ty;
            next = n;
            prev = p;
        }
        ListNode()
        {
            UserID = 0;
            Name = '\0';
            Email = '\0';
            Country = '\0';
            Type = '\0';
            next = nullptr;
            prev = nullptr;
        }
    };
    ListNode* head;
    ListNode* tail;

public:
    class Iterators
    {
        friend class UserList;
        ListNode* current;
        Iterators(ListNode* P) : current(P) {}
    public:
        Iterators()
        {
            current = nullptr;
        }
        int operator*() { return current->UserID; }
        Iterators& operator++() { current = current->next; return *this; }
        Iterators& operator--() { current = current->prev; return *this; }
        bool operator!=(const Iterators& rhs) { return rhs.current != current; }
        bool operator==(const Iterators& rhs) { return rhs.current == current; }
    };
    UserList()
    {
        head = new ListNode();
        tail = new ListNode();
        head->next = tail;
        tail->prev = head;
    }
    Iterators InsertAfter(int id, string na, string em, string cou, string Ty, Iterators T, bool checkDirection)
    {
        ListNode* temp = T.current;
        ListNode* TNode = new ListNode(id, na, em, cou, Ty, temp, temp->prev);
        if (checkDirection)// if 1 means 
        {
            TNode->next = temp->next;
            TNode->prev = temp;

            temp->next = TNode;
            temp->next->prev = TNode;
            Iterators It(TNode);
            return It;
        }
        temp->prev->next = TNode;
        temp->prev = TNode;
        Iterators It(TNode);
        return It;
    }
    ListNode* InsertatStart(int id, string na, string em, string cou, string Ty)
    {
        Iterators it(head->next);
        it = InsertAfter(id, na, em, cou, Ty, it, 0);
        return it.current;
    }
    ListNode* Insert(int id, string na, string em, string cou, string Ty, ListNode* ptr, bool checkDirection)
    {
        Iterators it(ptr);
        it = InsertAfter(id, na, em, cou, Ty, it, checkDirection);
        return it.current;
    }
    void PrintGivenUserDetails(ListNode* ptr)
    {
        if (ptr != nullptr)
        {
            cout << "UserId = " << ptr->UserID << "\n";
            cout << "Name = " << ptr->Name << "\n";
            cout << "Email = " << ptr->Email << "\n";
            cout << "Country = " << ptr->Country << "\n";
            cout << "Type = " << ptr->Type << "\n";
        }
    }
    void PrintAll()
    {
        ListNode* ptr = head->next;
        while (ptr != tail)
        {
            cout << "UserId = " << ptr->UserID << "\n";
            cout << "Name = " << ptr->Name << "\n";
            cout << "Email = " << ptr->Email << "\n";
            cout << "Country = " << ptr->Country << "\n";
            cout << "Type = " << ptr->Type << "\n";
            cout << "----------------------------------------------------\n\n";
            ptr = ptr->next;
        }
    }
    void DeleteUser(ListNode* ptr)
    {
        cout << "The User With These Details: \n";
        PrintGivenUserDetails(ptr);
        cout << "Has been deleted Successfully: \n\n\n";
        ListNode* temp = ptr;
        if (temp->next != tail)
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

        }
        else
        {
            temp->prev->next = nullptr;
            tail = temp->prev;
        }


        delete temp;
    }

    void SearchUserByNameAndPrintDetails(string tri)
    {
        ListNode* temp = head->next;
        while (temp != tail)
        {
            if (temp->Name == tri)
            {
                PrintGivenUserDetails(temp);
                return;
            }
            temp = temp->next;
        }
    }
    void SearchUserByEmailAndPrintDetails(string tri)
    {
        ListNode* temp = head->next;
        while (temp != tail)
        {
            if (temp->Email == tri)
            {
                PrintGivenUserDetails(temp);
                return;
            }
            temp = temp->next;
        }
    }
};

class LinkedList
{
private:
    friend class UserList;
    friend class AVLGroup;
    class LinkedListNode
    {
    public:
        int UserId;
        LinkedListNode* next;
        UserList::ListNode* ptr;
        LinkedListNode(int id = 0, UserList::ListNode* p = nullptr, LinkedListNode* n = nullptr)
        {
            UserId = id;
            next = n;
            ptr = p;
        }
        LinkedListNode()
        {
            UserId = 0;
            next = nullptr;
            ptr = nullptr;
        }
    };
    LinkedListNode* head;
    LinkedListNode* tail;
public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }
    void insertatHead(int id, UserList::ListNode* p)
    {
        LinkedListNode* t = new LinkedListNode(id, p);
        t->next = head;
        if (head == nullptr)
        {
            tail = t;
        }
        head = t;
    }

    void Print(string tri)
    {
        UserList::ListNode* ptr;
        LinkedListNode* c = head;
        cout << "The Users With same " << tri << " are below\n\n";
        while (c != nullptr)
        {
            ptr = c->ptr;
            cout << "UserId = " << ptr->UserID << "\n";
            cout << "Name = " << ptr->Name << "\n";
            cout << "Email = " << ptr->Email << "\n";
            cout << "Country = " << ptr->Country << "\n";
            cout << "Type = " << ptr->Type << "\n\n";

            c = c->next;
        }
        cout << "\n";
    }

    void Delete()
    {
        LinkedListNode* c = head;
        while (c != nullptr)
        {
            LinkedListNode* temp = head->next;
            head->ptr = nullptr;
            delete head;
            head = temp;
            if (head == nullptr)
            {
                tail = nullptr;
            }
        }
    }

    void DeleteUser(int id)
    {
        LinkedListNode* c = head;
        LinkedListNode* prev = nullptr; // Previous starts as nullptr for head handling.

        while (c != nullptr)
        {
            if (c->UserId == id)
            {
                if (prev == nullptr) // If it's the head node.
                {
                    head = c->next; // Move head to next node.
                    if (head == nullptr) // If the list becomes empty.
                        tail = nullptr;
                }
                else
                {
                    prev->next = c->next; // Bypass the current node.
                    if (c->next == nullptr) // If it's the tail node.
                        tail = prev;
                }

                delete c; // Free the memory for the deleted node.
                return;   // Exit after deleting the node (assuming unique IDs).
            }
            prev = c;        // Update prev.
            c = c->next;     // Move to the next node.
        }
    }

    int* GiveUsersId(int& count)
    {
        int* arr = new int[10];
        LinkedListNode* c = head;
        for (int i = 0; c != nullptr; i++)
        {
            count++;
            arr[i] = c->UserId;
            c = c->next;
        }
        return arr;
    }
};

class AVL
{
private:
    friend class UserList;
    class TreeNode
    {
    public:
        int UserId;
        TreeNode* left;
        TreeNode* right;
        int height;
        UserList::ListNode* Userptr;

        TreeNode(int id = 0, TreeNode* l = nullptr, TreeNode* r = nullptr, int h = 0, UserList::ListNode* ptr = nullptr)
            : UserId(id), left(l), right(r), height(h), Userptr(ptr) {}
    };
    TreeNode* root;
    int getheight(TreeNode* r)
    {
        if (r == nullptr) return -1;
        return r->height;
    }
    void rotateright(TreeNode*& r)
    {
        TreeNode* y = r->left;
        r->left = y->right;
        y->right = r;

        r->height = 1 + max(getheight(r->left), getheight(r->right));
        y->height = 1 + max(getheight(y->left), getheight(y->right));

        r = y;
    }
    void rotateleft(TreeNode*& r)
    {
        TreeNode* y = r->right;
        r->right = y->left;
        y->left = r;

        r->height = 1 + max(getheight(r->left), getheight(r->right));
        y->height = 1 + max(getheight(y->left), getheight(y->right));

        r = y;
    }
    void drotateright(TreeNode*& r)
    {
        rotateleft(r->left);
        rotateright(r);
    }
    void drotateleft(TreeNode*& r)
    {
        rotateright(r->right);
        rotateleft(r);
    }

    void insert(int id, UserList::ListNode* ptr, TreeNode*& r)
    {
        if (r == nullptr)
        {
            TreeNode* temp = new TreeNode(id);
            r = temp;
            r->Userptr = ptr;
            return;
        }
        else if (id < r->UserId)
        {
            insert(id, ptr, r->left);
            if (getheight(r->left) - getheight(r->right) == 2)
            {
                if (id < r->left->UserId)
                {
                    rotateright(r);
                }
                else
                {
                    drotateright(r);
                }
            }
        }
        else if (id > r->UserId)
        {
            insert(id, ptr, r->right);
            if (getheight(r->left) - getheight(r->right) == -2)
            {
                if (id > r->right->UserId)
                {
                    rotateleft(r);
                }
                else
                {
                    drotateleft(r);
                }
            }
        }
        r->height = 1 + max(getheight(r->left), getheight(r->right));
    }
    void balance(TreeNode*& r)
    {
        if (r == nullptr) return;

        int balanceFactor = getheight(r->left) - getheight(r->right);

        // Left heavy
        if (balanceFactor > 1)
        {
            if (getheight(r->left->left) >= getheight(r->left->right))
            {
                rotateright(r);  // Left-Left case
            }
            else
            {
                rotateleft(r->left);  // Left-Right case
                rotateright(r);
            }
        }
        // Right heavy
        else if (balanceFactor < -1)
        {
            if (getheight(r->right->right) >= getheight(r->right->left))
            {
                rotateleft(r);  // Right-Right case
            }
            else {
                rotateright(r->right);  // Right-Left case
                rotateleft(r);
            }
        }
    }
    TreeNode* findmax(TreeNode* r)
    {
        if (r == nullptr)
        {
            throw std::invalid_argument("Subtree is empty, cannot find maximum.");
        }

        TreeNode* current = r;
        while (current->right != nullptr)
        {
            current = current->right;
        }

        return current; // Return the maximum UserId value
    }
    UserList::ListNode* DeleteUser(int id, TreeNode*& r)
    {
        if (r == nullptr)
        {
            return nullptr;  // Node not found, nothing to delete
        }

        if (id < r->UserId)
        {
            return  DeleteUser(id, r->left);  // Go left if d is smaller
        }
        else if (id > r->UserId)
        {
            return DeleteUser(id, r->right);  // Go right if d is larger
        }
        else
        {  // Node found
            // Case 1: Node is a leaf
            if (r->left == nullptr && r->right == nullptr)
            {
                UserList::ListNode* temp = r->Userptr;
                delete r;
                r = nullptr;
                return temp;
            }
            // Case 2: Node has only right child
            else if (r->left == nullptr)
            {
                TreeNode* temp = r;
                UserList::ListNode* temp1 = r->Userptr;
                r = r->right;
                delete temp;
                return temp1;
            }
            // Case 3: Node has only left child
            else if (r->right == nullptr)
            {
                TreeNode* temp = r;
                UserList::ListNode* temp1 = r->Userptr;
                r = r->left;
                delete temp;
                return temp1;
            }
            // Case 4: Node has two children
            else
            {
                UserList::ListNode* temp1 = r->Userptr;
                TreeNode* m = findmax(r->left);  // Get max value from left subtree
                r->UserId = m->UserId;
                r->Userptr = m->Userptr;
                DeleteUser(m->UserId, r->left);  // Recursively delete the in-order predecessor
                return temp1;
            }
        }

        // Step 4: Update height and balance the tree
        if (r != nullptr)
        {
            r->height = 1 + max(getheight(r->left), getheight(r->right));  // Update height
            balance(r);  // Balance the node if needed
        }
    }
public:
    AVL()
    {
        root = nullptr;
    }
    UserList::ListNode* SearchLeafNode(int id, bool& check)
    {
        TreeNode* curr = root;
        while (curr != nullptr)
        {
            if (curr->UserId == id)
            {
                return nullptr;
            }
            else if (id < curr->UserId)
            {
                if (curr->left == nullptr)
                {
                    check = 0;
                    return curr->Userptr;
                }
                curr = curr->left;
            }
            else if (id > curr->UserId)
            {
                if (curr->right == nullptr)
                {
                    check = 1;
                    return curr->Userptr;
                }
                curr = curr->right;
            }
        }
    }

    UserList::ListNode* SearchNodeToPrintDetail(int id)
    {
        TreeNode* curr = root;
        while (curr != nullptr)
        {
            if (curr->UserId == id)
            {

                return curr->Userptr;
            }
            else if (id < curr->UserId)
            {
                curr = curr->left;
            }
            else if (id > curr->UserId)
            {

                curr = curr->right;
            }
        }
        cout << "No User is found with ID = " << id << "\n";
        return nullptr;
    }

    UserList::ListNode* DeleteUser(int id)
    {
        return DeleteUser(id, root);
    }

    void insert(int d, UserList::ListNode* ptr)
    {
        insert(d, ptr, root);
    }
};

class AVlString
{
private:
    friend class UserList;
    class TreeNodeString
    {
    public:
        string triat;
        TreeNodeString* left;
        TreeNodeString* right;
        int height;
        UserList::ListNode* Userptr;

        TreeNodeString(string t = "\0", TreeNodeString* l = nullptr, TreeNodeString* r = nullptr, int h = 0, UserList::ListNode* ptr = nullptr)
            : triat(t), left(l), right(r), height(h), Userptr(ptr) {}
    };
    TreeNodeString* root;
    int getheight(TreeNodeString* r)
    {
        if (r == nullptr) return -1;
        return r->height;
    }
    void rotateright(TreeNodeString*& r)
    {
        TreeNodeString* y = r->left;
        r->left = y->right;
        y->right = r;

        r->height = 1 + max(getheight(r->left), getheight(r->right));
        y->height = 1 + max(getheight(y->left), getheight(y->right));

        r = y;
    }
    void rotateleft(TreeNodeString*& r)
    {
        TreeNodeString* y = r->right;
        r->right = y->left;
        y->left = r;

        r->height = 1 + max(getheight(r->left), getheight(r->right));
        y->height = 1 + max(getheight(y->left), getheight(y->right));

        r = y;
    }
    void drotateright(TreeNodeString*& r)
    {
        rotateleft(r->left);
        rotateright(r);
    }
    void drotateleft(TreeNodeString*& r)
    {
        rotateright(r->right);
        rotateleft(r);
    }
    void balance(TreeNodeString*& r)
    {
        if (r == nullptr) return;

        int balanceFactor = getheight(r->left) - getheight(r->right);

        // Left heavy
        if (balanceFactor > 1)
        {
            if (getheight(r->left->left) >= getheight(r->left->right))
            {
                rotateright(r);  // Left-Left case
            }
            else
            {
                rotateleft(r->left);  // Left-Right case
                rotateright(r);
            }
        }
        // Right heavy
        else if (balanceFactor < -1)
        {
            if (getheight(r->right->right) >= getheight(r->right->left))
            {
                rotateleft(r);  // Right-Right case
            }
            else {
                rotateright(r->right);  // Right-Left case
                rotateleft(r);
            }
        }
    }
    void insert(string tri, UserList::ListNode* ptr, TreeNodeString*& r)
    {
        if (r == nullptr)
        {
            TreeNodeString* temp = new TreeNodeString(tri);
            r = temp;
            r->Userptr = ptr;
            return;
        }
        else if (tri < r->triat)
        {
            insert(tri, ptr, r->left);
            if (getheight(r->left) - getheight(r->right) == 2)
            {
                if (tri < r->left->triat)
                {
                    rotateright(r);
                }
                else
                {
                    drotateright(r);
                }
            }
        }
        else if (tri > r->triat)
        {
            insert(tri, ptr, r->right);
            if (getheight(r->left) - getheight(r->right) == -2)
            {
                if (tri > r->right->triat)
                {
                    rotateleft(r);
                }
                else
                {
                    drotateleft(r);
                }
            }
        }
        r->height = 1 + max(getheight(r->left), getheight(r->right));
    }
    TreeNodeString* findmax(TreeNodeString* r)
    {
        if (r == nullptr)
        {
            throw std::invalid_argument("Subtree is empty, cannot find maximum.");
        }

        TreeNodeString* current = r;
        while (current->right != nullptr)
        {
            current = current->right;
        }

        return current; // Return the maximum UserId value
    }
    void DeleteUser(string tri, TreeNodeString*& r)
    {
        if (r == nullptr)
        {
            return;  // Node not found, nothing to delete
        }

        if (tri < r->triat)
        {
            return  DeleteUser(tri, r->left);  // Go left if d is smaller
        }
        else if (tri > r->triat)
        {
            return DeleteUser(tri, r->right);  // Go right if d is larger
        }
        else
        {  // Node found
            // Case 1: Node is a leaf
            if (r->left == nullptr && r->right == nullptr)
            {
                r->Userptr = nullptr;
                delete r;
                r = nullptr;
                return;
            }
            // Case 2: Node has only right child
            else if (r->left == nullptr)
            {
                TreeNodeString* temp = r;
                r->Userptr = nullptr;
                r = r->right;
                delete temp;
                return;
            }
            // Case 3: Node has only left child
            else if (r->right == nullptr)
            {
                TreeNodeString* temp = r;
                r->Userptr = nullptr;
                r = r->left;
                delete temp;
                return;
            }
            // Case 4: Node has two children
            else
            {
                UserList::ListNode* temp1 = r->Userptr;
                TreeNodeString* m = findmax(r->left);  // Get max value from left subtree
                r->triat = m->triat;
                r->Userptr = m->Userptr;
                DeleteUser(m->triat, r->left);  // Recursively delete the in-order predecessor
                return;
            }
        }

        // Step 4: Update height and balance the tree
        if (r != nullptr)
        {
            r->height = 1 + max(getheight(r->left), getheight(r->right));  // Update height
            balance(r);  // Balance the node if needed
        }
    }
public:
    AVlString()
    {
        root = nullptr;
    }
    UserList::ListNode* SearchNodeToPrintDetail(string tri)
    {
        TreeNodeString* curr = root;
        while (curr != nullptr)
        {
            if (curr->triat == tri)
            {

                return curr->Userptr;
            }
            else if (tri < curr->triat)
            {
                curr = curr->left;
            }
            else if (tri > curr->triat)
            {

                curr = curr->right;
            }
        }
        cout << "No User is found with  = " << tri << "\n";
        return nullptr;
    }
    void DeleteUser(string tri)
    {
        DeleteUser(tri, root);
    }
    void insert(string tri, UserList::ListNode* ptr)
    {
        insert(tri, ptr, root);
    }
};

class AVLGroup
{
private:
    friend class LinkedList;
    friend class UserList;
    class TreeNodeGroup
    {
    public:
        string Triat;
        TreeNodeGroup* left;
        TreeNodeGroup* right;
        int height;
        LinkedList Userptr;
        TreeNodeGroup(string coun = "\0", int id = 0, TreeNodeGroup* l = nullptr, TreeNodeGroup* r = nullptr, int h = 0) : Userptr()
        {
            Triat = coun;
            left = l;
            right = r;
            height = h;
        }
    };

    TreeNodeGroup* root;
    int getheight(TreeNodeGroup* r)
    {
        if (r == nullptr) return -1;
        return r->height;
    }
    void rotateright(TreeNodeGroup*& r)
    {
        TreeNodeGroup* y = r->left;
        r->left = y->right;
        y->right = r;

        r->height = 1 + max(getheight(r->left), getheight(r->right));
        y->height = 1 + max(getheight(y->left), getheight(y->right));

        r = y;
    }
    void rotateleft(TreeNodeGroup*& r)
    {
        TreeNodeGroup* y = r->right;
        r->right = y->left;
        y->left = r;

        r->height = 1 + max(getheight(r->left), getheight(r->right));
        y->height = 1 + max(getheight(y->left), getheight(y->right));

        r = y;
    }
    void drotateright(TreeNodeGroup*& r)
    {
        rotateleft(r->left);
        rotateright(r);
    }
    void drotateleft(TreeNodeGroup*& r)
    {
        rotateright(r->right);
        rotateleft(r);
    }
    void balance(TreeNodeGroup*& r)
    {
        if (r == nullptr) return;

        int balanceFactor = getheight(r->left) - getheight(r->right);

        // Left heavy
        if (balanceFactor > 1)
        {
            if (getheight(r->left->left) >= getheight(r->left->right))
            {
                rotateright(r);  // Left-Left case
            }
            else
            {
                rotateleft(r->left);  // Left-Right case
                rotateright(r);
            }
        }
        // Right heavy
        else if (balanceFactor < -1)
        {
            if (getheight(r->right->right) >= getheight(r->right->left))
            {
                rotateleft(r);  // Right-Right case
            }
            else {
                rotateright(r->right);  // Right-Left case
                rotateleft(r);
            }
        }
    }
    void insert(string tri, int id, UserList::ListNode* ptr, TreeNodeGroup*& r)
    {
        if (r == nullptr)
        {
            TreeNodeGroup* temp = new TreeNodeGroup(tri);
            temp->Userptr.insertatHead(id, ptr);
            r = temp;

            return;
        }
        else if (tri < r->Triat)
        {
            insert(tri, id, ptr, r->left);
            if (getheight(r->left) - getheight(r->right) == 2)
            {
                if (tri < r->left->Triat)
                {
                    rotateright(r);
                }
                else
                {
                    drotateright(r);
                }
            }
        }
        else if (tri > r->Triat)
        {
            insert(tri, id, ptr, r->right);
            if (getheight(r->left) - getheight(r->right) == -2)
            {
                if (tri > r->right->Triat)
                {
                    rotateleft(r);
                }
                else
                {
                    drotateleft(r);
                }
            }
        }
        else if (tri == r->Triat)
        {
            r->Userptr.insertatHead(id, ptr);
        }
        r->height = 1 + max(getheight(r->left), getheight(r->right));

    }
    TreeNodeGroup* findmax(TreeNodeGroup* r)
    {
        if (r == nullptr)
        {
            throw std::invalid_argument("Subtree is empty, cannot find maximum.");
        }

        TreeNodeGroup* current = r;
        while (current->right != nullptr)
        {
            current = current->right;
        }

        return current; // Return the maximum UserId value
    }
    void DeleteUser(string tri, TreeNodeGroup*& r)
    {
        if (r == nullptr)
        {
            return;  // Node not found, nothing to delete
        }

        if (tri < r->Triat)
        {
            return  DeleteUser(tri, r->left);  // Go left if d is smaller
        }
        else if (tri > r->Triat)
        {
            return DeleteUser(tri, r->right);  // Go right if d is larger
        }
        else
        {  // Node found
            // Case 1: Node is a leaf
            if (r->left == nullptr && r->right == nullptr)
            {
                if (r->Userptr.head != nullptr)
                {
                    r->Userptr.Delete();
                }
                delete r;
                r = nullptr;
                return;
            }
            // Case 2: Node has only right child
            else if (r->left == nullptr)
            {
                TreeNodeGroup* temp = r;
                if (r->Userptr.head != nullptr)
                {
                    r->Userptr.Delete();
                }
                r = r->right;
                delete temp;
                return;
            }
            // Case 3: Node has only left child
            else if (r->right == nullptr)
            {
                TreeNodeGroup* temp = r;
                if (r->Userptr.head != nullptr)
                {
                    r->Userptr.Delete();
                }
                r = r->left;
                delete temp;
                return;
            }
            // Case 4: Node has two children
            else
            {
                LinkedList temp1 = r->Userptr;
                TreeNodeGroup* m = findmax(r->left);  // Get max value from left subtree
                r->Triat = m->Triat;
                r->Userptr = m->Userptr;
                DeleteUser(m->Triat, r->left);  // Recursively delete the in-order predecessor
                return;
            }
        }

        // Step 4: Update height and balance the tree
        if (r != nullptr)
        {
            r->height = 1 + max(getheight(r->left), getheight(r->right));  // Update height
            balance(r);  // Balance the node if needed
        }
    }
    void DeleteSpecificUser(string tri, int id, TreeNodeGroup*& r)
    {
        if (r == nullptr)
        {
            return;  // Node not found, nothing to delete
        }

        if (tri < r->Triat)
        {
            return  DeleteSpecificUser(tri, id, r->left);  // Go left if d is smaller
        }
        else if (tri > r->Triat)
        {
            return DeleteSpecificUser(tri, id, r->right);  // Go right if d is larger
        }
        else
        {  // Node found
            if (r->Userptr.head != nullptr)
            {
                r->Userptr.DeleteUser(id);
            }
            return;
        }
    }
    int* getIdsOfSpecificCountry(string coun, int& count, TreeNodeGroup*& r)
    {
        if (r == nullptr)
        {
            return nullptr;  // Node not found, nothing to delete
        }

        if (coun < r->Triat)
        {
            return  getIdsOfSpecificCountry(coun, count, r->left);  // Go left if d is smaller
        }
        else if (coun > r->Triat)
        {
            return getIdsOfSpecificCountry(coun, count, r->right);  // Go right if d is larger
        }
        else
        {  // Node found
            if (r->Userptr.head != nullptr)
            {
                int* arr = new int[10];
                arr = r->Userptr.GiveUsersId(count);
                return arr;
            }
            else
            {
                return nullptr;
            }

        }
    }

public:
    AVLGroup()
    {
        root = nullptr;
    }
    void DeleteSpecificUser(string tri, int id)
    {
        DeleteSpecificUser(tri, id, root);
    }
    void DeleteUser(string tri)
    {
        DeleteUser(tri, root);
    }
    void SearchNodeToPrintDetail(string tri)
    {
        TreeNodeGroup* curr = root;
        while (curr != nullptr)
        {
            if (curr->Triat == tri)
            {

                curr->Userptr.Print(tri);
                return;
            }
            else if (tri < curr->Triat)
            {
                curr = curr->left;
            }
            else if (tri > curr->Triat)
            {

                curr = curr->right;
            }
        }
        cout << "No User is found with = " << tri << "\n";

    }
    void insert(string tri, int id, UserList::ListNode* ptr)
    {
        insert(tri, id, ptr, root);
    }

    int* getIdsOfSpecificCountry(string coun, int& count)
    {
        int* arr = getIdsOfSpecificCountry(coun, count, root);
        return arr;
    }
};

class Complaint
{
private:
    int cid;
    int uid;
    int priority;
    string Complainttext;



public:
    Complaint(int c, int u, string t, string text)
    {
        cid = c;
        uid = u;
        priority = 0;
        Complainttext = text;
        if (t == "Platinum")
        {
            priority = 1;
        }
        else if (t == "Gold")
        {
            priority = 2;
        }
        else if (t == "Silver")
        {
            priority = 3;
        }
        else if (t == "New")
        {
            priority = 4;
        }
        else if (t == "Regular")
        {
            priority = 5;
        }
    }

    bool operator<(Complaint* t)
    {
        if (priority < t->priority)
        {
            return 1;
        }
        else if (priority == t->priority && cid < t->cid)
        {
            return 1;
        }
        return 0;
    }

    bool operator>(Complaint* t)
    {
        return !operator<(t);
    }

    void print()
    {
        cout << "User ID: " << uid;
        cout << "\nComplaint ID: " << cid;
        cout << "\nComplaint Text: " << Complainttext;
        cout << "\nIs Proceded: Thanks for your patience :)\n";
    }
    void printDetails()
    {
        cout << "\nComplaint ID: " << cid;
        cout << "\nComplaint Text: " << Complainttext;
        cout << "\n---------------------------------";
    }
    int getid()
    {
        return uid;
    }

};

class linkedlist
{
private:

    friend class avlGroup;
    class LinkedListNode
    {
    public:
        int UserId;
        LinkedListNode* next;
        Complaint* ptr;
        LinkedListNode(int id = 0, Complaint* p = nullptr, LinkedListNode* n = nullptr)
        {
            UserId = id;
            next = n;
            ptr = p;
        }
        LinkedListNode()
        {
            UserId = 0;
            next = nullptr;
            ptr = nullptr;
        }
    };
    LinkedListNode* head;
    LinkedListNode* tail;
public:
    linkedlist()
    {
        head = nullptr;
        tail = nullptr;
    }
    void insertatHead(int id, Complaint* p)
    {
        LinkedListNode* t = new LinkedListNode(id, p);
        t->next = head;

        cout << "Testing \n---------------\n";
        // head->ptr->print();
        cout << endl << endl;
        if (head == nullptr)
        {
            tail = t;
        }
        head = t;
    }

    //void Print(string tri)
    //{
    //    Complaint* ptr;
    //    LinkedListNode* c = head;
    //    cout << "The Users With same " << tri << " are below\n\n";
    //    while (c != nullptr)
    //    {
    //        ptr = c->ptr;
    //        /* cout << "UserId = " << ptr->UserID << "\n";
    //         cout << "Name = " << ptr->Name << "\n";
    //         cout << "Email = " << ptr->Email << "\n";
    //         cout << "Country = " << ptr->Country << "\n";
    //         cout << "Type = " << ptr->Type << "\n\n";*/

    //        c = c->next;
    //    }
    //    cout << "\n";
    //}

    void PrintUser(LinkedListNode* c)
    {
        c->ptr->print();

    }

    void PrintAllComplaint()
    {
        LinkedListNode* c = head;


        while (c != nullptr)
        {
            c->ptr->printDetails();

            c = c->next;
        }
    }

    void DeleteUser()
    {

        if (head == tail) // Only one node in the list
        {
            tail->ptr->print();
            tail->ptr = nullptr;
            delete tail;
            head = tail = nullptr; // The list is now empty
        }
        else
        {
            LinkedListNode* c = head;
            // Traverse to the second-to-last node
            while (c->next != tail)
            {
                c = c->next;
            }

            // c is now the second-to-last node
            tail->ptr->print();
            tail->ptr = nullptr;
            delete tail;       // Delete the last node
            tail = c;          // Update tail to the second-to-last node
            tail->next = nullptr; // Ensure the new tail's next pointer is null
        }
    }

    //void DeleteUser(int id)
    //{
    //    LinkedListNode* c = head;
    //    LinkedListNode* prev = nullptr; // Previous starts as nullptr for head handling.
    //    if (head != nullptr)
    //    {
    //        LinkedListNode* temp = head->next;

    //        delete head;
    //        head = temp;
    //        if (head == nullptr)
    //        {
    //            tail = nullptr;
    //        }
    //    }
    //}


};
// complaint avl group
class avlGroup
{
private:
    friend class linkedlist;
    friend class User;
    class TreeNodeGroup
    {
    public:
        int Id;
        TreeNodeGroup* left;
        TreeNodeGroup* right;
        int height;
        linkedlist ComplaintPtr;
        TreeNodeGroup(int id = 0, TreeNodeGroup* l = nullptr, TreeNodeGroup* r = nullptr, int h = 0) : ComplaintPtr()
        {
            Id = id;
            left = l;
            right = r;
            height = h;
        }
    };

    TreeNodeGroup* root;
    int getheight(TreeNodeGroup* r)
    {
        if (r == nullptr) return -1;
        return r->height;
    }
    void rotateright(TreeNodeGroup*& r)
    {
        TreeNodeGroup* y = r->left;
        r->left = y->right;
        y->right = r;

        r->height = 1 + max(getheight(r->left), getheight(r->right));
        y->height = 1 + max(getheight(y->left), getheight(y->right));

        r = y;
    }
    void rotateleft(TreeNodeGroup*& r)
    {
        TreeNodeGroup* y = r->right;
        r->right = y->left;
        y->left = r;

        r->height = 1 + max(getheight(r->left), getheight(r->right));
        y->height = 1 + max(getheight(y->left), getheight(y->right));

        r = y;
    }
    void drotateright(TreeNodeGroup*& r)
    {
        rotateleft(r->left);
        rotateright(r);
    }
    void drotateleft(TreeNodeGroup*& r)
    {
        rotateright(r->right);
        rotateleft(r);
    }
    void balance(TreeNodeGroup*& r)
    {
        if (r == nullptr) return;

        int balanceFactor = getheight(r->left) - getheight(r->right);

        // Left heavy
        if (balanceFactor > 1)
        {
            if (getheight(r->left->left) >= getheight(r->left->right))
            {
                rotateright(r);  // Left-Left case
            }
            else
            {
                rotateleft(r->left);  // Left-Right case
                rotateright(r);
            }
        }
        // Right heavy
        else if (balanceFactor < -1)
        {
            if (getheight(r->right->right) >= getheight(r->right->left))
            {
                rotateleft(r);  // Right-Right case
            }
            else {
                rotateright(r->right);  // Right-Left case
                rotateleft(r);
            }
        }
    }
    void insert(int id, Complaint* ptr, TreeNodeGroup*& r)
    {
        if (r == nullptr)
        {
            TreeNodeGroup* temp = new TreeNodeGroup(id);
            temp->ComplaintPtr.insertatHead(id, ptr);
            r = temp;

            return;
        }
        else if (id < r->Id)
        {
            insert(id, ptr, r->left);
            if (getheight(r->left) - getheight(r->right) == 2)
            {
                if (id < r->left->Id)
                {
                    rotateright(r);
                }
                else
                {
                    drotateright(r);
                }
            }
        }
        else if (id > r->Id)
        {
            insert(id, ptr, r->right);
            if (getheight(r->left) - getheight(r->right) == -2)
            {
                if (id > r->right->Id)
                {
                    rotateleft(r);
                }
                else
                {
                    drotateleft(r);
                }
            }
        }
        else if (id == r->Id)
        {
            r->ComplaintPtr.insertatHead(id, ptr);
        }
        r->height = 1 + max(getheight(r->left), getheight(r->right));

    }
    TreeNodeGroup* findmax(TreeNodeGroup* r)
    {
        if (r == nullptr)
        {
            throw std::invalid_argument("Subtree is empty, cannot find maximum.");
        }

        TreeNodeGroup* current = r;
        while (current->right != nullptr)
        {
            current = current->right;
        }

        return current; // Return the maximum UserId value
    }
    //void DeleteUser(string tri, TreeNodeGroup*& r)
    //{
    //    if (r == nullptr)
    //    {
    //        return;  // Node not found, nothing to delete
    //    }

    //    if (tri < r->Triat)
    //    {
    //        return  DeleteUser(tri, r->left);  // Go left if d is smaller
    //    }
    //    else if (tri > r->Triat)
    //    {
    //        return DeleteUser(tri, r->right);  // Go right if d is larger
    //    }
    //    else
    //    {  // Node found
    //        // Case 1: Node is a leaf
    //        if (r->left == nullptr && r->right == nullptr)
    //        {
    //            if (r->ComplaintPtr.head != nullptr)
    //            {
    //                r->ComplaintPtr.Delete();
    //            }
    //            delete r;
    //            r = nullptr;
    //            return;
    //        }
    //        // Case 2: Node has only right child
    //        else if (r->left == nullptr)
    //        {
    //            TreeNodeGroup* temp = r;
    //            if (r->ComplaintPtr.head != nullptr)
    //            {
    //                r->ComplaintPtr.Delete();
    //            }
    //            r = r->right;
    //            delete temp;
    //            return;
    //        }
    //        // Case 3: Node has only left child
    //        else if (r->right == nullptr)
    //        {
    //            TreeNodeGroup* temp = r;
    //            if (r->ComplaintPtr.head != nullptr)
    //            {
    //                r->ComplaintPtr.Delete();
    //            }
    //            r = r->left;
    //            delete temp;
    //            return;
    //        }
    //        // Case 4: Node has two children
    //        else
    //        {
    //            linkedlist temp1 = r->ComplaintPtr;
    //            TreeNodeGroup* m = findmax(r->left);  // Get max value from left subtree
    //            r->Triat = m->Triat;
    //            r->ComplaintPtr = m->ComplaintPtr;
    //            DeleteUser(m->Triat, r->left);  // Recursively delete the in-order predecessor
    //            return;
    //        }
    //    }

    //    // Step 4: Update height and balance the tree
    //    if (r != nullptr)
    //    {
    //        r->height = 1 + max(getheight(r->left), getheight(r->right));  // Update height
    //        balance(r);  // Balance the node if needed
    //    }
    //}

    void DeleteSpecificUserComplaint(int id, TreeNodeGroup*& r)
    {
        if (r == nullptr)
        {
            return;  // Node not found, nothing to delete
        }

        if (id < r->Id)
        {
            return  DeleteSpecificUserComplaint(id, r->left);  // Go left if d is smaller
        }
        else if (id > r->Id)
        {
            return DeleteSpecificUserComplaint(id, r->right);  // Go right if d is larger
        }
        else
        {  // Node found
            if (r->ComplaintPtr.head != nullptr)
            {
                r->ComplaintPtr.DeleteUser();
            }
            return;
        }
    }

    void SearchandDisplayComplaint(int id, TreeNodeGroup*& r)
    {
        if (r == nullptr)
        {
            return;  // Node not found, nothing to delete
        }

        if (id < r->Id)
        {
            return  SearchandDisplayComplaint(id, r->left);  // Go left if d is smaller
        }
        else if (id > r->Id)
        {
            return SearchandDisplayComplaint(id, r->right);  // Go right if d is larger
        }
        else
        {  // Node found
            if (r->ComplaintPtr.head != nullptr)
            {
                r->ComplaintPtr.PrintAllComplaint();
            }
            return;
        }


    }

public:
    avlGroup()
    {
        root = nullptr;
    }
    void DeleteSpecificUserComplaint(int id)
    {
        DeleteSpecificUserComplaint(id, root);
    }

    void insert(int id, Complaint* ptr)
    {
        insert(id, ptr, root);
    }

    void SearchandDisplayComplaint(int id)
    {
        SearchandDisplayComplaint(id, root);
    }
};




class minHeap
{
private:
    vector<Complaint*> vec;
    void bubble_up(int i) {
        int min = i;
        if (2 * i <= (vec.size() - 1) && (vec[2 * i])->operator<(vec[min])) {
            min = 2 * i;
        }
        if ((2 * i) + 1 <= (vec.size() - 1) && (vec[2 * i + 1])->operator<(vec[min])) {
            min = (2 * i) + 1;
        }

        if (i != min) {
            Complaint* temp;
            temp = vec[i];
            vec[i] = vec[min];
            vec[min] = temp;
            bubble_up(min);
        }
    }
    void bubble_down(int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < vec.size() - 1 && vec[left]->operator<(vec[smallest]))
        {
            smallest = left;
        }

        if (right < vec.size() - 1 && vec[right]->operator<(vec[smallest]))
        {
            smallest = right;
        }

        if (smallest != i)
        {
            swap(vec[i], vec[smallest]);
            bubble_down(smallest);
        }
    }
public:
    minHeap()
    {
        vec.push_back(0);
    }
    void buildMinHeap()
    {
        for (int i = (vec.size() / 2) - 1; i >= 0; i--)
        {
            bubble_down(i);
        }
    }

    void insert(Complaint* x)
    {
        vec.push_back(x);
        int i = (vec.size() - 1);

        while (i > 1 && vec[i / 2]->operator>(vec[i])) {
            swap(vec[i / 2], vec[i]);
            i = i / 2;
        }
    }

    bool isEmpty() const
    {
        return vec.empty();
    }
    Complaint* getMin()
    {
        if (!isEmpty())
        {
            return vec[1];
        }
        throw runtime_error("Heap is empty");
    }
    int deleteMin() {
        Complaint* temp;
        temp = vec[1];
        vec[1] = vec[(vec.size() - 1)];
        vec[(vec.size() - 1)] = temp;


        vec.pop_back();
        bubble_up(1);
        return temp->getid();

    }
    bool deleteAll(Complaint* key)
    {
        bool check = false;
        vector<Complaint*> temp;

        // Save all elements except key
        for (Complaint* element : vec)
        {
            if (element != key)
            {
                temp.push_back(element);
            }
            else
            {
                check = 1;
            }
        }

    }
    void printheap() {
        for (int i = 1; i < (vec.size()); i++) {
            vec[i]->print();
            cout << "\n";
        }
        cout << endl;
    }
};

class User
{
private:
    friend class UserList;
    AVL* Id_Avl;
    AVlString* Name_Avl;
    AVlString* Email_Avl;
    AVLGroup* Country;
    AVLGroup* Type;
    UserList* Head;
    minHeap* he;
    avlGroup* IdComplaint;

    int ComplaintNumber;
    bool notzero;
public:
    User()
    {
        Id_Avl = new AVL();
        Name_Avl = new AVlString();
        Email_Avl = new AVlString();
        notzero = 0;
        Head = new UserList();
        Country = new AVLGroup();
        Type = new AVLGroup();
        he = new minHeap();
        IdComplaint = new avlGroup();
        ComplaintNumber = 0;
    }

    void InsertUser(int id, string na, string em, string Co, string Ty) {
        if (!notzero)
        { // Check if the AVL tree is empty
            notzero = 1;
            UserList::ListNode* temp = Head->InsertatStart(id, na, em, Co, Ty);
            Id_Avl->insert(id, temp);
            Name_Avl->insert(na, temp);
            Email_Avl->insert(na, temp);
            Country->insert(Co, id, temp);
            Type->insert(Ty, id, temp);
        }
        else
        {
            bool Check = 0;
            UserList::ListNode* temp = Id_Avl->SearchLeafNode(id, Check);
            Id_Avl->insert(id, Head->Insert(id, na, em, Co, Ty, temp, Check));
            if (Check == 1)
            {
                Name_Avl->insert(na, temp->next);
                Email_Avl->insert(na, temp->next);
                Country->insert(Co, id, temp->next);
                Type->insert(Ty, id, temp->next);
            }
            else
            {
                Name_Avl->insert(na, temp->prev);
                Email_Avl->insert(na, temp->prev);
                Country->insert(Co, id, temp->prev);
                Type->insert(Ty, id, temp->prev);
            }


        }
    }

    void SearchUserById(int id)
    {
        Head->PrintGivenUserDetails(Id_Avl->SearchNodeToPrintDetail(id));
    }

    void PrintAllUser()
    {
        Head->PrintAll();
    }

    void DeleteSpecificUser(int id)
    {
        UserList::ListNode* temp = Id_Avl->DeleteUser(id);
        string name = temp->Name;
        string email = temp->Email;
        string country = temp->Country;
        string type = temp->Type;

        Head->DeleteUser(temp);
        Name_Avl->DeleteUser(name);
        Email_Avl->DeleteUser(email);
        Country->DeleteSpecificUser(country, id);
        Type->DeleteSpecificUser(type, id);
    }

    void SearchUserByName(string name)
    {

        UserList::ListNode* temp = Name_Avl->SearchNodeToPrintDetail(name);
        if (temp != nullptr)
        {
            Head->PrintGivenUserDetails(temp);
        }
        else
        {
            Head->SearchUserByNameAndPrintDetails(name);
        }

    }

    void SearchUserByEmail(string email)
    {

        UserList::ListNode* temp = Email_Avl->SearchNodeToPrintDetail(email);
        if (temp != nullptr)
        {
            Head->PrintGivenUserDetails(temp);
        }
        else
        {
            Head->SearchUserByEmailAndPrintDetails(email);
        }
    }

    void DeleteUserRecordByName(string name)
    {
        Name_Avl->DeleteUser(name);
    }

    void DeleteUserEmailRecord(string email)
    {
        Email_Avl->DeleteUser(email);
    }

    void PrintUsersWithSameCountry(string tri)
    {
        Country->SearchNodeToPrintDetail(tri);
    }

    void PrintUsersWithSameType(string tri)
    {
        Type->SearchNodeToPrintDetail(tri);
    }

    void DeleteUserWithSameCountry(string tri)
    {
        Country->DeleteUser(tri);
    }

    void DeleteUserWithSameType(string tri)
    {
        Type->DeleteUser(tri);
    }

    void registerComplaint(int id, string c)
    {
        UserList::ListNode* temp = Id_Avl->SearchNodeToPrintDetail(id);
        if (temp != nullptr)
        {
            string type = temp->Type;
            string country = temp->Country;

            ComplaintNumber++;
            Complaint* temp = new Complaint(ComplaintNumber, id, type, c);

            he->insert(temp);

            IdComplaint->insert(id, temp);

            cout << "Your Complaint Number is " << ComplaintNumber << " Please kepp Paitience \n\n";

        }
        else
        {
            cout << "User does not exits: \n\n\n";
        }
    }

    void ServiceComplaint()
    {
        int id = he->deleteMin();
        if (id == -1)
        {
            cout << "No more Complaints are in process\n\n";
            return;
        }
        IdComplaint->DeleteSpecificUserComplaint(id);
    }

    void Displaycomplaints(int id)
    {
        IdComplaint->SearchandDisplayComplaint(id);
    }

    void DisplayCountryComplaints(string country)
    {
        int count = 0;
        int* arr = Country->getIdsOfSpecificCountry(country, count);
        if (arr != nullptr)
        {
            for (int i = 0; i < count; i++)
            {
                IdComplaint->SearchandDisplayComplaint(arr[i]);
            }
        }
        else
        {
            cout << "Nothing found: \n\n";
        }


    }

};


int main()
{
    User U1;

    string name = "Ahmad";
    string email = "ahmubeen149@gmail.com";
    string country = "Pakistan";
    string Phone = "Gold";
    int userId = 93;
    U1.InsertUser(userId, name, email, country, Phone);

    name = "Haider Ali Shahid";
    email = "Haider202@gmail.com";
    country = "Pakistan";
    Phone = "Platinum";
    userId = 42;
    U1.InsertUser(userId, name, email, country, Phone);

    name = "Hassan Mahmood";
    email = "Hassan809@gmail.com";
    country = "Pakistan";
    Phone = "Platinum";
    userId = 25;
    U1.InsertUser(userId, name, email, country, Phone);

    name = "Ahmad Muaz";
    email = "Muaz387@gmail.com";
    country = "Pakistan";
    Phone = "Gold";
    userId = 77;
    U1.InsertUser(userId, name, email, country, Phone);

    name = "Taha Iqbal";
    email = "Iqbal12387@gmail.com";
    country = "Pakistan";
    Phone = "Gold";
    userId = 98;
    U1.InsertUser(userId, name, email, country, Phone);

    //U1.SearchUserById(17);






    U1.PrintAllUser();

    //U1.DeleteSpecificUser(98);



    //cout << "----------------------------------------------------------------\n\n\n";
    //U1.SearchUserByName("Ahmad");
    //cout << "----------------------------------------------------------------\n\n\n";
    //U1.DeleteUserRecordByName("Ahmad");
    //cout << "----------------------------------------------------------------\n\n\n";
    //U1.SearchUserByName("Ahmad");




    U1.PrintUsersWithSameType("Gold");

    //-------------------------------------------------------------------------------------------------------------------
    userId = 25;//platinum


    U1.registerComplaint(userId, "I cant do more assignments");
    userId = 77;//gold


    U1.registerComplaint(userId, "pajj jaaa");

    userId = 25;//platinum

    U1.registerComplaint(userId, "bakwass band kar ");


    userId = 93;//gold
    U1.registerComplaint(userId, "I cant do anymore");



    cout << "_-------------------------------------------------------\n";
    U1.Displaycomplaints(25);
    cout << "_-------------------------------------------------------\n";

    cout << "_-------------------------------------------------------\n";




    U1.DisplayCountryComplaints("Pakistan");


    cout << "_-------------------------------------------------------\n";
    U1.ServiceComplaint();
    cout << "_-------------------------------------------------------\n";

    U1.ServiceComplaint();
    cout << "_-------------------------------------------------------\n";

    U1.ServiceComplaint();
    cout << "_-------------------------------------------------------\n";

    U1.ServiceComplaint();
    cout << "_-------------------------------------------------------\n";


    system("pause");

    return 0;
}