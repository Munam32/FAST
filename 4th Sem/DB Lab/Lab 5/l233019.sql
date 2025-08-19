--1
SELECT * 
FROM Creature 
WHERE CreatureID = (SELECT CreatureID FROM Rank WHERE Level = (SELECT MAX(Level) FROM Rank));


--2  // More efficient way than discussed in lab
SELECT * 
FROM Ingredient 
WHERE IngredientID = (
    SELECT TOP 1 IngredientID 
    FROM Creature_Ingredient 
    GROUP BY IngredientID 
    ORDER BY COUNT(*) DESC
);

--3 --bohot badi chal gayi hai lekin chal rhi hai
SELECT *  
FROM Creature 
WHERE CreatureID IN (
    SELECT CreatureID 
    FROM (
        SELECT CreatureID, 
               (SELECT COUNT(*) FROM Fight WHERE Creature1ID = C.CreatureID) + (SELECT COUNT(*) FROM Fight WHERE Creature2ID = C.CreatureID) AS FightCount 
        FROM Creature AS C
    ) AS FightCounts

    WHERE FightCount = (
        SELECT MAX(FightCount) 
        FROM (
            SELECT CreatureID, 
                   (SELECT COUNT(*) FROM Fight WHERE Creature1ID = C.CreatureID) + (SELECT COUNT(*) FROM Fight WHERE Creature2ID = C.CreatureID) AS FightCount 
            FROM Creature AS C
        ) AS MaxFights
    )
);


--4
SELECT *
FROM Creature 
WHERE CreatureID IN (
    SELECT CreatureID 
    FROM Creature_Power 
    GROUP BY CreatureID 
    HAVING COUNT(PowerID) = 1
);


--5
SELECT * 
FROM Creature 
WHERE CreatureID NOT IN (
    SELECT Creature1ID 
    FROM Fight 
    WHERE WinnerID <> Creature1ID
) 
AND CreatureID NOT IN (
    SELECT Creature2ID 
    FROM Fight 
    WHERE WinnerID <> Creature2ID
);

--6 --USE OF OR,+,- and other operations before mid
SELECT * 
FROM Creature 
WHERE CreatureID = (
    SELECT MAX(CreatureID) 
    FROM Creature 
    WHERE CreatureID IN (
        SELECT Creature1ID 
        FROM FamilyRelation 
        WHERE RelationType = 'Sibling'
    )  
	OR CreatureID IN (
        SELECT Creature2ID 
        FROM FamilyRelation 
        WHERE RelationType = 'Sibling'
    )
);


--7 // for this dataset all creatures have the same powercount so everything is returned
SELECT * 
FROM Creature 
WHERE CreatureID IN (

    SELECT CreatureID 
    FROM Creature_Power 
    GROUP BY CreatureID 
    HAVING COUNT(PowerID) = (
        
		SELECT MAX(PowerCount) 
        FROM (
            SELECT COUNT(PowerID) AS PowerCount 
            FROM Creature_Power 
            GROUP BY CreatureID
        
		) AS MaxPowerCheck
    )
);

--8
SELECT * 
FROM Creature 
WHERE CreatureID IN (
    SELECT Creature1ID 
    FROM Fight 
    GROUP BY Creature1ID 
    HAVING COUNT(*) >= 2
) 
OR CreatureID IN (
    SELECT Creature2ID 
    FROM Fight 
    GROUP BY Creature2ID 
    HAVING COUNT(*) >= 2
);

--9  //NONE
SELECT * 
FROM Creature 
WHERE CreatureID IN (
    SELECT CreatureID FROM DeathLog
) 
AND CreatureID IN (
    SELECT CreatureID FROM Rank
);

--10
SELECT * 
FROM Creature 
WHERE CreatureID IN (
    SELECT CreatureID 
    FROM Creature_Ingredient 
    WHERE IngredientID = (
        SELECT IngredientID 
        FROM Ingredient 
        WHERE Name = 'Chemical X'
    )
);

--11 //Everything included since each opponent also has fought a different opponent
SELECT * 
FROM Creature 
WHERE CreatureID IN (
    SELECT CreatureID 
    FROM (
        SELECT CreatureID, (SELECT COUNT(DISTINCT Creature2ID) FROM Fight WHERE Creature1ID = C.CreatureID) + (SELECT COUNT(DISTINCT Creature1ID) FROM Fight WHERE Creature2ID = C.CreatureID) AS OpponentCount
        FROM Creature AS C
    ) AS OpponentCounts

    WHERE OpponentCount = (
        SELECT MAX(OpponentCount) 
        FROM (
            SELECT CreatureID, 
                   (SELECT COUNT(DISTINCT Creature2ID) FROM Fight WHERE Creature1ID = C.CreatureID) + (SELECT COUNT(DISTINCT Creature1ID) FROM Fight WHERE Creature2ID = C.CreatureID) AS OpponentCount
            FROM Creature AS C
        ) AS MaxOpponentCheck
    )
);





