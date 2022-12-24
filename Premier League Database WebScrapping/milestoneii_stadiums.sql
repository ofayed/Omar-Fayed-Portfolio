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
-- Table structure for table `stadiums`
--

DROP TABLE IF EXISTS `stadiums`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `stadiums` (
  `Club` text,
  `Stadium Name` text,
  `Capacity` int DEFAULT NULL,
  `Record PL attendance` text,
  `Bulit/opened` int DEFAULT NULL,
  `Pitch size` text,
  `Address` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stadiums`
--

LOCK TABLES `stadiums` WRITE;
/*!40000 ALTER TABLE `stadiums` DISABLE KEYS */;
INSERT INTO `stadiums` VALUES ('Arsenal','Emirates Stadium',60260,' 60,161 v Manchester United (3 November 2007)',2006,' 105m x 68m',' Highbury House, 75 Drayton Park, London, N5 1BU'),('Aston Villa','Villa Park',42682,NULL,1897,' 105m x 68m',' Villa Park, Trinity Road, Birmingham, B6 6HE'),('Brentford','Brentford Community Stadium',17250,NULL,2020,' 105m x 68m',' Brentford Community Stadium, Lionel Road South, Brentford, TW8 0RU'),('Brighton and Hove Albion','Amex Stadium',30666,' 30,565 v Everton (15 Oct 2017)',2011,' 105m x 68m',' American Express Community Stadium, Village Way, Brighton, BN1 9BL'),('Burnley','Turf Moor',21944,' 21,870 v Manchester United (24 April 2017)',1883,' 105m x 68m',' Turf Moor, Harry Potts Way, Burnley, Lancashire, BB10 4BX'),('Chelsea','Stamford Bridge',40853,' 42,332 v Newcastle United (4 December 2004)',1877,' 103m x 67.5m',' Stamford Bridge, Fulham Road, London, SW6 1HS'),('Crystal Palace','Selhurst Park',25486,' 30,115 v Manchester United (21 April 1993)',1924,' 101m x 68m',' Selhurst Park Stadium, Holmesdale Road, London, SE25 6PU'),('Everton','Goodison Park',39221,' 40,552 v Liverpool (11 December 2004)',1892,' 100.48m x 68m','Goodison Park, Goodison Road, Liverpool, L4 4EL'),('Leeds United','Elland Road',37890,NULL,1897,' 106m x 69m',' Elland Road, Leeds, LS11 0ES'),('Leicester City','King Power Stadium',32273,' 32,242 v Sunderland (8 August 2015)',2002,' 105m x 68m',' King Power Stadium, Filbert Way, Leicester, LE2 7FL'),('Liverpool','Anfield',53394,' 53,292 v AFC Bournemouth (5 April 2017)',1884,' 101m x 68m',' Anfield, Anfield Road, Liverpool, L4 0TH'),('Manchester City','Etihad Stadium',55017,' 54,693 v Leicester City (6 February 2016)',2002,' 105m x 68m','Etihad Stadium, Etihad Campus, Manchester, M11 3FF'),('Manchester United','Old Trafford',74879,' 76,098 v Blackburn Rovers (31 March 2007)',1909,' 105m x 68m',' Sir Matt Busby Way, Old Trafford, Manchester, M16 0RA'),('Newcastle United','St. James\' Park',52305,' 52,490 v West Ham United (11 November 2012)',1892,' 105m x 68m','St. James\' Park, Strawberry Place, Newcastle Upon Tyne, NE1 4ST'),('Norwich City','Carrow Road',27359,NULL,1935,' 104m x 68m',' Carrow Road, Norwich, NR1 1JE'),('Southampton','St. Mary\'s Stadium',32384,' 32,151 v Arsenal (29 December 2003)',2001,' 105m x 68m',' St Mary\'s Stadium, Britannia Road, Southampton, SO14 5FP'),('Tottenham Hotspur','Tottenham Hotspur Stadium',62062,NULL,2019,' 100m x 67m',' Lilywhite House, 782 High Road, Tottenham, London, N17 0BX'),('Watford','Vicarage Road',21000,' 21,590 v Sunderland (27 November 1999)',1922,' 105m x 68m',' Vicarage Road Stadium, Watford, Hertfordshire, WD18 0ER'),('West Ham United','London Stadium',60000,' 59,946 v Arsenal (12 January 2019)',2011,' 105m x 68m',' London Stadium, Queen Elizabeth Olympic Park, London, E20 2ST'),('Wolverhampton Wanderers','Molineux Stadium',32050,' 31,322 v Manchester City (25 August 2018)',1889,' 105m x 68m','Molineux Stadium, Waterloo Rd, Wolverhampton, WV1 4QR'),('Fulham','Craven Cottage',19000,NULL,1896,' 100m x 65m',' Stevenage Road, London, SW6 6HH'),('Sheffield United','Bramall Lane',32050,NULL,1855,' 102m x 66m',' Bramall Lane, Sheffield, South Yorkshire, S2 4SU'),('West Bromwich Albion','The Hawthorns',26688,' 27,751 v Portsmouth (15 May 2005)',1900,' 105m x 68m',' The Hawthorns, West Bromwich, West Midlands, B71 4LF'),('AFC Bournemouth','Vitality Stadium',11329,' 11,459 v Liverpool (4 December 2016 & 17 April 2016)',1910,' 105m x 68m',' Vitality Stadium, Dean Court, Bournemouth, BH7 7AF'),('Cardiff City','Cardiff City Stadium',33316,' 32,321 v Manchester City (22 September 2018)',2009,' 105m x 68m',' Cardiff City Stadium, Leckwith Road, Cardiff, CF11 8AZ'),('Huddersfield Town','John Smith\'s Stadium',24169,' 24,426 v Manchester United (21 October 2017)',1994,' 106m x 68m',' The John Smith\'s Stadium, Stadium Way, Huddersfield, HD1 6PX');
/*!40000 ALTER TABLE `stadiums` ENABLE KEYS */;
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
