//#include <iostream>
//#include <string>
//#include <unordered_map>
//#include <vector>
//#include <queue>
//#include <algorithm>
//#include <functional>
//using namespace std;
//
//// User Types Enum
//enum UserType {
//    PLATINUM, GOLD, SILVER, REGULAR, NEW
//};
//
//
//string UserTypeToString(UserType type) {
//    switch (type) {
//    case PLATINUM: return "PLATINUM";
//    case GOLD: return "GOLD";
//    case SILVER: return "SILVER";
//    case REGULAR: return "REGULAR";
//    case NEW: return "NEW";
//    default: return "UNKNOWN";
//    }
//}
//
//// User Class
//class User {
//public:
//    int userID;
//    string userName;
//    string email;
//    string country;
//    UserType type;
//
//    User(int id, const string& name, const string& mail, const string& cnt, UserType t)
//        : userID(id), userName(name), email(mail), country(cnt), type(t) {}
//};
//
//
//
//// Node for Doubly Linked List
//class Node {
//public:
//    User* user;
//    Node* next;
//    Node* prev;
//
//    Node(User* u) : user(u), next(nullptr), prev(nullptr) {}
//};
//
//// AVL Tree for UserID Index
//class AVLTree {
//private:
//    struct TreeNode {
//        int userID;
//        Node* userNode;
//        TreeNode* left;
//        TreeNode* right;
//        int height;
//
//        TreeNode(int id, Node* node) : userID(id), userNode(node), left(nullptr), right(nullptr), height(1) {}
//    };
//
//    TreeNode* root;
//
//    int getHeight(TreeNode* node) {
//        return node ? node->height : 0;
//    }
//
//    int getBalance(TreeNode* node) {
//        return node ? getHeight(node->left) - getHeight(node->right) : 0;
//    }
//
//    TreeNode* rotateRight(TreeNode* y) {
//        TreeNode* x = y->left;
//        TreeNode* T2 = x->right;
//        x->right = y;
//        y->left = T2;
//        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
//        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
//        return x;
//    }
//
//    TreeNode* rotateLeft(TreeNode* x) {
//        TreeNode* y = x->right;
//        TreeNode* T2 = y->left;
//        y->left = x;
//        x->right = T2;
//        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
//        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
//        return y;
//    }
//
//    TreeNode* insert(TreeNode* node, int userID, Node* userNode) {
//        if (!node) return new TreeNode(userID, userNode);
//
//        if (userID < node->userID)
//            node->left = insert(node->left, userID, userNode);
//        else if (userID > node->userID)
//            node->right = insert(node->right, userID, userNode);
//        else
//            return node;
//
//        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
//
//        int balance = getBalance(node);
//
//        if (balance > 1 && userID < node->left->userID)
//            return rotateRight(node);
//
//        if (balance < -1 && userID > node->right->userID)
//            return rotateLeft(node);
//
//        if (balance > 1 && userID > node->left->userID) {
//            node->left = rotateLeft(node->left);
//            return rotateRight(node);
//        }
//
//        if (balance < -1 && userID < node->right->userID) {
//            node->right = rotateRight(node->right);
//            return rotateLeft(node);
//        }
//
//        return node;
//    }
//
//    TreeNode* search(TreeNode* node, int userID) {
//        if (!node || node->userID == userID)
//            return node;
//
//        if (userID < node->userID)
//            return search(node->left, userID);
//        else
//            return search(node->right, userID);
//    }
//
//    TreeNode* minValueNode(TreeNode* node) {
//        TreeNode* current = node;
//        while (current && current->left)
//            current = current->left;
//        return current;
//    }
//
//    TreeNode* deleteNode(TreeNode* root, int userID) {
//        if (!root) return root;
//
//        if (userID < root->userID)
//            root->left = deleteNode(root->left, userID);
//        else if (userID > root->userID)
//            root->right = deleteNode(root->right, userID);
//        else {
//            if (!root->left || !root->right) {
//                TreeNode* temp = root->left ? root->left : root->right;
//                if (!temp) {
//                    temp = root;
//                    root = nullptr;
//                }
//                else
//                    *root = *temp;
//                delete temp;
//            }
//            else {
//                TreeNode* temp = minValueNode(root->right);
//                root->userID = temp->userID;
//                root->userNode = temp->userNode;
//                root->right = deleteNode(root->right, temp->userID);
//            }
//        }
//
//        if (!root) return root;
//
//        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
//
//        int balance = getBalance(root);
//
//        if (balance > 1 && getBalance(root->left) >= 0)
//            return rotateRight(root);
//
//        if (balance < -1 && getBalance(root->right) <= 0)
//            return rotateLeft(root);
//
//        if (balance > 1 && getBalance(root->left) < 0) {
//            root->left = rotateLeft(root->left);
//            return rotateRight(root);
//        }
//
//        if (balance < -1 && getBalance(root->right) > 0) {
//            root->right = rotateRight(root->right);
//            return rotateLeft(root);
//        }
//
//        return root;
//    }
//
//public:
//    AVLTree() : root(nullptr) {}
//
//    void insert(int userID, Node* userNode) {
//        root = insert(root, userID, userNode);
//    }
//
//    Node* search(int userID) {
//        TreeNode* node = search(root, userID);
//        return node ? node->userNode : nullptr;
//    }
//
//    void deleteNode(int userID) {
//        root = deleteNode(root, userID);
//    }
//};
//
//// Hashing Indexing
//class HashIndex {
//private:
//    unordered_map<string, Node*> hashTable;
//
//public:
//    void createIndex(const vector<Node*>& userList, function<string(Node*)> keyExtractor) {
//        for (const auto& node : userList) {
//            string key = keyExtractor(node);
//            hashTable[key] = node;
//        }
//    }
//
//    Node* search(const string& key) {
//        return hashTable.count(key) ? hashTable[key] : nullptr;
//    }
//
//    void deleteIndex() {
//        hashTable.clear();
//    }
//
//    void displayIndices() {
//        for (const auto& entry : hashTable) {
//            cout << "Key: " << entry.first
//                << ", UserID: " << entry.second->user->userID
//                << ", Name: " << entry.second->user->userName << endl;
//        }
//    }
//};
//
//
//
//// Group Hash Indexing
//class GroupHashIndex {
//private:
//    unordered_map<string, vector<Node*>> groupTable;
//
//public:
//    void createIndex(const vector<Node*>& userList, function<string(Node*)> keyExtractor) {
//        for (const auto& node : userList) {
//            string key = keyExtractor(node);
//            groupTable[key].push_back(node);
//        }
//    }
//
//    void listUsers(const string& key) {
//        if (groupTable.count(key)) {
//            for (const auto& node : groupTable[key]) {
//                cout << "UserID: " << node->user->userID
//                    << ", Name: " << node->user->userName
//                    << ", Country: " << node->user->country
//                    << ", Type: " << UserTypeToString(node->user->type) << endl;
//            }
//        }
//        else {
//            cout << "No users found for key: " << key << endl;
//        }
//    }
//
//    void deleteIndex() {
//        groupTable.clear();
//    }
//
//    void displayIndex() {
//        for (const auto& group : groupTable) {
//            cout << "Key: " << group.first << ", Users: ";
//            for (const auto& node : group.second) {
//                cout << node->user->userName << " ";
//            }
//            cout << endl;
//        }
//    }
//};
//
//// Complaint Management
//class Complaint {
//public:
//    int complaintID;
//    int userID;
//    string description;
//
//    Complaint(int cID, int uID, const string& desc)
//        : complaintID(cID), userID(uID), description(desc) {}
//};
//
//struct ComparePriority {
//    bool operator()(const pair<int, Complaint*>& a, const pair<int, Complaint*>& b) {
//        return a.first > b.first; // Higher priority comes first
//    }
//};
//
//class ComplaintQueue {
//private:
//    priority_queue<pair<int, Complaint*>, vector<pair<int, Complaint*>>, ComparePriority> complaintHeap;
//    unordered_map<int, vector<Complaint*>> userComplaints;
//
//    int getPriority(UserType type) {
//        switch (type) {
//        case PLATINUM: return 1;
//        case GOLD: return 2;
//        case SILVER: return 3;
//        case REGULAR: return 4;
//        case NEW: return 5;
//        default: return 6;
//        }
//    }
//
//public:
//    void registerComplaint(int complaintID, int userID, UserType userType, const string& description) {
//        Complaint* newComplaint = new Complaint(complaintID, userID, description);
//        int priority = getPriority(userType);
//        complaintHeap.emplace(priority, newComplaint);
//        userComplaints[userID].push_back(newComplaint);
//        cout << "Complaint registered: " << complaintID << endl;
//    }
//
//    void serviceComplaint() {
//        if (complaintHeap.empty()) {
//            cout << "No complaints to service!" << endl;
//            return;
//        }
//
//        auto highestPriority = complaintHeap.top();
//        complaintHeap.pop();
//        Complaint* complaint = highestPriority.second;
//
//        cout << "Servicing Complaint ID: " << complaint->complaintID
//            << ", UserID: " << complaint->userID
//            << ", Description: " << complaint->description << endl;
//
//        auto& userList = userComplaints[complaint->userID];
//        userList.erase(remove(userList.begin(), userList.end(), complaint), userList.end());
//    }
//
//    void displayUserComplaints(int userID) {
//        if (userComplaints.count(userID)) {
//            for (const auto& complaint : userComplaints[userID]) {
//                cout << "Complaint ID: " << complaint->complaintID
//                    << ", Description: " << complaint->description << endl;
//            }
//        }
//        else {
//            cout << "No complaints found for UserID: " << userID << endl;
//        }
//    }
//
//    void displayAllComplaints() {
//        auto tempHeap = complaintHeap;
//        while (!tempHeap.empty()) {
//            auto top = tempHeap.top();
//            tempHeap.pop();
//            Complaint* complaint = top.second;
//            cout << "Complaint ID: " << complaint->complaintID
//                << ", Priority: " << top.first
//                << ", UserID: " << complaint->userID
//                << ", Description: " << complaint->description << endl;
//        }
//    }
//};
//
//
//class UserList {
//private:
//    Node* head;
//    Node* tail;
//    AVLTree userIDIndex;
//
//public:
//    UserList() : head(nullptr), tail(nullptr) {}
//
//    void insertUser(User* user) {
//        Node* newNode = new Node(user);
//        if (!head) {
//            head = tail = newNode;
//        }
//        else {
//            // Insert into the doubly linked list in sorted order by UserID
//            Node* temp = head;
//            while (temp && temp->user->userID < user->userID) {
//                temp = temp->next;
//            }
//            if (!temp) { // Insert at the end
//                tail->next = newNode;
//                newNode->prev = tail;
//                tail = newNode;
//            }
//            else if (temp == head) { // Insert at the beginning
//                newNode->next = head;
//                head->prev = newNode;
//                head = newNode;
//            }
//            else { // Insert in the middle
//                newNode->next = temp;
//                newNode->prev = temp->prev;
//                temp->prev->next = newNode;
//                temp->prev = newNode;
//            }
//        }
//        userIDIndex.insert(user->userID, newNode);
//    }
//
//    Node* searchUser(int userID) {
//        return userIDIndex.search(userID);
//    }
//
//    void deleteUser(int userID) {
//        Node* userNode = userIDIndex.search(userID);
//        if (userNode) {
//            // Remove from doubly linked list
//            if (userNode->prev) {
//                userNode->prev->next = userNode->next;
//            }
//            else {
//                head = userNode->next; // Update head if it's the first node
//            }
//            if (userNode->next) {
//                userNode->next->prev = userNode->prev;
//            }
//            else {
//                tail = userNode->prev; // Update tail if it's the last node
//            }
//            // Delete from AVL tree
//            userIDIndex.deleteNode(userID);
//            delete userNode;
//        }
//    }
//
//    void printUsers() {
//        Node* temp = head;
//        while (temp) {
//            cout << "UserID: " << temp->user->userID
//                << ", Name: " << temp->user->userName
//                << ", Email: " << temp->user->email
//                << ", Country: " << temp->user->country
//                << ", Type: " << UserTypeToString(temp->user->type) << endl;
//            temp = temp->next;
//        }
//    }
//};
//
//
//
//// Main function
//void main() {
//    UserList userList;
//    AVLTree userIDIndex;
//    HashIndex userNameIndex, emailIndex;
//    GroupHashIndex countryIndex, typeIndex;
//    ComplaintQueue complaintQueue;
//
//    // Example Users
//    userList.insertUser(new User(1, "Alice", "alice@example.com", "USA", PLATINUM));
//    userList.insertUser(new User(2, "Bob", "bob@example.com", "Canada", GOLD));
//    userList.insertUser(new User(3, "Charlie", "charlie@example.com", "USA", SILVER));
//
//    cout << "All Users:\n";
//    userList.printUsers();
//
//    // Registering Complaints
//    complaintQueue.registerComplaint(1001, 1, PLATINUM, "Issue with game performance");
//    complaintQueue.registerComplaint(1002, 2, GOLD, "Unable to login");
//    complaintQueue.registerComplaint(1003, 3, SILVER, "Payment issue");
//
//    cout << "\nAll Complaints:\n";
//    complaintQueue.displayAllComplaints();
//
//    // Service a Complaint
//    cout << "\nServicing Complaint:\n";
//    complaintQueue.serviceComplaint();
//
//    system("pause");
//}



