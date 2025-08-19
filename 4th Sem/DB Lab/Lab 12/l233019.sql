----Q1

----CREATE PROCEDURE PrintSitesPerOrganization
----AS
----BEGIN
----    DECLARE @org_id INT, @org_name VARCHAR(255), @site_count INT;
    
----    -- Declare cursor to iterate through organizations
----    DECLARE org_cursor CURSOR FOR
    
----	--checkpoint
----	SELECT organization_id, organization_name
----    FROM Organization;
    
----    OPEN org_cursor;
----    FETCH NEXT FROM org_cursor INTO @org_id, @org_name;
    
----    WHILE @@FETCH_STATUS = 0
----    BEGIN
----        -- Count sites for the current organization
----        SELECT @site_count = COUNT(*)
----        FROM Site
----        WHERE organization_id = @org_id;
        
----        -- Print the result
----        PRINT 'Organization: ' + @org_name + ', Total Sites: ' + CAST(@site_count AS VARCHAR);
        
----        FETCH NEXT FROM org_cursor INTO @org_id, @org_name;
----    END;
    
----    CLOSE org_cursor;
----    DEALLOCATE org_cursor;
----END;
----GO

------ Execute the procedure
----EXEC PrintSitesPerOrganization;

--CREATE PROCEDURE PrintSitesPerOrganization
--AS
--BEGIN
--    -- Create a temporary table to store organizations
--    DECLARE @OrgTable TABLE (
--        organization_id INT,
--        organization_name VARCHAR(255),
--        processed BIT DEFAULT 0
--    );
    
--    -- Insert organizations into the temporary table
--    INSERT INTO @OrgTable (organization_id, organization_name)
--    SELECT organization_id, organization_name
--    FROM Organization;
    
--    DECLARE @org_id INT, @org_name VARCHAR(255), @site_count INT;
    
--    -- Loop through organizations
--    WHILE EXISTS (SELECT 1 FROM @OrgTable WHERE processed = 0)
--    BEGIN
--        -- Get the first unprocessed organization
--        SELECT TOP 1 @org_id = organization_id, @org_name = organization_name
--        FROM @OrgTable
--        WHERE processed = 0;
        
--        -- Count sites for the current organization
--        SELECT @site_count = COUNT(*)
--        FROM Site
--        WHERE organization_id = @org_id;
        
--        -- Print the result
--        PRINT 'Organization: ' + @org_name + ', Total Sites: ' + CAST(@site_count AS VARCHAR);
        
--        -- Mark the organization as processed
--        UPDATE @OrgTable
--        SET processed = 1
--        WHERE organization_id = @org_id;
--    END;
--END;
--GO

---- Execute the procedure
--EXEC PrintSitesPerOrganizationtemp;



----Q2

----CREATE PROCEDURE ResetEmissionFactor
----    @source_id INT
----AS
----BEGIN
----    DECLARE @record_id INT, @default_factor DECIMAL(10, 4);
    
----    -- Get the default emission factor for the source
----    SELECT @default_factor = default_emission_factor
----    FROM Emission_Source
----    WHERE source_id = @source_id;
    
----    IF @default_factor IS NULL
----    BEGIN
----        PRINT 'Invalid source_id: ' + CAST(@source_id AS VARCHAR);
----        RETURN;
----    END;
    
----    -- Declare cursor for emission records with the given source_id
----    DECLARE record_cursor CURSOR FOR
----    SELECT record_id
----    FROM Emission_Record
----    WHERE source_id = @source_id;
    
----	--TO ITERATE THROUGH EACH ROW
----    OPEN record_cursor;
----    FETCH NEXT FROM record_cursor INTO @record_id;
    
----    WHILE @@FETCH_STATUS = 0
----    BEGIN
----        -- Update emission_factor to default_emission_factor
----        UPDATE Emission_Record
----        SET emission_factor = @default_factor
----        WHERE record_id = @record_id;
        
----        PRINT 'Updated record_id: ' + CAST(@record_id AS VARCHAR) + ' to emission_factor: ' + CAST(@default_factor AS VARCHAR);
        
----        FETCH NEXT FROM record_cursor INTO @record_id;
----    END;
    
----    CLOSE record_cursor;
----    DEALLOCATE record_cursor;
----END;
----GO


------ Example execution
----EXEC ResetEmissionFactor @source_id = 2;


--CREATE PROCEDURE ResetEmissionFactor
--    @source_id INT
--AS
--BEGIN
--    DECLARE @default_factor DECIMAL(10, 4);
    
--    -- Get the default emission factor for the source
--    SELECT @default_factor = default_emission_factor
--    FROM Emission_Source
--    WHERE source_id = @source_id;
    
