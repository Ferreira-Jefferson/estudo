import { useEffect, useState } from "react";
import { useAppContext } from "../context/AppContext";

export default function SelectTables() {
  const [options, setOptions] = useState([]);
  const [selectedOption, setSelectedOption] = useState("");
  const { setTableSelected } = useAppContext();

  useEffect(() => {
    const fetchOptions = async () => {
      try {
        const response = await fetch("api/tables");
        const { tables } = await response.json();
        const tableList = tables.split("\n");
        setOptions(tableList);
      } catch (error) {
        console.error("Erro ao carregar opções:", error);
      }
    };

    fetchOptions();
  }, []);

  const handleSelectChange = (event) => {
    setSelectedOption(event.target.value);
  };

  const handleButtonClick = () => {
    setTableSelected(selectedOption);
  };

  return (
    <div className="w-full max-w-xl bg-white p-5 md:p-6 rounded-lg shadow-lg mt-16">
      <h1 className="text-3xl font-bold text-center text-red-900 mb-6">
        Tabelas do banco de dados
      </h1>
      <div className="flex mb-4 relative z-10">
        <select
          id="selectOpcoes"
          className="block w-full grow bg-white border border-gray-300 rounded-md py-2 px-3 mr-2 focus:outline-none focus:border-red-900"
          value={selectedOption}
          onChange={handleSelectChange}
        >
          <option value="">Selecione...</option>
          {options.map((option) => (
            <option key={option} value={option}>
              {option}
            </option>
          ))}
        </select>
        <button
          className="bg-red-900 text-white px-6 py-2 rounded-md hover:bg-red-800 transition-colors duration-300"
          onClick={handleButtonClick}
          disabled={!selectedOption}
        >
          Selecionar
        </button>
      </div>
    </div>
  );
}
