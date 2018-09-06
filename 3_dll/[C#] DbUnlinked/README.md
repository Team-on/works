# DbUnlinked
 Доступ до баз даних, як в Entity. Працює з MS SQL Server

## Фичи
 * Робота з БД як з List<T>
 * Створення таблиць на основі класів
 
## API
 * **UlDb** - клас для роботи з БД
	* **CreateOrLinkToDB(string connectionString, string dbName, bool alwaysRecreate = false)** - Створює чи привязуються до БД
		* **connectionString** - Стандартна connectionString, але без Initial Catalog
		* **dbName** - Імя БД
		* **alwaysRecreate** - завжди створювати нову БД, а не використовувати існуючу
	* Аналогічно можна викликати **bool CreateOrLinkToDB(string connectionString, string dbName, bool alwaysRecreate = false)**. Повертатиме чи була створена нова БД
	* **CreateOrLinkToTable<T>()** - в якості T передається клас, який буде таблицею. Повертає **UlTable<T>**
   
 * **UlTable<T>** - клас для роботи з таблицями
	* Наслідує IEnumerable<T>, і дублює більшість методів IList<T>
	* **Fill()** - Зчитує всю таблицю з БД
	* **Update()** - Вносить зміни з локальної копії у таблицю з БД
	* **UlTableColumnAttribute[] GetColumnAttributes()** - Повертає масив атрибутів стовбців
	* Підтримувані типи для автоматичного визначення: 
		* System.Byte
		* System.Int16
		* System.Int32
		* System.Int64
		* System.Float
		* System.Double
		* System.Decimal
		* System.DateTime
		* System.String (буде nvarchar(100))
		* Для всіх інших буде nvarchar(100) а зберігатися  .ToString()
	
 * Для того щоб **UlTable<T>** працював з класом типу T, то:
	* В класу може бути атрибут **UlTable**. Якщо його не буде то інформація створиться автоматично
		* **string name** - імя таблиці
	* В його публічних властивостей має бути атрибут **UlTableColumn**
		* **bool isPrimaryKey** - Чи буде ця властивість ключем
		* **bool notNull** - чи допускає вона NULL. Ігнорується при isPrimaryKey = true
		* **string dbType** - тип даних в таблиці
		* **string name** - імя колонки в таблиці
		* Якщо якесь поле залишити незаповненим то воно заповниться автоматично

 
## Зроблено на
 * С#
 * ADO.NET