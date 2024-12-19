
// Frontend (React + TailwindCSS)
import React, { useState, useEffect } from 'react';
import axios from 'axios';

const Motoboys = () => {
    const [motoboys, setMotoboys] = useState([]);
    const [selectedMotoboy, setSelectedMotoboy] = useState(null);
    const [diaria, setDiaria] = useState(0);
    const [pedidosEntregues, setPedidosEntregues] = useState(0);
    const [totalParcial, setTotalParcial] = useState(0);
    const [novoMotoboy, setNovoMotoboy] = useState({ nome: '', codigo: '' });
    const [showCadastro, setShowCadastro] = useState(false);

    useEffect(() => {
        axios.get('/api/motoboys').then((response) => setMotoboys(response.data));
    }, []);

    const fetchMotoboyData = (id) => {
        axios.get(`/api/motoboys/${id}`).then((response) => {
            setDiaria(response.data.diaria);
            setPedidosEntregues(response.data.entregues);
            setTotalParcial(response.data.total_parcial);
        });
    };

    const handleNovoMotoboy = () => {
        const codigo = Math.floor(1000 + Math.random() * 9000);
        console.log('Novo Código:', codigo);
        setNovoMotoboy((prev) => ({ ...prev, codigo }));
        setShowCadastro(true);
    };

    const cadastrarMotoboy = () => {
        axios.post('/api/motoboys', novoMotoboy).then(() => {
            setShowCadastro(false);
            setNovoMotoboy({ nome: '', codigo: '' });
            axios.get('/api/motoboys').then((response) => setMotoboys(response.data));
        });
    };

    return (
        <div className="p-8 bg-gray-100 min-h-screen">
            <div className="flex items-center justify-between">
                <select
                    className="border rounded p-2"
                    onChange={(e) => {
                        setSelectedMotoboy(e.target.value);
                        fetchMotoboyData(e.target.value);
                    }}
                >
                    <option value="">Selecione um Motoboy</option>
                    {motoboys.map((motoboy) => (
                        <option key={motoboy.id} value={motoboy.id}>
                            {motoboy.nome}
                        </option>
                    ))}
                </select>
                <button className="bg-blue-500 text-white px-4 py-2 rounded" onClick={handleNovoMotoboy}>
                    Novo Motoboy
                </button>
            </div>

            {showCadastro && (
                <div className="mt-4 p-4 bg-white shadow rounded">
                    <input
                        className="border p-2 rounded w-full mb-2"
                        type="text"
                        placeholder="Nome do Motoboy"
                        value={novoMotoboy.nome}
                        onChange={(e) => setNovoMotoboy({ ...novoMotoboy, nome: e.target.value })}
                    />
                    <p className="mb-2">Código: {novoMotoboy.codigo}</p>
                    <button className="bg-green-500 text-white px-4 py-2 rounded" onClick={cadastrarMotoboy}>
                        Cadastrar
                    </button>
                </div>
            )}

            {selectedMotoboy && (
                <div className="mt-8">
                    <h2 className="text-lg font-bold">Informações do Motoboy</h2>
                    <p>Diária: R$ {diaria}</p>
                    <p>Pedidos Entregues: {pedidosEntregues}</p>
                    <p>Total Parcial: R$ {totalParcial}</p>
                </div>
            )}
        </div>
    );
};

export default Motoboys;
