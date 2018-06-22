/*1*/
ALTER TABLE Author
ADD email nvarchar(64);

/*2*/
INSERT INTO Author
	([name], surname, city, country, phone, email)
 VALUES (N'Джеффри', N'Рихтер', 'NY', 'USA', '555-555-555', 'RischterDzeff@C#.net'),
	(N'Дональд Эрвин', N'Кнут', N'Милуоки', N'США', null, 'https://www-cs-faculty.stanford.edu/~knuth/'),
	(N'Роберт', N'Мартин', null, N'США', null, 'RefactorerCoder@gmail.com'),
	(N'Стив', N'Макконнелл', null, N'США', null, 'CleanCoder@gmail.com');

/*3*/
UPDATE Author 
SET email = 'authors@gmail.com' 
WHERE email is null;

/*4*/
SELECT name, surname, email
INTO newAuthor
FROM Author;

/*5*/
SELECT *
INTO BookForDelete
FROM Book;	
DELETE FROM BookForDelete 
WHERE year(date) < 2000;