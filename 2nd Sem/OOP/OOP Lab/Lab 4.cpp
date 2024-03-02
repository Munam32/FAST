//#include <iostream>
//#include <fstream>
//
//using namespace std;
//
//int STRlen(char* arr) {
//
//	int count = 0;
//
//	while (arr[count] != '\0') 
//		count++;
//
//	return count;
//}
//
//char* TOlower(char* arr) {
//	int i = 0;
//	while (arr[i] != '/0') 
//	{
//		if (arr[i] <= 'Z') 
//		{
//			arr[i] += 32;
//		}
//	}
//	return arr;
//}
//
//
//
//char** ReadStudentsListFromFile(int& size)
//{
//	ifstream input("StudentsList.txt");
//
//	if (input.is_open())
//	{
//		input >> size;
//		input.ignore();
//
//		char** List = new char* [size];
//		char name[100];
//
//		for (int i = 0; i < size; i++)
//		{
//
//			input.getline(name, 80);
//			List[i] = new char[STRlen(name) + 1];
//
//			for (int j = 0; j < STRlen(name); j++)
//			{
//				List[i][j] = name[j];
//			}
//
//
//			List[i][STRlen(name)] = '\0';
//	
//		}
//
//		input.close();
//		return List;
//	}
//	else
//		return nullptr;
//}
//
//
//
//void PrintAllNames(char** studentsList, const int& size) {
//
//	for (int i = 0; i < size; i++) {
//
//		cout << studentsList[i] << endl;
//	}
//
//	cout << endl;
//}
//
//
//
//int FirstIndexOfSubString(char* myStr, char* strToFind) {
//	int index = 0;
//
//	while (myStr[index] != '\0') {
//
//		int i = 0;
//		bool found = true;
//
//		do {
//			if (myStr[index + i] != strToFind[i]) {
//				found = false;
//				break;
//			}
//			i++;
//		} while (found == true && STRlen(strToFind) > i);
//
//
//		if (found == true) return index;
//		index++;
//	}
//
//	return -1;
//}
//
//
//// aalia handle nhi hoi
//
//char** FindNameFromStudentsList(char** list, char* SearchString, const int& size, int& count) {
//
//	char** tempFoundList = new char* [size];
//
//	for (int i = 0; i < size; i++) {
//		char* templist = list[i];
//
//		int found = FirstIndexOfSubString(list[i], SearchString);
//		
//		if (found != -1) {
//			tempFoundList[count++] = list[i];
//		}
//	}
//
//
//	if (count == 0) {
//		delete[] tempFoundList;
//		return nullptr;
//	}
//
//	char** foundList = new char* [count];
//
//	for (int i = 0; i < count; i++) {
//		foundList[i] = tempFoundList[i];
//	}
//
//	delete[] tempFoundList;
//
//	return foundList;
//
//}
//
//
//void main() {
//	int size;
//	char** List = ReadStudentsListFromFile(size);
//	if (List == nullptr)
//		cout << "Can not open file";
//	else
//	{
//		PrintAllNames(List, size);
//
//		/*char arr[80] = "Hi i am a Pakistani\0";
//		char tofind[7] = "am";
//		cout << FirstIndexOfSubString(arr, tof);*/
//
//		char* searchString = new char[80];
//		cout << "Enter string to search: ";
//		cin >> searchString;
//		int count = 0;
//		char** foundList = FindNameFromStudentsList(List, searchString, size, count);
//		if (foundList != nullptr) PrintAllNames(foundList, count);
//		else cout << "No Result Found";
//
//		delete[] searchString;
//	}
//
//	cout << "\n";
//	system("pause");
//
//}

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int STRlen(char* arr) {
	int count = 0;
	while (arr[count] != '\0') count++;
	return count;
}

char* TOlower(char* arr) {
	int i = 0;
	while (arr[i] != '\0') {
		if (arr[i] <= 'Z') {
			arr[i] += 32;
		}
		i++;
	}
	return arr;
}



char** ReadStudentsListFromFile(int& size) {
	ifstream toRead("StudentsList.txt");
	toRead >> size;
	toRead.ignore();
	char** List = new char* [size];
	char name[80];
	for (int i = 0; i < size; i++) {
		toRead.getline(name, 80);
		List[i] = new char[STRlen(name) + 1];
		for (int j = 0; j < STRlen(name); j++) {
			List[i][j] = name[j];
		}
		List[i][STRlen(name)] = '\0';
		//strcpy(List[i], name);
	}
	toRead.close();
	return List;
}



void PrintAllNames(char** studentsList, const int& size) {
	for (int i = 0; i < size; i++) {
		cout << studentsList[i] << endl;
	}
	cout << endl;
}



int FirstIndexOfSubString(char* myStr, char* strToFind) {
	int index = 0;
	while (myStr[index] != '\0') {
		int i = 0;
		bool found = true;
		do {
			if (myStr[index + i] != strToFind[i]) {
				found = false;
				break;
			}
			i++;
		} while (found == true && STRlen(strToFind) > i);
		if (found == true) return index;
		index++;
	}

	return -1;
}



char** FindNameFromStudentsList(char** list, char* SearchString, const int& size, int& count) {
	char** tempFoundList = new char* [size];

	for (int i = 0; i < size; i++) {
		int found = FirstIndexOfSubString(list[i], SearchString);
		if (found != -1) {
			tempFoundList[count] = list[i];
			count++;
		}
	}

	if (count == 0) {
		delete[] tempFoundList;
		return nullptr;
	}

	char** foundList = new char* [count];
	for (int i = 0; i < count; i++) {
		foundList[i] = tempFoundList[i];
	}

	delete[] tempFoundList;

	return foundList;

}



void RemoveStudents(char** list, const int& size, char**& AfterDel, int& j) {
	std::cout << "What to search: ";
	char remove[80];
	std::cin >> remove;
	int count = 0;
	char** toRemove = FindNameFromStudentsList(list, remove, size, count);
	j = 0;

	// Allocate memory for AfterDel
	AfterDel = new char* [size];

	for (int i = 0; i < size; i++) {
		bool found = false;
		for (int k = 0; k < count; k++) {
			if (list[i] == toRemove[k]) {
				found = true;
				break;
			}
		}
		if (!found) {
			AfterDel[j] = new char[strlen(list[i]) + 1];
			strcpy(AfterDel[j], list[i]);
			j++;
		}
	}

	for (int i = 0; i < count; ++i) {
		delete[] toRemove[i];
	}
	delete[] toRemove;
}

void main() {

	int size;
	char** List = ReadStudentsListFromFile(size);

	PrintAllNames(List, size);

	/*char arr[80] = "Hi i am a Pakistani\0";
	char tofind[7] = "am";
	cout << FirstIndexOfSubString(arr, tof);*/

	char* searchString = new char[80];
	cout << "Enter string to search: ";
	cin >> searchString;
	int count = 0;
	char** foundList = FindNameFromStudentsList(List, searchString, size, count);
	if (foundList != nullptr) PrintAllNames(foundList, count);
	else cout << "No Result Found";

	delete[] searchString;

	char** AfterDel = nullptr;
	int sizeAfterDel;
	RemoveStudents(List, size, AfterDel, sizeAfterDel);
	PrintAllNames(AfterDel, sizeAfterDel);

	cout << "\n";
	system("pause");
	
}
