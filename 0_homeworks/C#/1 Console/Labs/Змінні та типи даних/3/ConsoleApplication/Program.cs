using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication {
	class Program {
		static void Main(string[] args) {
			const double pi = Math.PI;
			double r = 1;

			r = Convert.ToDouble(Console.ReadLine());

			Console.WriteLine(pi * Math.Pow(r,2));
		}
	}
}
