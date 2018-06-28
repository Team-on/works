USE Publichers;

--1. Показать все книги трех произвольных авторов.
Select * 
From Book
Where IdAuthor in (
	SELECT TOP 3 IdAuthor 
	FROM Author
	ORDER BY NEWID()
)

--2. Показать все книги, в которых количество страниц больше 500, но меньше 650.
Select * 
From Book
Where 500 < Pages and Pages < 650 

--3. Необходимо вывести все названия книг, в которых первая буква или А, или С
Select * 
From Book
Where NameBook like '[A, C, А, С]%'

--4. Показать названия книг, тематика которых не "C++" и тираж которых >=20 экземпляров
Select IdBook as N'ID книги',
	Author.FirstName + ' ' + Author.LastName as N'Автор',
	NameTheme as N'Тема',
	NameBook as N'Назва',
	Price as N'Ціна',
	Pages as N'Сторінки',
	DateOfPublish as N'Дата виходу'
From Book inner join Theme on(Book.IdTheme=Theme.IdTheme) inner join Author on(Book.IdAuthor=Author.IdAuthor)
Where IdBook in (
	SELECT IdBook
	FROM Sale
	where Quantity >= 20
	group by IdBook
) 
and Book.IdTheme in (
	SELECT IdTheme
	FROM Theme
	where NameTheme <> N'C++'
) 

--5. Показать все книги-новинки, цена которых ниже 500.
--(Новинкой будет считаться книга, которая была издана на протяжении последних 5 лет).
Select IdBook as N'ID книги',
	Author.FirstName + ' ' + Author.LastName as N'Автор',
	NameTheme as N'Тема',
	NameBook as N'Назва',
	Price as N'Ціна',
	Pages as N'Сторінки',
	DateOfPublish as N'Дата виходу'
From Book inner join Theme on(Book.IdTheme=Theme.IdTheme) inner join Author on(Book.IdAuthor=Author.IdAuthor)
Where Year(DateOfPublish)+5>=Year(GETDATE())

--6. Показать книги, в названиях которых есть слово "Язык программирования", но нет слова "Java".
Select IdBook as N'ID книги',
	Author.FirstName + ' ' + Author.LastName as N'Автор',
	NameTheme as N'Тема',
	NameBook as N'Назва',
	Price as N'Ціна',
	Pages as N'Сторінки',
	DateOfPublish as N'Дата виходу'
From Book inner join Theme on(Book.IdTheme=Theme.IdTheme) inner join Author on(Book.IdAuthor=Author.IdAuthor)
Where NameBook like N'%Язык программирования%' and not NameBook like N'%Java%'

--7. Вывести названия книг, тематику, автора (полное имя),
-- цена одной страницы которых менее 1
Select IdBook as N'ID книги',
	Author.FirstName + ' ' + Author.LastName as N'Автор',
	NameTheme as N'Тема',
	NameBook as N'Назва',
	Price as N'Ціна',
	Pages as N'Сторінки',
	DateOfPublish as N'Дата виходу'
From Book inner join Theme on(Book.IdTheme=Theme.IdTheme) inner join Author on(Book.IdAuthor=Author.IdAuthor)
Where Price / Pages < 1

--8. Вывести информацию обо всех книгах, в имени которых больше 4-х слов.
Select IdBook as N'ID книги',
	Author.FirstName + ' ' + Author.LastName as N'Автор',
	NameTheme as N'Тема',
	NameBook as N'Назва',
	Price as N'Ціна',
	Pages as N'Сторінки',
	DateOfPublish as N'Дата виходу'
From Book inner join Theme on(Book.IdTheme=Theme.IdTheme) inner join Author on(Book.IdAuthor=Author.IdAuthor)
Where NameBook like N'% % % %'

--9. Вывести на экран все книги, их авторов и цены их
--продажи в у.е., дата продажи которых находится
--в диапазоне 01/01/2007 по сегодняшнюю дату.
Select IdBook as N'ID книги',
	Author.FirstName + ' ' + Author.LastName as N'Автор',
	NameTheme as N'Тема',
	NameBook as N'Назва',
	Price as N'Ціна',
	Pages as N'Сторінки',
	DateOfPublish as N'Дата виходу'
From Book inner join Theme on(Book.IdTheme=Theme.IdTheme) inner join Author on(Book.IdAuthor=Author.IdAuthor)
Where '2007-01-01' < DateOfPublish and DateOfPublish < GETDATE()

--10. Показать всю информацию по продажам книг в следующем виде:
--■ название книги;
--■ тематик, которые касаются "Computer Science";
--■ автор книги (полное имя);
--■ цена продажи книги;
--■ имеющееся количество продаж данной книги;
--■ название магазина, который находится не в Украине
-- и не в Канаде и продает эту книгу.

Select Book.IdBook as N'ID книги',
	Author.FirstName + ' ' + Author.LastName as N'Автор',
	NameTheme as N'Тема',
	NameBook as N'Назва',
	Sale.Price as N'Ціна',
	Sale.Quantity as N'Кількість',
	Shop.NameShop as N'Магазин'
