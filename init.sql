USE degustware;

CREATE TABLE IF NOT EXISTS products (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100),
  description VARCHAR(255),
  price DECIMAL(10, 2)
);

INSERT INTO products (name, description, price) VALUES
  ('Bife Acebolado', 'Bife com cebola', 25.50),
  ('Frango à Milanesa', 'Frango empanado e frito', 22.00),
  ('Arroz e Feijão', 'Acompanhamento tradicional', 10.00);
