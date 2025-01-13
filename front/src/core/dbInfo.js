import path from "path";

const containerName = "infra-db-1";

export default  {
  backupFile: path.join("backups", "backup.sql"),
  containerName,
  databaseName: "syscon_bd",
  baseCommand: `docker exec -e MYSQL_PWD=local_password -i ${containerName} mysql -uroot`,
};
