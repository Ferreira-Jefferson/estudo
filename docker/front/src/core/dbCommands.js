import execute from "./dbUtils";
import dbInfo from "./dbInfo";

const useDb = "USE syscon_bd;";

async function selectAll(selectCommand) {
  const command = `${dbInfo.baseCommand} -e "${useDb} ${selectCommand}"`;
  const commandName = "selectAll";
  const data = await execute(command, commandName);
  return data;
}

export { selectAll };
