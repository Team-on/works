using System;
using System.Collections.Generic;

namespace SSMO {
	class Client : Human {

	}

	class ClientsCompany {
		Client[] clients;
	}

	class Chair {

	}
	class Place {

	}
	class Hall {

	}

	class PizzaShop {

	}

	class Program {
		static void Main(string[] args) {
			//if (!IngradientLoader.IsIngradientsExist())
				IngradientLoader.CreateIngradientFile();
			//if (!PizzaLoader.IsPizzaExist())
				PizzaLoader.CreatePizzaFile();

			var i = PizzaLoader.Test();
			Console.WriteLine(i.Name);
			Console.WriteLine(i.Description);
			Console.WriteLine(i.MassGr);
			Console.WriteLine(i.Quality);
			Console.WriteLine("\t" + i.Ingradients.Length);
			foreach (var j in i.Ingradients)
				Console.WriteLine("\t: " + j.Name);



			Kitchen kitchen = new Kitchen(new Cargo(0.80, 1.05, new DeliveryBasic(DELIVERY_TYPE.All, 0.90, 1, 1.53)));

		}
	}
}
