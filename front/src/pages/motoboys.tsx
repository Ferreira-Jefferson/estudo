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
    const data_utf8 = data.map(item => ({
      ...item,
      nome: item.nome ? decodeURIComponent(escape(item.nome)) : "",
    }))
    setMotoboys(data_utf8)
  }

  useEffect(() => {
    carregarMotoboys()
  }, [])

  const handleChangeMotoboy = async (motoboy_id, dateFilter = undefined) => {
    const { entregues, total_parcial, diaria } = await fetcher(
      `/motoboys/${motoboy_id}`
    )

    const url = dateFilter
      ? `/entregas/${motoboy_id}|${dateFilter}`
      : `/entregas/${motoboy_id}`
    const data = await fetcher(url)

    setPedidosEntregues(entregues || 0)
    const totalParcial = parseFloat(total_parcial) + parseFloat(diaria)
    setTotalParcial(totalParcial || 0)
    setEntregas(data)
  }

  const handleSelectMotoboy = async motoboy => {
    setAbrirMensagemErro(false)
    setSelectedMotoboy(motoboy?.id)
    setDiaria(motoboy?.diaria || 0)
    setPedidosEntregues(motoboy?.pedidosEntregues || 0)
  }

  const buscarEntregas = () => {
    let dateFilter = ""
    const isValidEndDate = new Date(endDate) > new Date(startDate)

    if (startDate) {
      dateFilter += ` AND DATE(entregas.data_registro) ${
        isValidEndDate ? ">=" : "="
      } '${startDate}'`
    }

    if (endDate && isValidEndDate) {
      dateFilter += ` AND DATE(entregas.data_registro) <= '${endDate}'`
    }

    if(!dateFilter) {
      dateFilter = " AND DATE(entregas.data_registro) = CURDATE()"
    }

    handleChangeMotoboy(selectedMotoboy, dateFilter)
  }

  const [isModalOpen, setIsModalOpen] = useState(false)
  const [abrirMensagemErro, setAbrirMensagemErro] = useState(false)
  const [codigoPedido, setCodigoPedido] = useState("")
  const [problema, setProblema] = useState(false)

  const abrirModal = () => {
    if (!selectedMotoboy) return setAbrirMensagemErro(true)

    setIsModalOpen(true)
    setProblema(false)
    setCodigoPedido("")
    setBairroNome("")
  }

  const fecharModal = () => setIsModalOpen(false)

  const handleSalvar = async () => {
    // Dados da nova entrega
    const novaEntrega = {
      codigo_pedido: codigoPedido,
      problema,
      taxa,
      bairro_id,
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
      const data = await fetcher(`/entregas/${selectedMotoboy}`)
      setEntregas(data)
    }

    fecharModal()
  }

  // Input bairro
  const [bairro_id, setBairroId] = useState("")
  const [bairro_nome, setBairroNome] = useState("")
  const [taxa, setTaxa] = useState(0)
  const [suggestions, setSuggestions] = useState([])

  const handleSearch = async query => {
    setBairroNome(query)
    if (query.trim() === "") {
      setSuggestions([])
      return
    }
    // Busca os bairros no banco de dados (API ou serviço)
    const data = await fetcher(`/bairros?query=${query}`)
    setSuggestions(data)
  }

  const handleSelectBairro = sugestao => {
    setBairroId(sugestao.id)
    setBairroNome(sugestao.nome)
    setTaxa(sugestao.taxa)
    setSuggestions([])
  }

  const [startDate, setStartDate] = useState("")
  const [endDate, setEndDate] = useState("")

  const makeDate = date => {
    if (date === "") {
      const today = new Date()
      const year = today.getFullYear()
      const month = String(today.getMonth() + 1).padStart(2, "0")
      const day = String(today.getDate()).padStart(2, "0")
      return `${year}-${month}-${day}`
    }

    return date
  }

  return (
    <Layout title="" description="">
      <div className="p-6 bg-gray-100">
        {/* Select de motoboys */}
        <div className="flex flex-col md:flex-row space-y-4 md:space-y-0 md:space-x-4">
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
          <div className="flex-2">
            <label className="block text-gray-700">Data Inicial:</label>
            <input
              type="date"
              value={startDate}
              onChange={e => setStartDate(makeDate(e.target.value))}
              className="mt-1 p-2 border rounded"
            />
          </div>
          <div className="flex-1">
            <label className="block text-gray-700">Data Final:</label>
            <input
              type="date"
              value={endDate}
              onChange={e => setEndDate(makeDate(e.target.value))}
              className="mt-1 p-2 border rounded"
            />
          </div>
        </div>

        {/* Botão para adicionar nova corrida */}
        <div>
          <button
            className="bg-blue-500 text-white px-4 py-2 rounded mb-4"
            onClick={buscarEntregas}
          >
            Buscar Entregas
          </button>
        </div>

        {/* Informações do motoboy */}
        <div className="mt-10 mb-5">
          <p>Diária: R$ {diaria}</p>
          <p>Pedidos Entregues: {pedidosEntregues}</p>
          <p>Total Parcial: R$ {totalParcial}</p>
        </div>

        {/* Botão para adicionar nova corrida */}
        <div className="flex justify-center">
          <button
            className="bg-blue-500 text-white px-4 py-2 rounded mb-4"
            onClick={abrirModal}
          >
            + Nova Corrida
          </button>
        </div>

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
                <td className="border px-4 py-2">{entrega.bairro_nome}</td>
                <td className="border px-4 py-2">{entrega.taxa}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>

      {/* Modal */}
      {isModalOpen && (
        <div className="fixed inset-0 bg-gray-800 bg-opacity-75 flex justify-center items-center z-50">
          <div className="bg-white rounded-lg shadow-lg p-6 w-full max-w-lg mx-4">
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
                  value={bairro_nome}
                  onChange={e => handleSearch(e.target.value)}
                  onBlur={() => setTimeout(() => setSuggestions([]), 200)}
                />
                {suggestions.length > 0 && (
                  <ul className="absolute z-10 bg-white border w-full rounded shadow-md mt-1">
                    {suggestions.map(sugestao => (
                      <li
                        key={sugestao.id}
                        className="p-2 hover:bg-gray-200 cursor-pointer w-full"
                        onMouseDown={() => handleSelectBairro(sugestao)}
                      >
                        {sugestao.nome}
                      </li>
                    ))}
                  </ul>
                )}
              </div>

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

      {abrirMensagemErro && (
        <div className="fixed top-4 left-1/2 transform -translate-x-1/2 bg-red-100 border border-red-400 text-red-700 px-4 py-3 rounded shadow-md w-11/12 md:w-1/3 z-50">
          <div className="flex items-center">
            <svg
              xmlns="http://www.w3.org/2000/svg"
              className="h-6 w-6 mr-2 text-red-700"
              fill="none"
              viewBox="0 0 24 24"
              stroke="currentColor"
            >
              <path
                strokeLinecap="round"
                strokeLinejoin="round"
                strokeWidth="2"
                d="M18.364 5.636a9 9 0 11-12.728 0M12 8v4m0 4h.01"
              />
            </svg>
            <span>Por favor, selecione um motoboy antes de continuar.</span>
          </div>
        </div>
      )}
    </Layout>
  )
}
