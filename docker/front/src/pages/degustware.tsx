import Layout from "@/components/Layout"
import Header from "../components/Home/Header"
import NavigationButtons from "../components/Home/NavigationButtons"

export default function Degustware() {
  return (
    <Layout title="" description="">
      <div className="min-h-screen flex items-center justify-center bg-gradient-to-r from-yellow-700 to-red-900">
        <div className="w-full max-w-lg bg-white p-10 rounded-lg shadow-lg">
          <Header />
          <NavigationButtons />
        </div>
      </div>
    </Layout>
  )
}
