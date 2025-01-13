#include <iostream>
using namespace std;

class HashTable {
private:
    int size;         
    int* arr;         
    int count;        
    bool rehashFlag;  
    int collisionMethod;  

    
    int hashFunction(int key) {
        return key % size;
    }

    int secondaryHash(int key) {
        return 1 + (key % (size - 2));
    }

    void rehash() {
        int oldSize = size;
        int* oldArr = arr;

        
        size *= 2;
        arr = new int[size];
        for (int i = 0; i < size; i++) arr[i] = -1;

        count = 0;

        // Reinsert old keys
        for (int i = 0; i < oldSize; i++) {
            if (oldArr[i] != -1) {
                Insert(oldArr[i]);
            }
        }
        delete[] oldArr;
    }

    int probeSequence(int hashIndex, int key, int i) {
        switch (collisionMethod) {
        case 1:  // Linear Probing
            return (hashIndex + i) % size;

        case 2:  // Linear Probing with Steps (step size = 3)
            return (hashIndex + i * 3) % size;

        case 3:  // Pseudo-Random Probing (deterministic modular sequence)
            return (hashIndex + (i * i + i) % size) % size;

        case 4:  // Double Hashing
            return (hashIndex + i * secondaryHash(key)) % size;

        default:
            return hashIndex;
        }
    }

public:
    
    HashTable(bool rehashFlag, int collisionMethod, int initSize = 11) : rehashFlag(rehashFlag), collisionMethod(collisionMethod), size(initSize), count(0) {
        
        arr = new int[size];

        for (int i = 0; i < size; i++) arr[i] = -1;
    }

    
    ~HashTable() {
        delete[] arr;
    }

    // Insert key
    void Insert(int key) {
        int hashIndex = hashFunction(key);
        int i = 0;

        while (arr[probeSequence(hashIndex, key, i)] != -1 && i < size) {
            i++;
        }

        if (i == size) {
            cout << "Hash table is full!" << endl;
            return;
        }

        arr[probeSequence(hashIndex, key, i)] = key;
        count++;

        // Trigger rehashing if enabled and load factor > 0.5
        if (rehashFlag && (float)count / size > 0.5) {
            rehash();
        }
    }

    // Delete key
    void Delete(int key) {
        int hashIndex = hashFunction(key);
        int i = 0;

        while (arr[probeSequence(hashIndex, key, i)] != key && i < size) {
            i++;
        }

        if (i < size) {
            arr[probeSequence(hashIndex, key, i)] = -1;
            count--;
        }
    }

    // Update key
    void Update(int key, int newValue) {
        Delete(key);
        Insert(newValue);
    }

    
    int Access(int key) {
        int hashIndex = hashFunction(key);
        int i = 0;

        while (arr[probeSequence(hashIndex, key, i)] != key && i < size) {
            i++;
        }

        return i < size ? arr[probeSequence(hashIndex, key, i)] : -1;
    }

    
    void PrintTable() {
        for (int i = 0; i < size; i++) {
            if (arr[i] == -1) {
                cout << "[ ] ";
            }
            else {
                cout << "[" << arr[i] << "] ";
            }
        }
        cout << endl;
    }
};


void main() {



    HashTable linear(false, 1);
    HashTable linearSteps(false, 2);
    HashTable pseudoRandom(false, 3);
    HashTable doubleHash(false, 4);

    int keys[] = { 10, 40, 10, 80, 20, 90, 10, 30, 79, 15 };
    int numKeys = sizeof(keys) / sizeof(keys[0]);

    // Insert keys into all hash tables
    cout << "Linear Probing:\n";
    for (int i = 0; i < numKeys; i++) {
        linear.Insert(keys[i]);
        linear.PrintTable();
    }

    cout << "Linear Probing with Steps:\n";
    for (int i = 0; i < numKeys; i++) {
        linearSteps.Insert(keys[i]);
        linearSteps.PrintTable();
    }

    cout << "Pseudo-Random Probing:\n";
    for (int i = 0; i < numKeys; i++) {
        pseudoRandom.Insert(keys[i]);
        pseudoRandom.PrintTable();
    }

    cout << "Double Hashing:\n";
    for (int i = 0; i < numKeys; i++) {
        doubleHash.Insert(keys[i]);
        doubleHash.PrintTable();
    }







    cout << "\n";
    system("pause");

}