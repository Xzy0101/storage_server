CREATE SCHEMA IF NOT EXISTS CClip;
USE CClip;

CREATE USER IF NOT EXISTS 'cclip_admin'@'localhost' IDENTIFIED BY 'asdf123456JKL:';
GRANT ALL PRIVILEGES ON CClip.* TO 'cclip_admin'@'localhost';

DROP TABLE IF EXISTS Data;
DROP TABLE IF EXISTS User;

CREATE TABLE User(
	userName VARCHAR(16) PRIMARY KEY,
    passHash VARCHAR(64) NOT NULL,
    salt VARCHAR(64) NOT NULL,
    createTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE Data(
	userName VARCHAR(16) NOT NULL,
    recordNumber INT NOT NULL,
    deviceName VARCHAR(16) NOT NULL,
    createTime TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    data MEDIUMBLOB,
    CONSTRAINT data_PK PRIMARY KEY (userName, recordNumber),
    CONSTRAINT data_userName_FK FOREIGN KEY (userName) REFERENCES User(userName) ON DELETE CASCADE ON UPDATE CASCADE
);

DROP PROCEDURE IF EXISTS new_user;
DROP PROCEDURE IF EXISTS get_pass;
DROP PROCEDURE IF EXISTS change_pass;
DROP PROCEDURE IF EXISTS get_rnum;
DROP PROCEDURE IF EXISTS new_data;
DROP PROCEDURE IF EXISTS get_data;

DELIMITER $$

CREATE PROCEDURE new_user(IN uname VARCHAR(16), IN upass VARCHAR(64), IN usalt VARCHAR(64))
BEGIN
INSERT INTO User (userName, passHash, salt) VALUES (uname, upass, usalt);
END$$

CREATE PROCEDURE get_pass(IN uname VARCHAR(16))
BEGIN
SELECT passHash, salt FROM User WHERE userName = uname;
END$$

CREATE PROCEDURE change_pass(IN uname VARCHAR(16), IN upass VARCHAR(64), IN usalt VARCHAR(64))
BEGIN
UPDATE User SET passHash = upass, salt = usalt WHERE userName = uname;
END$$

CREATE PROCEDURE get_rnum(IN uname VARCHAR(16))
BEGIN
SELECT COUNT(*) AS numOfRecords FROM Data WHERE userName = uname;
END$$

CREATE PROCEDURE new_data(IN uname VARCHAR(16), IN dname VARCHAR(16), IN dt MEDIUMBLOB)
BEGIN
SET @old_count = (SELECT COUNT(*) FROM Data WHERE userName = uname);
INSERT INTO Data (userName, recordNumber, deviceName, data) VALUES (uname, @old_count + 1, dname, dt);
SELECT @old_count + 1 AS numOfRecords;
END$$

CREATE PROCEDURE get_data(IN uname VARCHAR(16), IN rnum INT)
BEGIN
SELECT deviceName, data FROM Data WHERE userName = uname AND recordNumber = rnum;
END$$

DELIMITER ;

CALL new_user('dummy', 'dummy_hash', 'dummy_salt');
CALL new_data('dummy', 'dummy_device', 'dummy_data');
CALL new_data('dummy', 'dummy_device2', 'dummy_data2');

COMMIT;