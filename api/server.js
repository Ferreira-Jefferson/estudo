const express = require('express');
const mysql = require('mysql2');
const app = express();
const port = 3000;

// Conectar ao banco de dados MySQL
const db = mysql.createConnection({
  host: process.env.MYSQL_HOST || 'db',
  user: process.env.MYSQL_USER || 'user',
  password: process.env.MYSQL_PASSWORD || 'userpassword',
  database: process.env.MYSQL_DATABASE || 'degustware'
});

db.connect(err => {
  if (err) throw err;
  console.log('Conectado ao banco de dados MySQL');
});

// Rota para listar produtos
app.get('/api', (req, res) => {
  db.query('SELECT * FROM products', (err, results) => {
    if (err) throw err;
    res.json(results);
  });
});

app.listen(port, () => {
  console.log(`API rodando em http://localhost:${port}`);
});
