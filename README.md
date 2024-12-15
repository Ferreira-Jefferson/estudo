# estudo

## Comandos usados
docker build -t mysql-image -f api/db/Dockerfile .

docker image ls

docker run -d --rm --name mysql-container mysql-image

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

docker run -d -v $(pwd)/api/db/data:/var/lib/mysql --rm --name mysql-container mysql-image

docker inspect mysql-container