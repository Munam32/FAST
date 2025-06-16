--Auto increment 

drop TABLE Persons
drop TABLE PersonA
CREATE TABLE Persons (
    Personid int IDENTITY(1,1) PRIMARY KEY,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int
);
INSERT INTO Persons (FirstName,LastName)
VALUES ('Lars','Monsen'),('Aleena','Ahmad'),('Taha','Ahmad');

select * from Persons

delete from Persons where Personid = 2

--Set Operations


select firstName from Persons Union select firstName from Persons ;


CREATE TABLE PersonA (
    Personid int IDENTITY(1,1) PRIMARY KEY,
    LastName varchar(255) NOT NULL,
    FirstName varchar(255),
    Age int
);

INSERT INTO PersonA (FirstName,LastName)
VALUES ('Lars','Monsen'),('Ali','Ahmad'),('Taha','Ahmad');

select firstName from Persons EXCEPT select firstName from PersonA ;
select * from Persons
select * from PersonA




--views
drop table Customers
CREATE TABLE Customers (
    CustomerID INT PRIMARY KEY,  -- Unique identifier for each customer
    cName VARCHAR(100) NOT NULL,  -- Name of the customer (cannot be null)
    Age INT,                     -- Age of the customer
    City VARCHAR(50),            -- City of the customer
    Email VARCHAR(100),          -- Email address of the customer
    Phone VARCHAR(15)            -- Phone number of the customer
);
INSERT INTO Customers (CustomerID, cName, Age, City, Email, Phone)
VALUES 
(1, 'Ali Ahmed', 28, 'Karachi', 'ali.ahmed@example.com', '0321-1234567'),
(2, 'Ayesha Khan', 32, 'Lahore', 'ayesha.khan@example.com', '0345-9876543'),
(3, 'Sadia Malik', 25, 'Islamabad', 'sadia.malik@example.com', '0301-5678901'),
(4, 'Hassan Ali', 40, 'Peshawar', 'hassan.ali@example.com', '0333-1122334'),
(5, 'Fatima Zahra', 22, 'Multan', 'fatima.zahra@example.com', '0312-4455667');

CREATE VIEW CustomerView AS SELECT CustomerID, cName, Age, City 
FROM Customers;

select * from CustomerView;

ALTER VIEW CustomerView AS 
SELECT CustomerID, cName, Age, City, Email 
FROM Customers;