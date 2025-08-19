import React, { useState, useEffect } from 'react';
import { PieChart, Pie, Cell, Tooltip, Legend } from 'recharts';
import axios from 'axios';

const EmissionPieChart = () => {
  const [data, setData] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  const COLORS = ['#ff9999', '#66b3ff', '#99ff99', '#ffcc99', '#cc99ff', '#99ffcc', '#ff99cc', '#ccff99'];

  useEffect(() => {
    axios
      .get('http://localhost:3001/emissions/last-month')
      .then((response) => {
        console.log('API response:', response.data);
        const formattedData = response.data
          .filter((item) => {
            const isValid =
              item.Emission_Source &&
              !isNaN(parseFloat(item.Total_Emissions)) &&
              parseFloat(item.Total_Emissions) > 0;
            if (!isValid) {
              console.warn('Invalid data entry:', item);
            }
            return isValid;
          })
          .map((item) => ({
            source_type: item.Emission_Source,
            total_emissions: parseFloat(item.Total_Emissions),
          }));
        console.log('Formatted data:', formattedData);
        setData(
          formattedData.length
            ? formattedData
            : [{ source_type: 'No Data', total_emissions: 1 }]
        );
        setLoading(false);
      })
      .catch((err) => {
        console.error('Fetch error:', err.message);
        setError('Failed to load emissions data: ' + err.message);
        setLoading(false);
      });
  }, []);

  // Inline styles for centering
  const containerStyle = {
    display: 'flex',
    flexDirection: 'column',
    alignItems: 'center',
    justifyContent: 'center',
    //minHeight: '300vh', // Full viewport height to center vertically
    textAlign: 'center',
  };

  const headerStyle ={
    textAlign : 'center'
  }

  return (
    
    <div style = {headerStyle}>
      <h2>Emission Distribution by Source - Previous Month</h2>
      <div style={containerStyle}>
      
      {loading ? (
        <p>Loading data...</p>
      ) : error ? (
        <p style={{ color: 'red' }}>Error: {error}</p>
      ) : data.length === 0 ? (
        <p>No data available for the previous month</p>
      ) : (
        <PieChart width={600} height={400}>
          <Pie
            data={data}
            dataKey="total_emissions"
            nameKey="source_type"
            cx="50%"
            cy="50%"
            outerRadius={150}
            fill="#8884d8"
            label={({ percent }) => `${(percent * 100).toFixed(1)}%`}
          >
            {data.map((entry, index) => (
              <Cell key={`cell-${index}`} fill={COLORS[index % COLORS.length]} />
            ))}
          </Pie>
          <Tooltip formatter={(value) => `${value} kgCO2e`} />
          <Legend />
        </PieChart>
      )}
      </div>
    </div>
  );
};

export default EmissionPieChart;