--    IF @default_factor IS NULL
--    BEGIN
--        PRINT 'Invalid source_id: ' + CAST(@source_id AS VARCHAR);
--        RETURN;
--    END;
    
--    -- Create a temporary table to store records
--    DECLARE @RecordTable TABLE (
--        record_id INT,
--        processed BIT DEFAULT 0
--    );
    
--    -- Insert records with the given source_id
--    INSERT INTO @RecordTable (record_id)
--    SELECT record_id
--    FROM Emission_Record
--    WHERE source_id = @source_id;
    
--    DECLARE @record_id INT;
    
--    -- Loop through records
--    WHILE EXISTS (SELECT 1 FROM @RecordTable WHERE processed = 0)
--    BEGIN
--        -- Get the first unprocessed record
--        SELECT TOP 1 @record_id = record_id
--        FROM @RecordTable
--        WHERE processed = 0;
        
--        -- Update emission_factor to default_emission_factor
--        UPDATE Emission_Record
--        SET emission_factor = @default_factor
--        WHERE record_id = @record_id;
        
--        PRINT 'Updated record_id: ' + CAST(@record_id AS VARCHAR) + ' to emission_factor: ' + CAST(@default_factor AS VARCHAR);
        
--        -- Mark the record as processed
--        UPDATE @RecordTable
--        SET processed = 1
--        WHERE record_id = @record_id;
--    END;
--END;
--GO

---- Example execution
--EXEC ResetEmissionFactor @source_id = 2;



----Q3

----CREATE PROCEDURE PrintMonthlyEmissions
----AS
----BEGIN
----    DECLARE @current_date DATE = GETDATE();
----    DECLARE @start_date DATE = DATEADD(MONTH, -12, @current_date);
----    DECLARE @month_date DATE = @start_date;
----    DECLARE @site_id INT, @site_name VARCHAR(255), @total_emissions DECIMAL(12, 2);
    
----    -- Loop through each month
----    WHILE @month_date <= @current_date
----    BEGIN
----        PRINT 'Emissions for Month: ' + CONVERT(VARCHAR, @month_date, 120);
        
----        -- Declare cursor for sites
----        DECLARE site_cursor CURSOR FOR
----        SELECT site_id, site_name
----        FROM Site;
        
----        OPEN site_cursor;
----        FETCH NEXT FROM site_cursor INTO @site_id, @site_name;
        
----        WHILE @@FETCH_STATUS = 0
----        BEGIN
----            -- Calculate total emissions for the site in the current month
----            SELECT @total_emissions = SUM(calculated_emission)
----            FROM Emission_Record
----            WHERE site_id = @site_id
----            AND YEAR(record_date) = YEAR(@month_date)
----            AND MONTH(record_date) = MONTH(@month_date);
            
----            -- Print if emissions exist
----            IF @total_emissions IS NOT NULL
----                PRINT 'Site: ' + @site_name + ', Total Emissions: ' + CAST(@total_emissions AS VARCHAR);
----            ELSE
----                PRINT 'Site: ' + @site_name + ', Total Emissions: 0';
                
----            FETCH NEXT FROM site_cursor INTO @site_id, @site_name;
----        END;
        
----        CLOSE site_cursor;
----        DEALLOCATE site_cursor;
        
----        -- Move to next month
----        SET @month_date = DATEADD(MONTH, 1, @month_date);
----    END;
----END;
----GO

------ Execute the procedure
----EXEC PrintMonthlyEmissions;

--CREATE PROCEDURE PrintMonthlyEmissions
--AS
--BEGIN
--    DECLARE @current_date DATE = GETDATE();
--    DECLARE @start_date DATE = DATEADD(MONTH, -12, @current_date);
--    DECLARE @month_date DATE = @start_date;
--    DECLARE @site_id INT, @site_name VARCHAR(255), @total_emissions DECIMAL(12, 2);
    
--    -- Create a temporary table for sites
--    DECLARE @SiteTable TABLE (
--        site_id INT,
--        site_name VARCHAR(255),
--        processed BIT DEFAULT 0
--    );
    
--    -- Insert sites into the temporary table
--    INSERT INTO @SiteTable (site_id, site_name)
--    SELECT site_id, site_name
--    FROM Site;
    
--    -- Loop through each month
--    WHILE @month_date <= @current_date
--    BEGIN
--        PRINT 'Emissions for Month: ' + CONVERT(VARCHAR, @month_date, 120);
        
--        -- Reset processed flags for sites
--        UPDATE @SiteTable
--        SET processed = 0;
        
--        -- Loop through sites
--        WHILE EXISTS (SELECT 1 FROM @SiteTable WHERE processed = 0)
--        BEGIN
--            -- Get the first unprocessed site
--            SELECT TOP 1 @site_id = site_id, @site_name = site_name
--            FROM @SiteTable
--            WHERE processed = 0;
            
