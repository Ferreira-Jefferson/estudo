const express = require('express');
const app = express();
const port = 80; // Porta padrão para HTTP

app.get('/', (req, res) => {
    res.send('<h1>Bem-vindo ao Degustware!</h1><p>Tudo ok por aqui!</p>');
});

app.listen(port, () => {
    console.log(`Servidor rodando em http://www.degustware.com.br:${port}`);
});
