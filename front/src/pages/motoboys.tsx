import { useEffect, useState } from "react"
import Layout from "../components/Layout"

export default function Motoboys() {
  const [motoboys, setMotoboys] = useState([]) // Lista de motoboys
  const [entregas, setEntregas] = useState([])
  const [selectedMotoboy, setSelectedMotoboy] = useState(null) // Motoboy selecionado
  const [diaria, setDiaria] = useState(0) // Valor da diária
  const [pedidosEntregues, setPedidosEntregues] = useState(0) // Pedidos entregues
  const [totalParcial, setTotalParcial] = useState(0) // Total parcial

  const fetcher = async (path: string, body = {}) => {
    try {
      const response = await fetch(`https://degustware.com.br/api${path}`, body) // Endpoint da sua API

      if (!response.ok) {
        const errorData = await response.json()
        return console.error("Erro:", errorData.error)
      }
      return await response.json()
    } catch (error) {
      console.error("Erro ao realizar a requisição:", error)
    }
  }

  const carregarMotoboys = async () => {
    const data = await fetcher("/motoboys")
    setMotoboys(data)
  }

  useEffect(() => {
    carregarMotoboys()
  }, [])

  const handleChangeMotoboy = async motoboy_id => {
    const { entregues, total_parcial } = await fetcher(
      `/motoboys/${motoboy_id}`
    )
    setPedidosEntregues(entregues || 0)
    setTotalParcial(total_parcial || 0)

    const data = await fetcher(`/entregas/${motoboy_id}`)
    setEntregas([data])
  }

  const handleSelectMotoboy = motoboy => {
    setSelectedMotoboy(motoboy?.id)
    setDiaria(motoboy?.diaria || 0)
    setPedidosEntregues(motoboy?.pedidosEntregues || 0)
    setTotalParcial(motoboy?.totalParcial || 0)
    handleChangeMotoboy(motoboy?.id)
  }

  const [isModalOpen, setIsModalOpen] = useState(false) 
  const [codigoPedido, setCodigoPedido] = useState("")
  const [problema, setProblema] = useState(false) 

  const abrirModal = () => {
    setProblema(false)
    setIsModalOpen(true)
  }

  const fecharModal = () => setIsModalOpen(false)

  const handleSalvar = async () => {
    // Dados da nova entrega
    const novaEntrega = {
      codigo_pedido: codigoPedido,
      problema,
      taxa,
      bairro_id: bairro,
      motoboy_id: selectedMotoboy,
    }

    // Enviar a requisição para a API
    const response = await fetcher("/entregas", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(novaEntrega),
    })

    if (response) {
      const data = await fetcher(`/bairros/${bairro}`)
      setEntregas([...entregas, {codigo_pedido: codigoPedido, bairro: data?.nome, taxa}])
    }
    
    fecharModal()
  }

  // Input bairro
  const [bairro, setBairro] = useState("")
  const [taxa, setTaxa] = useState(0)
  const [suggestions, setSuggestions] = useState([])

  const handleSearch = async query => {
    setBairro(query)
    if (query.trim() === "") {
      setSuggestions([])
      return
    }
    // Busca os bairros no banco de dados (API ou serviço)
    const data = await fetcher(`/bairros?query=${query}`)
    setSuggestions(data)
  }

  const handleSelectBairro = sugestao => {
    setBairro(sugestao.nome)
    setTaxa(sugestao.taxa)
    setSuggestions([])
    console.log("ID do bairro selecionado:", sugestao.id)
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
          onClick={abrirModal}
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

      {/* Modal */}
      {isModalOpen && (
        <div className="fixed inset-0 bg-gray-800 bg-opacity-75 flex justify-center items-center z-50">
          <div className="bg-white rounded-lg shadow-lg p-6 w-1/3">
            <h2 className="text-lg font-semibold mb-4">
              Adicionar Nova Corrida
            </h2>
            <form>
              <div className="mb-4">
                <label htmlFor="codigo" className="block text-gray-700">
                  Código do Pedido
                </label>
                <input
                  type="text"
                  id="codigo"
                  className="w-full border rounded p-2"
                  value={codigoPedido}
                  onChange={e => setCodigoPedido(e.target.value)}
                />
              </div>

              <div className="mb-4 relative">
                <label htmlFor="bairro" className="block text-gray-700">
                  Bairro
                </label>
                <input
                  type="text"
                  id="bairro"
                  className="w-full border rounded p-2"
                  value={bairro}
                  onChange={e => handleSearch(e.target.value)}
                  onBlur={() => setTimeout(() => setSuggestions([]), 200)} // Fecha sugestões ao sair do campo
                />
                {/* Lista de sugestões */}
                {suggestions.length > 0 && (
                  <ul className="absolute z-10 bg-white border w-full rounded shadow-md mt-1">
                    {suggestions.map(sugestao => (
                      <li
                        key={sugestao.id}
                        className="p-2 hover:bg-gray-200 cursor-pointer"
                        onClick={() => handleSelectBairro(sugestao)}
                      >
                        {sugestao.nome}
                      </li>
                    ))}
                  </ul>
                )}
              </div>

              {/* toggle switch */}
              <div className="mb-4 flex items-center">
                <label
                  htmlFor="problema"
                  className="flex items-center cursor-pointer"
                >
                  <span className="mr-3 text-gray-700">
                    Problema no pedido?
                  </span>
                  <div className="relative">
                    <input
                      type="checkbox"
                      id="problema"
                      className="sr-only"
                      checked={problema}
                      onChange={e => setProblema(e.target.checked)}
                    />
                    <div
                      className={`block w-10 h-6 rounded-full ${
                        problema ? "bg-red-500" : "bg-gray-400"
                      }`}
                    ></div>
                    <div
                      className={`dot absolute left-1 top-1 w-4 h-4 rounded-full bg-white transition ${
                        problema ? "translate-x-4" : "translate-x-0"
                      }`}
                    ></div>
                  </div>
                </label>
              </div>

              <div className="flex justify-end space-x-2">
                <button
                  type="button"
                  className="bg-gray-400 text-white px-4 py-2 rounded"
                  onClick={fecharModal}
                >
                  Cancelar
                </button>
                <button
                  type="button"
                  className="bg-blue-500 text-white px-4 py-2 rounded"
                  onClick={handleSalvar}
                >
                  Salvar
                </button>
              </div>
            </form>
          </div>
        </div>
      )}
    </Layout>
  )
}
