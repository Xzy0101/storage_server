CREATE DATABASE  IF NOT EXISTS `cclip` /*!40100 DEFAULT CHARACTER SET utf8 */;
USE `cclip`;
-- MySQL dump 10.13  Distrib 5.7.17, for Win64 (x86_64)
--
-- Host: localhost    Database: cclip
-- ------------------------------------------------------
-- Server version	5.7.21-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `data`
--

DROP TABLE IF EXISTS `data`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `data` (
  `username` varchar(16) NOT NULL,
  `record_number` int(11) unsigned NOT NULL,
  `device_name` varchar(16) NOT NULL,
  `create_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `data` mediumblob
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `data`
--

LOCK TABLES `data` WRITE;
/*!40000 ALTER TABLE `data` DISABLE KEYS */;
INSERT INTO `data` VALUES ('test1',1,'device1','2018-01-25 09:56:33','Test data 1.'),('test1',2,'','2018-01-25 13:09:47',''),('test1',3,'device null','2018-01-25 13:10:13',''),('test1',4,'device 2','2018-01-25 13:22:40','\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì'),('test1',5,'device 3','2018-01-25 13:23:59','\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\0\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì'),('test1',6,'device 2','2018-01-26 09:58:45','This is another test data.'),('test1',7,'device 3','2018-01-26 10:21:03','\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\0\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì'),('test1',8,'device 3','2018-01-26 10:24:31','\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\0\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì\Ì');
/*!40000 ALTER TABLE `data` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `user` (
  `username` varchar(16) NOT NULL,
  `password` varchar(64) NOT NULL,
  `create_time` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `record_number` int(10) unsigned NOT NULL DEFAULT '0',
  `salt` varchar(64) NOT NULL,
  PRIMARY KEY (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `user`
--

LOCK TABLES `user` WRITE;
/*!40000 ALTER TABLE `user` DISABLE KEYS */;
INSERT INTO `user` VALUES ('test1','1c81fc1d08cf849dd67fb45eede4c68db0f27365bd6eb11e53fb4dcf5bccf9d1','2018-01-23 10:19:51',8,'laorT9ylwMMaM5UJmlh8D9hr1w7FE5+e5k+JOT/Qdd2+fJ4NmXbHFscZ/55asg40'),('test2','0da4013a3f29a5231e45f2ae2378d6354670d7fea31f3b2453c19d7c8c72d968','2018-01-25 12:34:35',0,'68eRWD6yeZ5l3db5v9YpFx9Z0/Cwg/lH4qiVlCOHOxgGNM9NJN7A3xwW4BQyzgkb'),('test3','2acd2212c2d00f03fd3b4223a34becabf1e4f35360d44319a07bbe63ac07323c','2018-01-25 12:36:40',0,'cYtq4U+XLLrV5VoABfBwQGOdns2m0IMozkRC4G41oZQiEKeYj+T1hnk5nuVT2Zbg');
/*!40000 ALTER TABLE `user` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'cclip'
--
/*!50003 DROP PROCEDURE IF EXISTS `change_pass` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`cclip_admin`@`%` PROCEDURE `change_pass`(in uname varchar(16),
in newpass varchar(64))
begin
set @salt = to_base64(random_bytes(48));
update `user` set
`salt` = @salt,
`password` = sha2(concat(newpass,@salt),256)
where `username` = uname;
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `check_pass` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`cclip_admin`@`%` PROCEDURE `check_pass`(in uname varchar(16),
in upass varchar(64))
begin
select sha2(concat(upass,`salt`),256)=`password`
as name_pass_match
from `user`
where username = uname;
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `get_data` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`cclip_admin`@`%` PROCEDURE `get_data`(in uname varchar(16), 
in record_num int)
begin
select `data`.`data`, `data`.`device_name`
from `data` 
where `username`=uname and `record_number`=record_num;
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `get_rnum` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`cclip_admin`@`%` PROCEDURE `get_rnum`(in uname varchar(16))
begin
select `record_number`
from `user`
where `username` = uname;
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `new_data` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`cclip_admin`@`%` PROCEDURE `new_data`(in uname varchar(16), in device varchar(16), in dt MEDIUMBLOB)
begin

set @old_num = (select `record_number` from `user` where `username`=uname);

insert into `data`(`username`,`device_name`,`record_number`,`data`)
values(uname, device, @old_num+1, dt);

update `user` set `record_number` = @old_num+1
where `username` = uname;

select @old_num+1 as `record_number`;

end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `new_user` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8 */ ;
/*!50003 SET character_set_results = utf8 */ ;
/*!50003 SET collation_connection  = utf8_general_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'STRICT_TRANS_TABLES,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`cclip_admin`@`%` PROCEDURE `new_user`(in uname varchar(16), in upass varchar(64))
begin
set @salt = to_base64(random_bytes(48));
insert into `user`(`username`,`salt`,`password`) 
values(uname,@salt, SHA2(concat(upass,@salt),256));
end ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-01-27 17:21:56
