# Use Node.js como imagem base
FROM node:18

# Defina o diretório de trabalho
WORKDIR /app

# Copie os arquivos do projeto
COPY . .

# Instale as dependências
RUN npm install

# Copie o script wait-for-it.sh
COPY wait-for-it.sh /wait-for-it.sh

# Torne o script executável
RUN chmod +x /wait-for-it.sh

# Execute o script wait-for-it e depois inicie a API
CMD /wait-for-it.sh $MYSQL_HOST:3306 -- npm start
