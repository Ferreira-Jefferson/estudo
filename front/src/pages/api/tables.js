import { showTables } from "../../core/restore.js";

export default async (req, res) => {
  const { method } = req;
  if (method === "GET") {
    try {
      const tables = await showTables();
      res.status(200).json({ tables });
    } catch (error) {
      res.status(500).json({ message: "Erro na restauração do backup", error });
    }
  } else {
    res.status(405).json({ message: "Method not allowed" });
  }
};
