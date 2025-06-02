import React from "react";
import SuggestionList from "./SuggestionList";

import axios from "axios";
import { saveAs } from "file-saver";

const ReportFilters = ({
  client,
  idClient,
  startDate,
  endDate,
  reportType,
  suggestions,
  showSuggestions,
  handleClient,
  handleSuggestionClick,
  setReportType,
  setStartDate,
  setEndDate,
  handleSearch,
  makeDate,
  dataReport,
}) => {
  const handleExcel = async () => {
    try {
      const response = await axios.post("/api/generateExcel", dataReport, {
        responseType: "arraybuffer",
      });

      const blob = new Blob([response.data], {
        type: "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",
      });
      saveAs(blob, "planilha.xlsx");
    } catch (error) {
      console.error("Erro ao enviar dados:", error);
    }
  };

  return (
    <div className="bg-white shadow-md rounded p-6">
      <h2 className="text-2xl font-bold mb-4">Gerar de Relatório</h2>
      <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-4">
        <div className="flex flex-col md:flex-row space-y-4 md:space-y-0 md:space-x-4">
          <div className="flex-1">
            <label className="block text-gray-700">Tipo de Relatório:</label>
            <select
              value={reportType}
              onChange={(e) => setReportType(e.target.value)}
              className="mt-1 p-2 pr-10 border rounded w-full"
            >
              <option value="">Selecione o tipo ...</option>
              <option value="vendas">Vendas</option>
              <option value="produto">Produto</option>
              <option value="Item">Item</option>
              <option value="financeiro">Financeiro</option>
            </select>
          </div>
          <div className="relative flex-1">
            <label className="block text-gray-700">Pesquisar:</label>
            <input
              type="text"
              value={client}
              data-id={idClient}
              onChange={handleClient}
              className="w-full mt-1 p-2 border rounded"
            />
            <SuggestionList
              suggestions={suggestions}
              showSuggestions={showSuggestions}
              handleSuggestionClick={handleSuggestionClick}
            />
          </div>
        </div>
        <div className="flex flex-col md:flex-row space-y-4 md:space-y-0 md:space-x-4">
          <div className="flex-1">
            <label className="block text-gray-700">Data Inicial:</label>
            <input
              type="date"
              value={startDate}
              onChange={(e) => setStartDate(makeDate(e.target.value))}
              className="w-full mt-1 p-2 border rounded"
            />
          </div>
          <div className="flex-1">
            <label className="block text-gray-700">Data Final:</label>
            <input
              type="date"
              value={endDate}
              onChange={(e) => setEndDate(makeDate(e.target.value))}
              className="w-full mt-1 p-2 border rounded"
            />
          </div>
        </div>
      </div>
      <div className="mt-4">
        <button
          onClick={handleSearch}
          className="bg-blue-500 text-white py-2 px-4 rounded"
        >
          Aplicar Filtros
        </button>
        <button
          onClick={handleExcel}
          className="bg-green-500 ml-10 text-white py-2 px-4 rounded"
        >
          Gerar Excel
        </button>
      </div>
    </div>
  );
};

export default ReportFilters;
