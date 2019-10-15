using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1 {
	class Program {
		static void Main(string[] args) {
			int a, b, c;

			a = Convert.ToInt32(Console.ReadLine());
			b = Convert.ToInt32(Console.ReadLine());
			c = Convert.ToInt32(Console.ReadLine());

			Console.WriteLine((a + b + c) / 3.0);
		}
	}
}
