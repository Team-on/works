using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using LiteDB;
using LiteDB.Shell;

namespace Test {
	public class Company {
		public Guid Id { get; set; }
		public string Name { get; set; }
		public List<User> Users { get; set; }
	}
	public class User {
		public string Name { get; set; }
		public string Position { get; set; }
	}

	class Program {
		static void Main(string[] args) {
			using(var db = new LiteDatabase(@"MyData.db")) {
				var col = db.GetCollection<Company>("companies");

				var microsoft = new Company { Name = "Microsoft" };
				microsoft.Users = new List<User> { new User { Name = "Bill Gates" } };

				col.Insert(microsoft);

				microsoft.Name = "Microsoft Inc.";
				col.Update(microsoft);


				var google = new Company { Name = "Google" };
				google.Users = new List<User> { new User { Name = "Larry Page" } };
				col.Insert(google);

				var result = col.FindAll();
				foreach(Company c in result) {
					Console.WriteLine(c.Name);
					foreach(User u in c.Users)
						Console.WriteLine(u.Name);
					Console.WriteLine();
				}

				col.EnsureIndex(x => x.Name);

				col.Delete(x => x.Name.Equals("Google"));

				Console.WriteLine("После удаления Google");
				result = col.FindAll();
				foreach(Company c in result) {
					Console.WriteLine(c.Name);
					foreach(User u in c.Users)
						Console.WriteLine(u.Name);
					Console.WriteLine();
				}
			}
		}
	}
}