From Book inner join Theme on(Book.IdTheme=Theme.IdTheme)
 inner join Author on(Book.IdAuthor=Author.IdAuthor)
 inner join Sale on(Sale.IdBook=Book.IdBook)
 inner join Shop on(Shop.IdShop=Sale.IdShop)
 where Shop.IdCountry in (
 select IdCountry
 from Country
 where Country.NameCountry=N'Канада' or Country.NameCountry=N'Україна'
 )
 and Book.IdTheme in (
 select IdTheme
 from Theme
 where Theme.NameTheme=N'ІТ загальне'
 )

--11.Показать количество авторов в базе данных. Результат сохранить в другую таблицу.
Select Count(Author.IdAuthor) as 'Author count'
--into AuthortCount
From Author

--12.Показать среднеарифметическую цену продажи всех книг. 
--Результат сохранить в локальную временную таблицу.
Select avg(Sale.Price) as 'average sale.price'
--into #AvgSale
From Sale

--13.Показать тематики книг и сумму страниц по каждой из них.
select NameTheme,
	sum(Book.Pages)
from Theme inner join Book on(Theme.IdTheme=Book.IdTheme)
group by Theme.NameTheme

--14.Вывести количество книг и сумму страниц этих книг
--по каждому из первых трех (!) авторов в базе данных.
select Top 3 FirstName + ' ' + LastName as 'name',
		Count(Book.IdBook) as 'book count',
		Sum(Book.Pages) as 'pages sum'
from Author inner join Book on(Book.IdAuthor=Author.IdAuthor)
group by FirstName + ' ' + LastName

--15.Вывести информацию о книгах по "Computer Science"
--с наибольшим количеством страниц.
Select IdBook as N'ID книги',
	Author.FirstName + ' ' + Author.LastName as N'Автор',
	NameTheme as N'Тема',
	NameBook as N'Назва',
	Price as N'Ціна',
	Pages as N'Сторінки',
	DateOfPublish as N'Дата виходу'
From Book inner join Theme on(Book.IdTheme=Theme.IdTheme) inner join Author on(Book.IdAuthor=Author.IdAuthor)
where Book.IdTheme = 8 
and Book.Pages = (
	select max(Book.Pages)
	from Book
	where Book.IdTheme=8
) 

--16.Показать авторов и самую старую книгу по каждому
--из них. Результат сохранить в глобальную временную таблицу.
Select IdBook as N'ID книги',
	Author.FirstName + ' ' + Author.LastName as N'Автор',
	NameTheme as N'Тема',
	NameBook as N'Назва',
	Price as N'Ціна',
	Pages as N'Сторінки',
	DateOfPublish as N'Дата виходу'
From Book inner join Theme on(Book.IdTheme=Theme.IdTheme) inner join Author on(Book.IdAuthor=Author.IdAuthor)
where Book.IdBook=(
	select IdBook
	from Book
	where Book.IdAuthor=Author.IdAuthor and Book.DateOfPublish=(
		select Min(DateOfPublish)
		from Book
		where Book.IdAuthor=Author.IdAuthor
	)
)

--17.Показать на экран среднее количество страниц по каждой из тематик, при этом показать только тематики,
--в которых среднее количество более 400.
select NameTheme,
	sum(Book.Pages) as pages
from Theme inner join Book on(Theme.IdTheme=Book.IdTheme)
where pages>400
group by Theme.NameTheme


--18.Показать на экран сумму страниц по каждой из тематик, при этом учитывать только книги с количеством
--страниц более 300, но учитывать при этом только 3 тематики,
--например "Computer Science", "Science Fiction" и "Web Technologies".
select NameTheme,
	sum(Book.Pages) as pages
from Theme inner join Book on(Theme.IdTheme=Book.IdTheme)
where pages>300 and 
	(Theme.NameTheme like N'C#' or
	 Theme.NameTheme like N'C++' or
	 Theme.NameTheme like N'C')
group by Theme.NameTheme

--19.Показать количество проданных книг по каждому магазину, 
--в промежутке от 01/01/2007 до сегодняшней даты.
Select NameShop,
	Sum(Sale.Quantity) as Sell
From Shop 
inner join Sale on(Sale.IdShop=Shop.IdShop)
Where '2007-01-01' < Sale.DateOfSale and Sale.DateOfSale < GETDATE()
group by NameShop

--20.Вывести всю информацию о работе магазинов:
--что, когда, сколько и кем было продано, а также указать страну,
--где находится магазин. Результат сохранить в другую таблицу.
select IdSale,
	NameCountry,
	NameShop,
	NameBook,
	Quantity,
	Sale.Price
 --into NewTable
from Sale
inner join Shop on(Shop.IdShop=Sale.IdShop)
inner join Book on(Book.IdBook=Sale.IdBook)
inner join Country on(Country.IdCountry=Shop.IdCountry)
