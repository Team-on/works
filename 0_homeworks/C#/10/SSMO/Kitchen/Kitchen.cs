using System;
using System.Collections.Generic;

namespace SSMO {
	class Kitchen {
		class KitchenPizza {
			public Pizza piz;
			public ClientsCompany who;
			public DateTime whenOrder, whenStart;
			public KitchenStaff master;
		}

		Cargo cargo;
		System.Collections.Generic.List<KitchenStaff> staff;
		System.Collections.Generic.Queue<KitchenPizza> orders;
		List<KitchenPizza> cooked;

		public Kitchen(Cargo _cargo) {
			cargo = _cargo;
			orders = new System.Collections.Generic.Queue<KitchenPizza>(32);
			staff = new List<KitchenStaff>(6);
			cooked = new List<KitchenPizza>(staff.Capacity);
		}

		public void WeeklyDeliver() {
			foreach (var i in IngradientLoader.GetAll()) {
				i.MassGr = 10000;
				cargo.OrderIngradient(i);
			}
			cargo.OrderIngradient(null, true);
		}

		public void AddStaff(KitchenStaff _staff) {
			staff.Add(_staff);
		}

		public bool CanMake(Pizza order) {
			bool res = true, deli = false;
			foreach (var i in order.Ingradients) {
				if (cargo.CanTakeIngradient(i) != 0) {
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
			}
			if (deli)
				cargo.OrderIngradient(null, deli);
			return res;
		}

		public void PripaxatPovarov() {
			if(orders.Count != 0)
			foreach(var pizzaMaster in staff) {
				if (orders.Count == 0)
					break;
				if (pizzaMaster.IsReady) {
					pizzaMaster.IsReady = false;
					KitchenPizza order = orders.Dequeue();
					
					order.master = pizzaMaster;
					order.whenStart = DateTime.Now;
					order.piz.QualityMod = pizzaMaster.QualityMod;
					foreach (var i in order.piz.Ingradients)
						cargo.TakeIngradient(i, ref Money.value);

					cooked.Add(order);
				}
			}
			GivePizzaToCompany();
		}

		void GivePizzaToCompany() {
			foreach(var piz in cooked) {
				if(piz.whenStart.AddSeconds(piz.piz.MakeTime) <= DateTime.Now) {
					piz.master.IsReady = true;
					cooked.Remove(piz);

					piz.who.GetPizza();

					GivePizzaToCompany();
					break;
				}
			}
		}

		public void AddOrder(Pizza order, ClientsCompany _who) {
			orders.Enqueue(new KitchenPizza() { piz = order, who = _who, whenOrder = DateTime.Now });
		}

		public int OrderCnt() {
			return orders.Count + cooked.Count;
		}
	}
}
