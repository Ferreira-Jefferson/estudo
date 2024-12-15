# Usar a imagem do Node.js
FROM node:18-alpine

# Definir diretório de trabalho
WORKDIR /app

# Copiar arquivos de configuração
COPY package*.json ./

# Instalar dependências
RUN npm install

# Copiar o restante dos arquivos da API
COPY . .

# Expor a porta 3000
EXPOSE 3000

# Comando para iniciar a API
CMD ["node", "server.js"]
