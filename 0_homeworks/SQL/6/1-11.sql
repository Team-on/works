/*1. Написать представление, в котором необходимо
вывести перечень магазинов с указанием их места
расположения. При этом название страны следует
вывести на английском языке и в сокращенном виде
(например, United States – US).*/
IF OBJECT_ID ( 'dbo.tmpTable', N'U' ) IS NOT NULL   
    DROP table dbo.tmpTable;  
GO 

select * into tmpTable
from Country

update tmpTable set NameCountry='USA'
where NameCountry=N'США'
update tmpTable set NameCountry=N'Can'
where NameCountry=N'Канада'
update tmpTable set NameCountry=N'NIC'
where NameCountry=N'Королевство Нидерландов'
update tmpTable set NameCountry=N'Dan'
where NameCountry=N'Дания'
update tmpTable set NameCountry=N'Ang'
where NameCountry=N'Англія'
update tmpTable set NameCountry=N'Rum'
where NameCountry=N'Румунія'


select Shop.NameShop,
	tmpTable.NameCountry
from Shop
inner join tmpTable on tmpTable.IdCountry = Shop.IdCountry

/*2. Написать запрос, который изменяет данные в таблице Books следующим образом: если книги были изданы после 2008 года, тогда их тираж увеличить на
1000 екзмпляров, иначе тираж увеличить на 100 ед.
Примечание! Воспользоваться инструкцией CASE.*/
update Book set Price = Price +
case 
	when Year(DateOfPublish) > 2008 then 1000
	else 100
end

/*3. Написать виртуальное представление, которое выводит общее количество продаж и дату последней
реализации для каждого магазина.*/
declare @allSale int
set @allSale = (
	select count(Sale.IdSale)
	from Sale
)

print 'All sales cnt:'
print @allSale

select Shop.NameShop,
	max(Sale.DateOfSale) as N'Last sale'
from Sale
inner join Shop on Shop.IdShop = Sale.IdShop
group by Shop.NameShop

/*4. Создать хранимую процедуру, которая выводит на
экран список магазинов, которые продали хотя бы
одну книгу Вашего издательства. Указать также месторасположение (страну) магазина.*/
IF OBJECT_ID ( 'ShopList', N'P' ) IS NOT NULL   
    DROP procedure ShopList;  
GO 

create procedure ShopList
 @AuthorId int
 as begin
	select Shop.NameShop,
		Country.NameCountry
	from Sale
	inner join Shop on Shop.IdShop=Sale.IdShop
	inner join Book on Book.IdBook=Sale.IdBook
	inner join Country on Country.IdCountry=Shop.IdCountry
	where Book.IdAuthor=@AuthorId
	group by Shop.NameShop, Country.NameCountry
end

GO

exec ShopList 1

/*5. Написать процедуру, позволяющую просмотреть все
книги определенного автора, при этом его имя передается при вызове*/
IF OBJECT_ID ( 'AuthorBooksList', N'P' ) IS NOT NULL   
    DROP procedure AuthorBooksList;  
GO 

create procedure AuthorBooksList
 @AuthorFirstName nvarchar(32)
 as begin
	select [IdBook]
      ,[IdTheme]
      ,[NameBook]
      ,[Price]
      ,[Pages]
      ,[DateOfPublish]
      ,[DrawingOfBook]
	from Book
	inner join Author on Author.IdAuthor=Book.IdAuthor
	where Author.FirstName=@AuthorFirstName
end

GO

exec AuthorBooksList N'Петер'

/*6. Создать хранимую процедуру, которая возвращает
максимальное из двух чисел.*/
IF OBJECT_ID ( 'Max2Int', N'P' ) IS NOT NULL   
    DROP procedure Max2Int;  
GO 

create procedure Max2Int
 @a int,
 @b int,
 @rez int out
 as begin
 set @rez = @b
	if @a > @b
		set @rez = @a
end

GO

declare @rez int
exec Max2Int 55, 20, @rez out
print @rez

/*7. Написать процедуру, которая выводит на экран книги и цены по указанной тематике. При этом необходимо указывать направление сортировки: 0 – по цене,
по росту, 1 – по убыванию, любое другое – без сортировки.*/
IF OBJECT_ID ( 'ListBooksByTheme', N'P' ) IS NOT NULL   
    DROP procedure ListBooksByTheme;  
