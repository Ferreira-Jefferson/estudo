# Etapa 1: Construção
FROM node:18 

WORKDIR /app

# Copia o restante do código
COPY . .

# Instala as dependências
RUN npm install

# Build da aplicação
RUN npm run Build

# Expondo a porta 3000
EXPOSE 3000

# Comando para iniciar a aplicação
CMD ["npm", "start"]
