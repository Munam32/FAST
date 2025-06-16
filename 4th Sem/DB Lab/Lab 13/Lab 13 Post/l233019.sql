USE SuperDogCarbonDB;
GO

---- Create MissionDeploy table
--CREATE TABLE MissionDeploy (
--    deploy_id INT IDENTITY(1,1) PRIMARY KEY,
--    team_id INT NOT NULL CHECK (team_id IN (1, 2)), -- 1 for EcoCat, 2 for PandaBytes
--    risk_roll INT NOT NULL CHECK (risk_roll BETWEEN 1 AND 6), -- Random roll (1-6)
--    mission_count INT NOT NULL, -- Cumulative missions completed by the team
--    success BIT NOT NULL -- 1 for success, 0 for failure
--);



-- Declare variables for game state
DECLARE @team1_missions INT = 0; -- EcoCat's mission count
DECLARE @team2_missions INT = 0; -- PandaBytes' mission count
DECLARE @current_team INT = 1; -- Starting with Team 1 (EcoCat)
DECLARE @target INT = 10; -- Target number of missions to win
DECLARE @winning_team INT = 0; -- To store the winning team
DECLARE @roll INT; -- Random roll for the turn
DECLARE @success BIT; -- Success or failure of the mission


WHILE @team1_missions < @target AND @team2_missions < @target
BEGIN
    -- Simulate random roll (1-6)
    SET @roll = FLOOR(RAND() * 6) + 1;
    
    -- Determine success (success if roll > 4)
    SET @success = CASE WHEN @roll > 4 THEN 1 ELSE 0 END;


    BEGIN TRY
        BEGIN TRANSACTION;

        -- If mission is successful, increment the team's mission count
        IF @success = 1
        BEGIN
            IF @current_team = 1
                SET @team1_missions = @team1_missions + 1;
            ELSE
                SET @team2_missions = @team2_missions + 1;
        END

        -- Insert the attempt into MissionDeploy using Case Statement
        INSERT INTO MissionDeploy (team_id, risk_roll, mission_count, success)
        VALUES (
            @current_team,
            @roll,
            CASE 
                WHEN @current_team = 1 THEN @team1_missions 
                ELSE @team2_missions 
            END,
            @success
        );


        COMMIT;
    END TRY
    BEGIN CATCH

        ROLLBACK;
        PRINT 'Error in mission attempt for Team ' + CAST(@current_team AS VARCHAR) + ': ' + ERROR_MESSAGE();
        -- Log failure outside transaction if needed
        CONTINUE;
    END CATCH;

    -- Switch to the other team for the next turn
    SET @current_team = CASE @current_team WHEN 1 THEN 2 ELSE 1 END;
END

-- Determine the winner
IF @team1_missions >= @target
    SET @winning_team = 1;
ELSE IF @team2_missions >= @target
    SET @winning_team = 2;

-- Printing the winner
PRINT 'Team ' + CAST(@winning_team AS VARCHAR) + ' wins with ' + CAST(@target AS VARCHAR) + ' missions completed!';


SELECT 
    deploy_id,
    team_id,
    CASE team_id 
        WHEN 1 THEN 'EcoCat' 
        WHEN 2 THEN 'PandaBytes' 
    END AS team_name,
    risk_roll,
    mission_count,
    success
FROM MissionDeploy
ORDER BY deploy_id;