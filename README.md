# estudo

## Comandos usados
docker build -t mysql-image -f api/db/Dockerfile .

docker image ls

docker run -d -v $(pwd)/api/db/data:/var/lib/mysql --rm --name mysql-container mysql-image

docker ps

docker exec -i mysql-container mysql -uroot  -pprogramadorabordo < api/db/script.sql

docker exec -it mysql-container /bin/bash
mysql -uroot -pprogramadorabordo
show databases;
use programadorabordo;
select * from products;
exit
exit

docker stop mysql-container

docker inspect mysql-container

docker build -t node-image -f api/Dockerfile .

docker run -d -v $(pwd)/api:/home/node/app -p 9001:9001 --link mysql-container --rm --name node-container node-image

docker ps
docker restart <>
docker kill <>


//Para rodar a api com pm2
cd /api
pm2 start npm --name "api" -- run start

