import util from "util";

const exec = util.promisify(require("child_process").exec);

export default async function execute(command, commandName) {
  try {
    const { stdout, stderr } = await exec(command,  { maxBuffer: 1024 * 1024 * 10 });

    if (stderr) {
      console.error(`Erro no comando [${commandName}]: ${stderr}`);
      return stdout;
    }
    console.log(`Comando [${commandName}] executado com sucesso.`);
    return stdout;
  } catch (error) {
    console.error(`Erro no comando [${commandName}]: ${error}`);
    throw error;
  }
}