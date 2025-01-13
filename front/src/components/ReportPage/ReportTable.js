// components/ReportTable.js
import React from "react";
import ExpandedRow from "./ExpandedRow";

const ReportTable = ({
  dataReport,
  expandedRows,
  handleRowClick,
  dataItensPedido,
}) => {
  return (
    <div className="bg-white shadow-md rounded p-6 mt-10">
      <h2 className="text-2xl font-bold mb-4">Relatório</h2>
      <table className="min-w-full bg-white">
        <thead>
          <tr>
            <th className="py-1 px-1 border-b"></th>
            <th className="py-2 px-4 border-b">Cliente</th>
            <th className="py-2 px-4 border-b">Data</th>
            <th className="py-2 px-4 border-b">Itens</th>
            <th className="py-2 px-4 border-b">Valor Total</th>
          </tr>
        </thead>
        <tbody className="text-center">
          {dataReport.map(
            (
              { ID_PEDIDO,
          NOME_CLIENTE,
          DATA_PEDIDO,
          VALOR_TOTAL,
          totalItens,
          qtdItens},
              index,
            ) => {
              const isExpanded = expandedRows[ID_PEDIDO];
              return (
                <React.Fragment key={ID_PEDIDO}>
                  <tr
                    onClick={() => handleRowClick(ID_PEDIDO)}
                    className={`cursor-pointer ${
                      index % 2 === 0 ? "bg-orange-300" : "bg-yellow-300"
                    }`}
                  >
                    <td className="py-1 px-1 border-b">{index + 1}</td>
                    <td className="py-2 px-4 border-b">{NOME_CLIENTE}</td>
                    <td className="py-2 px-4 border-b">{DATA_PEDIDO}</td>
                    <td className="py-2 px-4 border-b">{qtdItens}</td>
                    <td className="py-2 px-4 border-b">
                      R$ {VALOR_TOTAL}
                      {VALOR_TOTAL != totalItens ? (
                        <sub className="px-1 bg-red-500">
                          {(VALOR_TOTAL - totalItens).toFixed(2)}
                        </sub>
                      ) : (
                        ""
                      )}
                    </td>
                  </tr>
                  {isExpanded && (
                    <ExpandedRow idPedido={ID_PEDIDO} dataItensPedido={dataItensPedido[ID_PEDIDO]} />
                  )}
                </React.Fragment>
              );
            },
          )}
        </tbody>
      </table>
    </div>
  );
};

export default ReportTable;
