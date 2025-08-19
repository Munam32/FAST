create database farewell;
go
use farewell;
go

-- 1. Create Students table
CREATE TABLE Students (
    student_id INT PRIMARY KEY,
    roll_number VARCHAR(10) UNIQUE NOT NULL,
    name VARCHAR(50),
    good_trait VARCHAR(100),
    remark VARCHAR(255),
    average_grade FLOAT DEFAULT 0
);
go
-- 2. Create Assignments table
CREATE TABLE Assignments (
    assignment_id INT PRIMARY KEY IDENTITY(1,1),
    student_id INT,
    assignment_name VARCHAR(100),
    score INT,
    FOREIGN KEY (student_id) REFERENCES Students(student_id)
);
go
-- 3. Create Memories table for farewell messages
CREATE TABLE Memories (
    memory_id INT PRIMARY KEY IDENTITY(1,1),
    student_id INT,
    memory_text VARCHAR(500),
    created_at DATETIME DEFAULT GETDATE(),
    FOREIGN KEY (student_id) REFERENCES Students(student_id)
);
go
-- 4. Create trigger to update average_grade in Students table after new assignment insertion
CREATE TRIGGER trg_UpdateStudentAverageGrade
ON Assignments
AFTER INSERT
AS
BEGIN
    DECLARE @student_id INT,
            @total_score INT,
            @num_assignments INT,
            @new_avg FLOAT;

    -- Get the student_id from the newly inserted row
    SELECT @student_id = student_id FROM inserted;

    -- Calculate total score and number of assignments for the student
    SELECT @total_score = SUM(score), @num_assignments = COUNT(*)
    FROM Assignments
    WHERE student_id = @student_id;

    -- Calculate new average grade
    SET @new_avg = CAST(@total_score AS FLOAT) / @num_assignments;

    -- Update the Students table with the new average grade
    UPDATE Students
    SET average_grade = @new_avg
    WHERE student_id = @student_id;
END;
go

INSERT INTO Students (student_id, roll_number, name, good_trait, remark)
VALUES
(1, '23I-0687', 'Qasim Shakil', 'Reliable', 'Consistently dependable in group work'),
(2, '23L-0557', 'Muhammad Razi', 'Analytical', 'Excels at breaking down complex problems'),
(3, '23L-0583', 'Haris Fayyaz', 'Enthusiastic', 'Brings energy and positivity to class'),
(4, '23L-0587', 'Rayan Irfan', 'Innovative', 'Always suggests solutions and asks questions'),
(5, '23L-0597', 'Mania Shakeel', 'Organized', 'Communicates on time and follows proactive approach'),
(6, '23L-0599', 'Muhammad Zahid', 'Hardworking', 'Never shies away from extra effort'),
(7, '23L-0650', 'Mohib Mansoor', 'Respectful', 'Well mannered and eager for learning'),
(8, '23L-0652', 'Aaleen Fatima', 'Attentive', 'Pays close attention to details and gets correct answers'),
(9, '23L-0654', 'Sabih Ud Din', 'Resourceful', 'Finds solutions even in tough situations'),
(10, '23L-0681', 'Rizwan Arshad', 'Lively', 'Keeps friends motivated and supports good environment'),
(11, '23L-0683', 'Rameel Naveed', 'Collaborative', 'Works well in team projects & always smiling!'),
(12, '23L-0703', 'Asra Bukhari', 'Hard Working', 'Maintains determination even when results are not immediate'),
(13, '23L-0717', 'Haziq Zargham', 'Adaptable', 'Handles changes smoothly & never complains'),
(14, '23L-0720', 'Abdul Rehman', 'Focused', 'Stays on task even during distractions'),
(15, '23L-0730', 'Abdullah', 'Motivated', 'Shows strong drive to succeed'),
(16, '23L-0747', 'Aiman Ashraf', 'Thoughtful', 'Manages difficult tasks with composure and skill'),
(17, '23L-0752', 'Fatima Mazhar', 'Disciplined', 'Maintains a consistent study routine'),
(18, '23L-0778', 'Subaina Munib', 'Optimistic', 'Spreads positivity among peers & asks for deadline extensions.'),
(19, '23L-0802', 'Ali Asad', 'Logical', 'Well mannered, knows Urdu and Approaches problems methodically'),
(20, '23L-0808', 'Hannan Asad', 'Ambitious', 'Sets high goals for personal growth'),
(21, '23L-0809', 'Mariyam Akram', 'Empathetic', 'Understands and supports classmates'),
(22, '23L-0811', 'Abdullah Iqbal', 'Persistent', 'Never gives up on difficult tasks & always on the spot and is always present and punctual.'),
(23, '23L-0824', 'Ahmad Mubeen', 'Observant', 'Notices important details others miss'),
(24, '23L-0844', 'Ahmad Muaz', 'Versatile', 'Intelligent & Excels in multiple subjects'),
(25, '23L-0856', 'Ali Shahid', 'Respectful', 'Treats everyone with kindness & stays humble'),
(26, '23L-0865', 'Khusham Ali', 'Learner', 'Attempts to understand the new concepts rapidly'),
(27, '23L-0872', 'Bilal Ahmad', 'Calm', 'Remains composed under pressure'),
(28, '23L-0912', 'Khadija Asim', 'Proactive', 'Works before deadlines approach'),
(29, '23L-0932', 'Areeb Zahra', 'Intelligent', 'Willing to consider new ideas'),
(30, '23L-0941', 'Shizza Razzaq', 'Communicative', 'Expresses thoughts clearly'),
(31, '23L-0942', 'Zainab Khalil', 'Responsible', 'Can always be counted on, completes assigned tasks'),
(32, '23L-0985', 'Shaiq Raza', 'Cheerful', 'Encourages a climate of mutual support and goodwill'),
(33, '23L-1014', 'Junaid Muhammad', 'Honest', 'Always truthful and trustworthy'),
(34, '23L-1015', 'Harmain Waleed', 'Sharp-minded', 'Knows how to get deadlines extended'),
(35, '23L-2501', 'Adeena Riaz', 'Disciplined', 'Well mannered, detailed oriented & Catches errors effectively improving quality'),
(36, '23L-2552', 'Ubaid Ullah', 'Flexible', 'Handles unexpected challenges well'),
(37, '23L-3019', 'Abdul Munam', 'Diligent', 'Handles situations with smily face and is Goal-Oriented; Works steadily towards objectives'),
(38, '24L-8017', 'Ali Ahmad', 'Engaged', 'We wish he had continued the course since he was fully involved and added a lot of value');
GO

INSERT INTO Memories (student_id, memory_text)
VALUES
(4, 'suggested themes for lab manual, Was interactive throughout the semester, was excited for labs'),
(22, 'Was focused on learning throughout the semester'),
(27, 'Worked on Dr Patient Appointment project'),
(9, 'Did a great project for sharing notes and items on campus even added email triggers'),
(8, 'performed really well on assessments, stayed focused'),
(37, 'Always smiling!.'),
(34, 'Received a deadline extension after providing anonymous feedback near the instructor’s office.');
