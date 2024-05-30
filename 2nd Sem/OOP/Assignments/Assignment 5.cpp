#include <iostream>
#include <fstream>
using namespace std;

class Helper {
public:
    
    static int strLen(char* text) {
        int i = 0;
        while (text[i] != '\0') i++;
        return i;
    }
    

     static void DeepCopy(char* to, char* from) {

        int i = 0;

        for (; from[i] != '\0'; i++)
        {
            to[i] = from[i];
        }

        to[i] = '\0';
    }
};

class Academics {

    static int totalStudents;
    static int totalQuiz;
    static int totalAssignment;

    char* rollno;
    char* fname;
    char* lname;
    int* quiz;
    int* assignment;
    int totalperperson = 0;

public:

    static int* quizMarks;
    static int* assignmentMarks;
    static char invalidRollNo[];
    static int* total;
    static int* min;
    static int* max;
    static int* avg;

    //Constructor
    Academics(char* _rollno =nullptr, char* _fname = nullptr, char* _lname = nullptr, int* _quiz = nullptr, int* _assignment = nullptr, int _total = 0) {
        rollno = _rollno;
        fname = _fname;
        lname = _lname;
        quiz = _quiz;
        assignment = _assignment;
        totalperperson = _total;
    }

    //CopyConstructorDeepCopy

    Academics(const Academics& copied) {

        rollno = new char[9];
        Helper::DeepCopy(rollno, copied.rollno);

        fname = new char[Helper::strLen(copied.fname) + 1];
        Helper::DeepCopy(fname, copied.fname);

        lname = new char[Helper::strLen(copied.lname) + 1];
        Helper::DeepCopy(lname, copied.lname);

        quiz = new int[totalQuiz];

        for (int i = 0; i < totalQuiz; i++) {
            quiz[i] = copied.quiz[i];
        }

        assignment = new int[totalAssignment];
        for (int i = 0; i < totalAssignment; i++) {
            assignment[i] = copied.assignment[i];
        }

        totalperperson = copied.totalperperson;
    }

    //EqualityDeepCopy
    const Academics& operator=(const Academics& copy) {

        if (&copy != this) {

            rollno = new char[9];
            Helper::DeepCopy(rollno, copy.rollno);

            fname = new char[Helper::strLen(copy.fname) + 1];
            Helper::DeepCopy(fname, copy.fname);

            lname = new char[Helper::strLen(copy.lname) + 1];
            Helper::DeepCopy(lname, copy.lname);

            quiz = new int[totalQuiz];
            for (int i = 0; i < totalQuiz; i++) {
                quiz[i] = copy.quiz[i];
            }


            assignment = new int[totalAssignment];
            for (int i = 0; i < totalAssignment; i++) {
                assignment[i] = copy.assignment[i];
            }

            totalperperson = copy.totalperperson;
        }

        return *this;
    }

    static void ReadHeader(ifstream& toRead) {
        toRead >> totalStudents;
        toRead >> totalQuiz;
        toRead >> totalAssignment;
    }

    void ReadDataFromFile(ifstream& toRead) {
        char tempRollNo[9];
        char tempFName[20];
        char tempLName[20];

        toRead >> tempRollNo;
        toRead >> tempFName;
        toRead >> tempLName;

        rollno = new char[Helper::strLen(tempRollNo)+1];
        Helper::DeepCopy(rollno, tempRollNo);

        fname = new char[Helper::strLen(tempFName)+1];
        Helper::DeepCopy(fname, tempFName);

        lname = new char[Helper::strLen(tempLName)+1];
        Helper::DeepCopy(lname, tempLName);

        quiz = new int[totalQuiz];
        for (int i = 0; i < totalQuiz; i++) {
            toRead >> quiz[i];
        }

        assignment = new int[totalAssignment];
        for (int i = 0; i < totalAssignment; i++) {
            toRead >> assignment[i];
        }
    }

    static int GetTotalStudents() {
        return totalStudents;
    }
    static int GetTotalQuiz() {
        return totalQuiz;
    }
    static int GetTotalAssignment() {
        return totalAssignment;
    }
    char* GetRollNo() {
        return rollno;
    }
    char* GetFName() {
        return fname;
    }
    char* GetLName() {
        return lname;
    }
    int GetQuizIndex(int index) {
        return quiz[index];
    }
    int GetAssignmentIndex(int index) {
        return assignment[index];
    }
    int GetTotal() {
        return totalperperson;
    }
    
