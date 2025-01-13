// components/ExpandedRow.js
import React from "react";

const ExpandedRow = ({ idPedido, dataItensPedido }) => {
  return (
    <tr>
      <td colSpan="5">
        <div className="overflow-x-auto">
          <table className="min-w-full table-auto border">
            <thead className="text-gray-700">
              <tr>
                <th className="py-2 px-4 border-b">Qtd</th>
                <th className="py-2 px-4 border-b">Produto</th>
                <th className="py-2 px-4 border-b">Valor Un.</th>
                <th className="py-2 px-4 border-b">Total</th>
                <th className="py-2 px-4 border-b">Descrição</th>
              </tr>
            </thead>
            <tbody>
              {dataItensPedido.map((item, index) => (
                <tr
                  key={item.idItem}
                  className={index % 2 === 0 ? "bg-gray-100" : "bg-gray-50"}
                >
                  <td className="px-4 py-2 border">{Math.round(item.qtd)}</td>
                  <td className="px-4 py-2 border">{item.descricao}</td>
                  <td className="px-4 py-2 border">
                    {`R$ ${(item.total / item.qtd).toString().replace('.', ',')}`}
                  </td>
                  <td className="px-4 py-2 border">
                    {`R$ ${item.total.replace(".", ",")}`}
                  </td>
                  <td className="px-4 py-2 border">
                    {item.obs.replaceAll("\\n", " ")}
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      </td>
    </tr>
  );
};

export default ExpandedRow;
