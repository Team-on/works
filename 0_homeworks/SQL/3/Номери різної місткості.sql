USE HotelDB;

select 
	Room.RoomName as 'Назва кімнати',
	Room.HumanCnt as 'Кількість людей',
	Room.Price as 'Ціна',
	concat(Worker.FirstName, ' ', Worker.Lastname) as 'Працівник',
	Worker.Phone as  'Телефон працівника'
from Room INNER JOIN Worker ON(Room.IdWorker=Worker.IdWorker)
where Room.HumanCnt = 3