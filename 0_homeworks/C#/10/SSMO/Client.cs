using System;
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

	class ClientsCompany {
		Place where;
		List<Client> clients;
		List<Pizza> wantOrder;
		public DateTime inCafe, inTable, makeOrder, getOrder;
		public ushort eatTime;
		ushort gettedPizza;

		public byte Count { get { return (byte)clients.Count; } }

		public ClientsCompany() {
			clients = new List<Client>(5);
			wantOrder = new List<Pizza>(3);
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

		public void Leave() {
			where.PlacePizza(false);
			where.PlaceHumans(255, false);
			where.isFree = true;
			where.client = null;
		}


	}
}
