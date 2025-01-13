#include <iostream>
#include <string>
using namespace std;

class HashTable {
private:
    struct Node {
        string key;  
        int value;  
        Node* next;  

        Node(string k, int v) : key(k), value(v), next(nullptr) {}
    };

    int size;      
    Node** table;  

    // Polynomial hash function
    int hashFunction(const string& key) {
        int hashCode = 0;
        int a = 33; // Polynomial coefficient
        for (char ch : key) {
            hashCode = (hashCode * a + ch) % size;
        }
        return hashCode;
    }

public:
    // Constructor
    HashTable(int size) : size(size) {
        table = new Node * [size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
    }

    
    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Node* current = table[i];
            while (current) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }

    // Insert key-value pair
    void Insert(string key, int value) {
        int index = hashFunction(key);
        Node* newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    // Delete a key
    void Delete(string key) {
        int index = hashFunction(key);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    table[index] = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
        cout << "Key not found: " << key << endl;
    }

    // Update the value of an existing key
    void Update(string key, int newValue) {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current) {
            if (current->key == key) {
                current->value = newValue;
                return;
            }
            current = current->next;
        }
        cout << "Key not found: " << key << endl;
    }

    // Access the value of a specific key
    int Access(string key) {
        int index = hashFunction(key);
        Node* current = table[index];

        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        cout << "Key not found: " << key << endl;
        return -1; // Indicate key not found
    }

    // Display the entire hash table 
    void Display() {
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "]: ";
            Node* current = table[i];
            while (current) {
                cout << "(" << current->key << ", " << current->value << ") -> ";
                current = current->next;
            }
            cout << "nullptr" << endl;
        }
    }
};

void main() {

    HashTable ht(20);

    // Insertion: Adding air pollution data for 50 cities
    ht.Insert("Karachi", 45);
    ht.Insert("Lahore", 50);
    ht.Insert("Islamabad", 35);
    ht.Insert("Peshawar", 40);
    ht.Insert("Quetta", 30);
    ht.Insert("Michigan", -5);

    // Update: Updating pollution index for a specific city
    ht.Update("Karachi", 48);


    cout << "Pollution index for Karachi: " << ht.Access("Karachi") << "%" << endl;

    // Deletion: Remove a city's data
    ht.Delete("Michigan");

    
    ht.Display();


    cout << "\n";
    system("pause");
}