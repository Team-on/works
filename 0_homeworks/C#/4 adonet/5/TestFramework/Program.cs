using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

using DBUnlinked;

using System.Linq;
using System.Data.Linq;
using System.Data.Linq.Mapping;

using System.Data;
using System.Data.Common;
using System.Data.SqlClient;

namespace TestFramework {
	//[Table()]
	class Program {
		//[Column()]
		static void Main(string[] args) {
			UlDb database = new UlDb(/*@"Server=(localdb)\mssqllocaldb; Integrated Security=True", "UlTestDB"*/);
			bool isCreated = database.CreateOrLinkToDB(@"Server=(localdb)\mssqllocaldb; Integrated Security=True", "UlTestDB", false);
			Console.WriteLine($"Is create new DB: {0}", isCreated);

			UlTable<Human> table = database.CreateOrLinkToTable<Human>();
			table.Fill();

			foreach(var i in table) {
				Console.WriteLine("{0, -5} {1, -10} {2}", i.Id, i.Name, i.Surname);
			}
		}
	}
}
