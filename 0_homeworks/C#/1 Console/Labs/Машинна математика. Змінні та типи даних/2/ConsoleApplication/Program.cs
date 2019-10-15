using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication {
	class Program {
		static void Main(string[] args) {
			string s1 = "\nмiй рядок 1";
			string s2 = "\tмiй рядок 1";
			string s3 = "\aмiй рядок 1";

			Console.WriteLine(s1);
			Console.WriteLine(s2);
			Console.WriteLine(s3);
		}
	}
}
