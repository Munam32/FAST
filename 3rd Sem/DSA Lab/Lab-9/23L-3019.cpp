#include <vector>
#include <iostream>
using namespace std;

template<typename T>
class minHeap {
public:
    
    minHeap() {}

    
    minHeap(T* arr, int N) {
        for (int i = 0; i < N; i++) {
            array.push_back(arr[i]);
        }
        buildMinHeap();
    }

    // Builds min heap from the vector
    void buildMinHeap() {
        for (int i = (array.size() / 2) - 1; i >= 0; i--) {
            bubble_down(i);
        }
    }

    // Insert element into heap
    void insert(const T& x) {
        array.push_back(x);
        bubble_up(array.size() - 1);
    }

    // Check if heap is empty
    bool isEmpty() const {
        return array.empty();
    }

    // Get minimum element
    const T& getMin() const {
        if (!isEmpty()) {
            return array[0];
        }
        throw runtime_error("Heap is empty");
    }

    // Delete minimum element
    void deleteMin() {
        if (isEmpty()) {
            throw runtime_error("Heap is empty");
        }

        array[0] = array.back();
        array.pop_back();

        if (!isEmpty()) {
            bubble_down(0);
        }
    }

    // Delete all occurrences of a key
    bool deleteAll(T key) {
        bool found = false;
        vector<T> temp;

        // Save all elements except key
        for (const T& elem : array) {
            if (elem != key) {
                temp.push_back(elem);
            }
            else {
                found = true;
            }
        }

        if (found) {
            array = temp;
            buildMinHeap(); // Rebuild heap
        }

        return found;
    }

private:
    vector<T> array;

    // Bubble up element at index i
    void bubble_up(int i) {
        if (i <= 0) return;

        int parent = (i - 1) / 2;
        if (array[parent] > array[i]) {
            swap(array[parent], array[i]);
            bubble_up(parent);
        }
    }

    // Bubble down element at index i
    void bubble_down(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < array.size() && array[left] < array[smallest]) {
            smallest = left;
        }

        if (right < array.size() && array[right] < array[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            swap(array[i], array[smallest]);
            bubble_down(smallest);
        }
    }
};

// Non-member heapsort function
template<typename T>
void Heapsort(T* arr, int size, int sorting_order) {
    // Create minHeap from array
    minHeap<T> heap(arr, size);

    // Sort in ascending order
    if (sorting_order == 1) {
        for (int i = 0; i < size; i++) {
            arr[i] = heap.getMin();
            heap.deleteMin();
        }
    }
    // Sort in descending order
    else {
        for (int i = size - 1; i >= 0; i--) {
            arr[i] = heap.getMin();
            heap.deleteMin();
        }
    }
}

void main() {
    // Task 1: Insert items
    minHeap<int> heap;
    int items[] = { 10, 40, 50, 5, 60, 15, 20 };
    for (int item : items) {
        heap.insert(item);
    }

    // Task 2: Find first, second, and third minimum
    cout << "1st 3 minimum elements: ";
    for (int i = 0; i < 3; i++) {
        cout << heap.getMin() << " ";
        heap.deleteMin();
    }
    cout << endl;

    // Task 3: Test Heapsort
    int array[] = { 10, 4, 5, 30, 3, 300 };
    int size = 6;

    cout << "Original: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    // Sort in ascending order
    Heapsort(array, size, 1);

    cout << "Ascending Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;

    system("pause");
}