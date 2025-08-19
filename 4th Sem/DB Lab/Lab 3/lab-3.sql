create database lab3;
GO
use lab3;

/***********************
  1. Movies Table
***********************/
CREATE TABLE Movies (
    MovieID INT PRIMARY KEY,
    Title VARCHAR(100),
    Genre VARCHAR(50),
    ReleaseYear INT,
    Rating DECIMAL(3,1),
    RuntimeMinutes INT  -- Included from some variants
);

-- Data from initial DDL and Fun SQL Land (dummy runtime values added for fun records)
INSERT INTO Movies VALUES
(1, 'Inception', 'Sci-Fi', 2010, 8.8, 148),
(2, 'Interstellar', 'Sci-Fi', 2014, 8.6, 169),
(3, 'The Dark Knight', 'Action', 2008, 9.0, 152),
(4, 'Parasite', 'Thriller', 2019, 8.6, 132),
(5, 'Soul', 'Animation', 2020, 8.1, 100),
(6, 'Happy Adventures', 'Comedy', 2018, 8.2, 120),
(7, 'Galaxy Quest', 'Sci-Fi', 2020, 8.5, 130),
(8, 'The Magic Chef', 'Family', 2019, 7.9, 110),
(9, 'Futbol Frenzy', 'Sports', 2021, 8.0, 140),
(10, 'The Poetic Journey', 'Drama', 2017, 7.5, 115);

/***********************
  2. Football Table
***********************/
CREATE TABLE Football (
    PlayerID INT PRIMARY KEY,
    Name VARCHAR(100),
    Position VARCHAR(50),
    GoalsScored INT,
    Club VARCHAR(50),
    Country VARCHAR(50)
);

-- Data from initial DDL and Fun SQL Land (IDs 1–5 from one source; 6–10 from playful data)
INSERT INTO Football VALUES
(1, 'Lionel Messi', 'Forward', 700, 'Inter Miami', 'Argentina'),
(2, 'Cristiano Ronaldo', 'Forward', 750, 'Al-Nassr', 'Portugal'),
(3, 'Neymar Jr', 'Forward', 400, 'Al-Hilal', 'Brazil'),
(4, 'Kylian Mbappe', 'Forward', 300, 'PSG', 'France'),
(5, 'Kevin De Bruyne', 'Midfielder', 100, 'Man City', 'Belgium'),
(6, 'Goalie Giggles', 'Forward', 120, 'Smiley FC', 'Funland'),
(7, 'Dribble Dazzle', 'Forward', 95, 'Sunshine United', 'Funland'),
(8, 'Striker Spark', 'Forward', 130, 'Happy Kickers', 'Funland'),
(9, 'Midfield Marvel', 'Midfielder', 80, 'Joyful FC', 'Funland'),
(10, 'Defender Dynamo', 'Defender', 20, 'Cheerful Club', 'Funland');

/***********************
  3. Cricket Table
***********************/
CREATE TABLE Cricket (
    PlayerID INT PRIMARY KEY,
    Name VARCHAR(100),
    Role VARCHAR(50),
    RunsScored INT,
    WicketsTaken INT,
    Country VARCHAR(50)
);

-- Data from initial DDL and Fun SQL Land
INSERT INTO Cricket VALUES
(1, 'Virat Kohli', 'Batsman', 12000, 0, 'India'),
(2, 'Shahid Afridi', 'All-Rounder', 8000, 350, 'Pakistan'),
(3, 'Muttiah Muralitharan', 'Bowler', 1300, 800, 'Sri Lanka'),
(4, 'AB de Villiers', 'Batsman', 10000, 0, 'South Africa'),
(5, 'Pat Cummins', 'Bowler', 500, 300, 'Australia'),
(6, 'Batsman Bliss', 'Batsman', 5000, 0, 'Funland'),
(7, 'Spinner Smile', 'Bowler', 3000, 150, 'Funland'),
(8, 'All-Rounder Amigo', 'All-Rounder', 4000, 100, 'Funland'),
(9, 'Fast Bowler Fun', 'Bowler', 2000, 120, 'Funland'),
(10, 'Wicket Wizard', 'Bowler', 2500, 200, 'Funland');

