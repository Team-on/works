using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SSMO {
	class Client : Human {
		public Client(string name, string surname) {
			base.Name = name;
			base.Surname = surname;
		}
	}

	class ClientsCompany : IEnumerable {
		Place where;
		List<Client> clients;
		List<Pizza> wantOrder;
		List<Pizza> OnTable;
		public DateTime inCafe, inTable, makeOrder, getOrder;
		public ushort eatTime;
		ushort gettedPizza;

		public List<Pizza> GetWhatOrder() {
			return OnTable;
		}

		public void AddOrderedPizza(Pizza p) {
			OnTable.Add(p);
		}

		public byte Count { get { return (byte)clients.Count; } }

		public ClientsCompany() {
			clients = new List<Client>(5);
			wantOrder = new List<Pizza>(3);
			OnTable = new List<Pizza>(3);
			inCafe = DateTime.Now;
		}

		public void SetEatTime(ushort _eatTime) {
			eatTime = _eatTime;
		}

		public void AddClient(Client cl) {
			clients.Add(cl);
		}

		public void AddPizza(Pizza piz) {
			wantOrder.Add(piz);
		}

		public void TakePlace(Place place) {
			inTable = DateTime.Now;
			where = place;
			where.PlaceHumans((byte)clients.Count, true);
			where.isFree = false;
			where.client = this;
		}

		public void MakeOrder(Kitchen kitchen) {
			foreach(var p in wantOrder)
				kitchen.AddOrder(p, this);
			makeOrder = DateTime.Now;
		}

		public void GetPizza() {
			getOrder = DateTime.Now;
			++gettedPizza;
			where.PlacePizza(true);
		}

		public bool Eat () {
			if (gettedPizza != wantOrder.Count || DateTime.Now <= getOrder.AddSeconds(eatTime)) {
				//Не ливать
				return true;
			}
			else {
				Leave();
				return false;
			}
		}

		public void PickPizzas(Kitchen kitchen) {
			int pizzaCnt = Rand.rand.Next(1, 4);
			while (pizzaCnt-- != 0) {
				Pizza pizza;
				while (!kitchen.CanMake(pizza = PizzaLoader.RandomPizza()));
				AddPizza(pizza);
			}
		}

		public void RePickPizzas(Kitchen kitchen, Pizza _pizza) {
			for (int i = 0; i < wantOrder.Count; i++) {
				if (wantOrder[i].Name == _pizza.Name) {
					wantOrder[i] = PizzaLoader.RandomPizza();
					int cnt = 0;
					while (!kitchen.CanMake(wantOrder[i] = PizzaLoader.RandomPizza()))
						if (++cnt > 1000) {
							wantOrder[i] = PizzaLoader.Fokacha();
							break;
						}
				}
			}
		}

		void Leave() {
			where.PlacePizza(false);
			where.PlaceHumans(255, false);
			where.isFree = true;
			where.client = null;
			foreach(var p in wantOrder)
				Money.value += p.Price;
			if(getOrder <= makeOrder.AddSeconds(15));
				Money.value += Rand.rand.Next(0, 11);
		}

		public IEnumerator GetEnumerator() {
			return clients.GetEnumerator();
		}
	}
}