#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <unordered_map>
#include <functional>

// ----------------------- User Class -----------------------

class User {
public:
    int userID;
    std::string userName;
    std::string email;
    std::string country;
    std::string type;

    User(int id, const std::string& name, const std::string& mail,
        const std::string& ctry, const std::string& tp)
        : userID(id), userName(name), email(mail), country(ctry), type(tp) {}
};

// ----------------------- AVL Tree -----------------------

class AVLNode {
public:
    int key;
    User* user;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k, User* u) : key(k), user(u), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) { return node ? node->height : 0; }

    int balanceFactor(AVLNode* node) { return node ? height(node->left) - height(node->right) : 0; }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVLNode* insertNode(AVLNode* node, int key, User* user) {
        if (!node) return new AVLNode(key, user);

        if (key < node->key)
            node->left = insertNode(node->left, key, user);
        else if (key > node->key)
            node->right = insertNode(node->right, key, user);
        else
            return node;

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int bf = balanceFactor(node);

        if (bf > 1 && key < node->left->key) return rotateRight(node);
        if (bf < -1 && key > node->right->key) return rotateLeft(node);
        if (bf > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* findMin(AVLNode* node) {
        while (node->left) node = node->left;
        return node;
    }

    AVLNode* deleteNode(AVLNode* node, int key) {
        if (!node) return node;

        if (key < node->key)
            node->left = deleteNode(node->left, key);
        else if (key > node->key)
            node->right = deleteNode(node->right, key);
        else {
            if (!node->left || !node->right) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;
                delete temp;
            }
            else {
                AVLNode* temp = findMin(node->right);
                node->key = temp->key;
                node->user = temp->user;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        if (!node) return node;

        node->height = std::max(height(node->left), height(node->right)) + 1;

        int bf = balanceFactor(node);

        if (bf > 1 && balanceFactor(node->left) >= 0) return rotateRight(node);
        if (bf > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (bf < -1 && balanceFactor(node->right) <= 0) return rotateLeft(node);
        if (bf < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    User* searchNode(AVLNode* node, int key) {
        if (!node) return nullptr;
        if (key < node->key) return searchNode(node->left, key);
        if (key > node->key) return searchNode(node->right, key);
        return node->user;
    }

    void printInOrder(AVLNode* node) {
        if (!node) return;
        printInOrder(node->left);
        std::cout << "UserID: " << node->key << " -> " << node->user->userName << std::endl;
        printInOrder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int key, User* user) { root = insertNode(root, key, user); }

    void remove(int key) { root = deleteNode(root, key); }

    User* search(int key) { return searchNode(root, key); }

    void printInOrder() { printInOrder(root); }
};

// ----------------------- Hash Table -----------------------

template <typename Key, typename Value>
class HashTable {
private:
    std::vector<std::list<std::pair<Key, Value*>>> table;
    size_t capacity;
    std::function<size_t(const Key&)> hashFunction;

    size_t hash(const Key& key) const { return hashFunction(key) % capacity; }

public:
    HashTable(size_t cap, std::function<size_t(const Key&)> hashFunc)
        : capacity(cap), hashFunction(hashFunc), table(cap) {}

    void insert(const Key& key, Value* value) {
        size_t idx = hash(key);
        table[idx].emplace_back(key, value);
    }

    Value* search(const Key& key) {
        size_t idx = hash(key);
        for (const auto& pair : table[idx]) {
            if (pair.first == key) return pair.second;
        }
        return nullptr;
    }

    void remove(const Key& key) {
        size_t idx = hash(key);
        table[idx].remove_if([&key](const std::pair<Key, Value*>& pair) { return pair.first == key; });
    }

    void display() const {
        for (size_t i = 0; i < capacity; ++i) {
            std::cout << "Index " << i << ": ";
            for (const auto& pair : table[i]) {
                std::cout << pair.first << " ";
            }
            std::cout << std::endl;
        }
    }
};

// ----------------------- Priority Queue for Complaints -----------------------

class Complaint {
public:
    int complaintID;
    int userID;
    std::string text;

    Complaint(int cid, int uid, const std::string& txt)
        : complaintID(cid), userID(uid), text(txt) {}
};

class ComplaintManager {
private:
    std::priority_queue<std::pair<int, Complaint*>> complaintQueue;
    AVLTree complaintAVL;

public:
    void registerComplaint(int priority, Complaint* complaint) {
        complaintQueue.push({ priority, complaint });
        complaintAVL.insert(complaint->userID, complaint);
    }

    Complaint* serviceComplaint() {
        if (complaintQueue.empty()) return nullptr;
        Complaint* topComplaint = complaintQueue.top().second;
        complaintQueue.pop();
        return topComplaint;
    }

    void displayComplaints() {
        // Iterate through the AVL Tree and print
        complaintAVL.printInOrder();
    }
};

// ----------------------- Main Program -----------------------

int main() {
    std::cout << "Customer Service Module" << std::endl;

    // Example usage
    AVLTree userIndex;
    ComplaintManager cm;

    User user1(1, "Alice", "alice@example.com", "USA", "Platinum");
    User user2(2, "Bob", "bob@example.com", "Canada", "Gold");

    userIndex.insert(user1.userID, &user1);
    userIndex.insert(user2.userID, &user2);

    userIndex.printInOrder();

    Complaint comp1(101, 1, "Issue with billing.");
    Complaint comp2(102, 2, "Bug in the game.");

    cm.registerComplaint(1, &comp1);
    cm.registerComplaint(2, &comp2);

    cm.displayComplaints();

    return 0;
}
