-- phpMyAdmin SQL Dump
-- version 5.1.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Apr 30, 2022 at 09:39 AM
-- Server version: 10.4.21-MariaDB
-- PHP Version: 8.0.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `db_cppmysql`
--

-- --------------------------------------------------------

--
-- Table structure for table `in_out_stocks`
--

CREATE TABLE `in_out_stocks` (
  `STOCKS_ID` varchar(10) NOT NULL,
  `STOCKS_NAME` varchar(100) NOT NULL,
  `STOCKS_CATEGORY` varchar(100) NOT NULL,
  `STOCKS_QUANTITY` varchar(100) NOT NULL,
  `STOCKS_LOCATION` varchar(100) NOT NULL,
  `STOCKS_INDATE` varchar(100) NOT NULL,
  `STOCKS_OUTDATE` varchar(100) NOT NULL,
  `MODIFIED_BY` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `in_out_stocks`
--

INSERT INTO `in_out_stocks` (`STOCKS_ID`, `STOCKS_NAME`, `STOCKS_CATEGORY`, `STOCKS_QUANTITY`, `STOCKS_LOCATION`, `STOCKS_INDATE`, `STOCKS_OUTDATE`, `MODIFIED_BY`) VALUES
('H000', 'ubat gigi', 'Healthcare', '500', 'A01', '02/04/2020', '     -', 'S000'),
('H000', 'ubat gigi', 'Healthcare', '571', 'A01', '04/04/2020', '     -', 'S000'),
('H001', 'pencuci muka', 'Healthcare', '150', 'A02', '06/04/2020', '     -', 'S000'),
('H003', 'berus gigi', 'Healthcare', '100', 'A03', '04/04/2020', '     -', 'S000'),
('F000', 'kerusi kayu', 'furniture', '90', 'B00', '06/04/2020', '     -', 'S000'),
('K001', 'pisau dapur', 'Kitchenware', '80', 'C01', '06/04/2020', '     -', 'S000'),
('K002', 'papan pemotong', 'Kitchenware', '94', 'C02', '06/04/2020', '     -', 'S000'),
('F000', 'kentang', 'frozenfood', '900', 'D01', '08/06/2020', '     -', 'S000'),
('G000', 'ice cream', 'frozenfood', '200', 'D01', '09/04/2020', '     -', 'S000'),
('G001', 'sosej', 'frozenfood', '200', 'D02', '09/04/2020', '     -', 'S000'),
('V000', 'steering ', 'Vehiclepart', '90', 'F01', '10/04/2020', '     -', 'S000'),
('F001 ', 'meja bula', 'furniture', '90', 'B01', '12/04/2020', '     -', 'A123'),
('H004', 'vitamin A', 'Healthcare', '300', 'A04', '13/04/2020', '     -', 'S002'),
('H005', 'vitamin b5', 'Healthcare', '300', 'A05', '12/04/2020', '     -', 'S002'),
('H006', 'vitamin c', 'Healthcare', '70', 'A06', '23/04/2020', '     -', 'A123'),
('H000', 'ubat gigi', 'Healthcare', '581', 'A01', '12/05/2020', '     -', 'S000'),
('H001', 'pencuci muka', 'Healthcare', '150', 'A02', '15', 'safi', 'S000'),
('H003', 'berus gigi', 'Healthcare', '100', 'A03', '13', 'darlie', 'S000'),
('F000', 'kerusi kayu', 'furniture', '90', 'B00', '129', 'ikea', 'S000'),
('K001', 'pisau dapur', 'Kitchenware', '80', 'C01', '23', 'king kong', 'S000'),
('K002', 'papan pemotong', 'Kitchenware', '94', 'C02', '32', 'king kong', 'S000'),
('F000', 'kentang', 'frozenfood', '900', 'D01', '3', 'desa farm', 'S000'),
('G000', 'ice cream', 'frozenfood', '200', 'D01', '12', 'walls', 'S000'),
('G001', 'sosej', 'frozenfood', '200', 'D02', '8', 'ayamas', 'S000'),
('V000', 'steering ', 'Vehiclepart', '90', 'F01', '55', 'momo', 'S000'),
('F001 ', 'meja bula', 'furniture', '90', 'B01', '89', 'ikea', 'A123'),
('H004', 'vitamin A', 'Healthcare', '300', 'A04', '21', 'calpis', 'S002'),
('H005', 'vitamin b5', 'Healthcare', '300', 'A05', '22', 'calpis', 'S002'),
('H006', 'vitamin c', 'Healthcare', '70', 'A06', '24', 'blackmores', 'A123'),
('H000', 'ubat gigi', 'Healthcare', '581', 'A01', '     -', '12/05/2020', 'A123');

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `STAFF_ID` varchar(10) NOT NULL,
  `STAFF_NAME` varchar(100) NOT NULL,
  `STAFF_IC` varchar(12) NOT NULL,
  `STAFF_PHONENUMBER` varchar(10) NOT NULL,
  `STAFF_ADDRESS` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`STAFF_ID`, `STAFF_NAME`, `STAFF_IC`, `STAFF_PHONENUMBER`, `STAFF_ADDRESS`) VALUES
