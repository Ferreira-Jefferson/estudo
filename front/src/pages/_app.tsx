import { AppProps } from "next/app";
import "../styles/globals.css";
import "@fontsource/inter";
import { AppProvider } from "../context/AppContext";

function MyApp({ Component, pageProps }: AppProps): JSX.Element {
    return (
    <AppProvider>
      <Component {...pageProps} />
    </AppProvider>
  );
}

export default MyApp;
