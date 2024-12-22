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

# Copia apenas os arquivos necessários do estágio de construção
COPY ./app/package.json ./package.json
COPY ./app/package-lock.json ./package-lock.json
COPY ./app/node_modules ./node_modules
COPY ./app/.next ./.next
COPY ./app/next.config.js ./next.config.js
COPY ./app/public ./public

# Expondo a porta 3000
EXPOSE 3000

# Comando para iniciar a aplicação
CMD ["npm", "start"]
