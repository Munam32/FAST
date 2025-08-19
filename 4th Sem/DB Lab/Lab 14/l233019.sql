--Q1
select * from Students where roll_number='23L-3019'

--Q2
--> calculates new average grade of student based o newly added asignment entry in the assignments table


--Q3
create table Friends(
	Friend_ID int primary key identity(1,1),
	student_id int,
	friend_student_id int,

	foreign key (student_id) references Students(student_id),
	foreign key (friend_student_id) references Students(student_id)

);

--Q4
CREATE TRIGGER prevent_excess_friends
ON Friends
INSTEAD OF INSERT
AS
BEGIN
    DECLARE @friend_count INT, @student_id INT;

    -- Get the student_id from the new row
    SELECT @student_id = student_id FROM inserted;

    -- Count the number of friends for this student
    SELECT @friend_count = COUNT(*) 
    FROM Friends 
    WHERE student_id = @student_id;

    -- If the student already has 10 friends, prevent insertion
    IF @friend_count >= 10
    BEGIN
        RAISERROR ('A student cannot have more than 10 friends.', 16, 1);
        RETURN;
    END
    
    -- If the limit isn't exceeded, allow the insertion
    ELSE
    BEGIN
        INSERT INTO Friends(student_id, friend_id)
        SELECT student_id, friend_id FROM inserted;
    END
END;


--Q5
CREATE TABLE Lab_Remarks(
	RemarkID int primary key identity (1,1),
	StudentID int,
	Remarks text,

	foreign key (StudentId) references Students(student_id)
);

--Q6
select *
from Students S 
join Friends F on (S.student_id = F.student_id) or (S.student_id = F.friend_student_id)
join Lab_Remarks LR on (LR.StudentID = F.friend_student_id) 

--Q7
select S.name,S.roll_number, count(F.friend_student_id) as FriendCount, S.average_grade, avg (SF.average_grade) as AverageFriendGrade
from Students S 
left join Friends F on (S.student_id = F.student_id) or (S.student_id = F.friend_student_id)
left join Students SF on SF.student_id = F.friend_student_id
group by S.name,S.roll_number,S.average_grade


--Q8
select *
from Memories M
join Students S on S.student_id = M.student_id
where S.roll_number = '23L-3019'

--Q9
select 'Goodbye Class! We Had Fun!!'