--            -- Calculate total emissions for the site in the current month
--            SELECT @total_emissions = SUM(calculated_emission)
--            FROM Emission_Record
--            WHERE site_id = @site_id
--            AND YEAR(record_date) = YEAR(@month_date)
--            AND MONTH(record_date) = MONTH(@month_date);
            
--            -- Print if emissions exist
--            IF @total_emissions IS NOT NULL
--                PRINT 'Site: ' + @site_name + ', Total Emissions: ' + CAST(@total_emissions AS VARCHAR);
--            ELSE
--                PRINT 'Site: ' + @site_name + ', Total Emissions: 0';
                
--            -- Mark the site as processed
--            UPDATE @SiteTable
--            SET processed = 1
--            WHERE site_id = @site_id;
--        END;
        
--        -- Move to next month
--        SET @month_date = DATEADD(MONTH, 1, @month_date);
--    END;
--END;
--GO

---- Execute the procedure
--EXEC PrintMonthlyEmissions;


----Q4
--CREATE TABLE Deleted_Emission_Log (
--    log_id INT PRIMARY KEY IDENTITY(1,1),
--    record_id INT NOT NULL,
--    site_id INT NOT NULL,
--    record_date DATE NOT NULL,
--    calculated_emission DECIMAL(12, 2) NOT NULL,
--    deleted_at DATETIME DEFAULT GETDATE()
--);
--GO

---- Create the trigger
--CREATE TRIGGER trg_AfterDeleteEmissionRecord
--ON Emission_Record
--AFTER DELETE
--AS
--BEGIN
--    INSERT INTO Deleted_Emission_Log (record_id, site_id, record_date, calculated_emission)
--    SELECT record_id, site_id, record_date, calculated_emission
--    FROM deleted;
--END;
--GO


----Q5
--ALTER TABLE Emission_Record
--ADD last_updated DATETIME NULL;
--GO

---- Create the trigger
--CREATE TRIGGER trg_AfterUpdateEmissionRecord
--ON Emission_Record
--AFTER UPDATE
--AS
--BEGIN
--    UPDATE Emission_Record
--    SET last_updated = GETDATE()
--    FROM Emission_Record er
--    INNER JOIN inserted i ON er.record_id = i.record_id
--    INNER JOIN deleted d ON er.record_id = d.record_id
--    WHERE i.quantity_used != d.quantity_used
--       OR i.emission_factor != d.emission_factor;
--END;
--GO



----Q6
--CREATE TABLE Drop_Attempt_Log (
--    log_id INT PRIMARY KEY IDENTITY(1,1),
--    table_name VARCHAR(255),
--    attempt_time DATETIME DEFAULT GETDATE(),
--    attempted_by VARCHAR(255)
--);
--GO

---- Create a database-level DDL trigger
--CREATE TRIGGER trg_PreventTableDrop
--ON DATABASE
--FOR DROP_TABLE
--AS
--BEGIN
--    DECLARE @table_name VARCHAR(255);
--    DECLARE @user_name VARCHAR(255);
    
--    -- Get the table name and user attempting the drop
--    SELECT @table_name = EVENTDATA().value('(/EVENT_INSTANCE/ObjectName)[1]', 'VARCHAR(255)');
--    SELECT @user_name = SUSER_SNAME();
    
--    -- Log the attempt
--    INSERT INTO Drop_Attempt_Log (table_name, attempted_by)
--    VALUES (@table_name, @user_name);
    
--    -- Rollback the drop operation
--    ROLLBACK;
    
--    -- Raise an error
--    RAISERROR ('Dropping tables is not allowed in SuperDogCarbonDB.', 16, 1);
--END;
--GO


----Q7
--CREATE TABLE Schema_Change_Log (
--    log_id INT PRIMARY KEY IDENTITY(1,1),
--    table_name VARCHAR(255),
--    changed_by VARCHAR(255),
--    change_time DATETIME DEFAULT GETDATE()
--);
--GO

---- Create a database-level DDL trigger
--CREATE TRIGGER trg_LogSchemaChanges
--ON DATABASE
--FOR ALTER_TABLE
--AS
--BEGIN
--    DECLARE @table_name VARCHAR(255);
--    DECLARE @user_name VARCHAR(255);
    
--    -- Get the table name and user
--    SELECT @table_name = EVENTDATA().value('(/EVENT_INSTANCE/ObjectName)[1]', 'VARCHAR(255)');
--    SELECT @user_name = SUSER_SNAME();
    
--    -- Log the schema change
--    INSERT INTO Schema_Change_Log (table_name, changed_by)
--    VALUES (@table_name, @user_name);
--END;
--GO