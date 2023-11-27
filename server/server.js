const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const port = 3000;

// Middleware to parse request bodies
app.use(bodyParser.text());

// Define a route to handle POST requests
app.post('/data', (req, res) => {
  // Process the received data
  const receivedData = req.body;
  console.log('Received data:', receivedData);

  // Perform any necessary operations with the data (e.g., store in Excel sheet)

  // Send a response back
  res.send('Data received successfully');
});

// Start the server
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});

