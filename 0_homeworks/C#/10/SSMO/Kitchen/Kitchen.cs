using System;
using System.Collections.Generic;

namespace SSMO {
	class Kitchen {
		const ushort secForSalary = 60;

		class KitchenPizza {
			public Pizza piz;
			public ClientsCompany who;
			public DateTime whenOrder, whenStart;
			public KitchenStaff master;
		}

		DateTime lastSalary = new DateTime(0);

		Cargo cargo;
		System.Collections.Generic.List<KitchenStaff> staff;
		System.Collections.Generic.Queue<KitchenPizza> orders;
		List<KitchenPizza> cooked;

		public KitchenStaff[] GetStaff() {
			return staff.ToArray();
		}

		public Kitchen(Cargo _cargo) {
			cargo = _cargo;
			orders = new System.Collections.Generic.Queue<KitchenPizza>(32);
			staff = new List<KitchenStaff>(6);
			cooked = new List<KitchenPizza>(staff.Capacity);
		}

		public Cargo GetCargo() => cargo;

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
						Log.log.LogNewLine("Kitchen->deliver");
						var massPrev = i.MassGr;
						i.MassGr = 7500;
						if (i.Name == IngradientLoader.Flour().Name || i.Name == IngradientLoader.Yeast().Name) 
							deli = true;
						cargo.OrderIngradient(new Ingradient(i));
						i.MassGr = massPrev;
					}
					res = false;
				}
			}
			if (deli)
				cargo.OrderIngradient(null, deli);
			return res;
		}

		void CheckSalary() {
			if(DateTime.Now >= lastSalary.AddSeconds(secForSalary)) {
				double salary = Money.value;
				foreach (var i in staff)
					Money.value -= i.Salary;
				lastSalary = DateTime.Now;
				salary -= Money.value;
				Log.log.LogNewLine("Salary time. Pay " + salary.ToString() + "$");
			}
		}

		public void PripaxatPovarov() {
			CheckSalary();
				if (orders.Count != 0)
					foreach (var pizzaMaster in staff) {
						if (orders.Count == 0)
							break;
						if (pizzaMaster.IsReady) {
							pizzaMaster.IsReady = false;
							KitchenPizza order = orders.Dequeue();
						RESTART:
						try {
							order.master = pizzaMaster;
							order.whenStart = DateTime.Now;
							order.piz.QualityMod = pizzaMaster.QualityMod;
							for(int i = 0; i < order.piz.Ingradients.Length; ++i) {
								double prev = Money.value;
								order.piz.Ingradients[i] = cargo.TakeIngradient(order.piz.Ingradients[i], ref Money.value);
								order.piz.Price += prev - Money.value;
							}
							order.piz.Price *= 1.5;

							cooked.Add(order);
						}
						catch (Exception exc) {
							foreach (var i in order.piz.Ingradients)
								if(!cargo.IsOrderedd(i))
									cargo.OrderIngradient(i);
							cargo.OrderIngradient(null, true);
							order.who.RePickPizzas(this, order.piz);
							goto RESTART;
						}
					}
					}
				GivePizzaToCompany();
		}

		void GivePizzaToCompany() {
			foreach(var piz in cooked) {
				if(piz.whenStart.AddSeconds(piz.piz.MakeTime) <= DateTime.Now) {
					piz.master.IsReady = true;
					piz.who.AddOrderedPizza(piz.piz);
					piz.who.GetPizza();

					cooked.Remove(piz);
					GivePizzaToCompany();
					break;
				}
			}
		}

		public void AddOrder(Pizza order, ClientsCompany _who) {
			orders.Enqueue(new KitchenPizza() { piz = order, who = _who, whenOrder = DateTime.Now });
		}

		public int CookedCnt() {
			return cooked.Count;
		}

		public int OrderCnt() {
			return orders.Count;
		}

		public DateTime WhenLastSalary() {
			return lastSalary;
		}

		public int SalarySeconds() {
			return secForSalary;
		}

		public double GetSalary() {
			double res = 0;
			foreach (var i in staff) {
				res += i.Salary;
			}
			return res;
		}

	}
}
