use OneMorePubs

select
	Book.name as 'Назва',
	YEAR(Book.date) as 'Рік виходу',
	Book.pub_id as 'Ід видавництва'
	
from 
	Book

where 
	YEAR(Book.date) > '2000'