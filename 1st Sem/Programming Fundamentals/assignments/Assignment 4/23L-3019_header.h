// menu
void menu();

// string manipulation
int string_length(char arr[]);
void string_concat(char first_arr[], char second_arr[],char combined_arr[]);
void string_copy(char source_arr[], char dest_arr[]);
void string_edit(char arr[], char ch,char ch_add);

// Calculator
float add(float num1, float num2);
float sub(float num1, float num2);
float mul(float num1, float num2);
float div(float num1, float num2);
float simp_power(float num, int power);
float power_frac(float num, float power);

//	Sorts
void BubbleSort(float arr[], int size,char ch);
void InsertionSort(float arr[], int size,char ch);
void SelectionSort(float arr[], int size,char ch);


// Searching
int LinearSearch(float arr[], int size,float value);
int BinarySearch(float arr[], int size, float target);