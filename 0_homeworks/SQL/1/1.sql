use OneMorePubs

select
	Author.name as 'Імя',
	Author.surname as 'Прізвище',
	Author.city as 'Місто',
	Author.country as 'Країна'
	
from 
	Author

where 
	surname LIKE N'Гослин'