USE degustware;

CREATE TABLE IF NOT EXISTS products (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100),
  description VARCHAR(255),
  price DECIMAL(10, 2)
);

-- Criar a tabela de motoboys
CREATE TABLE IF NOT EXISTS motoboys (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(255) NOT NULL,
    codigo INT NOT NULL UNIQUE,
    diaria DECIMAL(10, 2) NOT NULL
);


-- Criar a tabela de bairros
CREATE TABLE IF NOT EXISTS bairros (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(255) NOT NULL,
    taxa DECIMAL(10, 2) NOT NULL
);


-- Criar a tabela de entregas
CREATE TABLE IF NOT EXISTS entregas (
    id INT AUTO_INCREMENT PRIMARY KEY,
    codigo_pedido VARCHAR(50) NOT NULL,
    problema BOOLEAN NOT NULL,
    taxa DECIMAL(10, 2) NOT NULL,
    motoboy_id INT NOT NULL,
    bairro_id INT NOT NULL,
    data_registro DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (motoboy_id) REFERENCES motoboys(id)
    FOREIGN KEY (bairro_id) REFERENCES bairros(id)
);


INSERT INTO products (name, description, price) VALUES
  ('Bife Acebolado', 'Bife com cebola', 25.50),
  ('Frango à Milanesa', 'Frango empanado e frito', 22.00),
  ('Arroz e Feijão', 'Acompanhamento tradicional', 10.00);
  
  
-- Inserir dados de teste na tabela de motoboys
INSERT INTO motoboys (nome, codigo, diaria) VALUES 
('João Silva', 1234, 100.00),
('Maria Oliveira', 5678, 120.00),
('Carlos Santos', 9101, 150.00);


-- Inserir dados de teste na tabela de bairros
INSERT INTO bairros (nome, taxa) VALUES 
('Centro', 10.00),
('Zona Sul', 15.00),
('Zona Norte', 12.50),
('Zona Leste', 20.00);

-- Inserir dados de teste na tabela de entregas
INSERT INTO entregas (codigo_pedido, problema, taxa, bairro_id, motoboy_id) VALUES 
('123', FALSE, 10.00, 1, 1),
('456', FALSE, 15.00, 2, 2),
('789', TRUE, 12.50, 3, 3),
('012', FALSE, 20.00, 4, 1);
('aiq', FALSE, 15.00, 1, 1);
