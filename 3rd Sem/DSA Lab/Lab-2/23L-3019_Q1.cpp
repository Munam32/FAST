//#include <iostream>
//#include<cstring>
//using namespace std;
//
//class Department {
//
//	string dept_name;
//	string dept_id;
//
//
//	class Course {
//	public:
//		string courseName;
//		string courseId;
//		int credits;
//
//		void printCoursedetails() {
//			cout << "Course Name: " << courseName << endl << "Course ID: " << courseId << endl << "Credits:" << credits << endl;
//		}
//
//		Course(string _courseName, string _courseId, int _credits) {
//			courseName = _courseName;
//			courseId = _courseId;
//			credits = _credits;
//		}
//		Course() {
//			
//			courseName = "";
//			courseId = "";
//			credits = 0;
//			
//		
//		}
//		
//	};
//
//	class Student {
//
//	
//	public:
//		string studentName;
//		string studentId;
//		float gpa;
//		
//		Student(string _studentName, string _studentId, float _gpa) {
//			studentId = _studentId;
//			studentName = _studentName;
//			gpa = _gpa;
//
//		}
//		Student() {
//		
//			gpa = 0;
//			studentId = "";
//			studentName = "";
//		
//		}
//
//		void printStudentdetails() {
//			cout << "Student Name: " << studentName << endl << "Student ID: " << studentId << endl << "GPA: " << gpa << endl;;
//		}
//		
//
//	};
//	
//	Student* AllStudents;
//	int studentCapacity=0;
//	int studentsSize = 10;
//
//	Course* Allcourses;
//	int courseCapacity=0;
//	int coursesSize = 10;
//
//
//
//
//public:
//	
//	Department(string _deptName, string _deptId) {
//		dept_name = _deptName;
//		dept_id = _deptId;
//
//		AllStudents = new Student[10];
//		Allcourses = new Course[10];
//
//	}
//
//	void enrollStudent(string _studentName, string _studentId, float _gpa) {
//		if (studentCapacity < studentsSize) {
//			AllStudents[studentCapacity++] = Student(_studentName, _studentId, _gpa);
//		}
//		else
//		{
//			studentsSize *= 2;
//			Student* temp = new Student[studentsSize];
//
//			for (int i = 0; i < studentCapacity; i++) {
//				temp[i] = AllStudents[i];
//			}
//
//			delete[] AllStudents;
//			
//			AllStudents = temp;
//		}
//
//	}
//
//	void addCourse(string _courseName, string _courseId, int _credits) {
//		if (courseCapacity < coursesSize) {
//			Allcourses[courseCapacity++] = Course(_courseName, _courseId, _credits);
//		}
//		else
//		{
//			coursesSize *= 2;
//			Course* temp = new Course[studentsSize];
//
//			for (int i = 0; i < studentCapacity; i++) {
//				temp[i] = Allcourses[i];
//			}
//
//			delete[] Allcourses;
//
//			Allcourses = temp;
//		}
//	}
//
//	void printDepartmentDetails() {
//		cout << "Department Name: " << dept_name << endl << "Department ID: " << dept_id << endl;
//		for (int i = 0; i < studentCapacity; i++) {
//			AllStudents[i].printStudentdetails();
//			Allcourses[i].printCoursedetails();
//		}
//	}
//	
//	
//	
//	
//	
//	
//
//
//};
//
//
//void main()
//{
//	Department CS("Computer Science", "CS001");
//	CS.enrollStudent("Munam", "23L-3019", 3.9);
//	CS.addCourse("Numerical Computing", "CS-2009", 166);
//
//	CS.printDepartmentDetails();
//
//
//	cout << "\n";
//	system("pause");
//}