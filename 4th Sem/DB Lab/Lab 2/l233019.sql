--create database myDB; --student,attendance,class vanue teacher
--use myDB;

--create Table Student(
--	RollNum char(7) NOT NULL,
--	Name varchar(100),
--	Gender varchar(100),
--	Phone varchar(100),

--);

--create Table Attendance(
--	RollNum char(7) NOT NULL,
--	Date DATE,
--	Status char(1),
--	ClassVenue int,

--);

--create Table Teacher(
--	id int NOT NULL, 
--	Name varchar(100),
--	Designation varchar(100),
--	Department varchar(100),

--);

--create Table ClassVenue(
--	id int NOT NULL,
--	Building varchar(100),
--	RoomNum int,
--	TeacherId int
--);

--Insert into Student
--values
--('L230844','Ahmed Muaz','Male','0333-3333333'),
--('L124147','Kalsoom','Female','0333-3456789'),
--('L230654','Sabih Ud Din','Male','0345-3243567')

--insert into Attendance
--values
--('L230844','02-22-2016','P',2),
--('L124147','02-23-2016','A',1),
--('L230844','03-04-2016','P',2)

--insert into Teacher
--values
--(1,'Dr,Zeeshan Ali Rana','Assistant Prof.','Software Engineering'),
--(2,'Mr. Zeeshan Nazar','Lecturer','Data Science'),
--(3,'Dr. Kashif Zafar','Professor','Computer Science')

--insert into ClassVenue
--values
--(1,'CS',2,1),
--(2,'Civil',7,2)






--alter table Student add constraint PK_Student primary key (RollNum);
--alter table Attendance add constraint PK_Attendance primary key (RollNum);
--alter table ClassVenue add constraint PK_ClassVenue primary key (id);
--alter table Teacher add constraint PK_Teacher primary key (Teacherid);


--alter table Attendance add constraint FK_Attendance foreign key (RollNum) references Student (RollNum)
--alter table Attendance add constraint FK_Attendance2 foreign key (ClassVenue) references ClassVenue (id)
--alter table ClassVenue add constraint FK_ClassVenue foreign key (TeacherId) references Teacher (id)
--alter table student 
--add Warning_Count int;

--insert into Student
--values
--('L162334','Fozan Shahid','Male',3.2) -- Not Valid // 3.2 is float and if it is written as integer the query will run sucessfully


--insert into ClassVenue
--values
--(3,'CS',5,'Ali') --Not Valid // Ali is a string not an integer

--update Teacher
--set Name = 'Dr. Kashif Zafar'
--where Name = 'Dr. Kashif zafar' --Valid

--delete from Student
--where RollNum = 'L164123'



--delete from Attendance
--where RollNum= 'L164124' and Status = 'A'

--delete from Student
--where RollNum = 'L162334' -- valid


--alter table Student
--add CNIC char(13);


--alter table Student
--drop column Phone;

--alter table Teacher add constraint unique_name UNIQUE(Name);
--alter table Student add constraint check_gender check ( Gender='Male' or Gender = 'Female');
--alter table Attendance add constraint check_status check ( Status='A' or Status = 'P');

select *
from Student

select *
from Attendance

select *
from ClassVenue

select *
from Teacher