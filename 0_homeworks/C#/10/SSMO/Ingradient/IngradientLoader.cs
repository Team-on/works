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

		static void SerializeIngradiente(string name, string desc, DELIVERY_TYPE delType) {
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

			SerializeIngradiente("Риба", "Default", DELIVERY_TYPE.SeeFood);
			SerializeIngradiente("Морепродукти", "Default", DELIVERY_TYPE.SeeFood); 
			SerializeIngradiente("Крабове мясо", "Default", DELIVERY_TYPE.SeeFood);

			

			SerializeIngradiente("Ковбаса", "Default", DELIVERY_TYPE.MeatShop);
			SerializeIngradiente("Ветчина", "Default", DELIVERY_TYPE.MeatShop);			
			SerializeIngradiente("Бекон", "Default", DELIVERY_TYPE.MeatShop);			
			SerializeIngradiente("Ковбаса папероні", "Default", DELIVERY_TYPE.MeatShop);
			SerializeIngradiente("Салямі", "Default", DELIVERY_TYPE.MeatShop);


			SerializeIngradiente("Помідор", "Default", DELIVERY_TYPE.Grocery);
			SerializeIngradiente("Цибуля", "Default", DELIVERY_TYPE.Grocery);
			SerializeIngradiente("Огірок", "Default", DELIVERY_TYPE.Grocery);
			SerializeIngradiente("Часник", "Default", DELIVERY_TYPE.Grocery);
			SerializeIngradiente("Щось зелене", "Трава", DELIVERY_TYPE.Grocery);
			SerializeIngradiente("Маслини", "Default", DELIVERY_TYPE.Grocery);         
			SerializeIngradiente("Гриби", "Default", DELIVERY_TYPE.Grocery);          
			SerializeIngradiente("Болгарський перець", "Default", DELIVERY_TYPE.Grocery);          
			SerializeIngradiente("Орегано", "Default", DELIVERY_TYPE.Grocery);          
			SerializeIngradiente("Ананас", "Default", DELIVERY_TYPE.Grocery);           

			SerializeIngradiente("Італійський сир", "Default", DELIVERY_TYPE.Cheese);          
			SerializeIngradiente("Моцарела", "Default", DELIVERY_TYPE.Cheese);          
			SerializeIngradiente("Пармезан", "Default", DELIVERY_TYPE.Cheese);           

			SerializeIngradiente("Спеції", "Default", DELIVERY_TYPE.Spice);           

			SerializeIngradiente("Мука", "Білий порошок", DELIVERY_TYPE.Flour);
			SerializeIngradiente("Дріжді", "???", DELIVERY_TYPE.Flour);

			SerializeIngradiente("Кетчуп", "Default", DELIVERY_TYPE.Sauces);
			SerializeIngradiente("Соус", "Default", DELIVERY_TYPE.Sauces);
			SerializeIngradiente("Майонез", "Default", DELIVERY_TYPE.Sauces);
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

		static public Ingradient SeeFood() {
			return BasicLoad("Морепродукти");
		}
		static public Ingradient Crab() {
			return BasicLoad("Крабове мясо");
		}
		static public Ingradient Vetcina() {
			return BasicLoad("Ветчина");
		}
		static public Ingradient Becon() {
			return BasicLoad("Бекон");
		}
		static public Ingradient Paperoni() {
			return BasicLoad("Ковбаса папероні");
		}
		static public Ingradient Salami() {
			return BasicLoad("Салямі");
		}

		static public Ingradient Olives() {
			return BasicLoad("Маслини");
		}
		static public Ingradient Mushroom() {
			return BasicLoad("Гриби");
		}
		static public Ingradient BolgarPapper() {
			return BasicLoad("Болгарський перець");
		}
		static public Ingradient Oregano() {
			return BasicLoad("Орегано");
		}
		static public Ingradient Pineapple() {
			return BasicLoad("Ананас");
		}
		static public Ingradient Mozzarela() {
			return BasicLoad("Моцарела");
		}
		static public Ingradient ItalienCheese() {
			return BasicLoad("Італійський сир");
		}
		static public Ingradient Parmezan() {
			return BasicLoad("Пармезан");
		}
		static public Ingradient Spice() {
			return BasicLoad("Спеції");
		}

		static public Ingradient[] GetAll() {
			return new Ingradient[] {
				IngradientLoader.Garlic(),
				IngradientLoader.Grass(),
				IngradientLoader.Fish(),
				IngradientLoader.Sausage(),
				IngradientLoader.Tomato(),
				IngradientLoader.Onion(),
				IngradientLoader.Cucumber(),
				IngradientLoader.Flour(),
				IngradientLoader.Yeast(),
				IngradientLoader.Ketchup(),
				IngradientLoader.TomatoSauce(),
				IngradientLoader.Mayonnaise(),

				SeeFood(), 
			
			Crab(), 
			
			Vetcina(), 
			
			Becon(), 
			
			Paperoni(), 
			
			Salami(), 
			Olives(), 
			
			Mushroom(), 
			
			BolgarPapper(), 
			
			Oregano(), 
			
			Pineapple(), 
			Mozzarela(), 
			ItalienCheese(), 
			Parmezan(), 
			Spice()
		};
		}
	}
}
