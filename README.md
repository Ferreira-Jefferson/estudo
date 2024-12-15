# estudo

## Comandos usados
docker build -t mysql-image -f api/db/Dockerfile .

docker image ls

docker run -d --rm --name mysql-container mysql-image

docker ps

docker exec -i mysql-container mysql -uroot  -pprogramadorabordo < api/db/script.sql