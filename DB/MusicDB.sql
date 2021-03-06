-- MySQL Script generated by MySQL Workbench
-- Mon Jun  6 23:00:25 2022
-- Model: New Model    Version: 1.0
-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema MusicStore
-- -----------------------------------------------------

-- -----------------------------------------------------
-- Schema MusicStore
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `MusicStore` ;
USE `MusicStore` ;

-- -----------------------------------------------------
-- Table `MusicStore`.`Person`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `MusicStore`.`Person` (
  `Profession` VARCHAR(50) NOT NULL DEFAULT 'Исполнитель',
  `AName` VARCHAR(10) NULL,
  `PName` VARCHAR(50) NULL,
  PRIMARY KEY (`Profession`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `MusicStore`.`ansamble`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `MusicStore`.`ansamble` (
  `Aname` VARCHAR(50) NOT NULL,
  PRIMARY KEY (`Aname`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `MusicStore`.`Plate`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `MusicStore`.`Plate` (
  `id` INT NOT NULL,
  `Date` VARCHAR(10) NULL,
  `MAddress` VARCHAR(45) NULL,
  `MName` VARCHAR(45) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `MusicStore`.`PlateStat`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `MusicStore`.`PlateStat` (
  `id` INT NOT NULL,
  `OptPrice` FLOAT NULL,
  `Price` FLOAT NULL,
  `SellLastYear` INT NULL,
  `SellCurtYear` INT NULL,
  `InShop` INT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `MusicStore`.`Record`
-- -----------------------------------------------------
CREATE TABLE IF NOT EXISTS `MusicStore`.`Record` (
  `id` INT NOT NULL,
  `title` VARCHAR(50) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
