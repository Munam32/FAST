--cross product

DROP TABLE IF EXISTS Enrollment;
DROP TABLE IF EXISTS Students;
DROP TABLE IF EXISTS Courses;

-- Create two tables
CREATE TABLE Students (
    StudentID INT PRIMARY KEY,
    StudentName VARCHAR(50)
);

CREATE TABLE Courses (
    CourseID INT PRIMARY KEY,
    CourseName VARCHAR(50)
);

-- Insert sample data
INSERT INTO Students VALUES (1, 'Alice'), (2, 'Bob'),(3, 'john') ;
INSERT INTO Courses VALUES (101, 'Math'), (102, 'Science'), (103, 'English');

-- Cross Product (Cartesian Join)
SELECT * FROM Students, Courses;



CREATE TABLE Enrollment (
    StudentID INT,
    CourseID INT,
    FOREIGN KEY (StudentID) REFERENCES Students(StudentID),
    FOREIGN KEY (CourseID) REFERENCES Courses(CourseID)
);

-- Insert data
INSERT INTO Enrollment VALUES (1, 101), (2, 102);

Select * from Students;
Select * from Courses;
Select * from Enrollment;

-- Inner Join
SELECT Students.StudentID, Students.StudentName, Courses.CourseName
FROM Students
INNER JOIN Enrollment ON Students.StudentID = Enrollment.StudentID
INNER JOIN Courses ON Enrollment.CourseID = Courses.CourseID;

SELECT *
FROM Students
LEFT JOIN Enrollment ON Students.StudentID = Enrollment.StudentID
RIGHT JOIN Courses ON Enrollment.CourseID = Courses.CourseID;

SELECT *
FROM Students
RIGHT JOIN Enrollment ON Students.StudentID = Enrollment.StudentID
RIGHT JOIN Courses ON Enrollment.CourseID = Courses.CourseID;

SELECT Students.StudentID, Students.StudentName, Courses.CourseName
FROM Students
FULL JOIN Enrollment ON Students.StudentID = Enrollment.StudentID
FULL JOIN Courses ON Enrollment.CourseID = Courses.CourseID;

-- Create Employee table
CREATE TABLE Employees1 (
    EmpID INT PRIMARY KEY,
    EmpName VARCHAR(50),
    ManagerID INT  -- Self-referencing column
);

-- Insert data
INSERT INTO Employees1 VALUES (1, 'Alice', NULL), (2, 'Bob', 1), (3, 'Charlie', 1), (4, 'David', 2);

-- Self Join: Find Employees and Their Managers
SELECT E1.EmpName AS Employee, E2.EmpName AS Manager
FROM Employees1 E1
LEFT JOIN Employees1 E2 ON E1.ManagerID = E2.EmpID;