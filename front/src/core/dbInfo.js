import path from "path";

const containerName = "mysql_db";

export default  {
  backupFile: path.join("backups", "backup.sql"),
  containerName,
  databaseName: "syscon_bd",
  baseCommand: `docker exec -e MYSQL_PWD=rootpassword -i ${containerName} mysql -uroot`,
};