    void SetRollNo(char* set) {
        rollno = set;
    }
    void SetTotal(int set) {
        totalperperson = set;
    }


    friend void UpdateStatistics(Academics* gradesheet, int*& total, int*& max, int*& min, int*& avg);

    void PrintQuiz() {
        for (int i = 0; i < totalQuiz; i++) {
            cout << quiz[i] << '\t';
        }
    }
    void PrintAssignment() {
        for (int i = 0; i < totalAssignment; i++) {
            cout << assignment[i] << '\t';
        }
    }
    void PrintRow() {
        if (Helper::strLen(fname) + Helper::strLen(lname) < 16) cout << rollno << '\t' << fname << ' ' << lname << "\t\t\t";
        else cout << rollno << '\t' << fname << ' ' << lname << "\t\t";
        PrintQuiz();
        PrintAssignment();
        cout << totalperperson << endl;
    }
    void PrintDetailedView() {
        cout << "Roll No:\t" << rollno << endl;
        cout << "Name:\t" << fname << " " << lname << endl;
        cout << "Quiz Marks:" << endl;
        int totalpossible = 0;
        for (int i = 0; i < totalQuiz; i++) {
            totalpossible += quizMarks[i];
            cout << "\tQ" << i + 1 << ":\t" << quiz[i] << "/" << quizMarks[i] << endl;
        }
        cout << "Assignment Marks:" << endl;
        for (int i = 0; i < totalAssignment; i++) {
            totalpossible += assignmentMarks[i];
            cout << "\tA" << i + 1 << ":\t" << assignment[i] << "/" << assignmentMarks[i] << endl;
        }
        cout << "Total:\t" << totalperperson << "/" << totalpossible << endl << endl;
    }
    static void PrintStats() {
        int totalQuiz = GetTotalQuiz();
        int totalAssignment = GetTotalAssignment();

        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\t\t" << "-Q1-\t" << "-Q2-\t" << "-Q3-\t" << "-Q4-\t" << "-A1-\t" << "-A2-\t" << "-A3-\t" << "-A4-" << endl;
        cout << "\tTotal\t\t----------------\t";
        for (int i = 0; i < totalQuiz + totalAssignment; i++) {
            cout << total[i] << '\t';
        }

        cout << endl;
        cout << "\tMaximum\t\t----------------\t";
        for (int i = 0; i < totalQuiz + totalAssignment; i++) {
            cout << max[i] << '\t';
        }

        cout << endl;
        cout << "\tMinimum\t\t----------------\t";
        for (int i = 0; i < totalQuiz + totalAssignment; i++) {
            cout << min[i] << '\t';
        }
        cout << endl;
        cout << "\tAverage\t\t----------------\t";
        for (int i = 0; i < totalQuiz + totalAssignment; i++) {
            cout << avg[i] << '\t';
        }
        cout << endl;
        cout << "---------------------------------------------------------------------------------------------------------------------" << endl;
    }
    
    ~Academics() {
        if (rollno != nullptr) delete[] rollno;
        if (fname != nullptr) delete[] fname;
        if (lname != nullptr) delete[] lname;
        if (quiz != nullptr) delete[] quiz;
        if (assignment != nullptr) delete[] assignment;
    }
};

int Academics::totalStudents = 0;
int Academics::totalQuiz = 0;
int Academics::totalAssignment = 0;
int* Academics::quizMarks = nullptr;
int* Academics::assignmentMarks = nullptr;
int* Academics::total = nullptr;
int* Academics::min = nullptr;
int* Academics::max = nullptr;
int* Academics::avg = nullptr;
char invalidRollNo[] = "-1";
Academics* mainSheet;

Academics* ReadDataFromFile() {
    ifstream toRead("gradesheet.txt");
    //Reading File Header
    Academics::ReadHeader(toRead);
    int totalQuiz = Academics::GetTotalQuiz();
    int totalAssignment = Academics::GetTotalAssignment();
    int totalStudents = Academics::GetTotalStudents();

    Academics::quizMarks = new int[totalQuiz];
    for (int i = 0; i < totalQuiz; i++) {
        toRead >> Academics::quizMarks[i];
    }
    Academics::assignmentMarks = new int[totalAssignment];
    for (int i = 0; i < totalAssignment; i++) {
        toRead >> Academics::assignmentMarks[i];
    }
    //Dynamically allocating and storing in gradesheet
    if (totalStudents > 1) {
        Academics* gradesheet = new Academics[totalStudents + 1];
        for (int i = 0; i < totalStudents; i++) {
            gradesheet[i].ReadDataFromFile(toRead);
        }
        gradesheet[totalStudents].SetRollNo(invalidRollNo);
        return gradesheet;
    }
    toRead.close();
    //Returning the gradesheet
    return nullptr;
}