/***********************
  4. SpaceMissions Table
***********************/
CREATE TABLE SpaceMissions (
    MissionID INT PRIMARY KEY,
    MissionName VARCHAR(100),
    LaunchYear INT,
    Agency VARCHAR(50),
    DurationDays INT
);

-- Data from initial DDL and Fun SQL Land
INSERT INTO SpaceMissions VALUES
(1, 'Apollo 11', 1969, 'NASA', 8),
(2, 'Mars Rover', 2003, 'ESA', 1500),
(3, 'Voyager 1', 1977, 'NASA', 17000),
(4, 'Chandrayaan 3', 2023, 'ISRO', 15),
(5, 'Hubble Telescope', 1990, 'NASA', 12000),
(6, 'Star Chaser', 2015, 'FunAgency', 300),
(7, 'Moonlight Express', 2018, 'FunAgency', 150),
(8, 'Cosmic Cruiser', 2020, 'FunAgency', 500),
(9, 'Orbit Odyssey', 2017, 'FunAgency', 400),
(10, 'Galaxy Gallop', 2019, 'FunAgency', 350);

/***********************
  5. Recipes Table
***********************/
-- Combined definition from different versions: includes both ingredients and cost.
CREATE TABLE Recipes (
    RecipeID INT PRIMARY KEY,
    Name VARCHAR(100),
    Cuisine VARCHAR(50),
    Ingredients TEXT,       -- May be NULL if not provided
    CookingTime INT,        -- In minutes (CookingTime or CookingTimeMinutes)
    Cost DECIMAL(5,2)       -- May be NULL if not provided
);

-- Data from initial DDL (first set, without cost)
INSERT INTO Recipes VALUES
(1, 'Doraemon Dora Cake', 'Japanese', 'Flour, Sugar, Eggs, Red Bean Paste', 30, NULL),
(2, 'Pasta Carbonara', 'Italian', 'Pasta, Eggs, Parmesan Cheese, Bacon', 25, NULL),
(3, 'Biryani', 'Indian', 'Rice, Chicken, Spices', 60, NULL),
(4, 'Shakshuka', 'Middle Eastern', 'Eggs, Tomatoes, Peppers, Spices', 20, NULL),
(5, 'Tacos', 'Mexican', 'Tortilla, Beef, Cheese, Vegetables', 15, NULL),
-- Data from Fun SQL Land (using cost, ingredients not provided)
(6, 'Dora Cake Delight', 'Japanese', NULL, 30, 4.50),
(7, 'Pasta Party', 'Italian', NULL, 20, 3.00),
(8, 'Spicy Curry Fun', 'Indian', NULL, 40, 5.00),
(9, 'Taco Fiesta', 'Mexican', NULL, 15, 2.50),
(10, 'Burger Bonanza', 'American', NULL, 25, 4.00);

/***********************
  6. Workouts Table
***********************/
-- Combined definition (using Duration for minutes)
CREATE TABLE Workouts (
    WorkoutID INT PRIMARY KEY,
    Name VARCHAR(100),
    Category VARCHAR(50),
    Duration INT,       -- In minutes
    CaloriesBurned INT
);

-- Data from initial DDL
INSERT INTO Workouts VALUES
(1, 'Running', 'Cardio', 30, 300),
(2, 'Cycling', 'Cardio', 45, 400),
(3, 'Weightlifting', 'Strength', 60, 250),
(4, 'Yoga', 'Flexibility', 40, 200),
(5, 'HIIT', 'Cardio', 20, 350),
-- Data from Fun SQL Land
(6, 'Jumping Jacks', 'Cardio', 10, 100),
(7, 'Dancing Dash', 'Cardio', 20, 180),
(8, 'Flexibility Frolic', 'Flexibility', 15, 90),
(9, 'Strength Swing', 'Strength', 30, 250),
(10, 'Yoga Yonder', 'Flexibility', 25, 150);

/***********************
  7. Poetry Table
***********************/
CREATE TABLE Poetry (
    PoemID INT PRIMARY KEY,
    Title VARCHAR(100),
    Poet VARCHAR(100),
    Era VARCHAR(50),
    Theme VARCHAR(50)
);

