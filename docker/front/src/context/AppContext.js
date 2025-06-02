// context/AppContext.js
import { useRouter } from "next/router";
import { createContext, useState, useContext } from "react";

const AppContext = createContext();

export const AppProvider = ({ children }) => {
  const [tableSelected, setTableSelected] = useState();
  const [data, setData] = useState([]);
  const router = useRouter();

  const navigateToNewPage = (page) => {
    router.push(page);
  };

  return (
    <AppContext.Provider
      value={{
        tableSelected,
        setTableSelected,
        data,
        setData,
        navigateToNewPage
      }}
    >
      {children}
    </AppContext.Provider>
  );
};

export const useAppContext = () => useContext(AppContext);
