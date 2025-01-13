import { selectAll } from "../../core/dbCommands.js";

export default async (req, res) => {
  const { method } = req;
  if (method === "POST") {
    try {
      const data = await selectAll(req.body);
      const rowNames = data.split("\n");
      const columnNames = rowNames.shift();
      res.status(200).json({ columnNames, rowNames });
    } catch (error) {
      res.status(500).json({ message: "Erro desconhecido", error });
    }
  } else {
    res.status(405).json({ message: "Method not allowed" });
  }
};
