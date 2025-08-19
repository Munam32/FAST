--1
select *
from Movies
where Genre='Sci-Fi' and ReleaseYear >= '2010'
order by Rating ASC;

go

--2
select *
from Recipes
where CookingTime < 30;

go

--3
select Name,Position,Club,GoalsScored
from Football
where GoalsScored > 400 and GoalsScored < 700;

go

--4
select AVG(RunsScored) as AverageRuns
from Cricket
where Role='Batsman';

go

select Sum(WicketsTaken) as WicketsTaken
from Cricket
where Role='Bowler';

go

--5
select *
from SpaceMissions
where LaunchYear<1980 or DurationDays>1000;
go

--6
select *
from Workouts
where Category = 'Cardio' and CaloriesBurned < (select AVG(CaloriesBurned) from Workouts);
go

--7
select *
from Movies
where Genre!='Action' and Genre!='Thriller' and Rating>8.5 and ReleaseYear>2010;
go

--8
select *
from SpaceMissions
where (Agency!='NASA' AND LaunchYear>=1900 and DurationDays>1000) or (LaunchYear<1900 and DurationDays>1000)
go

--9
select *
from Recipes
where CookingTime < 30 and Ingredients like '%Eggs%'
order by CookingTime;

go


--10
select *
from Workouts
where Category='Cardio' or Category='Strength' and CaloriesBurned < (select AVG(CaloriesBurned) from Workouts) and CaloriesBurned>250;
go

--11
select Title,Poet,Theme
from Poetry
where Theme = 'Love' or Theme = 'Imagination' and (Era = 'Romantic' or Era='Mystical');
go

--12
select MissionName,LaunchYear,DurationDays, (DurationDays/365) as Years, (DurationDays % 365) as Days
from SpaceMissions;
go

--13
select *
from Workouts
where CaloriesBurned >=  0.3 * (select AVG(CaloriesBurned) from Workouts) ;

