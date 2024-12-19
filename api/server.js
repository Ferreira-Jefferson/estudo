const express = require('express');
const mysql = require('mysql2');
const bodyParser = require('body-parser'); // Para suportar requisições POST
const motoboysRoutes = require('./motoboys'); // Importar o arquivo motoboys.js

const app = express();
const port = 3000;

// Middleware para parsear JSON
app.use(bodyParser.json());

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

// Endpoint para listar produtos
app.get('/api', (req, res) => {
  db.query('SELECT * FROM products', (err, results) => {
    if (err) throw err;
    res.json(results);
  });
});

// Usar rotas do arquivo motoboys.js
app.use('/api', motoboysRoutes);

app.listen(port, () => {
  console.log(`API rodando em https://degustware.com.br:${port}/api`);
});