void UpdateStatistics(Academics* gradesheet, int*& total, int*& max, int*& min, int*& avg) {
    int totalQuiz = Academics::GetTotalQuiz();
    int totalAssignment = Academics::GetTotalAssignment();
    int totalStudents = Academics::GetTotalStudents();
    
    //Update Total Row
    total = new int[totalQuiz + totalAssignment];
    for (int i = 0; i < totalQuiz + totalAssignment; i++) {
        if (i < totalQuiz) {
            total[i] = Academics::quizMarks[i];
        }
        else {
            total[i] = Academics::assignmentMarks[i - totalQuiz];
        }
    }
    //Update Max Row
    max = new int[totalQuiz + totalAssignment];
    for (int i = 0; i < totalQuiz + totalAssignment; i++) {
        for (int j = 0; j < totalStudents; j++) {
            if (j == 0 && i < totalQuiz) max[i] = gradesheet[j].quiz[i];
            else if (j == 0) max[i] = gradesheet[j].assignment[i - totalQuiz];
            else {
                if (i < totalQuiz) {
                    if (gradesheet[j].quiz[i] > max[i]) max[i] = gradesheet[j].quiz[i];
                }
                else if (i >= totalQuiz) {
                    if (gradesheet[j].assignment[i - totalQuiz] > max[i]) max[i] = gradesheet[j].assignment[i - totalQuiz];
                }
            }
        }
    }
    //Update Min Row
    min = new int[totalQuiz + totalAssignment];
    for (int i = 0; i < totalQuiz + totalAssignment; i++) {
        for (int j = 0; j < totalStudents; j++) {
            if (j == 0 && i < totalQuiz) min[i] = gradesheet[j].quiz[i];
            else if (j == 0) min[i] = gradesheet[j].assignment[i - totalQuiz];
            else {
                if (i < totalQuiz) {
                    if (gradesheet[j].quiz[i] < min[i]) min[i] = gradesheet[j].quiz[i];
                }
                else if (i >= totalQuiz) {
                    if (gradesheet[j].assignment[i - totalQuiz] < min[i]) min[i] = gradesheet[j].assignment[i - totalQuiz];
                }
            }
        }
    }
    //Update Avg Row
    avg = new int[totalQuiz + totalAssignment]();
    for (int i = 0; i < totalQuiz + totalAssignment; i++) {
        for (int j = 0; j < totalStudents; j++) {
            if (i < totalQuiz) {
                avg[i] += gradesheet[j].quiz[i];
            }
            else if (i >= totalQuiz) {
                avg[i] += gradesheet[j].assignment[i - totalQuiz];
            }
        }
        avg[i] /= totalStudents;
    }
}

void ProduceTotal() {
    int totalQuiz = Academics::GetTotalQuiz();
    int totalAssignment = Academics::GetTotalAssignment();

    for (int i = 0; mainSheet[i].GetRollNo() != invalidRollNo; i++) {
        int total = 0;
        for (int j = 0; j < totalQuiz + totalAssignment; j++) {
            if (j < totalQuiz) total += mainSheet[i].GetQuizIndex(j);
            else total += mainSheet[i].GetAssignmentIndex(j - totalQuiz);
        }
        mainSheet[i].SetTotal(total);
    }
}

void PrintAll(Academics* gradeSheet) {
    cout << "RollNo\t\t" << "Name\t\t\t\t" << "-Q1-\t" << "-Q2-\t" << "-Q3-\t" << "-Q4-\t" << "-A1-\t" << "-A2-\t" << "-A3-\t" << "-A4-\t" << "TOTAL" << endl;
    for (int i = 0; gradeSheet[i].GetRollNo() != invalidRollNo; i++) {
        gradeSheet[i].PrintRow();
    }
    cout << endl;
}

Academics* SearchStudentByRollNo(char* rollNo) {
    int totalStudents = Academics::GetTotalStudents();

    for (int i = 0; i < totalStudents; i++) {
        int index = 0;
        while (mainSheet[i].GetRollNo()[index] == rollNo[index]) {
            index++;
        }
        if (index == 9) return &mainSheet[i];
    }
    return &mainSheet[totalStudents];
}

