import React, { useState, useEffect } from "react";
import { useAppContext } from "../context/AppContext";

import selectModel, {generateSelect} from "../models/selectModel";

const DynamicTable = () => {
  const { tableSelected } = useAppContext();
  const [columns, setColumns] = useState([]);
  const [rows, setRows] = useState([]);

  useEffect(() => {
    const fetchData = async () => {
      try {
        selectModel.tableName = tableSelected;
        selectModel.limit = 100;
        selectModel.where = (tableSelected == 'item_pedido') ? "id_item > 81000" : null
        const selectCommand = generateSelect(selectModel);
        
        const response = await fetch("/api/tableData", {
          method: "POST",
          body: selectCommand,
        });
        const { columnNames, rowNames } = await response.json();
        const columns = columnNames.split("\t");
        const rows = rowNames;
        setColumns(columns);
        setRows(rows);
      } catch (error) {
        console.error("Erro ao carregar opções:", error);
      }
    };

    fetchData();
  }, [tableSelected]);

  return (
    <div className="mt-5 bg-white rounded-lg shadow-md overflow-x-auto p-4">
      <div className="w-full max-w-5xl mx-auto overflow-x-auto">
        <table className="w-full table-auto">
          <thead>
            <tr className="bg-gray-200">
              {columns.map((column) => (
                <th
                  key={column}
                  className="py-2 px-4 text-left font-semibold whitespace-nowrap"
                >
                  {column}
                </th>
              ))}
            </tr>
          </thead>
          <tbody>
            {rows.map((row, index) => (
              <tr key={index} className="border-t">
                {row.split("\t").map((subRow, subIndex) => (
                  <td key={subIndex} className="py-2 px-4 whitespace-nowrap">
                    {subRow}
                  </td>
                ))}
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </div>
  );
};

export default DynamicTable;
