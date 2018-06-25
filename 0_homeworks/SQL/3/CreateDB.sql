create database HotelDB on primary(
Name=HotelDB,
FileName='D:\code\works\0_homeworks\SQL\3\HotelDB.mdf',
Size=1,
MaxSize=64,
FILEGROWTH=1   
)

Go

USE HotelDB;

CREATE TABLE Position(
    IdPosition INT IDENTITY PRIMARY KEY,
    PositionName NVARCHAR(10) NOT NULL,
	Salary INT not null,
    Duties NVARCHAR(64),
	Requirements NVARCHAR(64)
)


CREATE TABLE Worker(
    IdWorker INT IDENTITY PRIMARY KEY,
    FirstName NVARCHAR(10) NOT NULL,
    Lastname NVARCHAR(10) NOT NULL,
	FatherName NVARCHAR(10),
	BitrhDate DATE,
	IsMan bit NOT NULL,
	Adress NVARCHAR(32),
    Phone NVARCHAR(9) NOT NULL,
	IdPasport NVARCHAR(10) NOT NULL,
	IdPosition int
	
	FOREIGN KEY (IdPosition) REFERENCES Position(IdPosition) ON DELETE CASCADE ON UPDATE CASCADE
)

CREATE TABLE Room(
    IdRoom INT IDENTITY PRIMARY KEY,
    RoomName NVARCHAR(10) NOT NULL,
	HumanCnt INT NOT NULL,
	Description NVARCHAR(64),
	Price INT NOT NULL,
	IdWorker INT
	FOREIGN KEY (IdWorker) REFERENCES Worker(IdWorker) ON DELETE CASCADE ON UPDATE CASCADE
)

CREATE TABLE Service(
    IdService INT IDENTITY PRIMARY KEY,
    ServiceName NVARCHAR(10) NOT NULL,
	Description NVARCHAR(64),
	Price INT NOT NULL
)

CREATE TABLE Client(
    IdClient INT IDENTITY PRIMARY KEY,
    FirstName NVARCHAR(10) NOT NULL,
    Lastname NVARCHAR(10) NOT NULL,
	FatherName NVARCHAR(10),
	InDate DATE NOT NULL,
	OutDate DATE NOT NULL,
	IdRoom INT,
	IdService1 INT,
	IdService2 INT,
	IdService3 INT,
	Price INT NOT NULL,
	IdWorker INT
)