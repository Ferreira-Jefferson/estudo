// Dropzone.js

import React, { useCallback, useState } from 'react';
import { useDropzone } from 'react-dropzone';
import Modal from './Modal'; // Importe o componente Modal

export default function Dropzone({ onFileAccepted }) {
  const [showModal, setShowModal] = useState(false);
  const [modalMessage, setModalMessage] = useState("");

  const onCloseModal = () => {
    setShowModal(false);
  };

  const onDrop = useCallback((acceptedFiles) => {
    const nameSplited = acceptedFiles[0].name.split(".");
    const isSQL = nameSplited[nameSplited.length - 1] === "sql";
    if (isSQL) {
      onFileAccepted(acceptedFiles);
    } else {
      setModalMessage("Selecione um arquivo com extensão .sql");
      setShowModal(true);
    }
  }, [onFileAccepted]);

  const { getRootProps, getInputProps, isDragActive, open } = useDropzone({
    onDrop,
    accept: '.sql',
  });

  return (
    <div
      {...getRootProps()}
      className={`flex flex-col items-center justify-center border-4 border-dashed border-yellow-700 p-8 rounded-lg transition-colors duration-300 ${isDragActive ? 'bg-yellow-100' : 'bg-white'}`}
    >
      <input {...getInputProps()} />
      <p className="text-red-900 font-semibold text-lg">
        {isDragActive ? "Solte o arquivo aqui..." : "Arraste e solte o arquivo aqui, ou clique para selecionar"}
      </p>
      <button 
        className="mt-4 bg-red-900 text-white px-6 py-3 rounded-md hover:bg-red-800 transition-colors duration-300" 
        type="button" 
        onClick={open}
      >
        Escolher Arquivo
      </button>

      {showModal && (
        <Modal
          title="Formato Incompatível"
          message={modalMessage}
          onClose={onCloseModal}
        />
      )}
    </div>
  );
}
