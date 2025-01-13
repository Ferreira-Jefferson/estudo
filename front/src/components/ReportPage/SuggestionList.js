import React from "react";

const SuggestionList = ({ suggestions, showSuggestions, handleSuggestionClick }) => {
  if (!showSuggestions) return null;

  return (
    <ul className="absolute z-10 w-full bg-white border border-gray-300 rounded mt-1 max-h-48 overflow-auto">
      {suggestions.map((suggestion, index) => (
        <li
          key={index}
          className="p-2 cursor-pointer hover:bg-gray-200"
          onClick={() => handleSuggestionClick(suggestion)}
        >
          {suggestion.split("\t")[0]}
        </li>
      ))}
    </ul>
  );
};

export default SuggestionList;
