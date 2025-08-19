--Foreign key
Drop TABLE Departments
Drop TABLE Employees
CREATE TABLE Departments (
    DeptID INT PRIMARY KEY,
    DeptName VARCHAR(100)
);

CREATE TABLE Employees (
    EmpID INT PRIMARY KEY,
    EmpName VARCHAR(100),
    DeptID INT,
    FOREIGN KEY (DeptID) REFERENCES Departments(DeptID) ON DELETE CASCADE on UPDATE CASCADE
);

INSERT INTO Departments VALUES (1, 'HR'), (2, 'IT');

INSERT INTO Employees VALUES (101, 'Alice', 1), (102, 'Bob', 1), (103, 'Charlie', 2);

SELECT * FROM Departments
SELECT * FROM Employees


DELETE FROM Departments WHERE DeptID = 1;


--ON DELETE SET NULL
Drop TABLE Departments
Drop TABLE Employees
CREATE TABLE Departments (
    DeptID INT PRIMARY KEY,
    DeptName VARCHAR(100)
);

CREATE TABLE Employees (
    EmpID INT PRIMARY KEY,
    EmpName VARCHAR(100),
    DeptID INT NULL,
    FOREIGN KEY (DeptID) REFERENCES Departments(DeptID) ON DELETE SET NULL
);
INSERT INTO Departments VALUES (1, 'HR'), (2, 'IT');

INSERT INTO Employees VALUES (101, 'Alice', 1), (102, 'Bob', 1), (103, 'Charlie', 2);
SELECT * FROM Departments
SELECT * FROM Employees

DELETE FROM Departments WHERE DeptID = 1;



--ON DELETE SET DEFAULT
DROP TABLE IF EXISTS Employees;
DROP TABLE IF EXISTS Departments;

-- Create parent table
CREATE TABLE Departments (
    DeptID INT PRIMARY KEY,
    DeptName VARCHAR(100)
);

-- Create child table with a properly defined default constraint
CREATE TABLE Employees (
    EmpID INT PRIMARY KEY,
    EmpName VARCHAR(100),
    DeptID INT NOT NULL,
);
ALTER table Employees add CONSTRAINT DF_Employees_DeptID DEFAULT 2 FOR DeptID,  -- Define explicit DEFAULT constraint
    CONSTRAINT FK_Employees_Departments FOREIGN KEY (DeptID) 
        REFERENCES Departments(DeptID) ON DELETE SET DEFAULT

-- Insert sample data

INSERT INTO Departments VALUES (1, 'HR'), (2, 'IT');
INSERT INTO Employees VALUES (101, 'Alice', 1), (102, 'Bob', 1), (103, 'Charlie', 2);

-- Check data before deletion
SELECT * FROM Departments;
SELECT * FROM Employees;

-- Now, try deleting DeptID = 1 (should set Employees' DeptID to 99)
DELETE FROM Departments WHERE DeptID = 1;

-- Verify changes
SELECT * FROM Employees;





--ON DELETE SET DEFAULT
DROP TABLE IF EXISTS Employees;
DROP TABLE IF EXISTS Departments;

-- Create parent table
CREATE TABLE Departments (
    DeptID INT PRIMARY KEY,
    DeptName VARCHAR(100)
);
CREATE TABLE Employees (
    EmpID INT PRIMARY KEY,
    EmpName VARCHAR(100),
    DeptID INT NOT NULL,
    FOREIGN KEY (DeptID) REFERENCES Departments(DeptID) ON DELETE No ACTION
);
INSERT INTO Departments VALUES (1, 'HR'), (2, 'IT');
INSERT INTO Employees VALUES (101, 'Alice', 1);

DELETE FROM Departments WHERE DeptID = 1;