using System;
using System.Collections.Generic;
using System.Threading;

namespace SSMO {
	class PizzaShop {
		//[25%; 200%]
		const int ClientEatTime = 1;
		const int CargoDeliverTime = 1;

		List<ClientsCompany> waitClients;
		Hall hall;
		Kitchen kitchen;

		public PizzaShop() {
			waitClients = new List<ClientsCompany>(8);
		}

		public void Launch() {
			Init();
			GenerateKitchen();
			GenerateHall();

			Thread.Sleep(1500);

			while (true) {
				if (waitClients.Count < 8)
					GenerateClients();

				hall.ClientsEat();
				CheckWaitClients();
				kitchen.PripaxatPovarov();
				Print();

				Console.SetCursorPosition(0, 15);
				Console.WriteLine(kitchen.OrderCnt().ToString() + "  " + Money.value.ToString() + "        ");
				Console.WriteLine(waitClients.Count);

				Thread.Sleep(250);
			}
		}

		void Init() {
			Console.CursorVisible = false;
			//if (!IngradientLoader.IsIngradientsExist())
			IngradientLoader.CreateIngradientFile();
			//if (!PizzaLoader.IsPizzaExist())
			PizzaLoader.CreatePizzaFile();
		}

		void GenerateClients() {
			ClientsCompany comp = new ClientsCompany();
			double timeMult = (double)(Rand.rand.Next(25, 200)) / 100;
			ushort eatTime = (ushort)(ClientEatTime * timeMult);
			comp.SetEatTime((ushort)(eatTime != 0? eatTime : 1));

			comp.AddClient(new Client(Human.GenerateName(), Human.GenerateName()));
			//comp.AddClient(new Client(Human.GenerateName(), Human.GenerateName()));
			//comp.AddClient(new Client(Human.GenerateName(), Human.GenerateName()));
			//comp.AddClient(new Client(Human.GenerateName(), Human.GenerateName()));

			Pizza pizza;
			while (!kitchen.CanMake(pizza = PizzaLoader.RandomPizza())) ;
			comp.AddPizza(pizza);

			//if (kitchen.CanMake(PizzaLoader.Test()))
			//comp.AddPizza(PizzaLoader.Test());

			var place = hall.GetFreePlace(comp.Count);
			if (place != null) {
				comp.TakePlace(place);
				comp.MakeOrder(kitchen);
			}
			else {
				waitClients.Add(comp);
			}
		}

		void CheckWaitClients() {
			foreach (var cli in waitClients) {
				var place = hall.GetFreePlace(cli.Count);
				if (place != null) {
					cli.TakePlace(place);
					cli.MakeOrder(kitchen);
					waitClients.Remove(cli);
					break;
				}
			}
		}

		void GenerateKitchen() {
			kitchen = new Kitchen(new Cargo(0.80, 1.05, new DeliveryBasic(DELIVERY_TYPE.All, 0.90, CargoDeliverTime, 1.53)));

			kitchen.AddStaff(new KitchenStaff(new Staff(Human.GenerateName(), "Povar Senior", Human.GenerateName(), Human.GenerateName()), 2.10));
			kitchen.AddStaff(new KitchenStaff(new Staff(Human.GenerateName(), "Povar Middle", Human.GenerateName(), Human.GenerateName()), 1.50));
			kitchen.AddStaff(new KitchenStaff(new Staff(Human.GenerateName(), "Povar Junior", Human.GenerateName(), Human.GenerateName()), 0.90));

			kitchen.WeeklyDeliver();
		}

		void GenerateHall() {
			hall = new Hall(new Coord(1, 1), new Coord(Console.LargestWindowWidth - 40, Console.LargestWindowHeight - 10));

			Place pl = new Place(new Coord(20, 5));
			pl.AddChair(new Chair(new Coord(0, 1)));
			pl.AddChair(new Chair(new Coord(0, -1)));
			pl.AddChair(new Chair(new Coord(1, 0)));
			pl.AddChair(new Chair(new Coord(-1, 0)));

			ManyPlaces pls = new ManyPlaces(new Coord(5, 5));
			pls.AddTable((new Coord(0, 1)));
			pls.AddTable((new Coord(0, -1)));
			pls.AddChair(new Chair(new Coord(-1, -1)));
			pls.AddChair(new Chair(new Coord(-1, 0)));
			pls.AddChair(new Chair(new Coord(-1, 1)));
			pls.AddChair(new Chair(new Coord(1, -1)));
			pls.AddChair(new Chair(new Coord(1, 0)));
			pls.AddChair(new Chair(new Coord(1, 1)));

			hall.AddPlace(pl);
			hall.AddPlace(pls);
		}

		void Print() {
			hall.Print();
			Console.BackgroundColor = ConsoleColor.Black;
			Console.ForegroundColor = ConsoleColor.Green;

		}
	}
}
