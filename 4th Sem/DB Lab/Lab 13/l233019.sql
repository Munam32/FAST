-- PART 1 --
--1
BEGIN TRANSACTION
	BEGIN TRY
	INSERT INTO Emission_Record(record_id,site_id,supplier_id,scope_id,source_id,record_date,quantity_used,emission_factor) VALUES 
	(101,1,1,3,4,'2025-02-13',666,444),
	(102,2,3,4,2,'2025-02-12',666,448)
	COMMIT 

END TRY
BEGIN CATCH
	 
	PRINT 'Error Encountered, Transaction rolled back'
	ROLLBACK
END CATCH

--2
BEGIN TRANSACTION
	BEGIN TRY
	UPDATE Emission_Record SET EmissionTotal = EmissionTotal + 50 WHERE SiteID = 101;
	UPDATE Emission_Record SET TotalEmissions = TotalEmissions + 50 WHERE SiteID = 101;
	COMMIT;
END TRY
BEGIN CATCH
	ROLLBACK;
	PRINT 'ERROR'
END CATCH


--3
BEGIN TRANSACTION
INSERT INTO Emission_Record(site_id,supplier_id,scope_id,source_id,record_date,quantity_used,emission_factor) VALUES
(1,1,3,4,'2025-02-13',666,444)
SAVE TRANSACTION S1;

INSERT INTO Emission_Record(site_id,supplier_id,scope_id,source_id,record_date,quantity_used,emission_factor) VALUES
(101,1,3,4,'2025-02-13',666,444)
ROLLBACK TRANSACTION S1;
COMMIT;

--4
BEGIN TRANSACTION
	BEGIN TRY
	INSERT INTO Emission_Record(site_id,supplier_id,scope_id,source_id,record_date,quantity_used,emission_factor) VALUES 
	(9,1,3,4,'2025-02-13',666,444)

	INSERT INTO Emission_Record(site_id,supplier_id,scope_id,source_id,record_date,quantity_used,emission_factor) VALUES 
	(101,1,3,4,'2025-02-13',666,444)

	COMMIT

END TRY
BEGIN CATCH
	PRINT 'Error Encountered, Transaction rolled back'
	ROLLBACK
END CATCH

--5

BEGIN TRANSACTION
	UPDATE Emission_Record SET quantity_used = 0 WHERE site_id=7

	select * from Emission_Record

	ROLLBACK

	select * from Emission_Record



--6

BEGIN TRANSACTION
	UPDATE OrganizationCredits SET Credits = Credits-100 WHERE OrgID=1;
	UPDATE OrganizationCredits SET Credits = Credits+100 WHERE OrgID=2;
	
	IF (SELECT Credits FROM OrganzationCredits WHERE OrgID =1 ) < 0
		ROLLBACK
	ELSE
		COMMIT;

--7
BEGIN TRANSACTION

INSERT INTO Site(site_name,organization_id,location) VALUES
('NEW SITE',3,'EAST ZONE')

INSERT INTO SiteManagers(ManagerID,Name) VALUES
(201,'Kashif Zafar')
COMMIT;


--8
BEGIN TRANSACTION
INSERT INTO Emission_Record(site_id,supplier_id,scope_id,source_id,record_date,quantity_used,emission_factor) VALUES
(8,1,3,4,'2025-02-13',666,444)
SAVE TRANSACTION S1;

INSERT INTO Emission_Record(site_id,supplier_id,scope_id,source_id,record_date,quantity_used,emission_factor) VALUES
(7,1,3,4,'2025-02-13',666,444)
SAVE TRANSACTION S2;

BEGIN TRY
	INSERT INTO Emission_Record(site_id,supplier_id,scope_id,source_id,record_date,quantity_used,emission_factor) VALUES
	(204,1,3,4,'2025-02-13',666,444)
END TRY
BEGIN CATCH
	PRINT '3RD Insert Statement failed'
	ROLLBACK TRANSACTION S2;
END CATCH
COMMIT;



--9 -- THERE IS ONLY 1 TRANSACTION WHICH IS THE OUTER MOST AND IT CONTROLS ALL THE ACTIONS IN SUB TRANSACTIONS
BEGIN TRANSACTION
	UPDATE Emission_Record SET supplier_id = 0 WHERE site_id = 7
	BEGIN TRANSACTION
		UPDATE Site SET site_name = 'SUPER KUTTA' WHERE location = 'New York'
	COMMIT
ROLLBACK


--10
CREATE PROCEDURE ProcessCarbonData
	@SiteID INT , @City VARCHAR(255)
AS
BEGIN
	BEGIN TRY
		BEGIN TRANSACTION
		UPDATE Site SET site_name = 'SUPER KUTTA' WHERE location = @City
		INSERT INTO Emission_Record(site_id,supplier_id,scope_id,source_id,record_date,quantity_used,emission_factor) VALUES
		(@SiteID,1,3,4,'2025-02-13',666,444)
		COMMIT;


	END TRY
	BEGIN CATCH
		ROLLBACK
		PRINT 'Error in ProcessCarbonData'+ ERROR_MESSAGE()
	END CATCH;
END;

EXEC ProcessCarbonData 7,'New York';