using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Data.SqlClient;


using EzDBAccess;

namespace TestMyLib {
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
			//3 аргумент - примусово видалити БД та створити нову
			var list = new EzDBList<DataExample>("System.Data.SqlClient", @"Server=(localdb)\mssqllocaldb; Database=master; Integrated Security=True", true);

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
}
