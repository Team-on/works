--1. Вывести все книги, которые продаются более чем одним магазином.
select *
from Book
where 1<(
	select COUNT(Sale.IdShop)
	from Sale
	where Sale.IdBook = Book.IdBook
	group by  Sale.IdBook
)

-- 2. Вывести только тех авторов, чьи книги продаются
-- больше, чем книги авторов США.
declare @avgUSASale int
set @avgUSASale = (
	select avg(Quantity)
	from Sale
	inner join Book on Book.IdBook = Sale.IdBook
	where Book.IdAuthor=1
)
print 'Average USA author sales:' 
print @avgUSASale

select Book.IdAuthor,
avg(Quantity) as avgSale into #tmpTable
from Sale
inner join Book on Book.IdBook = Sale.IdBook
where Book.IdAuthor<>1
group by Book.IdAuthor

select *
from #tmpTable
where avgSale > @avgUSASale

-- 3. Вывести всех авторов, которые существуют в базе
-- данных с указанием (при наличии) их книг, которые издаются издательством.
select distinct Author.IdAuthor, 
	Author.FirstName + ' ' + Author.LastName as 'name'
from Author
right join Book on Book.IdAuthor = Author.IdAuthor
right join Sale on Sale.IdBook = Book.IdBook

--4. С помощью подзапросов найдите всех авторов, которые живут в странах, где есть магазин, который продает их книги.
-- Отсортировать выборку по фамилии автора.
select Author.IdAuthor, 
	Author.LastName + ' ' + Author.FirstName as 'name'
from Author
inner join Book on Book.IdAuthor = Author.IdAuthor
inner join Sale on Sale.IdBook = Book.IdBook
inner join Shop on Shop.IdShop = Sale.IdShop
where Shop.IdCountry=Author.IdCountry
order by Author.LastName

-- 5. Доказать, что книги тематики, например, "C++;" выпускаются самым большим тиражом. 
-- Примечание! Доказательством будет NULL значений, иначе – книги наиболее реализуемых тематик.
declare @theme nvarchar(32)
set @theme = (
	select top 1 Theme.NameTheme
	from Sale
	inner join Book on Book.IdBook = Sale.IdBook
	inner join Theme on Theme.IdTheme = Book.IdTheme
	group by Theme.NameTheme
	order by sum(Sale.Quantity)  desc
)

if 'C++' = @theme
	print 'Yes! ' + @theme + 'the most popular theme'
else
	print @theme + ' the most popular theme'

-- 6. Сформируйте объединения из трех запросов. 
-- Первое будет выводить список авторов, тематики книг которых, например, 'C++';
-- второе – список авторов, которые издавали свои книги в 2014 году;
-- третья выводит список самых дорогих авторов. 
-- В двух последних запросах сохраните дубликаты. Отсортировать выборку по фамилии автора по убыванию.
select top 3 Author.IdAuthor, 
		Author.LastName + ' ' + Author.FirstName as 'name' into #tmpTable
	from Author
	inner join Book on Book.IdAuthor = Author.IdAuthor
	inner join Sale on Sale.IdBook = Book.IdBook
	group by Author.IdAuthor, Author.LastName + ' ' + Author.FirstName
	order by sum(Sale.Price) desc

(
	select distinct Author.IdAuthor, 
		Author.LastName + ' ' + Author.FirstName as 'name'
	from Author
	inner join Book on Book.IdAuthor = Author.IdAuthor
	inner join Theme on Book.IdTheme = Theme.IdTheme
	where Theme.NameTheme='C++'
)
union all
(
	select Author.IdAuthor, 
		Author.LastName + ' ' + Author.FirstName as 'name'
	from Author
	inner join Book on Book.IdAuthor = Author.IdAuthor
	where year(Book.DateOfPublish)=2014
)
union all
(
	select *
	from #tmpTable
)

-- 8. Вывести имена всех авторов, книг которых не издавало еще издательство, то есть которые не присутствуют в таблице Books. 
select *
from Author
where 0=(
	select COUNT(Book.IdBook)
	from Book
	where Book.IdAuthor = Author.IdAuthor
)

-- 9. Создайте таблицу ShopAuthors, которая содержит следующие поля:
-- имя и фамилия автора, название магазина и страна.
-- Напишите команду, которая вставляла в нее всех авторов,
-- книги которых реализуются более чем одним магазином издательства
select x.FirstName, x.LastName, Shop.NameShop, Country.NameCountry into ShopAuthors
from (
	select Author.FirstName,
		Author.LastName,
		Shop.IdCountry,
		Shop.IdShop
	from Sale 
	inner join Book on Book.IdBook=Sale.IdBook
	inner join Author on Book.IdAuthor=Author.IdAuthor
	inner join Shop on Shop.IdShop=Sale.IdShop
)x
	inner join Shop on Shop.IdShop=x.IdShop
	inner join Country on Country.IdCountry=x.IdCountry

-- 10.Удалить все книги, в которых количество страниц больше, чем среднее
declare @avgPages int
set @avgPages = (
	select avg(Book.Pages)
	from Book
)

delete
from Book
where Book.Pages > @avgPages

--11.Удалить все книги, в которых не указан автор
select * --delete
from Book
where Book.IdAuthor is null

-- 12.В связи с закрытием магазинов в Англии, написать
-- запрос, который уничтожает информацию обо всех
-- магазинах, которые там размещались
select * --delete
from Shop
where Shop.IdCountry = (
	select IdCountry
	from Country
	where NameCountry=N'Англія'
)

-- 13.Изменить информацию о продаже книг, которые
-- осуществлялись одним из магазинов в Украине, например, магазином "Hash Tag" следующим образом:
-- цены на книги, которые продавались 01/07/2010 года
-- увеличить на 5%, а количество увеличить на 10 ед
update Book
Set Book.Price = Book.Price * 1.05
where Book.IdBook in (
	select Book.IdBook
	from Book
		inner join Sale on Sale.IdBook=Book.IdBook
		inner join Shop on Sale.IdShop=Shop.IdShop
	where Shop.NameShop=N'Addison-Wesley Professional' and
		Book.DateOfPublish < '2010-07-01'
)

-- 14.Уменьшить количество книг в магазинах, которые за
-- последний год продали наименьшее количество книг, на 15%.
update Shop
Set Shop.NameShop=Shop.NameShop + 'loser'
where Shop.IdShop in (
	select x.IdShop
	from (
		select top 1 Sale.IdShop, min(Sale.Price) as profit
		from Sale
		group by Sale.IdShop
		order by profit
	) x
)










