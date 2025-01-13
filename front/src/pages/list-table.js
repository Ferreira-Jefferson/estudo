import SelectTables from "../components/SelectTables";
import DynamicTable from "../components/DynamicTable";
import { useAppContext } from "../context/AppContext";

export default function listTable() {
  const { tableSelected } = useAppContext();
  return (
    <div className="flex flex-col items-center">
      <SelectTables />
      {tableSelected && <DynamicTable />}
    </div>
  );
}
