const express = require('express');
const sql = require('mssql');
const cors = require('cors');
const app = express();
const port = 3001;

// Enable CORS for React frontend
app.use(cors());

// Database configuration
const dbConfig = {
  user: 'test', // Replace with your SQL Server username
  password: 'testing', // Replace with your SQL Server password
  server: 'LAPTOP-CKL4VSTC', // Replace with your SQL Server instance (e.g., localhost)
  database: 'SuperDogCarbonDB',
  options: {
    encrypt: false, // Use encryption (set to false if not needed)
    trustServerCertificate: true, // For local dev, set to true
  },
};

// API endpoint to fetch emissions data for the previous month
app.get('/emissions/last-month', async (req, res) => {
  try {
    let pool = await sql.connect(dbConfig);
    let result = await pool.request().query(`
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
        SUM(er.calculated_emission) DESC;
    `);
    res.json(result.recordset);
  } catch (err) {
    console.error('Database query error:', err);
    res.status(500).json({ error: 'Internal server error' });
  }
});

// Start the server
app.listen(port, () => {
  console.log(`Server running on http://localhost:${port}`);
});