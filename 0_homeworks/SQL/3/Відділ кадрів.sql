USE HotelDB;

select
	Worker.FirstName as 'Імя',
	Worker.Lastname as 'Прізвище',
	Position.PositionName as 'Посада',
	Position.Salary as 'Зарплата'
from Worker INNER JOIN Position ON(Worker.IdPosition=Position.IdPosition)