DROP TABLE IF EXISTS Employees;
DROP TABLE IF EXISTS Departments;
CREATE TABLE Departments (
    DeptID INT PRIMARY KEY,
    DeptName VARCHAR(100), 
    DeptLocation VARCHAR(100)
);
CREATE TABLE Employees (
    EmpID INT PRIMARY KEY,
    EmpName VARCHAR(100),
    Salary INT,
    DeptID INT NOT NULL,
    FOREIGN KEY (DeptID) REFERENCES Departments(DeptID) ON DELETE No ACTION
);

INSERT INTO Departments (DeptID, DeptName, DeptLocation) VALUES
(1, 'HR', 'New York'),
(2, 'Finance', 'Chicago'),
(3, 'IT', 'San Francisco'),
(4, 'Marketing', 'Los Angeles'),
(5, 'Sales', 'Houston');

INSERT INTO Departments (DeptID, DeptName, DeptLocation) VALUES
(6, 'Admin', 'New York');
INSERT INTO Employees (EmpID, EmpName, Salary, DeptID) VALUES
(101, 'Alice Johnson', 70000, 1),
(102, 'Bob Smith', 85000, 2),
(103, 'Charlie Davis', 95000, 3),
(104, 'David Wilson', 62000, 4),
(105, 'Emma Brown', 58000, 5),
(106, 'Frank Thomas', 72000, 3),
(107, 'Grace White', 77000, 2),
(108, 'Henry Green', 68000, 1),
(109, 'Ivy Hall', 89000, 4),
(110, 'Jack Lewis', 76000, 5);

INSERT INTO Employees (EmpID, EmpName, Salary, DeptID) VALUES
(111, 'Alice Smith', 70000, 1),
(112, 'Bob Davis', 85000, 2),
(113, 'Charlie Wilson', 96000, 3),
(114, 'David Wilson', 62000, 4),
(115, 'Emma Brown', 58000, 5),
(116, 'Frank Thomas', 72000, 3),
(117, 'Grace White', 77000, 2),
(118, 'Henry Green', 69000, 1),
(119, 'Ivy Hall', 89000, 4),
(120, 'Jack Lewis', 77000, 5);

Select * from Employees;
Select * from Departments;

-- Scalar value
SELECT EmpName, 
       (SELECT COUNT(*) FROM employees) AS total_employees 
FROM employees 
WHERE EmpID = 105;

SELECT EmpName, DeptID 
FROM employees 
WHERE (salary,DeptID ) In 
      (SELECT MAX(salary), DeptID  FROM employees group by DeptID ;

-- multi-row
SELECT EmpName, salary 
FROM employees 
WHERE salary < ALL (SELECT MAX(salary)  FROM employees WHERE DeptID = 5);

SELECT EmpName, salary 
FROM employees 
WHERE salary > ANY (SELECT salary  FROM employees WHERE DeptID = 5);


-- Salary Queries
SELECT EmpName , salary 
FROM employees 
WHERE (salary) = 
      (SELECT MAX(salary) FROM employees);

SELECT EmpName 
FROM employees WHERE (salary) = (SELECT MAX(salary) FROM employees
WHERE (salary) <> 
      (SELECT MAX(salary) FROM employees));
SELECT EmpName, salary, DeptID from employees ORDER by Salary desc;

SELECT EmpName, salary, DeptID from employees e1 
where 3 = ( Select count (Distinct Salary) from Employees e2
 where e2.salary > e1.Salary)

-- Corelated Queries

SELECT EmpName, salary, DeptID from employees e1
WHERE salary = (SELECT MAX(salary)  FROM employees e2 WHERE e1.DeptID = e2.DeptID);

SELECT DeptID,avg(salary)  FROM employees group by DeptID;

SELECT EmpName, salary, DeptID from employees e1
WHERE salary > (SELECT avg(salary)  FROM employees e2 WHERE e1.DeptID = e2.DeptID);

SELECT DeptID, DeptName 
FROM Departments d
WHERE EXISTS (SELECT * FROM Employees e WHERE e.DeptID = d.DeptID);
SELECT DeptID, DeptName 
FROM Departments d
WHERE NOT EXISTS (SELECT * FROM Employees e WHERE e.DeptID = d.DeptID);




-- from clause
SELECT DeptID, avg_salary 
FROM (SELECT DeptID, AVG(salary) AS avg_salary FROM employees 
GROUP BY DeptID) AS dept_avg 
WHERE avg_salary > 50000;

-- order by clause
SELECT EmpName, salary , DeptID
FROM employees e1
ORDER BY (SELECT max(salary) FROM employees e2
WHERE e2.DeptID = e1.DeptID) DESC;
-- having clause
SELECT DeptID, AVG(salary) AS avg_salary 
FROM employees 
GROUP BY DeptID
HAVING AVG(salary) > (SELECT AVG(salary) 
FROM employees WHERE DeptID = 1);
-- group by clause (not allowed)
SELECT DeptID, COUNT(*) 
FROM employees e1
GROUP BY (SELECT DeptID FROM departments );

