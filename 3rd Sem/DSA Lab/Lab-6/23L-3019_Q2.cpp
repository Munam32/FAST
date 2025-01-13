//#include <iostream>
//using namespace std;
//
//int binarySearchInRange(int arr[], int low, int high, int target) {
//	
//	if (high >= low) {
//		int mid = (high + low) / 2;
//
//		if (arr[mid] == target) {
//			return mid;
//		}
//		if (target < arr[mid]) {
//			return binarySearchInRange(arr, low, mid - 1, target);
//		}
//		else
//			return binarySearchInRange(arr, mid + 1, high, target);
//
//	}
//	return -1;
//
//
//
//
//}
//
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
//	int arr[] = { 1,2,3,4,5,6,7,8,9 };
//
//	cout << binarySearchInRange(arr, 0, 8, 5);
//
//
//	cout << "\n";
//	system("pause");
//}