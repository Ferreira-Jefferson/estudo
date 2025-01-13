import path from "path";
import main from "../../core/restore";

export default async (req, res) => {
  const { method } = req;
  if (method === "GET") {
    try {
      const fileName = "backup.sql";
      const backupPath = path.join(
        process.cwd(),
        "public",
        "backups",
        fileName,
      );
      await main(backupPath);
      res.status(200).json({ message: "Restauração concluída com sucesso" });
    } catch (error) {
      res.status(500).json({ message: "Erro na restauração do backup", error });
    }
  } else {
    res.status(405).json({ message: "Method not allowed" });
  }
};
