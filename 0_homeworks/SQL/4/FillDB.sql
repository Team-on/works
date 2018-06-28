USE Publichers;

insert into Country
 (NameCountry)
 values
 (N'США'), --1
 (N'Канада'),--2
 (N'Королевство Нидерландов'),--3
 (N'Дания'),--4
 (N'Англія'),--5
 (N'Румунія')--6

insert into Author
 (FirstName, LastName, IdCountry)
 values
 (N'Петер', N'Наур', 4),
 (N'Гарольд', N'Абельсон', 1),
 (N'Кеннет', N'Айверсон', 2),
 (N'Андре́й', N'Александре́ску', 6),
 (N'Альфред', N'Ахо', 2),
 (N'Джереми', N'Ашкенас', 1),
 (N'Эдсгер Вибе', N'Дейкстра', 3),
 (N'Джеймс', N'Гослинг', 2),
 (N'Джон Джордж', N'Кемени', 1),
 (N'Брайан Уилсон', N'Керниган', 2),
 (N'Дональд Эрвин', N'Кнут', 1),
 (N'Джон', N'Маккарти', 1),
 (N'Роб', N'Пайк', 2),
 (N'Бьёрн', N'Страуструп', 4),
 (N'Андерс', N'Хейлсберг', 4)
 
 insert into Theme
 (NameTheme)
 values
 (N'C++'),--1
 (N'C#'),--2
 (N'Java'),--3
 (N'.NET'),--4
 (N'Алгоритми'),--5
 (N'ALGOL 60'),--6
 (N'Наука'),--7
 (N'ІТ загальне'),--8
 (N'Бізнес'), --9
 (N'Математика'), --10
 (N'APL'), --11
 (N'D'), --12
 (N'Компілятори'), --13
 (N'C'), --14
 (N'Go'), --15
 (N'UNIX') --16

insert into Book
(IdAuthor, IdTheme, Price, Pages, DateOfPublish, DrawingOfBook, NameBook)
values
(1, 6, 600, 314, '1960-05-01', N'None', N'Report on the algorithmic language ALGOL 60'),
(1, 8, 400, 231, '1969-01-01', N'None', N'Software Engineering'),
(2, 8, 350, 155, '1996-01-01', N'None', N'Structure and Interpretation of Computer Programs'),
(2, 10, 450, 234, '1981-01-01', N'None', N'Turtle Geometry: The Computer As a Medium'),
(2, 9, 450, 223, '2008-01-01', N'None', N'Blown to Bits: Your Life, Liberty, and Happiness'),
(3, 11, 1000, 455, '1962-01-01', N'None', N'A Programming Language'),
(3, 11, 1000, 593, '1991-01-01', N'None', N'A Personal View of APL'),
(4, 1, 550, 224, '2014-01-01', N'None', N'Стандарты программирования на С++'),
(4, 12, 100, 363, '2008-01-01', N'None', N'The D Programming Language'),
(5, 13, 1500, 672, '2007-01-01', N'None', N'Compilers: Principles, Techniques, & Tools'),
(5, 13, 1300, 614, '1978-01-01', N'None', N'The Theory of Parsing, Translation, and Compiling'),
(7, 8, 50, 7, '1975-01-01', N'None', N'О вреде оператора GOTO'),
(7, 8, 250, 110, '1966-01-01', N'None', N'Дисциплина программирования'),
(8, 3, 790, 672, '2015-01-01', N'None', N'Язык программирования Java SE 8'),
(8, 3, 1200, 624, '2001-01-01', N'None', N'The Java Programming Language'),
(9, 10, 450, 484, '1965-01-01', N'None', N'Введение в конечную математику'),
(9, 10, 300, 271, '1970-01-01', N'None', N'Конечные цепи Маркова. '),
(10, 14, 500, 288, '2007-01-01', N'None', N'Язык программирования C'),
(10, 15, 850, 432, '2016-01-01', N'None', N'Язык программирования Go'),
(11, 10, 1300, 632, '1980-01-01', N'None', N'Искусство программирования'),
(11, 10, 880, 725, '1997-01-01', N'None', N'Конкретная математика. Основание информатики'),
(13, 16, 800, 438, '2001-01-01', N'None', N'The UNIX Programming Environment'),
(14, 1, 1200, 1248, '2011-01-01', N'None', N'Программирование: принципы и практика использования C++'),
(14, 1, 1500, 1337, '2000-08-15', N'None', N'The C++ Programming Language'),
(15, 2, 800, 857, '2010-10-01', N'None', N'The C# Programming Language, 4th Edition'),
(15, 2, 650, 648, '2006-07-09', N'None', N'The C# Programming Language, 2th Edition')

insert into Shop
(IdCountry, NameShop)
values
(1, N'Addison-Wesley Professional'),
(1, N'Look Inna Book'),
(2, N'The Book Basement'),
(2, N'Book Addicts'),
(3, N'Books-R-Us'),
(3, N'Downtown Books'),
(4, N'Rainbow Books'),
(4, N'Uptown Books'),
(5, N'Turn the Page'),
(5, N'Peepers Books'),
(6, N'Paging All Readers!'),
(6, N'Author Attic')

insert into Sale
(IdBook, IdShop, Price, Quantity, DateOfSale)
values
(15, 1, 1300, 1, 		'2018-05-12'),
(20, 1, 1300, 1, 		'2018-09-06'),
(14, 1, 12000, 15, 		'2018-06-11'),
(13, 1, 12500, 50, 		'2018-01-08'),
(12, 2, 1500, 25, 		'2018-02-25'),
(23, 2, 120000, 100, 	'2018-05-04'),
(22, 3, 40000, 50, 		'2018-07-22'),
(2, 3, 12000, 30,		'2018-08-01'),
(8, 3, 12000, 20, 		'2018-09-05'),
(7, 4, 5000, 5, 		'2018-02-16'),
(4, 4, 2500, 5, 		'2018-01-18'),
(2, 5, 2000, 5, 		'2018-02-09'),
(4, 5, 4500, 10,		'2018-05-17'),
(3, 5, 1200, 3, 		'2018-06-02'),
(2, 5, 900, 2, 			'2018-03-09'),
(1, 6, 2400, 4, 		'2018-07-26'),
(5, 6, 450000, 100, 	'2018-08-30'),
(10, 6, 20000, 13, 		'2018-09-05'),
(13, 6, 3250, 25, 		'2018-10-14'),
(26, 6, 1350, 2, 		'2018-10-23')