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
			SerializePizza("NullPizza", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 0 },
													},
													1
			);
			
			SerializePizza("АрМар", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 500 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 25 },
														new Ingradient(IngradientLoader.TomatoSauce()){MassGr = 25 },
														new Ingradient(IngradientLoader.Grass()){MassGr = 25 },
														new Ingradient(IngradientLoader.Vetcina()){MassGr = 100 },
														new Ingradient(IngradientLoader.ItalienCheese()){MassGr = 100 },
														new Ingradient(IngradientLoader.Becon()){MassGr = 100 },
														new Ingradient(IngradientLoader.Tomato()){MassGr = 100 },
														new Ingradient(IngradientLoader.Olives()){MassGr = 100 },
														new Ingradient(IngradientLoader.Paperoni()){MassGr = 100 },

													},
													5
			);
			SerializePizza("Венеция", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 500 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 25 },
														new Ingradient(IngradientLoader.TomatoSauce()){MassGr = 25 },
														new Ingradient(IngradientLoader.Grass()){MassGr = 25 },
														new Ingradient(IngradientLoader.Vetcina()){MassGr = 100 },
														new Ingradient(IngradientLoader.ItalienCheese()){MassGr = 100 },
														new Ingradient(IngradientLoader.Salami()){MassGr = 100 },
														new Ingradient(IngradientLoader.Becon()){MassGr = 100 },
														new Ingradient(IngradientLoader.Mushroom()){MassGr = 100 },
														new Ingradient(IngradientLoader.BolgarPapper()){MassGr = 100 },
														new Ingradient(IngradientLoader.Tomato()){MassGr = 100 },
														new Ingradient(IngradientLoader.Spice()){MassGr = 10 },
													},
													5
			);
			SerializePizza("Папперони", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 500 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 25 },
														new Ingradient(IngradientLoader.TomatoSauce()){MassGr = 25 },
														new Ingradient(IngradientLoader.ItalienCheese()){MassGr = 100 },
														new Ingradient(IngradientLoader.Mushroom()){MassGr = 100 },
														new Ingradient(IngradientLoader.Olives()){MassGr = 100 },
														new Ingradient(IngradientLoader.Oregano()){MassGr = 10 },
														new Ingradient(IngradientLoader.Paperoni()){MassGr = 10 }
													},
													5
			);
			SerializePizza("Морская", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 500 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 25 },
														new Ingradient(IngradientLoader.TomatoSauce()){MassGr = 25 },
														new Ingradient(IngradientLoader.ItalienCheese()){MassGr = 100 },
														new Ingradient(IngradientLoader.Mushroom()){MassGr = 100 },
														new Ingradient(IngradientLoader.Spice()){MassGr = 10 },
														new Ingradient(IngradientLoader.Crab()){MassGr = 100 },
														new Ingradient(IngradientLoader.SeeFood()){MassGr = 100 },

													},
													5
			);
			

			SerializePizza("Рико", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 500 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 25 },
														new Ingradient(IngradientLoader.TomatoSauce()){MassGr = 25 },
														new Ingradient(IngradientLoader.ItalienCheese()){MassGr = 100 },
														new Ingradient(IngradientLoader.Spice()){MassGr = 10 },
														new Ingradient(IngradientLoader.Pineapple()){MassGr = 100 },
													},
													5
			);
			SerializePizza("Сырная", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 500 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 25 },
														new Ingradient(IngradientLoader.Mozzarela()){MassGr = 100 },
														new Ingradient(IngradientLoader.Parmezan()){MassGr = 100 },
													},
													5
			);
			SerializePizza("Грибной люкс", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 500 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 25 },
														new Ingradient(IngradientLoader.TomatoSauce()){MassGr = 25 },
														new Ingradient(IngradientLoader.ItalienCheese()){MassGr = 100 },
														new Ingradient(IngradientLoader.Spice()){MassGr = 10 },
														new Ingradient(IngradientLoader.Mushroom()){MassGr = 100 },
													},
													5
			);
			SerializePizza("Княжеская", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 500 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 25 },
														new Ingradient(IngradientLoader.TomatoSauce()){MassGr = 25 },
														new Ingradient(IngradientLoader.ItalienCheese()){MassGr = 100 },
														new Ingradient(IngradientLoader.Spice()){MassGr = 10 },
														new Ingradient(IngradientLoader.Mushroom()){MassGr = 100 },
														new Ingradient(IngradientLoader.Tomato()){MassGr = 100 },
													},
													5
			);
			SerializePizza("Фокача", "Норм", new Ingradient[] {
														new Ingradient(IngradientLoader.Flour()){MassGr = 500 },
														new Ingradient(IngradientLoader.Yeast()){MassGr = 25 },
													},
													5
			);
		}

		static public Pizza RandomPizza() {
			switch (Rand.rand.Next(0,9)) {
			case 0:
			return ArMar();
			case 1:
			return Venetia();
			case 2:
			return Papperoni();
			case 3:
			return See();
			case 4:
			return Riko();
			case 5:
			return Cheese();
			case 6:
			return MusroomLux();
			case 7:
			return King();
			case 8:
			return Fokacha();
			}
			return Null();
		}

		static public Pizza ArMar() {
			return BasicLoad("АрМар");
		}
		static public Pizza Venetia() {
			return BasicLoad("Венеция");
		}
		static public Pizza Papperoni() {
			return BasicLoad("Папперони");
		}
		static public Pizza See() {
			return BasicLoad("Морская");
		}
		static public Pizza Riko() {
			return BasicLoad("Рико");
		}
		static public Pizza Cheese() {
			return BasicLoad("Сырная");
		}
		static public Pizza MusroomLux() {
			return BasicLoad("Грибной люкс");
		}
		static public Pizza King() {
			return BasicLoad("Княжеская");
		}
		static public Pizza Fokacha() {
			return BasicLoad("Фокача");
		}

		static public Pizza Test() {
			return BasicLoad("ТестоваПіца№1");
		}

		static public Pizza Null() {
			return BasicLoad("NullPizza");
		}
	}
}
