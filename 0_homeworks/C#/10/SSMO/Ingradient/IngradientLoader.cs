using System;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Soap;


namespace SSMO {
	static class IngradientLoader {
		static IFormatter fs = new SoapFormatter();
		static FileStream fout;
		static Ingradient ing;

		static string ingradientsFolder = System.Environment.CurrentDirectory + @"\Ingradients\";

		static void SerializeIngradiente(string name, string desc, DELIVERY_TYPE delType, IFormatter fs) {
			using (fout = new FileStream(ingradientsFolder + name + ".ing", FileMode.OpenOrCreate)) {
				ing = new Ingradient(delType, name, desc, 0, 10000);
				fs.Serialize(fout, ing);
			}
		}

		static Ingradient BasicLoad(string name) {
			using (fout = new FileStream(ingradientsFolder + name + ".ing", FileMode.OpenOrCreate))
				return fs.Deserialize(fout) as Ingradient;
		}

		static public bool IsIngradientsExist() {
			return Directory.Exists(ingradientsFolder);
		}

		static public void CreateIngradientFile() {
			Directory.CreateDirectory(ingradientsFolder);

			SerializeIngradiente("Риба", "Біла і слизька", DELIVERY_TYPE.SeeFood, fs);

			SerializeIngradiente("Ковбаса", "Червона і довга", DELIVERY_TYPE.MeatShop, fs);

			SerializeIngradiente("Помідор", "Червоний і круглий", DELIVERY_TYPE.Grocery, fs);
			SerializeIngradiente("Цибуля", "Біля і кругла", DELIVERY_TYPE.Grocery, fs);
			SerializeIngradiente("Огірок", "Зелений і довгий", DELIVERY_TYPE.Grocery, fs);
			SerializeIngradiente("Часник", "Білий і гіркий", DELIVERY_TYPE.Grocery, fs);
			SerializeIngradiente("Щось зелене", "Трава", DELIVERY_TYPE.Grocery, fs);


			SerializeIngradiente("Мука", "Білий порошок", DELIVERY_TYPE.Flour, fs);
			SerializeIngradiente("Дріжді", "???", DELIVERY_TYPE.Flour, fs);

			SerializeIngradiente("Кетчуп", "Червоний і вологий", DELIVERY_TYPE.Sauces, fs);
			SerializeIngradiente("Соус", "Помісь Кетчупу і Майонезу", DELIVERY_TYPE.Sauces, fs);
			SerializeIngradiente("Майонез", "Білий і вологий", DELIVERY_TYPE.Sauces, fs);
		}
		static public Ingradient Garlic() {
			return BasicLoad("Часник");
		}
		static public Ingradient Grass() {
			return BasicLoad("Щось зелене");
		}
		static public Ingradient Fish() {
			return BasicLoad("Риба");
		}
		static public Ingradient Sausage() {
			return BasicLoad("Ковбаса");
		}
		static public Ingradient Tomato() {
			return BasicLoad("Помідор");
		}
		static public Ingradient Onion() {
			return BasicLoad("Цибуля");
		}
		static public Ingradient Cucumber() {
			return BasicLoad("Огірок");
		}
		static public Ingradient Flour() {
			return BasicLoad("Мука");
		}
		static public Ingradient Yeast() {
			return BasicLoad("Дріжді");
		}
		static public Ingradient Ketchup() {
			return BasicLoad("Кетчуп");
		}
		static public Ingradient TomatoSauce() {
			return BasicLoad("Соус");
		}
		static public Ingradient Mayonnaise() {
			return BasicLoad("Майонез");
		}
	}
}
