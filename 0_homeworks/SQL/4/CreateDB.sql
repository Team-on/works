create database Publichers on primary(
Name=Publichers,
FileName='D:\code\works\0_homeworks\SQL\4\Publichers.mdf',
Size=1,
MaxSize=64,
FILEGROWTH=1   
)

Go
USE Publichers;

CREATE TABLE Country(
    IdCountry INT IDENTITY PRIMARY KEY,
    NameCountry NVARCHAR(32) NOT NULL
)

CREATE TABLE Theme(
    IdTheme INT IDENTITY PRIMARY KEY,
    NameTheme NVARCHAR(32) NOT NULL
)

CREATE TABLE Author(
	IdAuthor  INT IDENTITY PRIMARY KEY,
    FirstName NVARCHAR(32) NOT NULL,
	LastName  NVARCHAR(32) not null,
	IdCountry INT not null
	
	FOREIGN KEY (IdCountry) REFERENCES Country(IdCountry) ON DELETE CASCADE ON UPDATE CASCADE
)

create table Book(
	IdBook  INT IDENTITY PRIMARY KEY,
	IdAuthor  INT not null,
	IdTheme  INT not null,
	NameBook NVARCHAR(64) NOT NULL,
	Price INT not null,
	Pages  INT not null,
	DateOfPublish DATE not null,
	DrawingOfBook NVARCHAR(32) not null
	
	FOREIGN KEY (IdAuthor) REFERENCES Author(IdAuthor) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (IdTheme) REFERENCES Theme(IdTheme) ON DELETE CASCADE ON UPDATE CASCADE
)


CREATE TABLE Shop(
    IdShop INT IDENTITY PRIMARY KEY,
    NameShop NVARCHAR(32) NOT NULL,
	IdCountry INT not null
	
	FOREIGN KEY (IdCountry) REFERENCES Country(IdCountry) ON DELETE CASCADE ON UPDATE CASCADE
)

CREATE TABLE Sale(
	IdSale  INT IDENTITY PRIMARY KEY,
	IdBook  INT not null,
	IdShop  INT not null,
	Price INT not null,
	Quantity  INT not null,
	DateOfSale DATE not null
	
	
	FOREIGN KEY (IdBook) REFERENCES Book(IdBook) ON DELETE CASCADE ON UPDATE CASCADE,
	FOREIGN KEY (IdShop) REFERENCES Shop(IdShop) ON DELETE NO ACTION ON UPDATE NO ACTION
)