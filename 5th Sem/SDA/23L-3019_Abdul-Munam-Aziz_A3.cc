#include <iostream>
#include <string>


//                  Person
//                   /  \
//            Student    Teacher
//                  \    /
//                    TA



// Common base class
class Person {
protected:
    std::string name;
public:
    Person(const std::string& n) : name(n) {
        // std::cout << "Person constructor called" << std::endl;
    }

    virtual ~Person() {} // Virtual destructor for base class
    
    // Virtual print function
    virtual void print() {
        std::cout << "Name: " << name << std::endl;
    }
};

// Student class inherits virtually from Person
class Student : public virtual Person {
protected:
    std::string program;
public:
    Student(const std::string& n, const std::string& p)
        : Person(n), program(p) {}

    void print() override {
        std::cout << "--- Student ---" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Program: " << program << std::endl;
    }
};

// Teacher class inherits virtually from Person
class Teacher : public virtual Person {
protected:
    std::string designation;
public:
    Teacher(const std::string& n, const std::string& d)
        : Person(n), designation(d) {}

    void print() override {
        std::cout << "--- Teacher ---" << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Designation: " << designation << std::endl;
    }
};






// TA class inherits from both Student and Teacher
class TA : public Student, public Teacher {
private:
    // Assuming the 4th argument "1000" is a stipend
    int stipend; 
    // Assuming the 3rd argument "TA" is the designation
    // which is already handled by the Teacher base class.

public:
    // The most derived class (TA) must initialize the virtual base class (Person)
    TA(const std::string& n, const std::string& p, const std::string& d, int s)
        : Person(n), Student(n, p), Teacher(n, d), stipend(s) {}

    // This print function prints all data members [cite: 24]
    void print() override {
        std::cout << "--- Teaching Assistant ---" << std::endl;
        std::cout << "Name: " << name <<" (Inherited)" << std::endl;         // From Person
        std::cout << "Program: " << program <<" (Inherited)" << std::endl;     // From Student
        std::cout << "Designation: " << designation <<" (Inherited)" << std::endl; // From Teacher
        std::cout << "Stipend: " << stipend <<std::endl;   // From TA
    }
};

// Main function as provided in the question
int main() {
    Student s1("Aslam", "BSCS");
    Teacher t1("Zahid", "Assistant Professor");
    TA ta1("Nasir", "BSEE", "TA", 1000);
    
    s1.print();
    std::cout << std::endl;
    
    t1.print();
    std::cout << std::endl;
    
    ta1.print();
    
    return 0;
}