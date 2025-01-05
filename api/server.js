const express = require("express")
const mysql = require("mysql2/promise")
const bodyParser = require("body-parser") // Para suportar requisições POST
const cors = require("cors")

const app = express()
const port = 3000

// Middleware cors
app.use(cors())

// Middleware para parsear JSON
app.use(bodyParser.json())

const db = mysql.createPool({
  host: process.env.MYSQL_HOST || "db",
  user: process.env.MYSQL_USER || "user",
  password: process.env.MYSQL_PASSWORD || "userpassword",
  database: process.env.MYSQL_DATABASE || "degustware",
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0,
})

// Teste de conexão (opcional)
;(async () => {
  try {
    await db.getConnection()
    console.log("Conectado ao banco de dados MySQL com sucesso!")
  } catch (error) {
    console.error("Erro ao conectar ao banco de dados:", error.message)
  }
})()

// Endpoint para listar produtos
app.get("/api", async (req, res) => {
  try {
    const data = {
      status: "Conectado ao banco de dados MySQL com sucesso!",
      motoboys: "https://degustware.com/api/motoboys",
      motoboys_id: "https://degustware.com/api/motoboys/ID",
      bairros: "https://degustware.com/api/bairros",
      bairros_id_motoboy: "https://degustware.com/api/bairros/ID",
      entregas: "https://degustware.com/api/entregas",
      entregas_id_motoboy: "https://degustware.com/api/entregas/ID_MOTOBOY",
    }
    res.json(data)
  } catch (err) {
    res.status(500).json({ error: "Erro ao listar produtos." })
  }
})

// Listar motoboys
app.get("/api/motoboys", async (req, res) => {
  const [rows] = await db.query("SELECT * FROM motoboys")
  res.json(rows)
})

// Adicionar motoboy
app.post("/api/motoboys", async (req, res) => {
  const { nome, codigo, diaria } = req.body
  try {
    await db.query(
      "INSERT INTO motoboys (nome, codigo, diaria) VALUES (?, ?, ?)",
      [nome, codigo, diaria]
    )
    res.status(201).json({ message: "Motoboy cadastrado com sucesso!" })
  } catch (error) {
    res.status(500).json({ error: "Erro ao cadastrar motoboy." })
  }
})

// Consultar diária, pedidos entregues, e total parcial
app.get("/api/motoboys/:id", async (req, res) => {
  const { id } = req.params
  try {
    const [motoboy] = await db.query(
      "SELECT diaria FROM motoboys WHERE id = ?",
      [id]
    )
    const [entregas] = await db.query(
      "SELECT COUNT(*) AS entregues, SUM(taxa) AS total_parcial FROM entregas WHERE motoboy_id = ?",
      [id]
    )
    res.json({ ...motoboy[0], ...entregas[0] })
  } catch (error) {
    res.status(500).json({ error: "Erro ao buscar informações do motoboy." })
  }
})

app.get("/api/entregas", async (req, res) => {
  try {
    const [entregas] = await db.query(
      `
    SELECT 
      entregas.id,
      entregas.codigo_pedido,
      entregas.problema,
      entregas.taxa,
      motoboys.nome AS motoboy_nome,
      bairros.nome AS bairro_nome, 
      entregas.data_registro
    FROM entregas
    JOIN bairros ON entregas.bairro_id = bairros.id
    JOIN motoboys ON entregas.motoboy_id = motoboys.id
    `
    )
    res.json(entregas)
  } catch (error) {
    console.error("Erro ao buscar entregas:", error)
    res.status(500).json({ error: "Erro interno no servidor" })
  }
})

app.get("/api/entregas/:id_motoboy", async (req, res) => {
  const { id_motoboy } = req.params

  try {
    const [entregas] = await db.query(
      `
    SELECT 
      entregas.id,
      entregas.codigo_pedido,
      entregas.problema,
      entregas.taxa,
      entregas.motoboy_id,
      bairros.nome AS bairro_nome, 
      entregas.data_registro
    FROM entregas
    JOIN bairros ON entregas.bairro_id = bairros.id
    WHERE entregas.motoboy_id = ?
    AND DATE(entregas.data_registro) = CURDATE()
    `,
      [id_motoboy]
    )
    res.json(entregas)
  } catch (error) {
    console.error("Erro ao buscar entregas:", error)
    res.status(500).json({ error: "Erro interno no servidor" })
  }
})

// Consultar bairros dinamicamente
app.get("/api/bairros", async (req, res) => {
  const { query } = req.query

  try {
    if (!query) {
      const [rows] = await db.query("SELECT * FROM bairros")
      res.json(rows)
    } else {
      const [rows] = await db.query(
        "SELECT * FROM bairros WHERE nome LIKE ? LIMIT 10",
        [`%${query}%`]
      )
      res.json(rows)
    }
  } catch (error) {
    console.error("Erro ao consultar bairros:", error)
    res.status(500).json({ error: "Erro interno no servidor" })
  }
})

app.get("/api/bairros/:id", async (req, res) => {
  const { id } = req.params
  try {
    const [bairro] = await db.query("SELECT * FROM bairros WHERE id = ?", [id])
    res.json({ ...bairro[0] })
  } catch (error) {
    res.status(500).json({ error: "Erro ao buscar informações do bairro." })
  }
})

// Cadastrar nova entrega
app.post("/api/entregas", async (req, res) => {
  const { codigo_pedido, bairro_id, problema, taxa, motoboy_id } = req.body
  try {
    await db.query(
      "INSERT INTO entregas (codigo_pedido, problema, taxa, bairro_id, motoboy_id) VALUES (?, ?, ?, ?, ?)",
      [codigo_pedido, problema, taxa, bairro_id, motoboy_id]
    )
    res.status(201).json({ message: "Entrega cadastrada com sucesso!" })
  } catch (error) {
    res.status(500).json({ error: "Erro ao cadastrar entrega." })
  }
})

app.listen(port, () => {
  console.log(`API rodando em https://degustware.com.br/api`)
})
