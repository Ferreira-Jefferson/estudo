const express = require('express');
const mysql = require('mysql2/promise');
const dotenv = require('dotenv');

dotenv.config();

const app = express();
const port = process.env.PORT || 3000;

// Configuração do pool de conexões MySQL
const db = mysql.createPool({
  host: process.env.DB_HOST,
  user: process.env.DB_USER,
  password: process.env.DB_PASSWORD,
  database: process.env.DB_NAME
});

// Endpoint para retornar todos os dados
app.get('/data', async (req, res) => {
  try {
    const [rows] = await db.query('SELECT * FROM your_table');
    res.json(rows);
  } catch (error) {
    console.error(error);
    res.status(500).json({ error: 'Erro ao buscar dados do banco.' });
  }
});

// Inicializando o servidor
app.listen(port, () => {
  console.log(`API rodando na porta ${port}`);
});
