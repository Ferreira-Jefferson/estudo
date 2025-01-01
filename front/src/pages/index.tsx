import Layout from "../components/Layout";

/**
 * Página inicial da aplicação.
 * @returns {JSX.Element} Elemento JSX renderizado.
 */
const Home = (): JSX.Element => {
  return (
    <Layout title="Página Inicial" description="Minha aplicação Next.js no VPS">
      <div className="flex flex-col items-center justify-center h-screen bg-gray-100">
        <h1 className="text-5xl font-bold mb-4">
          Te amo minha Leoa 🦁
        </h1>
        <p className="text-xl text-gray-700">Feliz ano novo ❤️</p>
      </div>
    </Layout>
  );
};

export default Home;
