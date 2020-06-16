CREATE DATABASE IF NOT EXISTS wemos;

use wemos;

CREATE TABLE `chips`(
    id INT UNIQUE NOT NULL AUTO_INCREMENT,
    name VARCHAR(20) UNIQUE NOT NULL,
    Description TEXT,

    PRIMARY KEY(id)
);

CREATE TABLE `tempHistory`(
    chip_id INT NOT NULL,
    time DATETIME NOT NULL,
    value DECIMAL NOT NULL,

    UNIQUE(chip_id, time),
    PRIMARY KEY(chip_id, time),
    FOREIGN KEY(chip_id) REFERENCES chips(id)
);

CREATE TABLE `lightControl`(
    chip_id INT UNIQUE NOT NULL,
    status BOOLEAN NOT NULL,
    
    PRIMARY KEY(chip_id),
    FOREIGN KEY(chip_id) REFERENCES chips(id)
);