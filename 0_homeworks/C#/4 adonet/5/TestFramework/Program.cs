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

			table.Add(new Human("wsdefr", "asg"));
			table.Add(new Human("2", "2s"));
			table.Add(new Human("3", "3s"));
			table.Add(new Human("4", null));
			table.Add(new Human("5", null));

			table.Update();

			table.Clear();
			table.Fill();
			PrintTable(table);


			var non5 = table.Find((a) => a.Name == "5");
			table.Remove(non5);
			table.Update();

			table.Clear();
			table.Fill();
			PrintTable(table);
		}

		static void PrintTable(dynamic table) {
			var columnNames = table.GetColumnNames();
			Console.WriteLine("{0, -5} {1, -10} {2}", columnNames[0], columnNames[1], columnNames[2]);
			foreach(var i in table)
				Console.WriteLine("{0, -5} {1, -10} {2}", i.Id, i.Name, i.Surname ?? "NULL");
			Console.WriteLine();
		}
	}
}
