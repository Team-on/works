using System;
using System.Collections.Generic;

namespace SSMO {
	class Kitchen {
		class KitchenPizza {
			public Pizza piz;
			public ClientsCompany who;
			public DateTime whenOrder, whenStart;
		}

		Cargo cargo;
		System.Collections.Generic.List<KitchenStaff> staff;
		System.Collections.Generic.Queue<KitchenPizza> orders;

		public Kitchen(Cargo _cargo) {
			cargo = _cargo;
			orders = new System.Collections.Generic.Queue<KitchenPizza>(32);
			staff = new List<KitchenStaff>(6);
		}

		public void AddStaff(KitchenStaff _staff) {
			staff.Add(_staff);
		}

		public bool CanMake(Pizza order) {
			bool res = true, deli = false;
			Ingradient[] ing = order.Ingradients;
			foreach (var i in ing) {
				Console.Write(i.Name);
				if (cargo.CanTakeIngradient(i) != 0) {
					Console.Write(" : false");
					if (!cargo.IsOrderedd(i)) {
						var massPrev = i.MassGr;
						i.MassGr = 7500;
						if (i.Name == IngradientLoader.Flour().Name || i.Name == IngradientLoader.Yeast().Name)
							deli = true;
						cargo.OrderIngradient(i);
						i.MassGr = massPrev;
					}
					res = false;
				}
				Console.Write("\n");
			}
			if (deli)
				cargo.OrderIngradient(null, deli);
			return res;
		}

		public void PripaxatPovarov() {
			foreach(var i in staff) {
				if (i.IsReady) {

					i.IsReady = false;
				}
			}
		}

		public void AddOrder(Pizza order, ClientsCompany _who) {
			orders.Enqueue(new KitchenPizza() { piz = order, who = _who, whenOrder = DateTime.Now });
		}

		public int OrderCnt() {
			return orders.Count;
		}
	}
}
