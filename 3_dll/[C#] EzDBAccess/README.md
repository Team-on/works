# EzDBAccess
 Access to MS SQL Server like to List<T>

## Features
 * Work with DB like its List<T>. No additional methods.
 
## How to use
```С#
class DataExample{
	//Property Id MUST be public
	//But it will set auto
	public int Id{ get; set; }
	//Only props with public get and set will be save in DB
	//Works with: int, string
	public string UserData{ get; set; }

	public DataExample() : this("Empty") { } 
	public DataExample(string str) => UserData = str;
}

class Program {
	static void Main(string[] args) {
		//Database=master
		//DB and table will create auto
		//DB name: ClassName + s
		//Table name: ClassName
		var list = new EzDBList<DataExample>("System.Data.SqlClient", @"Server=(localdb)\mssqllocaldb; Database=master; Integrated Security=True");

		list.Add(new DataExample("Value1")); // Id 1
		list.Add(new DataExample("Value2")); // Id 2
		list.Add(new DataExample("Value3")); // Id 3

		//Find example
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

		//Delete example
		list.Remove(find2);

		foreach(var i in list)
			Console.WriteLine($"foreach: {i.Id, -3} {i.UserData}");
		Console.WriteLine();
	}
}
```

## API
 * **EzDBList(string providerName, string connectionStr, bool ForceRecreate)**
	* *providerName* - DbProvider name(like System.Data.ProviderName). Works only with System.Data.SqlClient (MS SQL Server)
	* *connectionStr* - Connection string. Must contain Database=master
	* *ForceRecreate* - force recreate DB. Add data will be deleted
 * **void Add(T obj)** - Add element. Id will set automatically
 * **void AddRange(IEnumerable<T> obj)** - Add few elements
 * **void Remove(T obj)** - Remove element from DB and list. Compare by Id
 * **T Find(Predicate<T> predicate)** - Find by predicat.  Return first element
 * **T[] FindAll(Predicate<T> predicate)** - Find by predicat.  Return all elements
 * **int Count** - rows count
 * Indexar[] also overloaded, but it cant be different with Id
 
 * Class T must have public int Id{get; set;} 
 * All public props saves in table
 
## Made with
 * С#
 * ADO.NET
