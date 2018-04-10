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

		static void SerializePizza(string name, string desc, Ingradient[] ings, ushort MakeTime) {
			using (fout = new FileStream(pizzaFolder + name + ".piz", FileMode.OpenOrCreate)) {
				piz = new Pizza(name, desc, ings, 1.00, MakeTime);
				fs.Serialize(fout, piz);
			}
		}

		static Pizza BasicLoad(string name) {
			using (fout = new FileStream(pizzaFolder + name + ".piz", FileMode.Open))
				return fs.Deserialize(fout) as Pizza;
		}

		static public bool IsPizzaExist() {
				return Directory.Exists(pizzaFolder);
		}

		static public void CreatePizzaFile() {
			Directory.CreateDirectory(pizzaFolder);

			SerializePizza("ТестоваПіца№1", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 300 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 10 },
														new Ingradient(IngradientLoader.Grass()){MassGr = 500 },
														new Ingradient(IngradientLoader.Sausage()){MassGr = 500 }
													},
													1
			);


		}

		static public Pizza Test() {
			return BasicLoad("ТестоваПіца№1");
		}

	}
}
