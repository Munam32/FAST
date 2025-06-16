--1
CREATE VIEW Q1 AS
select *
from Dungeons
where DungeonID = (select DungeonID from Hunter_Missions where HunterID=1);



--2
Create view Q2_lab5 As
select B.BeyonderID,B.Name,B.Path,B.PotionConsumption,B.Status,O.Name as NN
from Beyonders B
join Organizations O on B.OrganizationID = O.OrganizationID
where B.Status = 'At Risk' or B.status= 'Lost Control';




--3
Create View Monitoring_View as
select M.MissionID, M.Title,M.Type,M.DifficultyLevel,M.Status,O.Name
from Missions M
join Hunter_Missions HM on HM.MissionID = M.MissionID
join Hunters H on HM.HunterID = H.HunterID
join Organizations O on H.OrganizationID = O.OrganizationID
where M.Status='Ongoing' or M.Status='Pending'; 



--4
--expendable


--5
Create View Q3 as
select H.HunterID,H.Name,H.Guild,H.PowerLevel,O.Name as NN
from Hunters H
join Organizations O on H.OrganizationID = O.OrganizationID
where H.Rank='S';



--6
Create Procedure Q6
@HunterID int, @dungeonID int

as
begin
	if not exists(select* from Hunter_Missions HM where HM.HunterID = @HunterID)
	begin
	
	insert into Hunter_Missions values(@HunterID,@dungeonID,'Assigned')

	end


end;
exec Q6 4,6;



--7
create procedure Q7
as
begin
	
	update Dungeons
	set Status='Cleared'
	where Dungeons.DungeonID = (select DungeonID from Hunter_Missions HM where HM.MissionStatus='Completed')
end;



--8
create procedure Automatic_logging
@MissionID int
as
begin
	IF NOT EXISTS(select MissionID from Artifacts where MissionID = @MissionID and SealedStatus!='Sealed')
	begin
		insert into Intelligence_Reports (MissionID,SubmittedBy,ReportContent,DateSubmitted)
		values (@MissionID,'Audrey Hall','Artifact sucessfuly retrieved and sealed',GETDATE())
	end

end;



--9
create procedure Promotion
@HunterID int
as
begin
	if exists(select HunterID from Hunters where @HunterID=HunterID)
	begin
		update Hunters
		set Rank = 'S'
		where PowerLevel>= 9000
		
		update Hunters
		set Rank = 'A'
		where PowerLevel>=7500

		update Hunters
		set Rank = 'B'
		where PowerLevel>=5000

		
	end

end;

exec Promotion 5; 

--10
create procedure Failed_Missions
as
begin
	update Intelligence_Reports
	set ReportContent = 'Forbidden Knowledge', DateSubmitted = GETDATE()
	where MissionID in (select A.MissionID from Artifacts A join Hunter_Missions H on A.MissionID = H.MissionID where H.MissionStatus='Failed' group by A.MissionID having count(*)>=2) --add aliases otherwise error 'H.MissionID' not 'MissionID'

	update Intelligence_Reports
	set ReportContent = 'Warning', DateSubmitted = GETDATE()
	where MissionID in (select A.MissionID from Artifacts A join Hunter_Missions H on A.MissionID = H.MissionID where H.MissionStatus='Failed' and A.RiskLevel='High' group by A.MissionID having Count(*)>=3) --'Use in rather than = as more than 1 val returned'

end;


