USE degustware;

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
    FOREIGN KEY (motoboy_id) REFERENCES motoboys(id),
    FOREIGN KEY (bairro_id) REFERENCES bairros(id)
);

-- Inserir dados de teste na tabela de motoboys
INSERT INTO motoboys (nome, codigo, diaria) VALUES 
('João', 0001, 35.00),
('Chacrinha', 0010, 35.00),
('Iago',0011 , 35.00);
('Lucas Bironha', 0100, 30.00);
('Lucas Churrasco', 0101, 35.00);
('Almir Rogério', 0110, 35.00);
('Luiz', 0111, 35.00);
('Novo boy', 1000, 35.00);


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
