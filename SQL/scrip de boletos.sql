-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Versión del servidor:         8.0.37 - MySQL Community Server - GPL
-- SO del servidor:              Win64
-- HeidiSQL Versión:             10.2.0.5599
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


-- Volcando estructura de base de datos para aerolinea
DROP DATABASE IF EXISTS `aerolinea`;
CREATE DATABASE IF NOT EXISTS `aerolinea` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `aerolinea`;

-- Volcando estructura para tabla aerolinea.boletos
DROP TABLE IF EXISTS `boletos`;
CREATE TABLE IF NOT EXISTS `boletos` (
  `nombre` text,
  `fecha_salida` text,
  `fecha_llegada` text,
  `asiento` text,
  `numero_vuelo` text
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Volcando datos para la tabla aerolinea.boletos: ~7 rows (aproximadamente)
DELETE FROM `boletos`;
/*!40000 ALTER TABLE `boletos` DISABLE KEYS */;
INSERT INTO `boletos` (`nombre`, `fecha_salida`, `fecha_llegada`, `asiento`, `numero_vuelo`) VALUES
	('Ana Perez', '2024-09-24 11:00:00', '2024-09-24 12:00:00', 'A12', 'VUELO005'),
	('Iris Ramirez', '2024-09-24 11:00:00', '2024-09-24 12:00:00', 'B13', 'VUELO005'),
	('Tereza Mendez', '2024-09-24 11:00:00', '2024-09-24 12:00:00', 'A01', 'VUELO005'),
	('Jorge Ruiz', '2024-09-24 11:00:00', '2024-09-24 12:00:00', 'A11', 'VUELO005'),
	('Ivan Gongora', '2024-09-24 11:00:00', '2024-09-24 12:00:00', 'A13', 'VUELO005'),
	('Juan Perez', '2024-09-24 11:00:00', '2024-09-24 12:00:00', 'A13', 'VUELO150'),
	('Alma Gozo', '2024-09-24 11:00:00', '2024-09-25 13:00:00', 'A17', 'VUELO150'),
	('Nery Estrada', '2024-09-24 11:00:00', '2024-09-25 13:00:00', 'B09', 'VUELO150'),
	('Isidro Pastor', '2024-09-24 11:00:00', '2024-09-25 13:00:00', 'A11', 'VUELO150'),
	('Antonio Garcia', '2024-09-24 11:00:00', '2024-09-25 13:00:00', 'A18', 'VUELO150');
/*!40000 ALTER TABLE `boletos` ENABLE KEYS */;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
