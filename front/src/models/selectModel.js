export default {
  tableName: "",
  cols: [],
  where: "",
  limit: null,
};

const sanitazyCols = (cols) => {
  if (!cols.length) return "*";
  return cols.reduce((value, acc) => acc + "," + value, "").slice(0, -1);
};

export const generateSelect = (model) => {
  if (!model.tableName) throw new Error("Tabela não informada");

  let select = `SELECT ${sanitazyCols(model.cols)} FROM ${model.tableName}`;

  if (model.where) 
    select += ` WHERE ${model.where}`;
  
  if(model.limit)
    select += ` LIMIT ${model.limit}`;
  
  return select + ";"
};
