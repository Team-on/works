using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1 {
	class Program {
		static void Main(string[] args) {
			const double pi = Math.PI;
			double r, h;

			r = Convert.ToDouble(Console.ReadLine());
			h = Convert.ToDouble(Console.ReadLine());

			Console.WriteLine($"V: {pi * Math.Pow(r, 3) * h}");
			Console.WriteLine($"S: {2 * pi * r * (r + h)}");
		}
	}
}
