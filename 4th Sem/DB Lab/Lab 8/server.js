const express = require('express');
const sql = require('mssql');
const cors = require('cors');

const app = express();
app.use(cors());
app.use(express.json());

const dbConfig = {
  user: 'your_username', // Replace with your SQL Server username
  password: 'your_password', // Replace with your SQL Server password
  server: 'your_server', // Replace with your SQL Server instance
  database: 'PakLegionWebToonDB',
  options: { encrypt: true, trustServerCertificate: true }
};

// Connect to database
sql.connect(dbConfig).catch(err => console.log('Database connection failed:', err));

// 1. Signup API - Create a new hero
app.post('/api/characters', async (req, res) => {
  try {
    const { CharacterName, Alias, Age, BackgroundStory, RegionID } = req.body;
    const result = await sql.query`
      INSERT INTO Characters (CharacterName, Alias, Age, BackgroundStory, RegionID)
      VALUES (${CharacterName}, ${Alias}, ${Age}, ${BackgroundStory}, ${RegionID});
      SELECT SCOPE_IDENTITY() as CharacterID
    `;
    res.json({ success: true, CharacterID: result.recordset[0].CharacterID });
  } catch (err) {
    console.error('Error during signup:', err);
    res.status(500).json({ success: false, message: 'Signup failed' });
  }
});

// 2. Signin API - Authenticate a hero
app.post('/api/signin', async (req, res) => {
  try {
    const { CharacterName, RegionID } = req.body;
    const result = await sql.query`
      SELECT CharacterID, CharacterName, RegionID
      FROM Characters 
      WHERE CharacterName = ${CharacterName} AND RegionID = ${RegionID}
    `;
    if (result.recordset.length > 0) {
      res.json({ success: true, character: result.recordset[0] });
    } else {
      res.status(401).json({ success: false, message: 'Invalid credentials' });
    }
  } catch (err) {
    console.error('Error during signin:', err);
    res.status(500).json({ success: false, message: 'Signin failed' });
  }
});

// 3. Alliances API - Get hero's alliances
app.get('/api/alliances', async (req, res) => {
  try {
    const { characterName, regionID } = req.query;
    const result = await sql.query`
      SELECT ca.CharacterID2, c2.CharacterName as CharacterName2, ca.AllianceType
      FROM CharacterAlliances ca
      JOIN Characters c1 ON ca.CharacterID1 = c1.CharacterID
      JOIN Characters c2 ON ca.CharacterID2 = c2.CharacterID
      WHERE c1.CharacterName = ${characterName} AND c1.RegionID = ${regionID}
    `;
    res.json(result.recordset);
  } catch (err) {
    console.error('Error fetching alliances:', err);
    res.status(500).json({ success: false, message: 'Failed to fetch alliances' });
  }
});

// 4. Superpowers API - Get hero's superpowers
app.get('/api/superpowers', async (req, res) => {
  try {
    const { characterName, regionID } = req.query;
    const result = await sql.query`
      SELECT sp.PowerName, csp.ProficiencyLevel
      FROM CharacterSuperpowers csp
      JOIN Characters c ON csp.CharacterID = c.CharacterID
      JOIN Superpowers sp ON csp.PowerID = sp.PowerID
      WHERE c.CharacterName = ${characterName} AND c.RegionID = ${regionID}
    `;
    res.json(result.recordset);
  } catch (err) {
    console.error('Error fetching superpowers:', err);
    res.status(500).json({ success: false, message: 'Failed to fetch superpowers' });
  }
});

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));