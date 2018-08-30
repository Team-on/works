using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

using System.Linq;
using System.Data.Linq;
using System.Data.Linq.Mapping;

namespace ConsoleApp25
{
	class Program
	{

		[Table]
		public class Student
		{
			[Column(IsPrimaryKey = true, IsDbGenerated = true)]
			public int Id { get; set; }

			[Column(Name = "Name")]
			public string FirstName { get; set; }

			[Column]
			public int Age { get; set; }
		}


		static string connectionString = @"Data Source=(localdb)\mssqllocaldb;Initial Catalog=DBB;Integrated Security=True";

		static void Main(string[] args)
		{
			DataContext db = new DataContext(connectionString);

			
			Table<Student> users = db.GetTable<Student>();


			// var query = users.Where(u => u.Age > 28).OrderBy(u => u.FirstName);

			//var query = from u in users
			//			where u.Age > 28
			//			orderby u.FirstName
			//			select u;



			//Update

			//Student user1 = users.FirstOrDefault();
			//user1.Age = 32;

			//db.SubmitChanges();




			//Insert

			//Student user1 = new Student { FirstName = "Ronald", Age = 34 };

			//users.InsertOnSubmit(user1);

			//db.SubmitChanges();


			//Delete

			//var user1 = users.OrderByDescending(u => u.Id).FirstOrDefault();

			//if (user1 != null)
			//{
			//	users.DeleteOnSubmit(user1);

			//	db.SubmitChanges();

			//}




			var query = users.GroupBy(u => u.Age);

			//var query1 = from u in users
			//			 group u by u.Age
			//			into groups
			//			 select groups;






			foreach (var group in query)
			{
				Console.WriteLine("Возраст: {0}", group.Key);
				foreach (var user in group)
					Console.WriteLine(user.FirstName);
				Console.WriteLine();
			}





			//foreach (var user in users.Take(10) /*query*/)
			//{
			//	Console.WriteLine("{0} \t{1} \t{2}", user.Id, user.FirstName, user.Age);
			//}



			Console.Read();
		}





	}
	
}
