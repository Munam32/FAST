import React, { useState, useEffect } from 'react';
import { BrowserRouter as Router, Routes, Route, Link } from 'react-router-dom';

// API not present hence not signing in or signnig up thus no displaying of alliances and superpowers. Ensure API

// SignupForm Component
function SignupForm() {
  const [heroData, setHeroData] = useState({
    CharacterName: '',
    Alias: '',
    Age: '',
    BackgroundStory: '',
    RegionID: ''
  });
  const [signupStatus, setSignupStatus] = useState('');

  const handleInputChange = (e) => {
    setHeroData({ ...heroData, [e.target.name]: e.target.value });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await fetch('http://localhost:5000/api/characters', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(heroData),
      });

      if (response.ok) {
        setSignupStatus('Hero successfully signed up!');
        setHeroData({
          CharacterName: '',
          Alias: '',
          Age: '',
          BackgroundStory: '',
          RegionID: ''
        });
      } else {
        setSignupStatus('Signup failed. Please try again.');
      }
    } catch (error) {
      console.error('Error during signup:', error);
      setSignupStatus('An error occurred during signup.');
    }
  };

  const styles = {
    container: { maxWidth: '500px', margin: '0 auto', padding: '20px' },
    title: { textAlign: 'center', marginBottom: '20px' },
    form: { background: '#f5f5f5', padding: '20px', borderRadius: '8px' },
    input: { display: 'block', width: '100%', marginBottom: '10px', padding: '8px', border: '1px solid #ddd', borderRadius: '4px', boxSizing: 'border-box' },
    textarea: { display: 'block', width: '100%', marginBottom: '10px', padding: '8px', border: '1px solid #ddd', borderRadius: '4px', boxSizing: 'border-box', minHeight: '100px' },
    button: { background: '#007bff', color: 'white', padding: '10px 20px', border: 'none', borderRadius: '4px', cursor: 'pointer', width: '100%' },
    status: { textAlign: 'center', marginTop: '15px', padding: '10px', borderRadius: '4px', background: signupStatus.includes('successfully') ? '#d4edda' : signupStatus.includes('failed') ? '#f8d7da' : 'transparent', color: signupStatus.includes('successfully') ? '#155724' : signupStatus.includes('failed') ? '#721c24' : '#000' },
    link: { display: 'block', textAlign: 'center', marginTop: '15px', color: '#007bff', textDecoration: 'none' }
  };

  return (
    <div style={styles.container}>
      <h2 style={styles.title}>Hero Signup</h2>
      <form onSubmit={handleSubmit} style={styles.form}>
        <input type="text" name="CharacterName" value={heroData.CharacterName} onChange={handleInputChange} placeholder="Hero Name" required style={styles.input} />
        <input type="text" name="Alias" value={heroData.Alias} onChange={handleInputChange} placeholder="Alias" style={styles.input} />
        <input type="number" name="Age" value={heroData.Age} onChange={handleInputChange} placeholder="Age" style={styles.input} />
        <textarea name="BackgroundStory" value={heroData.BackgroundStory} onChange={handleInputChange} placeholder="Background Story" style={styles.textarea} />
        <input type="number" name="RegionID" value={heroData.RegionID} onChange={handleInputChange} placeholder="Region ID" required style={styles.input} />
        <button type="submit" style={styles.button}>Sign Up</button>
      </form>
      {signupStatus && <p style={styles.status}>{signupStatus}</p>}
      <Link to="/signin" style={styles.link}>Already have an account? Sign In</Link>
      <Link to="/" style={styles.link}>Back to Home</Link>
    </div>
  );
}

// SigninForm Component
function SigninForm({ onSignin }) {
  const [signinData, setSigninData] = useState({
    CharacterName: '',
    RegionID: ''
  });
  const [signinStatus, setSigninStatus] = useState('');

  const handleInputChange = (e) => {
    setSigninData({ ...signinData, [e.target.name]: e.target.value });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await fetch('http://localhost:5000/api/signin', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify(signinData),
      });

      if (response.ok) {
        const data = await response.json();
        setSigninStatus('Successfully signed in!');
        onSignin({ CharacterName: signinData.CharacterName, RegionID: signinData.RegionID });
        setSigninData({ CharacterName: '', RegionID: '' });
      } else {
        setSigninStatus('Signin failed. Check your credentials.');
      }
    } catch (error) {
      console.error('Error during signin:', error);
      setSigninStatus('An error occurred during signin.');
    }
  };

  const styles = {
    container: { maxWidth: '500px', margin: '0 auto', padding: '20px' },
    title: { textAlign: 'center', marginBottom: '20px' },
    form: { background: '#f5f5f5', padding: '20px', borderRadius: '8px' },
    input: { display: 'block', width: '100%', marginBottom: '10px', padding: '8px', border: '1px solid #ddd', borderRadius: '4px', boxSizing: 'border-box' },
    button: { background: '#007bff', color: 'white', padding: '10px 20px', border: 'none', borderRadius: '4px', cursor: 'pointer', width: '100%' },
    status: { textAlign: 'center', marginTop: '15px', padding: '10px', borderRadius: '4px', background: signinStatus.includes('successfully') ? '#d4edda' : signinStatus.includes('failed') ? '#f8d7da' : 'transparent', color: signinStatus.includes('successfully') ? '#155724' : signinStatus.includes('failed') ? '#721c24' : '#000' },
    link: { display: 'block', textAlign: 'center', marginTop: '15px', color: '#007bff', textDecoration: 'none' }
  };

  return (
    <div style={styles.container}>
      <h2 style={styles.title}>Hero Signin</h2>
      <form onSubmit={handleSubmit} style={styles.form}>
        <input type="text" name="CharacterName" value={signinData.CharacterName} onChange={handleInputChange} placeholder="Hero Name" required style={styles.input} />
        <input type="number" name="RegionID" value={signinData.RegionID} onChange={handleInputChange} placeholder="Region ID" required style={styles.input} />
        <button type="submit" style={styles.button}>Sign In</button>
      </form>
      {signinStatus && <p style={styles.status}>{signinStatus}</p>}
      <Link to="/signup" style={styles.link}>Need an account? Sign Up</Link>
      <Link to="/" style={styles.link}>Back to Home</Link>
    </div>
  );
}