Academics** SearchStudentByKeyword(char* toSearch) {
    Academics* foundList;
    int totalStudents = Academics::GetTotalStudents();
    int* indexToStore = new int[totalStudents];
    int lenStr = Helper::strLen(toSearch);
    int count = 0;

    //Finding what indexes to store
    for (int i = 0; i < totalStudents; i++) {
        int j = 0;

        //Checking RollNo
        char* getRollNo = mainSheet[i].GetRollNo();
        bool  found = false;
        while (getRollNo[j] != '\0') {
            if (getRollNo[j] == toSearch[0]) {
                found = true;
                for (int k = 0; k < lenStr; k++) {
                    if (getRollNo[j + k] != toSearch[k]) {
                        found = false;
                        break;
                    }
                }
                break;
            }
            j++;
        }
        if (found == true) {
            indexToStore[count] = i;
            count++;
            continue;
        }
        //Checking First Name
        char* getFName = mainSheet[i].GetFName();
        found = false;
        j = 0;
        while (getFName[j] != '\0') {
            if (getFName[j] == toSearch[0]) {
                found = true;
                for (int k = 0; k < lenStr; k++) {
                    if (getFName[j + k] != toSearch[k]) {
                        found = false;
                        break;
                    }
                }
                break;
            }
            j++;
        }
        if (found == true) {
            indexToStore[count] = i;
            count++;
            continue;
        }
        //Checking Last Name
        char* getLName = mainSheet[i].GetLName();
        found = false;
        j = 0;
        while (getLName[j] != '\0') {
            if (getLName[j] == toSearch[0]) {
                found = true;
                for (int k = 0; k < lenStr; k++) {
                    if (getLName[j + k] != toSearch[k]) {
                        found = false;
                        break;
                    }
                }
                break;
            }
            j++;
        }
        if (found == true) {
            indexToStore[count] = i;
            count++;
            continue;
        }
    }
    //ShallowCopying the Class references
    if (count == 0) 
        return nullptr;

    foundList = new Academics[count+1];
    for (int i = 0; i < count; i++) {
        foundList[i] = mainSheet[indexToStore[i]];
    }

    foundList[count].SetRollNo(invalidRollNo);
    
    delete[] indexToStore;
    
    return &foundList;
}

void SortListByTotal() {
    int totalStudents = Academics::GetTotalStudents();

    for (int i = 0; i < totalStudents - 1; i++) {
        for (int j = 0; j < totalStudents - 1 - i; j++) {
            if (mainSheet[j].GetTotal() > mainSheet[j + 1].GetTotal()) {
                Academics temp = mainSheet[j];
                mainSheet[j] = mainSheet[j+1];
                mainSheet[j+1] = temp;

            }
        }
    }
}

void main()
{
    //Read and Display
        mainSheet = ReadDataFromFile();
        UpdateStatistics(mainSheet, Academics::total, Academics::max, Academics::min, Academics::avg);
        mainSheet->PrintStats();
        ProduceTotal();
        PrintAll(mainSheet);

    //KeyWord Search and Printing
        char keyWord[] = "43";

        Academics** searchKeyWord = SearchStudentByKeyword(keyWord);

        if (searchKeyWord != nullptr) 
            PrintAll(*searchKeyWord);
        else cout << "No Rows match Criteria" << endl << endl;

    //RollNo search and Printing
        char rollNo1[] = "15L-1234";
        Academics* searchRoll1 = SearchStudentByRollNo(rollNo1);
        if ((*searchRoll1).GetRollNo() != invalidRollNo) (*searchRoll1).PrintDetailedView();
        else cout << "No Record Found!" << endl << endl;
        
        char rollNo2[] = "15L-4023";
        Academics* searchRoll2 = SearchStudentByRollNo(rollNo2);
        if ((*searchRoll2).GetRollNo() != invalidRollNo) (*searchRoll2).PrintDetailedView();
        else cout << "No Record Found!" << endl << endl;

    //Sort List and Display
        SortListByTotal();
        PrintAll(mainSheet);

    delete[] Academics::quizMarks;
    delete[] Academics::assignmentMarks;
    delete[] Academics::total;
    delete[] Academics::max;
    delete[] Academics:: min;
    delete[] Academics::avg;


    system("pause");

}