import ExcelJS from "exceljs";
import { createValidDate } from "../../utils";

export default async function handler(req, res) {
  const dataReport = req.body;
  const workbook = new ExcelJS.Workbook();
  const sheet = workbook.addWorksheet("Planilha");

  const dataObj = dataReport.reduce((acc, item) => {
    let qtd_M = 0;
    let qtd_P = 0;
    let valorTotal_M = 0;
    let valorTotal_P = 0;
    let qtd_outros = 0;
    let valorTotal_outros = 0;

    const [data, hora] = item.DATA_PEDIDO.split(" ");

    if (!acc[data]) {
      acc[data] = [];
    }

    let ehJanta = false;
    for (const { descricao, qtd, total, obs } of item.itens) {
      const qtdInt = parseInt(qtd);
      const totalFloat = parseFloat(total);
      if (descricao.includes("MARMITEX OBRA")) {
        qtd_M += qtdInt;
        valorTotal_M += totalFloat;
      } else if (descricao.includes('MARMITEX BARATO DO DIA "P"')) {
        qtd_P += qtdInt;
        valorTotal_P += totalFloat;
      } else {
        qtd_outros += qtdInt;
        valorTotal_outros += totalFloat;
      }
      ehJanta = obs.toUpperCase().includes("JANTA");
    }

    ehJanta =
      ehJanta ||
      createValidDate(data, hora) >= createValidDate(data, "13:30:00");

    const pedido = {
      data,
      hora,
      qtdTotalItens: item.qtdItens,
      valorTotalItens: item.totalItens,
      valorTotalPedido: item.VALOR_TOTAL,
      qtd_M,
      qtd_P,
      valorTotal_M,
      valorTotal_P,
      qtd_outros,
      valorTotal_outros,
      ehJanta,
      taxaEntrega: item.VALOR_TOTAL - item.totalItens,
    };

    const definirNome = (nomesNaData) => {
      let nome = undefined;
      const nomeIsJanta = () => {
        const nomeJanta = item.NOME_CLIENTE + " " + "(JANTA)";
        if (nomesNaData.includes(nomeJanta)) {
          nome = nomeJanta + " " + hora;
        } else {
          nome = nomeJanta;
        }
      };

      const nomeEntregaExtra = () => {
        const nomeExtra = item.NOME_CLIENTE + " " + "(TAXA EXTRA)";
        if (nomesNaData.includes(nomeExtra)) {
          nome = nomeExtra + " " + hora;
        } else {
          nome = nomeExtra;
        }
      };

      if (!nomesNaData.includes(item.NOME_CLIENTE)) {
        nome = item.NOME_CLIENTE;
      } else {
        if (ehJanta) {
          nomeIsJanta();
        } else if (pedido.taxaEntrega) {
          nomeEntregaExtra();
        } else {
          nome = item.NOME_CLIENTE + " " + hora;
        }
      }
      return nome;
    };

    const nomesNaData = acc[data].map(({ nome }) => nome);
    const nome = definirNome(nomesNaData);
    pedido["nome"] = nome;
    acc[data].push(pedido);

    return acc;
  }, {});

  const datas = Object.keys(dataObj);

  // Adicionando cabeçalhos
  const headers = ["NOME", ...datas];
  sheet.addRow(headers);

  let todosOsNomes = [];
  for (let item of Object.values(dataObj))
    todosOsNomes = new Set([...todosOsNomes, ...item.map(({ nome }) => nome)]);

  const criaArrayRow = (nomeBase, len, ext = "") => {
    const nome = nomeBase + (ext ? `[${ext}]` : "");
    const arrayRow = new Array(len + 1).fill(0);
    arrayRow[0] = nome;
    return arrayRow;
  };

  const todosOsNomesOrdenados = [...todosOsNomes].sort();

  const criaArrayRowComTodosOsNomesPossiveis = () => {
    const dados = [];
    for (let currentNome of todosOsNomesOrdenados) {
      const dadosObj = {};
      for (let valores of Object.values(dataObj)) {
        for (let valor of valores) {
          const { nome, qtd_M, qtd_P, qtd_outros } = valor;
          if (currentNome === nome) {
            if (qtd_M) {
              const arrayRow = criaArrayRow(currentNome, datas.length);
              dadosObj[arrayRow[0]] = arrayRow;
            }
            if (qtd_P) {
              const arrayRow = criaArrayRow(currentNome, datas.length, "P");
              dadosObj[arrayRow[0]] = arrayRow;
            }
            if (qtd_outros) {
              const arrayRow = criaArrayRow(
                currentNome,
                datas.length,
                "OUTROS",
              );
              dadosObj[arrayRow[0]] = arrayRow;
            }
          }
        }
      }

      dados.push(dadosObj);
    }
    const dadosUnificados = dados.reduce((acc, dado) => {
      Object.entries(dado).forEach(([key, value]) => {
        acc[key] = value;
      });
      return acc;
    }, {});

    for (let ultimosNomes of [
      "Taxa de ent. extra",
      "Taxa de ent. extra (Escritório)",
      "QuanT. Total (G)",
      "QuanT. Total (P)",
      "QuanT. Total (OUTROS)",
      "Valor total",
    ]) {
      const arrayRow = criaArrayRow(ultimosNomes, datas.length);
      dadosUnificados[arrayRow[0]] = arrayRow;
    }
    return dadosUnificados;
  };

  const popularRows = (dados) => {
    for (let [data, valores] of Object.entries(dataObj)) {
      const index = datas.indexOf(data) + 1;
      for (let valor of valores) {
        const {
          nome,
          qtd_M,
          qtd_P,
          qtd_outros,
          valorTotal_outros,
          taxaEntrega,
        } = valor;
        if (qtd_M) {
          dados[nome][index] += qtd_M;
          dados["QuanT. Total (G)"][index] += qtd_M;
          dados["Valor total"][index] += qtd_M * 15;
        }
        if (qtd_P) {
          dados[`${nome}[P]`][index] += qtd_P;
          dados["QuanT. Total (P)"][index] += qtd_P;
          dados["Valor total"][index] += qtd_P * 13;
        }
        if (qtd_outros) {
          dados[`${nome}[OUTROS]`][index] += qtd_outros;
          dados["QuanT. Total  (OUTROS)"][index] += qtd_outros;
          dados["Valor total"][index] += qtd_outros * valorTotal_outros;
        }
        if (taxaEntrega) {
          if (nome.includes("Escrit")) {
            dados["Taxa de ent. extra (Escritório)"][index] += 1;
            dados["Valor total"][index] += 5;
          } else {
            dados["Taxa de ent. extra"][index] += 1;
            dados["Valor total"][index] += 9;
          }
        }
      }
    }
    dados["Valor total"] = dados["Valor total"].map(value => `R$ ${String(value).replace(".", ",")}`)
    return Object.values(dados);
  };

  const dados = criaArrayRowComTodosOsNomesPossiveis();
  const rows = popularRows(dados);

  // Adicionando dados
  rows.forEach((row) => {
    sheet.addRow(row);
  });

  // Estilizando a planilha
  sheet.getRow(1).font = { bold: true };
  sheet.getRow(1).alignment = { horizontal: "center" };

  // Valores zero ficam na cor branca
  sheet.eachRow((row, rowNumber) => {
    row.eachCell((cell, colNumber) => {
      if (cell.value === 0) {
        cell.font = { color: { argb: "FFFFFFFF" } }; // Branco
      }
    });
  });

  const buffer = await workbook.xlsx.writeBuffer();
  res.setHeader(
    "Content-Type",
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",
  );
  res.setHeader("Content-Disposition", "attachment; filename=planilha.xlsx");
  res.send(buffer);
}
