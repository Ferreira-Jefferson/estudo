import React from 'react';

export default function Modal({ title, message, onClose }) {
  return (
    <div className="fixed inset-0 flex items-center justify-center z-50 bg-black bg-opacity-50">
      <div className="bg-white rounded-lg p-8 max-w-sm mx-auto relative">
        <h2 className="text-red-900 font-bold text-xl mb-4">{title}</h2>
        <p className="text-gray-700 mb-8">{message}</p>
        <button 
          className="bg-red-900 text-white px-4 py-2 rounded-md hover:bg-red-800 transition-colors duration-300 absolute bottom-4 right-4"
          onClick={onClose}
        >
          Fechar
        </button>
      </div>
    </div>
  );
}
