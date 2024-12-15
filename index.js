const express = require('express');
const app = express();
const port = 80; // Porta padrão para HTTP

app.get('/', (req, res) => {
    res.send('<h1>Bem-vindo ao meu servidor!</h1><p>Servidor funcionando!</p>');
});

app.listen(port, () => {
    console.log(`Servidor rodando em http://www.degustware.com.br:${port}`);
});
