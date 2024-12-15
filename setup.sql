-- Criação do banco de dados
CREATE DATABASE IF NOT EXISTS degustware;

-- Uso do banco de dados
USE degustware;

-- Criação da tabela de exemplo
CREATE TABLE IF NOT EXISTS your_table (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    price DECIMAL(10, 2),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Inserção de dados de exemplo
INSERT INTO your_table (name, description, price) VALUES
('Item 1', 'Descrição do Item 1', 10.50),
('Item 2', 'Descrição do Item 2', 20.00),
('Item 3', 'Descrição do Item 3', 15.75),
('Item 4', 'Descrição do Item 4', 18.90),
('Item 5', 'Descrição do Item 5', 25.00);
