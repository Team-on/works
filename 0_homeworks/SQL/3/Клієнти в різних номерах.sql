USE HotelDB;

select
	concat(Client.FirstName, ' ', Client.Lastname) as 'Клієнт',
	Client.InDate as 'Вїзд',
	Client.OutDate as 'Виїзд',
	Room.RoomName as 'Назва кімнати',
	Room.Price as 'Ціна',
	s1.ServiceName as 'Послуга 1',
	s2.ServiceName as 'Послуга 2',
	s3.ServiceName as 'Послуга 3',
	concat(Worker.FirstName, ' ', Worker.Lastname) as 'Працівник',
	Worker.Phone as  'Телефон працівника'
from Client INNER JOIN Room ON(Client.IdRoom=Room.IdRoom)
			INNER JOIN Worker ON(Client.IdWorker=Worker.IdWorker)
			INNER JOIN [Service] as s1 ON(Client.IdService1=s1.IdService)
			INNER JOIN [Service] as s2 ON(Client.IdService2=s2.IdService)
			INNER JOIN [Service] as s3 ON(Client.IdService3=s3.IdService)
where Room.IdRoom in (
	select 
	Room.IdRoom
	from Client INNER JOIN Room ON(Client.IdRoom=Room.IdRoom)
	group by Room.IdRoom
	HAVING  count(Client.IdRoom)=1
)
