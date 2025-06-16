--Q1
select Driver.first_name,Driver.last_name,Driver.license_number, Car.model
from Driver_Car
inner join Driver on Driver_car.driver_id = Driver.driver_id
inner join Car on Driver_Car.driver_id = Car.car_id 
go


--Q2

select COUNT(Race_Participant.race_id) as Participants , Race.race_name
from Race
Left join Race_Participant on Race.race_id = Race_Participant.race_id group by Race.race_name;  
go

--Q3

select Driver.first_name,Driver.last_name
from Race_Result
Inner join Driver on Driver.driver_id = Race_Result.driver_id
inner join Race on Race.race_id = Race_Result.race_id 
where Race_Result.completion_time = (select MIN(Race_Result.completion_time) from Race_Result)
go


--Q4
select D.first_name as FirstName, D.last_name as LastName, SUM(Dr.reward_amount) AS TotalPrize
from Driver_Reward Dr
inner join Driver D ON Dr.driver_id = D.driver_id
group by D.first_name, D.last_name;
go


--Q5  ----aaye haye maza aagaya
select Car.Model as Model , Upgrade.upgrade_name as UpgradeName, Upgrade.upgrade_type as UpgradeType
from Car_Upgrade CU
inner join Car on Car.car_id = CU.car_id
inner join Upgrade on CU.upgrade_id = Upgrade.upgrade_id
go


--Q6
select Driver.first_name, Driver.last_name
from Driver
inner join Race_Participant on Driver.Driver_id = Race_Participant.driver_id 
group by Driver.first_name, Driver.last_name
having Count(Race_Participant.race_id) >= 2;
go

--Q7
select R.race_name as RaceName, AVG(RR.completion_time) as AverageCompletionTime
from Race_Result RR
inner join Race R on R.race_id = RR.race_id
group by R.race_name
go

--Q8
select D.first_name, D.last_name, D.license_number, C.model, C.price
from Driver_Car DC
inner join Car C on C.car_id = DC.car_id												--treat nested queries independant than outer queries
inner join  Driver D on D.driver_id = C.car_id
group by D.first_name, D.last_name, D.license_number, C.price, C.model
having C.price = (select MAX(Car.price) from Car);

--Q9
select D.first_name, D.last_name, SUM(DR.reward_amount) as TotalPrize, RANK() over (order by SUM(DR.reward_amount)) as Ranking
from Driver_Reward DR
inner join Driver D on DR.driver_id = D.driver_id
group by D.first_name, D.last_name
order by TotalPrize;		--order normally sorts by asc if not mentioned
go

--Q10
select d.first_name as FirstName, d.last_name as LastName
from Driver_Car DC
inner join Car C on DC.car_id = C.car_id
inner join Driver D on DC.driver_id = D.driver_id
group by D.driver_id, D.first_name, D.last_name
having COUNT(distinct C.brand) >= 2;
go

--Q11
select D.first_name as FirstName,  D.last_name as LastName, D.license_number as LisenceNum
from Driver D
inner join Race_Participant RP ON D.driver_id = RP.driver_id
group by D.driver_id, D.first_name, D.last_name, D.license_number
having COUNT(DISTINCT rp.race_id) = (select COUNT(*) from Race);
go

--Q12
select top 3 D.first_name as FirstName, D.last_name as LastName, AVG(RR.completion_time) as AvgTime
from Race_Result RR
inner join Driver D on RR.driver_id = d.driver_id
group by D.driver_id, D.first_name, D.last_name
order by AvgTime;
go

--Q13
select D.first_name as FirstName, D.last_name as LastName
from Driver d
join Driver_Car DC on D.driver_id = DC.driver_id
join Car_Upgrade CU on DC.car_id = CU.car_id
group by D.driver_id, D.first_name, D.last_name
having COUNT(distinct CU.upgrade_id) >= 2;


