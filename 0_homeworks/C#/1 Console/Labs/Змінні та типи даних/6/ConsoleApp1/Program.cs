using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1 {
	class Program {
		static void Main(string[] args) {
			int a, b;

			a = Convert.ToInt32(Console.ReadLine());
			b = Convert.ToInt32(Console.ReadLine());

			Console.WriteLine(a + b);
			Console.WriteLine(a - b);
			Console.WriteLine(a * b);
			Console.WriteLine(a / b);
			Console.WriteLine(a / (float)b);
			Console.WriteLine(a % b);
			Console.WriteLine(Math.Pow(a, b));
			Console.WriteLine(Math.Pow(b, a));
			Console.WriteLine(Math.Sqrt(a));
			Console.WriteLine(Math.Sqrt(b));
		}
	}
}
