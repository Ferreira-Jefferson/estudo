import { useEffect, useState } from "react"
import Layout from "../components/Layout"

export default function Motoboys() {
  const [motoboys, setMotoboys] = useState([]) // Lista de motoboys
  const [entregas, setEntregas] = useState([])
  const [selectedMotoboy, setSelectedMotoboy] = useState(null) // Motoboy selecionado
  const [diaria, setDiaria] = useState(0) // Valor da diária
  const [pedidosEntregues, setPedidosEntregues] = useState(0) // Pedidos entregues
  const [totalParcial, setTotalParcial] = useState(0) // Total parcial

  const fetcher = async (path: string) => {
    const response = await fetch(`https://degustware.com.br/api${path}`) // Endpoint da sua API
    return await response.json()
  }

  const carregarMotoboys = async () => {
    const data = await fetcher("/motoboys") 
    setMotoboys(data)
  }

  useEffect(() => {
    carregarMotoboys()
  }, [])

  const handleChangeMotoboy = async () => {
     const { entregues, total_parcial } = await fetcher(`/motoboys/${selectedMotoboy}`)
    setPedidosEntregues(entregues || 0)
    setTotalParcial(total_parcial || 0)

    const data = await fetcher(`/entregas/${selectedMotoboy}`)
    setEntregas(data)
  }

  // Atualiza os dados do motoboy selecionado
  const handleSelectMotoboy = motoboy => {
    setSelectedMotoboy(motoboy.id)
    setDiaria(motoboy.diaria || 0)
    setPedidosEntregues(motoboy.pedidosEntregues || 0)
    setTotalParcial(motoboy.totalParcial || 0)
    handleChangeMotoboy()
  }

  return (
    <Layout title="" description="">
      <div className="p-6 bg-gray-100">
        {/* Select de motoboys */}
        <div className="mb-5">
          <label htmlFor="motoboys" className="block text-gray-700">
            Motoboy:
          </label>
          <select
            id="motoboys"
            className="border rounded p-2"
            onChange={e =>
              handleSelectMotoboy(
                motoboys.find(motoboy => motoboy.id == e.target.value)
              )
            }
          >
            <option value="">Selecione um motoboy</option>
            {motoboys.map(motoboy => (
              <option key={motoboy.id} value={motoboy.id}>
                {motoboy.nome}
              </option>
            ))}
          </select>
        </div>

        {/* Informações do motoboy */}
        <div className="mb-5">
          <p>Diária: R$ {diaria}</p>
          <p>Pedidos Entregues: {pedidosEntregues}</p>
          <p>Total Parcial: R$ {totalParcial}</p>
        </div>

        {/* Botão para adicionar nova corrida */}
        <button
          className="bg-blue-500 text-white px-4 py-2 rounded mb-4"
          onClick={() => alert("Adicionar nova corrida")}
        >
          + Nova Corrida
        </button>

        {/* Tabela de corridas */}
        <table className="table-auto w-full border">
          <thead>
            <tr>
              <th className="border px-4 py-2">Código</th>
              <th className="border px-4 py-2">Bairro</th>
              <th className="border px-4 py-2">Taxa</th>
            </tr>
          </thead>
          <tbody>
            {entregas.map((entrega, index) => (
              <tr key={index}>
                <td className="border px-4 py-2">{entrega.codigo_pedido}</td>
                <td className="border px-4 py-2">{entrega.bairro}</td>
                <td className="border px-4 py-2">{entrega.taxa}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </Layout>
  )
}
