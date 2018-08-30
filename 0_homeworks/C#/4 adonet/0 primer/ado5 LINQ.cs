using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp24
{

	 static class STringoiufhgoihjfoighoifgoihu
	{
		public static int LN(this String se)
		{
			return se.Length;
		}

		public static string con(this String se,String s)
		{
			return se+s;
		}

		public static string coN(this object se, object s)
		{
			return se.ToString() + s.ToString();
		}

	}



	class Program
	{


		
		static void Main(string[] args)
		{

			string[] names = { "Tom", "Dick", "Harry", "Mary", "Jay" };


			///Console.WriteLine(names[0].coN(10).con("fghkjfihgjoifgh").Length    );

			//Console.WriteLine(STringoiufhgoihjfoighoifgoihu.con(  STringoiufhgoihjfoighoifgoihu.coN(names[0],10),  "fghkjfihgjoifgh").Length);

			//var filtered = System.Linq.Enumerable.Where(names, n => n.Length > 3);


			//IEnumerable<string> filtered = names.Where( /*n => n.Length > 4*/ n=>n.Contains("a"));


			//var filtered = names
			//		  .Where(n => n.Contains("a") && (n.Length > 3))
			//		   .OrderBy(n => n.Length)
			//		  .Select(n => n.ToUpper());//.Where(n=>n.Length>3);


			//	Console.WriteLine(filtered);


			//IEnumerable<string> filtered = Enumerable.Where(names, n => n.Contains("a"));

			//IEnumerable<string> sorted = Enumerable.OrderBy(filtered, n => n.Length);

			//IEnumerable<string> finalQuery = Enumerable.Select(sorted,n => n.ToUpper());




			//IEnumerable<string> filtered = from string n in names
			//							   where n.Contains("a")
			//							   orderby n
			//								// n;

	


			//IEnumerable<string> filtered = from n in names
			//							   where n.Contains("a")
			//                                        orderby n.Length
			//                                        select n.ToUpper(); 

			//foreach (string n in filtered)
			//	Console.WriteLine(n);

		}
	}
}
