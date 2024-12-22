# Etapa 1: Construção
FROM node:18-alpine AS builder

WORKDIR /app

# Copia os arquivos de dependências
COPY package.json package-lock.json ./

# Instala as dependências
RUN npm install

# Copia o restante do código
COPY . .

# Build da aplicação
RUN npm run build

# Etapa 2: Execução
FROM node:18-alpine

WORKDIR /app

# Instala o Node.js e o npm
RUN apk add --no-cache nodejs npm

# Copia apenas os arquivos necessários do estágio de construção
COPY --from=builder /app/package.json ./
COPY --from=builder /app/package-lock.json ./
COPY --from=builder /app/node_modules ./node_modules
COPY --from=builder /app/.next ./.next
COPY --from=builder /app/next.config.js ./
COPY --from=builder /app/public ./public

# Expondo a porta 3000
EXPOSE 3000

# Comando para iniciar a aplicação
CMD ["npm", "start"]
