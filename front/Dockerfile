# Etapa 1: Construção
FROM node:18 

WORKDIR /app

# Copia os arquivos de dependências
COPY package.json package-lock.json ./

# Instala as dependências
RUN npm install

# Copia o restante do código
COPY . .

# Build da aplicação
RUN npm run build

# Expondo a porta 3030
EXPOSE 3030

# Comando para iniciar a aplicação
CMD ["npm", "start"]
