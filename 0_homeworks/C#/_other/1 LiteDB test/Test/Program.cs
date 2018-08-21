using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.IO;

using LiteDB;
using LiteDB.Shell;

namespace Test {
	///http://www.litedb.org/

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
				microsoft.Users = new List<User> { new User { Name = "Bill Gates" }, new User() { Name = "MS user" } };
				col.Insert(microsoft);

				var google = new Company { Name = "Google" };
				google.Users = new List<User> { new User { Name = "Larry Page" }, new User() { Name = "Google user" } };
				col.Insert(google);

				microsoft.Name = "Microsoft Inc.";
				col.Update(microsoft);

				foreach(Company c in col.FindAll()) {
					Console.WriteLine(c.Name);
					foreach(User u in c.Users)
						Console.WriteLine(u.Name);
					Console.WriteLine();
				}

				col.EnsureIndex(x => x.Name);
				col.Delete(x => x.Name.Equals("Google"));

				Console.WriteLine("После удаления Google");
				foreach(Company c in col.FindAll()) {
					Console.WriteLine(c.Name);
					foreach(User u in c.Users)
						Console.WriteLine(u.Name);
					Console.WriteLine();
				}


				db.FileStorage.Upload("image.jpg", @"D:\home\Arthasdeathknight.jpg");
				db.FileStorage.FindById("image.jpg").SaveAs(@"D:\ArthasdeathknightFromDB.jpg");
			}
			

		}
	}
}
