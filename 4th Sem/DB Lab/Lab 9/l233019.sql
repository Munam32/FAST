--1
SELECT 
    site_name,
    organization_name,
    total_emission
FROM 
    (
        SELECT 
            site_id,
            (SELECT organization_name 
             FROM Organization O 
             WHERE O.organization_id = 
                 (SELECT organization_id FROM Site S WHERE S.site_id = E.site_id)
            ) AS organization_name,
            (SELECT site_name 
             FROM Site S 
             WHERE S.site_id = E.site_id
            ) AS site_name,
            SUM(calculated_emission) AS total_emission
        FROM 
            Emission_Record E
        GROUP BY 
            site_id
    ) AS SiteEmissions
ORDER BY 
    total_emission DESC;

--2
SELECT 
    O.organization_name,
    ES.scope_type,
    YEAR(ER.record_date) AS emission_year,
    SUM(ER.calculated_emission) AS yearly_total_emission,
    SUM(SUM(ER.calculated_emission)) OVER (
        PARTITION BY O.organization_name, ES.scope_type 
        ORDER BY YEAR(ER.record_date)
    ) AS running_total_emission
FROM 
    Emission_Record ER
INNER JOIN 
    Site S ON ER.site_id = S.site_id
INNER JOIN 
    Organization O ON S.organization_id = O.organization_id
INNER JOIN 
    Emission_Scope ES ON ER.scope_id = ES.scope_id
GROUP BY 
    O.organization_name,
    ES.scope_type,
    YEAR(ER.record_date)
ORDER BY 
    O.organization_name,
    ES.scope_type,
    emission_year;

--3
SELECT 
    O.organization_name,
    ET.year AS target_year,
    ES.scope_type,
    ET.emission_limit,
    ActualEmissions.actual_emission,
    CASE 
        WHEN ActualEmissions.actual_emission > ET.emission_limit THEN 'Exceeded'
        ELSE 'Within Limit'
    END AS status
FROM 
    Emission_Target ET
JOIN 
    Organization O ON ET.organization_id = O.organization_id
JOIN 
    Emission_Scope ES ON ET.scope_id = ES.scope_id
JOIN 
    (
        SELECT 
            S.organization_id,
            ER.scope_id,
            YEAR(ER.record_date) AS emission_year,
            SUM(ER.calculated_emission) AS actual_emission
        FROM 
            Emission_Record ER
        JOIN 
            Site S ON ER.site_id = S.site_id
        GROUP BY 
            S.organization_id, ER.scope_id, YEAR(ER.record_date)
    ) AS ActualEmissions 
ON 
    ET.organization_id = ActualEmissions.organization_id 
    or ET.scope_id = ActualEmissions.scope_id 
    or ET.year = ActualEmissions.emission_year
WHERE 
    ActualEmissions.actual_emission > ET.emission_limit
ORDER BY 
    O.organization_name, target_year, ES.scope_type;

--4
SELECT 
    S.site_name,
    (
        SELECT 
            STUFF(
                (SELECT DISTINCT ', ' + ES.source_type
                 FROM Emission_Record ER
                 INNER JOIN Emission_Source ES ON ER.source_id = ES.source_id
                 WHERE ER.site_id = S.site_id
                 FOR XML PATH('')
                ), 1, 2, ''
            ) AS emission_sources_used
    ) AS emission_sources_used
FROM 
    Site S
ORDER BY 
    S.site_name;

--5
SELECT 
    ER.record_id,
    S.site_name,
    ER.record_date,
    ER.calculated_emission AS Current_Emission,
    LAG(ER.calculated_emission) OVER (
        PARTITION BY S.site_id 
        ORDER BY ER.record_date
    ) AS previous_emission,
    ER.calculated_emission - LAG(ER.calculated_emission) OVER (
        PARTITION BY S.site_id 
        ORDER BY ER.record_date
    ) AS emission_difference
FROM 
    Emission_Record ER
INNER JOIN 
    Site S ON ER.site_id = S.site_id
ORDER BY 
    ER.record_id;

--6
SELECT 
    site_id,
    FIRST_VALUE(record_date) OVER (PARTITION BY site_id ORDER BY record_date ASC) AS first_emission_date,
    FIRST_VALUE(quantity_used) OVER (PARTITION BY site_id ORDER BY record_date ASC) AS first_quantity_used,
    FIRST_VALUE(emission_factor) OVER (PARTITION BY site_id ORDER BY record_date ASC) AS first_emission_factor,
    FIRST_VALUE(calculated_emission) OVER (PARTITION BY site_id ORDER BY record_date ASC) AS first_calculated_emission
FROM 
    Emission_Record;



--7
DECLARE @LastMonthStart DATE = DATEADD(MONTH, DATEDIFF(MONTH, 0, GETDATE()) - 1, 0);
DECLARE @LastMonthEnd DATE = EOMONTH(@LastMonthStart);

SELECT 
    es.source_type AS Emission_Source,
    SUM(er.calculated_emission) AS Total_Emissions
FROM 
    Emission_Record er
JOIN 
    Emission_Source es
ON 
    er.source_id = es.source_id
WHERE 
    er.record_date BETWEEN @LastMonthStart AND @LastMonthEnd
GROUP BY 
    es.source_type
ORDER BY 
    Total_Emissions DESC;




