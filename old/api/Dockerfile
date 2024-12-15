FROM node:12.22.9

# Defina o diretório de trabalho no contêiner
WORKDIR /home/node/app

# Copie os arquivos de dependências do projeto
COPY package*.json ./

# Instale as dependências do projeto
RUN npm install

# Copie todos os arquivos do projeto para o diretório de trabalho
COPY . .

# Exponha a porta 9001
EXPOSE 9001

# Comando para iniciar a aplicação
CMD ["npm", "start"]
