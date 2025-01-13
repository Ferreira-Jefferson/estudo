import React, { useState } from "react";
import selectModel, { generateSelect } from "../../models/selectModel";


import { dataFormatada } from "../../utils";
import ReportTable from "./ReportTable";
import ReportFilters from "./ReportFilters";

const ReportPage = () => {
  const [client, setClient] = useState("");
  const [idClient, setIdClient] = useState(null);
  const [startDate, setStartDate] = useState("");
  const [endDate, setEndDate] = useState("");
  const [reportType, setReportType] = useState("vendas");
  const [suggestions, setSuggestions] = useState([]);
  const [showSuggestions, setShowSuggestions] = useState(false);
  const [dataReport, setDataReport] = useState([]);
  const [expandedRows, setExpandedRows] = useState({});
  const [dataItensPedido, setDataItensPedido] = useState({});

  const fetchClient = async () => {
    try {
      selectModel.tableName = "tbl_cliente";
      selectModel.cols = ["ID_CLIENTE", "NOME"];
      selectModel.where = `NOME LIKE '%${client}%'`;
      const selectCommand = generateSelect(selectModel);

      const response = await fetch("/api/tableData", {
        method: "POST",
        body: selectCommand,
      });
      const { rowNames } = await response.json();
      return rowNames;
    } catch (error) {
      console.error("Erro ao carregar opções:", error);
    }
  };

  const makeDate = (date) => {
    if (date === "") {
      const today = new Date();
      const year = today.getFullYear();
      const month = String(today.getMonth() + 1).padStart(2, "0");
      const day = String(today.getDate()).padStart(2, "0");
      return `${year}-${month}-${day}`;
    }

    return date;
  };

  const handleClient = async (e) => {
    const value = e.target.value;
    setClient(value);
    setIdClient(null);
    if (value.length > 2) {
      const results = await fetchClient();
      setSuggestions(results);
      setShowSuggestions(true);
    } else {
      setShowSuggestions(false);
    }
  };

  const handleSuggestionClick = (suggestion) => {
    const [suggestionClient, suggestionId] = suggestion.split("\t");
    setClient(suggestionClient);
    setIdClient(suggestionId);
    setShowSuggestions(false);
  };

  const getPedidosWithItems = () => {
    let allPedidos = false;
    let selectCommand = `SELECT 
      p.ID_PEDIDO,
      p.NOME_CLIENTE,
      p.DATA_PEDIDO,
      p.VALOR_TOTAL,
      p.ID_CLIENTE,
      i.id_item,
      i.descricao,
      i.categoria,
      i.obs,
      i.qtd,
      i.total,
      i.codigo
    FROM tbl_pedido p
    LEFT JOIN item_pedido i ON p.ID_PEDIDO = i.id_pedido`;

    if (idClient) {
      selectCommand += ` WHERE p.ID_CLIENTE = ${idClient}`;
    } else if (client.trim()) {
      selectCommand += ` WHERE p.NOME_CLIENTE LIKE '%${client}%'`;
    } else {
      allPedidos = true;
    }

    const isValidEndDate = new Date(endDate) > new Date(startDate);

    if (startDate) {
      selectCommand += ` ${allPedidos ? "WHERE" : "AND"} DATE(p.DATA_PEDIDO) ${isValidEndDate ? ">=" : "="} '${startDate}'`;
    }

    if (endDate && isValidEndDate) {
      selectCommand += ` AND DATE(p.DATA_PEDIDO) <= '${endDate}'`;
    }

    if (!client && !startDate) {
      selectCommand += ` LIMIT 100`;
    }

    selectCommand += ";";

    return selectCommand;
  };

  const getVendas = async () => {
    const selectCommand = getPedidosWithItems();

    const response = await fetch("/api/tableData", {
      method: "POST",
      body: selectCommand,
    });

    const { rowNames, columnNames } = await response.json();
    rowNames.pop();

    const pedidosMap = {};
    for (const item of rowNames) {
      const [
        ID_PEDIDO,
        NOME_CLIENTE,
        DATA_PEDIDO,
        VALOR_TOTAL,
        ID_CLIENTE,
        idItem,
        descricao,
        categoria,
        obs,
        qtd,
        total,
        codigo,
      ] = item.split("\t");

      if (!pedidosMap[ID_PEDIDO]) {
        pedidosMap[ID_PEDIDO] = {
          ID_PEDIDO,
          NOME_CLIENTE,
          DATA_PEDIDO: dataFormatada(DATA_PEDIDO),
          VALOR_TOTAL,
          ID_CLIENTE,
          itens: [],
          totalItens: 0,
          qtdItens: 0,
        };
      }

      if (idItem) {
        pedidosMap[ID_PEDIDO].itens.push({
          idItem,
          descricao,
          categoria,
          obs,
          qtd,
          total,
          codigo,
        });
        pedidosMap[ID_PEDIDO].qtdItens += parseInt(qtd);
        pedidosMap[ID_PEDIDO].totalItens += parseFloat(total);
      }
    }

    const pedidosMapArray = Object.values(pedidosMap);

    setDataReport(pedidosMapArray);
  };

  const fetchData = async () => {
    try {
      if (reportType == "vendas") getVendas();
      if (reportType == "item") getItem();
    } catch (error) {
      console.error("Erro ao carregar dados:", error);
    }
  };

  const ativarBotao = (e, ativar) => {
    if (ativar) {
      e.target.style.cursor = "default"; // Cursor padrão
      e.target.style.opacity = "1"; // Opacidade padrão
      e.target.disabled = false;
    } else {
      e.target.disabled = true; // Desativa o botão
      e.target.style.cursor = "not-allowed"; // Cursor indicando que não é clicável
      e.target.style.opacity = "0.6"; // Transparência para dar aparência esmaecida
    }
  };

  const handleSearch = async (e) => {
    setShowSuggestions(false);
    ativarBotao(e, false);
    await fetchData();
    ativarBotao(e, true);
  };

  const getItensPedido = (idPedido, campos = null) => {
    const camposDefault =
      "id_item, descricao, categoria, obs, qtd, total, id_pedido, codigo";
    let selectCommand = `SELECT 
  ${campos ? campos : camposDefault}
    FROM item_pedido
    WHERE id_pedido = ${idPedido}`;

    return selectCommand;
  };

  const fetchItensPedido = async (idPedido, campos = null) => {
    try {
      const selectCommand = getItensPedido(idPedido, campos);

      const response = await fetch("/api/tableData", {
        method: "POST",
        body: selectCommand,
      });
      const { rowNames, columnNames } = await response.json();
      return rowNames;
    } catch (error) {
      console.error("Erro ao carregar opções:", error);
    }
  };

  const handleRowClick = async (idPedido) => {
    const getDataInFirstExpanded = !dataItensPedido[idPedido];
    if (getDataInFirstExpanded) {
      const data = await fetchItensPedido(idPedido);
      const dataSanityzed = data
        .map((value) => {
          const [
            idItem,
            descricao,
            categoria,
            obs,
            qtd,
            total,
            id_pedido,
            codigo,
          ] = value.split("\t");

          return {
            idItem,
            descricao,
            categoria,
            obs,
            qtd,
            total,
            id_pedido,
            codigo,
          };
        })
        .filter((value) => value.idItem);

      setDataItensPedido((prev) => ({
        ...prev,
        [idPedido]: dataSanityzed,
      }));
    }

    setExpandedRows((prev) => ({
      ...prev,
      [idPedido]: !prev[idPedido],
    }));
  };



  return (
    <div className="container mx-auto mt-10">
      <ReportFilters
        client={client}
        idClient={idClient}
        startDate={startDate}
        endDate={endDate}
        reportType={reportType}
        suggestions={suggestions}
        showSuggestions={showSuggestions}
        handleClient={handleClient}
        handleSuggestionClick={handleSuggestionClick}
        setReportType={setReportType}
        setStartDate={setStartDate}
        setEndDate={setEndDate}
        handleSearch={handleSearch}
        makeDate={makeDate}
        dataReport={dataReport}
      />

      <ReportTable
        dataReport={dataReport}
        expandedRows={expandedRows}
        handleRowClick={handleRowClick}
        dataItensPedido={dataItensPedido}
      />
    </div>
  );
};

export default ReportPage;
