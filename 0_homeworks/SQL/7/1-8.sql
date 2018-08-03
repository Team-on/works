/*1. В своей базе данных найдите все таблицы, которые не имеют кластеризованных индексов. Для каждой из
них добавьте кластеризованный индекс или измените первичный ключ на кластеризованный.*/

/*2. Найдите медленно выполняемые запросы. Создайте некластеризованные индексы, для повышения скорости выполнения этих запросов.*/

/*3. Возьмите одно из представлений, созданных на предыдущем занятии (в качестве домашнего задания), и превратите его в индексируемое.*/

/*4. В базе данных создайте полнотекстовый каталог.*/

/*5. Написать запрос с полнотекстовым поиском, который будет выводить названия магазинов, которые
содержат слово "книга". Вместе с названием магазина необходимо вывести страну их расположения.*/

/*6. Выполните полнотекстовый поиск всех книг, в названиях которых содержатся слова "Java", "Guide" или
"Web", при этом для каждого слова задается свой вес.*/

/*7. Напишите запрос, который в результате работы выведет книги, с указанием их авторов и рангами соответствия условию в следующем порядке важности
тематик: "Computer Science", "Science Fiction", "Web
Technologies". Для этого воспользуйтесь возможностью установки весовых коэффициентов для частей шаблона.*/

/*8. Выведите все названия магазинов, которые продавали книги после 01/01/2010. Укажите также объем
продаж книг, месторасположение магазина и ранг соответствия условию поиска. Условие: в названиях
книг встречаются следующие совпадения: "Windows" и "NET" или "Java" и "guide".
Примечание! Для запросов с полнотекстовым поиском создайте необходимые полнотекстовые индексы.
Написать следующие триггеры:
	1. Триггер, который при продаже книги автоматически
	изменяет количество книг в таблице Books. (Примечание Добавить в таблице Books необходимое поле
	количества имеющихся книг QuantityBooks).
	2. Триггер на проверку, чтобы количество продаж книг
	не превысила имеющуюся.
	3. Триггер, который при удалении книги, копирует данные о ней в отдельную таблицу "DeletedBooks".
	4. Триггер, который следит, чтобы цена продажи книги
	не была меньше основной цены книги из таблицы
	Books.
	5. Триггер, запрещающий добавления новой книги, для
	которой не указана дата выпуска и выбрасывает соответствующее сообщение об ошибке.
	6. Триггер или набор триггеров, которые запрещают
	удаление объектов любой базы данных на сервере
	(таблиц, значений по умолчанию и т.д.).
	7. Добавьте к базе данных триггер, который выполняет
	аудит изменений данных в таблице B*/