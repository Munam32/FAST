----1


--CREATE TABLE Characters_Log(
--character_id int,
--name varchar(500),
--faction varchar(50),
--titan_form varchar(50),
--cursed_technique varchar(100),
--rank varchar (50),
--created_at date
--);


--CREATE TRIGGER trg_AfterInsert_CharLog
--ON Characters 
--AFTER INSERT
--AS
--BEGIN
--		INSERT INTO Characters_Log(character_id,name,faction,titan_form,cursed_technique,rank,created_at)
--		SELECT character_id,name,faction,titan_form,cursed_technique,rank,created_at 
--		FROM inserted
--		WHERE faction = 'Jujutsu Sorcerer' or faction = 'Titan-shifter';

--END;


------2

--CREATE TABLE Rank_Log(
--character_id int,
--name varchar(500),
--faction varchar(50),
--titan_form varchar(50),
--cursed_technique varchar(100),
--rank varchar (50),
--created_at date
--);


--CREATE TRIGGER trg_AfterInsert_RankLog
--ON Characters 
--AFTER UPDATE
--AS
--BEGIN	IF UPDATE(rank)
--		begin
--		INSERT INTO Rank_Log(character_id,name,faction,titan_form,cursed_technique,rank,created_at)
--		SELECT character_id,name,faction,titan_form,cursed_technique,rank,created_at 
--		FROM inserted
--		end
--END;


----3

--CREATE TRIGGER trg_AfterDelete
--ON Characters 
--AFTER delete
--AS
--BEGIN	
--	IF NOT EXISTS (SELECT TOP 1 FROM Characters where name='Gojo Satoru')
--	BEGIN
--	PRINT 'DELTION PREVENTED'
--	ROLLBACK
--	END

--END;

----4
--CREATE TRIGGER trg_PreventInsert
--ON Characters
--INSTEAD OF INSERT
--AS
--BEGIN
--	IF EXISTS( SELECT * FROM Characters C join Character_Techniques CT on C.character_id = CT.character_id where C.faction = 'Jujutsu Sorcerer' and CT.mastery_level<30)
--	BEGIN
--	PRINT 'CANNOT INSERT'
--	ROLLBACK
--	END
--END; 

----5
--CREATE TRIGGER trg_PreventInsert
--ON Character_Techniques
--AFTER UPDATE
--AS
--BEGIN
--	IF EXISTS( SELECT 1 FROM inserted i join deleted d on i.character_id = d.character_id where i.mastery_level < d.mastery_level)
--	BEGIN
--	PRINT 'CANNOT REDUCE'
--	ROLLBACK
--	END
--END;


----6
-- CREATE TRIGGER trg_PreventDrop
-- ON DATABASE
-- FOR DROP_TABLE
-- AS
-- BEGIN
--	PRINT 'ERROR: TABLE DELETION NOT ALLOWED'
--	ROLLBACK TRANSACTION
--END;

----7 

--CREATE TRIGGER trg_DDL_Audit
--ON DATABASE
--FOR CREATE_TABLE, ALTER_TABLE, DROP_TABLE, 
--    CREATE_PROCEDURE, ALTER_PROCEDURE, DROP_PROCEDURE,
--    CREATE_VIEW, ALTER_VIEW, DROP_VIEW
--AS
--BEGIN
--    SET NOCOUNT ON --> Suppresses row,column numbers affected

--    INSERT INTO DDL_AuditLog (EventType, ObjectName, ObjectType, UserName, CommandText)
--    SELECT
--        EVENTDATA().value('(/EVENT_INSTANCE/EventType)[1]', 'NVARCHAR(100)') AS EventType, --> Parsing to store data from XML format
--        EVENTDATA().value('(/EVENT_INSTANCE/ObjectName)[1]', 'NVARCHAR(255)') AS ObjectName,
--        EVENTDATA().value('(/EVENT_INSTANCE/ObjectType)[1]', 'NVARCHAR(100)') AS ObjectType,
--        SYSTEM_USER AS UserName,
--        EVENTDATA().value('(/EVENT_INSTANCE/TSQLCommand/CommandText)[1]', 'NVARCHAR(MAX)') AS CommandText;
--END;

----8

--CREATE TRIGGER trg_RestrictLogon
--ON ALL SERVER
--FOR LOGON
--AS
--BEGIN
--	IF DATEPART(HOUR,GETDATE()) NOT BETWEEN 9 AND 18
--	BEGIN
--		PRINT 'LOGON NOT ALLOWED BETWEEN 9am AND 6pm'
--		ROLLBACK
--	END
--END;

----9
--CREATE TRIGGER trg_TrackStrongestWarrior
--ON Character_Techniques
--AFTER INSERT
--AS
--BEGIN
	
--	INSERT INTO Battle_Strongest_Hybrid (character_id,technique_id,mastery_level,last_updated)
--	SELECT 1 character_id,technique_id,mastery_level,last_updated
--	FROM inserted ORDER BY mastery_level DESC

--END;