-- Data from initial DDL
INSERT INTO Poetry VALUES
(1, 'The Road Not Taken', 'Robert Frost', 'Modern', 'Choices'),
(2, 'Ode to the Nightingale', 'John Keats', 'Romantic', 'Mortality'),
(3, 'Shikwa', 'Allama Iqbal', 'Classical', 'Complaint'),
(4, 'Kubla Khan', 'Samuel Taylor Coleridge', 'Romantic', 'Imagination'),
(5, 'Rumi Ghazal', 'Rumi', 'Mystical', 'Love'),
-- Data from Mathematical Verses
(6, 'Ode to Mathematics', 'Emily Dickinson', 'Modern', 'Logic'),
(7, 'The Calculus of Love', 'William Wordsworth', 'Romantic', 'Love'),
(8, 'Geometry of the Heart', 'Robert Frost', 'Modern', 'Nature'),
(9, 'Verses on Infinity', 'Walt Whitman', 'Modern', 'Imagination'),
(10, 'The Algebraic Muse', 'John Keats', 'Romantic', 'Passion'),
-- Data from Fun SQL Land
(11, 'Ode to Laughter', 'Joyful Jim', NULL, 'Happiness'),
(12, 'Rhymes of the Stars', 'Cosmic Claire', NULL, 'Inspiration'),
(13, 'Whispers of Wind', 'Breezy Ben', NULL, 'Nature'),
(14, 'Melody of the Heart', 'Loving Lily', NULL, 'Love'),
(15, 'Verses in the Rain', 'Rainy Ray', NULL, 'Melancholy');

/***********************
  8. PhysicsExperiments Table
***********************/
CREATE TABLE PhysicsExperiments (
    ExperimentID INT PRIMARY KEY,
    Title VARCHAR(100),
    Field VARCHAR(50),
    YearConducted INT,
    ImpactScore DECIMAL(4,1)
);

-- Data from Classic SQL Problems
INSERT INTO PhysicsExperiments VALUES
(1, 'Double-Slit Experiment', 'Quantum Mechanics', 1801, 9.5),
(2, 'Cavendish Experiment', 'Gravitation', 1797, 8.2),
(3, 'Higgs Boson Discovery', 'Particle Physics', 2012, 9.8),
(4, 'Superconductivity Test', 'Condensed Matter', 1987, 8.7),
(5, 'Quantum Entanglement Study', 'Quantum Mechanics', 2020, 9.1),
-- Data from Fun SQL Land
(6, 'Gravity Groove', 'Mechanics', 2010, 8.0),
(7, 'Quantum Quirk', 'Quantum Mechanics', 2015, 9.0),
(8, 'Relativity Rhythm', 'Relativity', 2012, 8.5),
(9, 'Electro Beat', 'Electromagnetism', 2018, 7.5),
(10, 'Thermo Twist', 'Thermodynamics', 2016, 8.2);

/***********************
  9. Mathematics Table
***********************/
CREATE TABLE Mathematics (
    ProblemID INT PRIMARY KEY,
    Title VARCHAR(100),
    Category VARCHAR(50),         -- e.g., Algebra, Calculus, Geometry
    DifficultyLevel VARCHAR(20),   -- e.g., Easy, Medium, Hard, Insanely Hard
    Points INT CHECK (Points > 0),
    Description TEXT
);

INSERT INTO Mathematics VALUES
(1, 'Sum of Natural Numbers', 'Algebra', 'Easy', 5, 'Calculate the sum of the first n natural numbers.'),
(2, 'Pythagorean Theorem Proof', 'Geometry', 'Medium', 10, 'Prove the Pythagorean Theorem using geometric methods.'),
(3, 'Limits and Continuity', 'Calculus', 'Hard', 15, 'Analyze limits for continuous functions in various scenarios.'),
(4, 'Matrix Multiplication', 'Algebra', 'Medium', 8, 'Multiply two matrices and interpret the result.'),
(5, 'Integral of a Function', 'Calculus', 'Insanely Hard', 20, 'Evaluate the definite integral of a complex function.');
