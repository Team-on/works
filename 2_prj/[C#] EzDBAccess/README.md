# EzDBAccess
 Доступ до баз даних як до звичайного List<T>

## Фичи
 * Робота з БД як з List<T>. Ніяких додаткових функцій.
 
## Як використовувати
```С#
class DataExample{
	//Властивість Id має бути завжди
	//Але встановлюється воно автоматично
	public int Id{ get; set; }
	//Опрацьовуються лише публічні властивості з публічними get та set
	//Типи властивостей: int, string. З іншими не факт що працюватиме
	public string UserData{ get; set; }

	public DataExample() : this("Empty") { } 
	public DataExample(string str) => UserData = str;
}

class Program {
	static void Main(string[] args) {
		//Database=master. Має бути завжди
		//Потім створиться потрібна БД і в ній таблиця(Якщо потрібно)
		//Імя БД: ІмяКласу + s
		//Імя таблиці: ІмяКласу
		var list = new EzDBList<DataExample>("System.Data.SqlClient", @"Server=(localdb)\mssqllocaldb; Database=master; Integrated Security=True");

		list.Add(new DataExample("Value1")); // Id 1
		list.Add(new DataExample("Value2")); // Id 2
		list.Add(new DataExample("Value3")); // Id 3

		//Пошук реалізований лише так
		DataExample find1 = list.Find(
			(a)=>a.Id==3
		);
		Console.WriteLine($"Id==3: {find1.UserData}");
		Console.WriteLine();

		DataExample find2 = list.Find(
			(a) => a.UserData == "Value2"
		);
		Console.WriteLine($"UserData == \"Value2\": {find2.UserData}");
		Console.WriteLine();

		//Видалення лише з попереднім пошуком
		list.Remove(find2);

		foreach(var i in list)
			Console.WriteLine($"foreach: {i.Id, -3} {i.UserData}");
		Console.WriteLine();
	}
}
```

## API
 * **EzDBList(string providerName, string connectionStr, bool ForceRecreate)**
	* *providerName* - Імя DbProvider у вигляді System.Data.ProviderName. Перевірялося лише з System.Data.SqlClient (MS SQL Server)
	* *connectionStr* - Стрічка налаштувань. Обовязково має бути лише Database=master
	* *ForceRecreate* - примусово перестворити БД. Всі дані будуть втрачені
 * **void Add(T obj)** - Додавання елементу. Id заповниться самостійно
 * **void AddRange(IEnumerable<T> obj)** - Додавання кількох елементів
 * **void Remove(T obj)** - Видалення елементу. Перевіряється за Id
 * **T Find(Predicate<T> predicate)** - Пошук за предикатом
 * Також є перевантаження []. Але індекс масиву не обовязково відповідатиме Id
 
 * Клас T має мати властивість public int Id{get; set;} 
 * У БД зберігаються всі властивості з публічними get та set.
 
## Зроблено на
 * С#
 * ADO.NET