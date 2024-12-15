const express = require('express');
const mysql = require('mysql');

const app = express();

const connection = mysql.createConnection({
  host: 'mysql-container',
  user: 'root',
  password: 'programadorabordo',
  database: 'programadorabordo'
});

connection.connect();

app.get('/products', function(req, res) {
  connection.query('SELECT * FROM products', function (error, results) {
    if (error) { 
      throw error;
    };
    res.send(results.map(item => ({ name: item.name, price: item.price })));
  });
});

// Corrigindo o método app.listen()
const port = 9001;
app.listen(port, function() {
  console.log(`Server is listening on port ${port}`);
});
