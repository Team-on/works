using System;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Soap;

namespace SSMO {
	static class PizzaLoader {
		static IFormatter fs = new SoapFormatter();
		static FileStream fout;
		static Pizza piz;
		static string pizzaFolder = System.Environment.CurrentDirectory + @"\Pizza\";

		static void SerializePizza(string name, string desc, Ingradient[] ings) {
			using (fout = new FileStream(pizzaFolder + name + ".piz", FileMode.OpenOrCreate)) {
				piz = new Pizza(name, desc, ings, 65000);
				fs.Serialize(fout, piz);
			}
		}

		static Pizza BasicLoad(string name) {
			using (fout = new FileStream(pizzaFolder + name + ".piz", FileMode.Open))
				return fs.Deserialize(fout) as Pizza;
		}

		static public bool IsPizzaExist() {
				return Directory.Exists(pizzaFolder;
		}


	}
}