('S000', 'mohd malik ibrahim', '970102040101', '123984312', 'kemaman,terengganu'),
('', '', '', '', ''),
('S002', 'mohd yahya majid', '010304091212', '0121231231', 'mersing, johor'),
('S004', 'muhammad karim', '980809071212', '0102345832', 'skudai, johor'),
('S005', 'mahmud bin ahmad', '010403025756', '0137853212', 'kemaman, Terengganu');

-- --------------------------------------------------------

--
-- Table structure for table `stocks`
--

CREATE TABLE `stocks` (
  `STOCKS_ID` varchar(10) NOT NULL,
  `STOCKS_NAME` varchar(50) NOT NULL,
  `STOCKS_CATEGORY` varchar(100) NOT NULL,
  `STOCKS_QUANTITY` varchar(1000) NOT NULL,
  `STOCKS_LOCATION` varchar(5) NOT NULL,
  `STOCKS_PRICE` varchar(10) NOT NULL,
  `Supplier_Name` varchar(100) NOT NULL,
  `RegisterarID` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `stocks`
--

INSERT INTO `stocks` (`STOCKS_ID`, `STOCKS_NAME`, `STOCKS_CATEGORY`, `STOCKS_QUANTITY`, `STOCKS_LOCATION`, `STOCKS_PRICE`, `Supplier_Name`, `RegisterarID`) VALUES
('H000', 'ubat gigi', 'Healthcare', '571', 'A01', '12', 'colgate', 'S000'),
('H001', 'pencuci muka', 'Healthcare', '150', 'A02', '15', 'safi', 'S000'),
('H003', 'berus gigi', 'Healthcare', '100', 'A03', '13', 'darlie', 'S000'),
('F000', 'kerusi kayu', 'furniture', '90', 'B00', '129', 'ikea', 'S000'),
('K001', 'pisau dapur', 'Kitchenware', '80', 'C01', '23', 'king kong', 'S000'),
('K002', 'papan pemotong', 'Kitchenware', '94', 'C02', '32', 'king kong', 'S000'),
('F000', 'kentang', 'frozenfood', '900', 'D01', '3', 'desa farm', 'S000'),
('G000', 'ice cream', 'frozenfood', '200', 'D01', '12', 'walls', 'S000'),
('G001', 'sosej', 'frozenfood', '200', 'D02', '8', 'ayamas', 'S000'),
('V000', 'steering ', 'Vehiclepart', '90', 'F01', '55', 'momo', 'S000'),
('F001 ', 'meja bula', 'furniture', '90', 'B01', '89', 'ikea', 'A123'),
('H004', 'vitamin A', 'Healthcare', '300', 'A04', '21', 'calpis', 'S002'),
('H005', 'vitamin b5', 'Healthcare', '300', 'A05', '22', 'calpis', 'S002'),
('H006', 'vitamin c', 'Healthcare', '70', 'A06', '24', 'blackmores', 'A123');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `userID` varchar(10) NOT NULL,
  `username` varchar(100) NOT NULL,
  `userPassword` varchar(50) NOT NULL,
  `userType` varchar(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`userID`, `username`, `userPassword`, `userType`) VALUES
('A123', 'amar ibrahim', '1234', 'a'),
('S000', 'mohd malik ibrahim', '123', 'b'),
('S002', 'mohd yahya majid', '123', 'b'),
('S004', 'muhammad karim', '123', 'b'),
('S005', 'mahmud bin ahmad', '123', 'b');
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
