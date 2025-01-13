import { format } from "date-fns";
import { ptBR } from "date-fns/locale";

const delay = (time) => new Promise((resolve) => setTimeout(resolve, time));

const dataFormatada = (data) => {
  new Date(data);
  return format(data, "dd/MM/yyyy HH:mm:ss", { locale: ptBR });
};

const createValidDate = (data, hora) => {
  const [dia, mes, ano] = data.split("/");
  const dataISO = `${ano}-${mes}-${dia}T${hora}Z`;
  const dataObj = new Date(dataISO);
  return dataObj.toISOString();
};

export { delay, dataFormatada, createValidDate };