GO 

create procedure ListBooksByTheme
 @orderByType int
 as begin
	if @orderByType=1 
		select Theme.NameTheme,
			avg(Book.Price) as Avg_price
		from Book
		inner join Theme on Theme.IdTheme = Book.IdTheme
		group by Theme.NameTheme
		order by avg(Book.Price) desc
	else if @orderByType=0 
		select Theme.NameTheme,
			avg(Book.Price) as Avg_price
		from Book
		inner join Theme on Theme.IdTheme = Book.IdTheme
		group by Theme.NameTheme
		order by avg(Book.Price)
	else 
		select Theme.NameTheme,
			avg(Book.Price) as Avg_price
		from Book
		inner join Theme on Theme.IdTheme = Book.IdTheme
		group by Theme.NameTheme
end
	

GO

exec ListBooksByTheme 0


/*8. Написать процедуру, которая возвращает полное имя
автора, книг которого больше всех было издано.*/
IF OBJECT_ID ( 'MostProductiveAuthor', N'P' ) IS NOT NULL   
    DROP procedure MostProductiveAuthor;  
GO 

create procedure MostProductiveAuthor
 @autName nvarchar(32) out
 as begin
	set @autName = (
		select top 1 Author.FirstName + ' ' + LastName
		from Book
			inner join Author on Author.IdAuthor=Book.IdAuthor
		group by  Author.FirstName + ' ' + LastName
		order by count(Book.IdBook) desc
	)
end
	

GO

declare @author nvarchar(32)
exec MostProductiveAuthor @author out
print @author

/*9. Написать процедуру для расчета факториала числа.*/
IF OBJECT_ID ( 'Factorial', N'P' ) IS NOT NULL   
    DROP procedure Factorial;  
GO 

create procedure Factorial
 @factorial int,
 @outMult int out
 as begin
	set @outMult = 1
	while @factorial > 1 begin
		set @outMult = @outMult * @factorial
		set @factorial = @factorial - 1
	end
end
	

GO

declare @outMult int
exec Factorial 5, @outMult out
print @outMult

/*10.Написать хранимую процедуру, которая позволяет
увеличить дату издательства каждой книги, которая
соответствует шаблону на 2 года. Шаблон передается
в качестве параметра в процедуру.*/
IF OBJECT_ID ( 'IncreaceDateOfPublish', N'P' ) IS NOT NULL   
    DROP procedure IncreaceDateOfPublish;  
GO 

create procedure IncreaceDateOfPublish
 @template nvarchar(32)
 as begin	
	update Book set DateOfPublish = DATEADD(YEAR, 20, DateOfPublish)
	where Book.NameBook like @template
end
	

GO

exec IncreaceDateOfPublish N'%C++%'
select *
from Book

/*11.Написать хранимую процедуру с параметрами, определяющими диапазон дат выпуска книг. Процедура
позволяет обновить данные о тираже выпуска книг
по следующим условиям:
• Если дата выпуска книги находится в определенном диапазоне, тогда тираж нужно увеличить в два
раза, а цену за единицу увеличить на 20%;
• Если дата выпуска книги не входит в диапазон,
тогда тираж оставить без изменений.
Предусмотреть вывод на экран соответствующих сообщений об ошибке, если передаваемые даты одинаковые,
или конечная дата промежутка меньше начала, или же
начальная больше текущей даты.*/
IF OBJECT_ID ( 'IncreacePriceInInterval', N'P' ) IS NOT NULL   
    DROP procedure IncreacePriceInInterval;  
GO 

create procedure IncreacePriceInInterval
 @startDate date,
 @endDate date
 as begin	
	if @startDate > @endDate begin
		print N'@startDate > @endDate'
		return
	end
	if @startDate = @endDate begin
		print N'@startDate == @endDate'
		return
	end
	if @startDate > GETDATE() begin
		print N'@startDate > now'
		return
	end


	update Book set Book.Price = 
	case
		when @startDate <= Book.DateOfPublish and Book.DateOfPublish <= @endDate then Price * 1.20
		else Price
	end
end
	

GO

select *
from Book
exec IncreacePriceInInterval '1900-01-01', '2000-01-01'
select *
from Book