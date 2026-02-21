-- Drop tables if they already exist (order matters because of FK constraints)
DROP TABLE IF EXISTS order_items;
DROP TABLE IF EXISTS orders;
DROP TABLE IF EXISTS books;
DROP TABLE IF EXISTS authors;
DROP TABLE IF EXISTS customers;

-- -------------------------
-- TABLE: authors
-- -------------------------
CREATE TABLE authors (
    author_id      INTEGER PRIMARY KEY AUTOINCREMENT,
    name           VARCHAR(100) NOT NULL,
    birth_year     INTEGER
);

-- -------------------------
-- TABLE: books
-- -------------------------
CREATE TABLE books (
    book_id        INTEGER PRIMARY KEY AUTOINCREMENT,
    title          VARCHAR(200) NOT NULL,
    author_id      INTEGER NOT NULL,
    price          DECIMAL(6,2) NOT NULL,
    stock          INTEGER NOT NULL DEFAULT 0,
    FOREIGN KEY (author_id) REFERENCES authors(author_id)
);

-- -------------------------
-- TABLE: customers
-- -------------------------
CREATE TABLE customers (
    customer_id    INTEGER PRIMARY KEY AUTOINCREMENT,
    name           VARCHAR(100) NOT NULL,
    email          VARCHAR(200) UNIQUE NOT NULL
);

-- -------------------------
-- TABLE: orders
-- -------------------------
CREATE TABLE orders (
    order_id       INTEGER PRIMARY KEY AUTOINCREMENT,
    customer_id    INTEGER NOT NULL,
    order_date     DATE NOT NULL,
    FOREIGN KEY (customer_id) REFERENCES customers(customer_id)
);

-- -------------------------
-- TABLE: order_items
-- -------------------------
CREATE TABLE order_items (
    order_item_id  INTEGER PRIMARY KEY AUTOINCREMENT,
    order_id       INTEGER NOT NULL,
    book_id        INTEGER NOT NULL,
    quantity       INTEGER NOT NULL,
    FOREIGN KEY (order_id) REFERENCES orders(order_id),
    FOREIGN KEY (book_id) REFERENCES books(book_id)
);

-- -------------------------
-- SAMPLE DATA
-- -------------------------

INSERT INTO authors (name, birth_year) VALUES
('George Orwell', 1903),
('J.K. Rowling', 1965),
('J.R.R. Tolkien', 1892);

INSERT INTO books (title, author_id, price, stock) VALUES
('1984', 1, 9.99, 12),
('Animal Farm', 1, 7.99, 5),
('Harry Potter and the Philosopher''s Stone', 2, 12.50, 20),
('The Hobbit', 3, 10.99, 8);

INSERT INTO customers (name, email) VALUES
('Alice Johnson', 'alice@example.com'),
('Bob Smith', 'bob@example.com');

INSERT INTO orders (customer_id, order_date) VALUES
(1, '2024-01-10'),
(2, '2024-01-11');

INSERT INTO order_items (order_id, book_id, quantity) VALUES
(1, 1, 1),
(1, 2, 2),
(2, 4, 1);

--created not needed to be understood

/*
    SELECT field(s) or *
    FROM table(s)
    WHERE condition(s) [AND | OR]
    LIKE "val%"
    ORDER BY [ASC | DESC] ASC by default
        (optional nested select statement);
*/

/*
    DELETE FROM [table]
    WHERE [field] opcode [condition]
*/

/*
    UPDATE [table]
    SET (field = value), ...
    --WHERE [field] opcode [condition]
*/

/*
    SELECT table1.field1, table2.field2
    FROM table1
    JOIN table2
    ON table1.foreign_key = table2.foreign_key
    WHERE table1.foreign_key=smt
*/

--DROP TABLE [table_name]