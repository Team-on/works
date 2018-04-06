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
			if (!IngradientLoader.IsIngradientsExist())
				IngradientLoader.CreateIngradientFile();

			Kitchen kitchen = new Kitchen(new Cargo(0.80, 1.05, new DeliveryBasic(DELIVERY_TYPE.All, 0.90, 1, 1.53)));

		}
	}
}
