const tailWindConfig = {
  content: [
    "./src/pages/**/*.{js,ts,jsx,tsx}",
    "./src/components/**/*.{js,ts,jsx,tsx}",
  ],
  safelist: [
    {
      pattern:
        /from-(red|yellow|green|purple|blue)-(100|200|300|400|500|600|700|800|900)/,
    },
    {
      pattern:
        /to-(red|yellow|green|purple|blue)-(100|200|300|400|500|600|700|800|900)/,
    },
  ],
  theme: {
    extend: {
      fontFamily: {
        sans: ["Inter", "sans-serif"],
      },
       colors: {
        yellow: {
          50: "#FFF7E6",
          100: "#FFFAF0",
          200: "#FFE4B2",
          300: "#FFD580",
          400: "#FFC04D",
          500: "#FFB333",
          700: "#FF8C00",
          900: "#FFA500",
        },

        red: {
          700: "#B22222",
          750: "#9B1C1C",
          800: "#A52A2A",
          850: "#7F1A1A",
          900: "#8B0000",
          950: "#600000",
        },
        orange: {
          100: "#FFE4CC", // tom mais claro
          300: "#FFA94D", // tom médio
          500: "#FF7F24", // tom padrão
          700: "#FF5700", // tom escuro
          900: "#E04A00", // tom mais escuro
        },
        brown: {
          100: "#D2B48C", // tom mais claro
          300: "#A0522D", // tom médio
          500: "#8B4513", // tom padrão
          700: "#5C3317", // tom escuro
          900: "#3E2311", // tom mais escuro
        },
        gray: {
          100: "#F5F5F5", // tom mais claro
          300: "#D3D3D3", // tom médio
          500: "#A9A9A9", // tom padrão
          700: "#696969", // tom escuro
          900: "#2F4F4F", // tom mais escuro
        }
      },
    },
  },
  plugins: [],
};

module.exports = tailWindConfig;
