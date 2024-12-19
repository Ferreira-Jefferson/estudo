const express = require('express');
const router = express.Router();
const mysql = require('mysql2/promise');

// MySQL connection
const db = mysql.createPool({
    host: 'localhost',
    user: 'root',
    password: 'password',
    database: 'entregas_motoboy',
});

// Endpoints

// Listar motoboys
router.get('/api/motoboys', async (req, res) => {
    const [rows] = await db.query('SELECT * FROM motoboys');
    res.json(rows);
});

// Adicionar motoboy
router.post('/api/motoboys', async (req, res) => {
    const { nome, codigo, diaria } = req.body;
    try {
        await db.query('INSERT INTO motoboys (nome, codigo, diaria) VALUES (?, ?, ?)', [nome, codigo, diaria]);
        res.status(201).json({ message: 'Motoboy cadastrado com sucesso!' });
    } catch (error) {
        res.status(500).json({ error: 'Erro ao cadastrar motoboy.' });
    }
});

// Consultar diária, pedidos entregues, e total parcial
router.get('/api/motoboys/:id', async (req, res) => {
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
router.post('/api/entregas', async (req, res) => {
    const { codigo_pedido, bairro, problema, taxa, motoboy_id } = req.body;
    try {
        await db.query('INSERT INTO entregas (codigo_pedido, bairro, problema, taxa, motoboy_id) VALUES (?, ?, ?, ?, ?)', [codigo_pedido, bairro, problema, taxa, motoboy_id]);
        res.status(201).json({ message: 'Entrega cadastrada com sucesso!' });
    } catch (error) {
        res.status(500).json({ error: 'Erro ao cadastrar entrega.' });
    }
});

// Consultar bairros e suas taxas
router.get('/api/bairros', async (req, res) => {
    const [rows] = await db.query('SELECT * FROM bairros');
    res.json(rows);
});

// Exporte o router
module.exports = router;