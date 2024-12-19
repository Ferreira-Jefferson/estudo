const express = require('express');
const mysql = require('mysql2');
const bodyParser = require('body-parser'); // Para suportar requisições POST
const motoboysRoutes = require('./motoboys'); // Importar o arquivo motoboys.js
const cors = require('cors');

const app = express();
const port = 3000;

// Middleware
app.use(cors());
app.use(bodyParser.json());

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


// Listar motoboys
app.get('/api/motoboys', async (req, res) => {
    const [rows] = await db.query('SELECT * FROM motoboys');
    res.json(rows);
});

// Adicionar motoboy
app.post('/api/motoboys', async (req, res) => {
    const { nome, codigo, diaria } = req.body;
    try {
        await db.query('INSERT INTO motoboys (nome, codigo, diaria) VALUES (?, ?, ?)', [nome, codigo, diaria]);
        res.status(201).json({ message: 'Motoboy cadastrado com sucesso!' });
    } catch (error) {
        res.status(500).json({ error: 'Erro ao cadastrar motoboy.' });
    }
});

// Consultar diária, pedidos entregues, e total parcial
app.get('/api/motoboys/:id', async (req, res) => {
    const { id } = req.params;
    try {
        const [motoboy] = await db.query('SELECT diaria FROM motoboys WHERE id = ?', [id]);
        const [entregas] = await db.query('SELECT COUNT(*) AS entregues, SUM(taxa) AS total_parcial FROM entregas WHERE motoboy_id = ?', [id]);
        res.json({ ...motoboy[0], ...entregas[0] });
    } catch (error) {
        res.status(500).json({ error: 'Erro ao buscar informações do motoboy.' });
    }
});

// Cadastrar nova entrega
app.post('/api/entregas', async (req, res) => {
    const { codigo_pedido, bairro, problema, taxa, motoboy_id } = req.body;
    try {
        await db.query('INSERT INTO entregas (codigo_pedido, bairro, problema, taxa, motoboy_id) VALUES (?, ?, ?, ?, ?)', [codigo_pedido, bairro, problema, taxa, motoboy_id]);
        res.status(201).json({ message: 'Entrega cadastrada com sucesso!' });
    } catch (error) {
        res.status(500).json({ error: 'Erro ao cadastrar entrega.' });
    }
});

// Consultar bairros e suas taxas
app.get('/api/bairros', async (req, res) => {
    const [rows] = await db.query('SELECT * FROM bairros');
    res.json(rows);
});

app.listen(port, () => {
  console.log(`API rodando em https://degustware.com.br/api`);
});
