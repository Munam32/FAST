--1
CREATE TRIGGER PreventDuplicateEmissionRecord
ON Emission_Record
INSTEAD OF INSERT
AS
BEGIN
    -- Suppress row count messages
    SET NOCOUNT ON;

    -- Check for duplicate records
    IF EXISTS (
        SELECT 1
        FROM Emission_Record er
        JOIN inserted i
            ON er.site_id = i.site_id
            AND er.source_id = i.source_id
            AND er.record_date = i.record_date
    )
    BEGIN
        -- Log and raise error for duplicates
        RAISERROR ('Duplicate emission record detected for the same site, source, and date.', 16, 1);
        ROLLBACK;
        RETURN;

    END
    ELSE
    BEGIN
        -- If no duplicates, proceed with the insert
        INSERT INTO Emission_Record (
            site_id,
            supplier_id,
            scope_id,
            source_id,
            record_date,
            quantity_used,
            emission_factor
        )
		--checking flow 
        SELECT 
            site_id,
            supplier_id,
            scope_id,
            source_id,
            record_date,
            quantity_used,
            emission_factor
        FROM inserted;

    END
END;

--2
-- Recreate the function to use quantity_used and emission_factor
CREATE FUNCTION fn_GetEmissionCategory
(
    @QuantityUsed DECIMAL(12,2),
    @EmissionFactor DECIMAL(10,4)
)
RETURNS VARCHAR(8)
WITH SCHEMABINDING
AS
BEGIN
    DECLARE @Emission INT;
    
    -- Calculate emission (quantity_used * emission_factor)
    SET @Emission = CAST(@QuantityUsed * @EmissionFactor AS INT);

    -- Categorize based on emission value
    IF (@Emission < 500)
        RETURN 'Low';
    IF (@Emission < 5000)
        RETURN 'Moderate';
    RETURN 'High';
END;
GO

--3   
ALTER TABLE Emission_Record
ADD emission_category AS dbo.fn_GetEmissionCategory(quantity_used, emission_factor) PERSISTED;
GO


--4
--Removing dependancy on calculated_emission
ALTER TABLE Emission_Record
ADD scope_type VARCHAR(50);
GO


UPDATE er
SET er.scope_type = es.scope_type
FROM Emission_Record er
JOIN Emission_Scope es ON er.scope_id = es.scope_id;
GO

--Create a trigger to maintain scope_type on insert
CREATE TRIGGER MaintainScopeType
ON Emission_Record
AFTER INSERT
AS
BEGIN
    SET NOCOUNT ON;

    UPDATE er
    SET er.scope_type = es.scope_type
    FROM Emission_Record er
    JOIN inserted i ON er.record_id = i.record_id
    JOIN Emission_Scope es ON i.scope_id = es.scope_id
    WHERE er.scope_type IS NULL;
END;
GO

-- Create the scalar function to compute the Risk Score
CREATE FUNCTION fn_ComputeRiskScore
(
    @QuantityUsed DECIMAL(12,2),
    @EmissionFactor DECIMAL(10,4),
    @ScopeType VARCHAR(50)
)
RETURNS DECIMAL(12,2)
WITH SCHEMABINDING
AS
BEGIN
    RETURN ((@QuantityUsed * @EmissionFactor) * 1.2) + (@QuantityUsed * 0.5) + 
           (CASE WHEN @ScopeType = 'Scope 1' THEN 100 ELSE 50 END);
END;
GO

--Add the computed column risk_score to Emission_Record
ALTER TABLE Emission_Record
ADD risk_score AS dbo.fn_ComputeRiskScore(quantity_used, emission_factor, scope_type) PERSISTED;

--5
CREATE TABLE Emergency_Alerts (
    alert_id INT PRIMARY KEY IDENTITY(1,1),
    record_id INT NOT NULL,
    site_id INT NOT NULL,
    source_id INT NOT NULL,
    quantity_used DECIMAL(12,2) NOT NULL,
    alert_date DATETIME NOT NULL DEFAULT GETDATE(),
    alert_message VARCHAR(255) NOT NULL,
    FOREIGN KEY (record_id) REFERENCES Emission_Record(record_id),
    FOREIGN KEY (site_id) REFERENCES Site(site_id),
    FOREIGN KEY (source_id) REFERENCES Emission_Source(source_id)
);

--Creating trigger to handle emergency fuel burn for testing
CREATE TRIGGER HandleEmergencyFuelBurn
ON Emission_Record
AFTER INSERT, UPDATE
AS
BEGIN
    SET NOCOUNT ON;

    --Identify emergency diesel records (> 20000 liters)
    DECLARE @EmergencyRecords TABLE (
        record_id INT,
        site_id INT,
        source_id INT,
        quantity_used DECIMAL(12,2)
    );

    INSERT INTO @EmergencyRecords (record_id, site_id, source_id, quantity_used)
    SELECT i.record_id, i.site_id, i.source_id, i.quantity_used
    FROM inserted i
    JOIN Emission_Source es ON i.source_id = es.source_id
    WHERE es.source_type = 'Diesel Fuel'
    AND i.quantity_used > 20000;

    --Insert alerts into Emergency_Alerts
    INSERT INTO Emergency_Alerts (record_id, site_id, source_id, quantity_used, alert_message)
    SELECT 
        er.record_id,
        er.site_id,
        er.source_id,
        er.quantity_used,
        'Emergency fuel burn detected: ' + CAST(er.quantity_used AS VARCHAR(20)) + ' liters of diesel fuel'
    FROM @EmergencyRecords er;

    --Update source_type in Emission_Source to append ' - Emergency Burn'
    UPDATE es
    SET es.source_type = 
        CASE 
            WHEN LEN(es.source_type + ' - Emergency Burn') <= 100 
            THEN es.source_type + ' - Emergency Burn'
            ELSE LEFT(es.source_type, 83) + ' - Emergency Burn' -- Truncate to fit within 100
        END
    FROM Emission_Source es
    JOIN @EmergencyRecords er ON es.source_id = er.source_id
    WHERE es.source_type = 'Diesel Fuel'; -- Ensure we only tag unmodified Diesel Fuel records
END;