function App() {
  const [signedInHero, setSignedInHero] = useState(null);
  const [alliances, setAlliances] = useState([]);
  const [superpowers, setSuperpowers] = useState([]);

  useEffect(() => {
    if (signedInHero) {
      fetchHeroData();
    }
  }, [signedInHero]);

  const fetchHeroData = async () => {
    try {
      // Fetch alliances
      const alliancesResponse = await fetch(`http://localhost:5000/api/alliances?characterName=${signedInHero.CharacterName}&regionID=${signedInHero.RegionID}`);
      const alliancesData = await alliancesResponse.json();
      setAlliances(alliancesData);

      // Fetch superpowers
      const superpowersResponse = await fetch(`http://localhost:5000/api/superpowers?characterName=${signedInHero.CharacterName}&regionID=${signedInHero.RegionID}`);
      const superpowersData = await superpowersResponse.json();
      setSuperpowers(superpowersData);
    } catch (error) {
      console.error('Error fetching hero data:', error);
    }
  };

  const handleSignin = (hero) => {
    setSignedInHero(hero);
  };

  const handleSignout = () => {
    setSignedInHero(null);
    setAlliances([]);
    setSuperpowers([]);
  };

  const styles = {
    app: { minHeight: '100vh', display: 'flex', flexDirection: 'column', fontFamily: 'Arial, sans-serif' },
    header: { backgroundColor: '#282c34', padding: '20px', color: 'white', textAlign: 'center' },
    headerTitle: { margin: '0 0 10px 0', fontSize: '2.5rem' },
    nav: { display: 'flex', justifyContent: 'center', gap: '20px' },
    navLink: { color: '#61dafb', textDecoration: 'none', fontSize: '1.1rem' },
    main: { flex: 1, padding: '20px' },
    homeContainer: { maxWidth: '500px', margin: '0 auto', padding: '20px' },
    homeTitle: { textAlign: 'center', marginBottom: '20px' },
    sectionTitle: { marginTop: '20px', marginBottom: '10px' },
    list: { listStyle: 'none', padding: 0 },
    listItem: { padding: '5px 0', borderBottom: '1px solid #ddd' },
    button: { background: '#dc3545', color: 'white', padding: '10px 20px', border: 'none', borderRadius: '4px', cursor: 'pointer', marginTop: '20px', width: '100%' },
    footer: { backgroundColor: '#f8f9fa', padding: '10px', textAlign: 'center', borderTop: '1px solid #e9ecef' },
    footerText: { margin: 0, color: '#6c757d' }
  };

  const Home = () => (
    <div style={styles.homeContainer}>
      <h2 style={styles.homeTitle}>Welcome to Pak Legion</h2>
      {!signedInHero ? (
        <>
          <p style={{ textAlign: 'center' }}>Join the Pak Legion WebToon Universe!</p>
          <Link to="/signup" style={{ ...styles.navLink, display: 'block', marginTop: '20px', textAlign: 'center' }}>Sign Up</Link>
          <Link to="/signin" style={{ ...styles.navLink, display: 'block', marginTop: '10px', textAlign: 'center' }}>Sign In</Link>
        </>
      ) : (
        <>
          <p style={{ textAlign: 'center' }}>Welcome, {signedInHero.CharacterName}!</p>
          <h3 style={styles.sectionTitle}>Your Alliances</h3>
          {alliances.length > 0 ? (
            <ul style={styles.list}>
              {alliances.map((alliance, index) => (
                <li key={index} style={styles.listItem}>
                  {alliance.CharacterName2} - {alliance.AllianceType}
                </li>
              ))}
            </ul>
          ) : (
            <p>No alliances found.</p>
          )}
          <h3 style={styles.sectionTitle}>Your Superpowers</h3>
          {superpowers.length > 0 ? (
            <ul style={styles.list}>
              {superpowers.map((power, index) => (
                <li key={index} style={styles.listItem}>
                  {power.PowerName} - {power.ProficiencyLevel}
                </li>
              ))}
            </ul>
          ) : (
            <p>No superpowers found.</p>
          )}
          <button onClick={handleSignout} style={styles.button}>Sign Out</button>
        </>
      )}
    </div>
  );

  return (
    <Router>
      <div style={styles.app}>
        <header style={styles.header}>
          <h1 style={styles.headerTitle}>Pak Legion WebToon Database</h1>
          <nav style={styles.nav}>
            <Link to="/" style={styles.navLink}>Home</Link>
            <Link to="/signup" style={styles.navLink}>Signup</Link>
            <Link to="/signin" style={styles.navLink}>Signin</Link>
          </nav>
        </header>
        <main style={styles.main}>
          <Routes>
            <Route path="/" element={<Home />} />
            <Route path="/signup" element={<SignupForm />} />
            <Route path="/signin" element={<SigninForm onSignin={handleSignin} />} />
          </Routes>
        </main>
        <footer style={styles.footer}>
          <p style={styles.footerText}>© 2025 Pak Legion. All rights reserved.</p>
        </footer>
      </div>
    </Router>
  );
}

export default App;