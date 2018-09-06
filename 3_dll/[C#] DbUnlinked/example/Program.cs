using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

using DBUnlinked;

/*
using System.Linq;
using System.Data.Linq;
using System.Data.Linq.Mapping;
*/

using System.Data;
using System.Data.Common;
using System.Data.SqlClient;

namespace TestFramework {
	class Program {
		static void Main(string[] args) {
			UlDb database = new UlDb(/*@"Server=(localdb)\mssqllocaldb; Integrated Security=True", "UlTestDB"*/);
			bool isCreated = database.CreateOrLinkToDB(@"Server=(localdb)\mssqllocaldb; Integrated Security=True", "UlTestDB", true);
			Console.WriteLine("Is create new DB: {0}\n", isCreated);

			UlTable<Human> table = database.CreateOrLinkToTable<Human>();
			table.Fill();

			table.Add(new Human("Shiro", "Shirogane"));
			table.Add(new Human("Keith", null));
			table.Add(new Human("Lance", null));
			table.Add(new Human("Pidge", "Holt"));
			table.Add(new Human("Hunk", null));
			table.Add(new Human("Allura", null));
			table.Add(new Human("Coran", "Hieronymus Wimbleton Smythe"));
			table.Update();

			//Clear і Fill треба лише для перевірки роботи. Викликати після кожного Update їх не обовязково
			table.Clear();
			table.Fill();
			PrintTable(table);


			var todelete = table.Find((a) => a.Name == "Allura");
			table.Remove(todelete);
			todelete = table.Find((a) => a.Name == "Coran");
			table.Remove(todelete);
			table.Update();

			table.Clear();
			table.Fill();
			PrintTable(table);

			var find = table.Find((a) => a.Surname == "Holt");
			find.Name = "Katie";
			table.Update();

			table.Clear();
			table.Fill();
			PrintTable(table);
		}

		static void PrintTable(dynamic table) {
			var columnNames = table.GetColumnNames();
			Console.WriteLine("=> table:");
			Console.WriteLine("{0, -5} {1, -10} {2}", columnNames[0], columnNames[1], columnNames[2]);
			foreach(var i in table)
				Console.WriteLine("{0, -5} {1, -10} {2}", i.Id, i.Name, i.Surname ?? "NULL");
			Console.WriteLine();
		}
	}
}
