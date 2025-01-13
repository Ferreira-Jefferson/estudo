import dbInfo from "./dbInfo";
import execute from "./dbUtils"

async function checkDatabaseExists() {
  const command = `${dbInfo.baseCommand} -e "SHOW DATABASES LIKE '${dbInfo.databaseName}';"`;
  const commandName = "checkDatabaseExists";
  const db = await execute(command, commandName);
  return db == true;
}

async function copyBackupToContainer() {
  const command = `docker cp ${dbInfo.backupFile} ${dbInfo.containerName}:/backup.sql`;
  const commandName = "copyBackupToContainer";
  await execute(command, commandName);
}

async function createDatabase() {
  const command = `${dbInfo.baseCommand} -e "CREATE DATABASE ${dbInfo.databaseName};"`;
  const commandName = "createDatabase";
  await execute(command, commandName);
}

async function restoreDatabase(backupFile) {
  const command = `${dbInfo.baseCommand} ${dbInfo.databaseName} < ${backupFile}`;
  const commandName = "restoreDatabase";
  console.log("Iniciando restauração do backup, aguarde...");
  await execute(command, commandName);
}

async function listDatabases() {
  const command = `${dbInfo.baseCommand} -e "SHOW DATABASES;"`;
  const commandName = "listDatabases";
  await execute(command, commandName).then(console.log);
}

async function deleteDatabase() {
  const command = `${dbInfo.baseCommand} -e "DROP DATABASE IF EXISTS ${dbInfo.databaseName};"`;
  const commandName = "deleteDatabase";
  await execute(command, commandName);
}

async function selectDbToUse() {
  const command = `${dbInfo.baseCommand} -e "USE ${dbInfo.databaseName};"`;
  const commandName = "selectDbToUse";
  await execute(command, commandName);
}

async function showTables() {
  const command = `${dbInfo.baseCommand} -e "SHOW TABLES IN ${dbInfo.databaseName};"`;
  const commandName = "showTables";
  return await execute(command, commandName);
}

export default async function main(backupFile) {
  try {
    await deleteDatabase();
    await createDatabase();
    await restoreDatabase(backupFile);
    await selectDbToUse();
    console.log("Processo concluído com sucesso.");
  } catch (error) {
    console.error(`Erro durante o processo: ${error}`);
  }
}

// main(backupFile)
export {
  checkDatabaseExists,
  copyBackupToContainer,
  createDatabase,
  restoreDatabase,
  listDatabases,
  deleteDatabase,
  selectDbToUse,
  showTables,
};
