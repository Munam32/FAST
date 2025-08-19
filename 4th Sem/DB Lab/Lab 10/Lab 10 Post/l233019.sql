
USE myDB;
GO

-- Drop existing objects if they exist to avoid conflicts
IF OBJECT_ID('LudoGamePlay', 'U') IS NOT NULL
    DROP TABLE LudoGamePlay;
IF OBJECT_ID('CalculateNewPosition', 'FN') IS NOT NULL
    DROP FUNCTION CalculateNewPosition;
IF OBJECT_ID('trg_UpdatePosition', 'TR') IS NOT NULL
    DROP TRIGGER trg_UpdatePosition;
IF OBJECT_ID('SimulateTurn', 'P') IS NOT NULL
    DROP PROCEDURE SimulateTurn;
GO


CREATE TABLE LudoGamePlay (
    game_id INT IDENTITY(1,1) PRIMARY KEY,
    player_id INT NOT NULL,
    dice_roll INT NOT NULL,
    position INT NOT NULL,
    turn_id INT NOT NULL 
);
GO

-- Scalar Function to Calculate New Position
CREATE FUNCTION CalculateNewPosition (@current_position INT, @dice_roll INT)
RETURNS INT
AS
BEGIN
    DECLARE @new_position INT;
    SET @new_position = @current_position + @dice_roll;

    -- If new position exceeds 100, stay at current position
    IF @new_position > 100
        SET @new_position = @current_position;


    RETURN @new_position;
END;
GO

-- Trigger to Update Position on Insert
CREATE TRIGGER trg_UpdatePosition
ON LudoGamePlay
AFTER INSERT
AS
BEGIN
    DECLARE @game_id INT, @player_id INT, @dice_roll INT;
    
    SELECT @game_id = game_id, 
           @player_id = player_id, 
           @dice_roll = dice_roll
    FROM inserted;


    -- Get the player's last position (before this insert), default to 0 if none exists
    DECLARE @last_position INT;
    SELECT @last_position = ISNULL((
        SELECT TOP 1 position
        FROM LudoGamePlay
        WHERE player_id = @player_id
        AND game_id < @game_id
        ORDER BY game_id DESC
    ), 0);


    -- Calculate new position using the scalar function
    DECLARE @new_position INT;
    SET @new_position = dbo.CalculateNewPosition(@last_position, @dice_roll);


    -- Update the position in the current inserted row
    UPDATE LudoGamePlay
    SET position = @new_position
    WHERE game_id = @game_id;
END;
GO

-- Stored Procedure to Simulate a Turn
CREATE PROCEDURE SimulateTurn
AS
BEGIN
    DECLARE @player_id INT;
    DECLARE @dice_roll INT;
    DECLARE @current_position INT;
    DECLARE @new_turn_id INT;
    
    -- Determine whose turn it is (odd turn_id: Player 1, even: Player 2)
    DECLARE @last_turn_id INT;
    SELECT @last_turn_id = ISNULL(MAX(turn_id), 0) FROM LudoGamePlay;
    
    IF @last_turn_id % 2 = 0
        SET @player_id = 1; -- Player 1's turn
    ELSE
        SET @player_id = 2; -- Player 2's turn

    -- Generate random dice roll (1 to 6)
    SET @dice_roll = FLOOR(RAND() * 6) + 1;

    -- Get player's current position, default to 0 if no previous position
    SELECT @current_position = ISNULL((
        SELECT TOP 1 position
        FROM LudoGamePlay
        WHERE player_id = @player_id
        ORDER BY game_id DESC
    ), 0);

    -- Calculate new turn_id
    SET @new_turn_id = @last_turn_id + 1;

    -- Insert the new move with the calculated position
    INSERT INTO LudoGamePlay (player_id, dice_roll, position, turn_id)
    VALUES (@player_id, @dice_roll, @current_position, @new_turn_id);
END;
GO

-- Game Loop to Simulate the Game
DECLARE @game_ongoing INT = 1;

-- Initialize the game with a dummy row
INSERT INTO LudoGamePlay (player_id, dice_roll, position, turn_id)
VALUES (1, 0, 0, 0);

WHILE @game_ongoing = 1
BEGIN
    -- Simulate a turn
    EXEC SimulateTurn;
    
    -- Display current game state
    SELECT * FROM LudoGamePlay ORDER BY turn_id DESC;
    
    -- Check if Player 1 has won
    IF EXISTS (SELECT 1 FROM LudoGamePlay WHERE player_id = 1 AND position = 100)
    BEGIN
        PRINT 'Player 1 has won!';
        SET @game_ongoing = 0; -- End the game
    END
    
    -- Check if Player 2 has won
    IF EXISTS (SELECT 1 FROM LudoGamePlay WHERE player_id = 2 AND position = 100)
    BEGIN
        PRINT 'Player 2 has won!';
        SET @game_ongoing = 0; -- End the game
    END
END;
GO