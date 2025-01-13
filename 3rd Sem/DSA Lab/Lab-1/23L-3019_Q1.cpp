//#include <iostream>
//using namespace std;
//
//struct Book {
//	int id;
//	const char* title;
//
//	friend ostream& operator << (ostream& out, const Book& obj) {
//		cout << "ID: " << obj.id << endl << "Title: " << obj.title << endl << "------------------";
//		return out;
//	}
//
//};
//
//
//
//
//class Library {
//	Book** books;
//	int capacity;
//	int size;
//	
//
//public:
//	Library() {
//	
//		books = 0;
//
//	}
//
//	Library(int _capacity) {
//		capacity = _capacity;
//		books = 0;
//		
//	}
//	~Library() {
//		for (int i = 0; i < size; i++)
//			delete books[i];
//		
//		
//		size = 0;
//		capacity = 0;
//	}
//
//	void addBook(int id, const char* title) {
//		
//		if (size -1 < capacity) {
//
//			Book** temp = new Book * [size++];
//			for (int i = 0; i < size - 1; i++) {
//				temp[i] = books[i];
//			}
//
//			
//
//			temp[size - 1] = new Book {id,title};
//
//			books = temp;
//		}
//		else
//			cout << "Max Capacity reached"<<endl;
//	
//	}
//	void displayBooks()const {
//		
//		for (int i = 0; i < size; i++) {
//			cout << "Book" << i + 1 << endl;
//			cout << *books[i] << endl;
//		}
//	
//	
//	
//	}
//	
//
//
//
//};
//
//void main() {
//	int capacity = 2;
//	Library lib(capacity);
//	
//	lib.addBook(9, "Haalo");
//	lib.addBook(10, "Boye");
//
//	lib.displayBooks();
//
//
//	system("pause");
//}