import { useAppContext } from "../../context/AppContext";

export default function NavigationButtons() {
  const { navigateToNewPage } = useAppContext();

  return (
    <div className="flex justify-around">
      <button
        className="mt-4 mg-auto bg-red-900 text-white px-6 py-3 rounded-md hover:bg-red-800 transition-colors duration-300"
        type="button"
        onClick={() => navigateToNewPage("/restore-file")}
      >
        Restaurar
      </button>
      <button
        className="mt-4 mg-auto bg-yellow-700 px-6 py-3 rounded-md hover:bg-yellow-900 transition-colors duration-300"
        type="button"
        onClick={() => navigateToNewPage("/list-table")}
      >
        Analisar DB
      </button>
      <button
        className="mt-4 mg-auto  bg-red-900  text-white px-6 py-3 rounded-md hover:bg-red-800  transition-colors duration-300"
        type="button"
        onClick={() => navigateToNewPage("/reports")}
      >
        Relatórios
      </button>
    </div>
  );
}
