-- MySQL dump 10.13  Distrib 8.0.28, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: milestoneii
-- ------------------------------------------------------
-- Server version	8.0.28

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `clubs`
--

DROP TABLE IF EXISTS `clubs`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `clubs` (
  `Name` text,
  `Website` text,
  `Stadium` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `clubs`
--

LOCK TABLES `clubs` WRITE;
/*!40000 ALTER TABLE `clubs` DISABLE KEYS */;
INSERT INTO `clubs` VALUES ('Arsenal','www.arsenal.com','Emirates Stadium'),('Aston Villa','www.avfc.co.uk','Villa Park'),('Brentford','www.brentfordfc.com','Brentford Community Stadium'),('Brighton and Hove Albion','www.brightonandhovealbion.com','Amex Stadium'),('Burnley','www.burnleyfootballclub.com','Turf Moor'),('Chelsea','www.chelseafc.com','Stamford Bridge'),('Crystal Palace','www.cpfc.co.uk','Selhurst Park'),('Everton','www.evertonfc.com','Goodison Park'),('Leeds United','www.leedsunited.com/','Elland Road'),('Leicester City','www.lcfc.com','King Power Stadium'),('Liverpool','www.liverpoolfc.com','Anfield'),('Manchester City','www.mancity.com','Etihad Stadium'),('Manchester United','www.manutd.com','Old Trafford'),('Newcastle United','www.nufc.co.uk','St. James\' Park'),('Norwich City','www.canaries.co.uk','Carrow Road'),('Southampton','www.southamptonfc.com','St. Mary\'s Stadium'),('Tottenham Hotspur','www.tottenhamhotspur.com','Tottenham Hotspur Stadium'),('Watford','www.watfordfc.com','Vicarage Road'),('West Ham United','www.whufc.com','London Stadium'),('Wolverhampton Wanderers','https://www.wolves.co.uk','Molineux Stadium'),('Fulham','www.fulhamfc.com','Craven Cottage'),('Sheffield United','https://www.sufc.co.uk/','Bramall Lane'),('West Bromwich Albion','www.wba.co.uk','The Hawthorns'),('AFC Bournemouth','www.afcb.co.uk','Vitality Stadium'),('Cardiff City','www.cardiffcityfc.co.uk','Cardiff City Stadium'),('Huddersfield Town','www.htafc.com','John Smith\'s Stadium');
/*!40000 ALTER TABLE `clubs` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-04-11  3:42:56
