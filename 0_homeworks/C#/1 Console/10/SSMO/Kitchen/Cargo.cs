﻿using System;
using System.Collections.Generic;

namespace SSMO {
	class Cargo {
		public double QualityMod { get; private set; }
		public double SellMod { get; private set; }
		public double EarnedMoney { get; private set; }
		IDelivery delivery;
		List<IngradientOnCargo> ingradients;

		public List<IngradientOnCargo> GetIngradients() => ingradients;

		public DeliveryBasic GetDelivery() => (DeliveryBasic)delivery;

		public Cargo() : this(1, 1, null) {
		}

		public Cargo(double _QualityMod, double _SellMod, IDelivery _delivery) {
			QualityMod = _QualityMod;
			SellMod = _SellMod;
			delivery = _delivery;
			ingradients = new List<IngradientOnCargo>();
		}

		public int CanTakeIngradient(Ingradient what) {
			CheckOrder();
			Ingradient find = ingradients.Find(i => i.Name == what.Name);
			if (find == null)
				return -1;
			if (find.MassGr < what.MassGr)
				return -1;
			return 0;
		}

		public uint GetIngMass(Ingradient what) {
			IngradientOnCargo find = ingradients.Find(i => i.Name == what.Name);
			return find?.MassGr??0;
		}

		public Ingradient TakeIngradient(Ingradient what, ref double userMoney) {
			CheckOrder();
			IngradientOnCargo find = ingradients.Find(i => i.Name == what.Name);
			if (find == null || find.MassGr < what.MassGr) {
				return null;
				throw new Exception("No more ings");
			}

			var res = new Ingradient(find) { MassGr = what.MassGr };
			find.MassGr -= what.MassGr;
			res.Quality.current = (int)(res.Quality.current * this.QualityMod) - (DateTime.Now - find.PlacedOn).Seconds / 5;

			double deliverPriceBuy = find.PriceSell * what.MassGr / 1000;
			if (userMoney != 0) {
				userMoney -= deliverPriceBuy * SellMod;
				EarnedMoney += deliverPriceBuy * SellMod;
			}

			if (find.MassGr == 0)
				ingradients.Remove(find);
			return res;
		}

		public bool IsOrderedd(Ingradient what) {
			return (delivery as DeliveryBasic).IsInOrder(what);
		}

		bool isOrdered = false;
		public void OrderIngradient(Ingradient what, bool Immediate = false) {
			if (what != null && delivery.CanOrder(what))
				delivery.AddToOrder(what);
			if (Immediate || GetOrderPrice() >= 1500) {
				isOrdered = true;
				CheckOrder();
				isOrdered = false;
			}
		}

		void CheckOrder() {
			if (isOrdered)
				EarnedMoney -= delivery.Order();
			if (delivery.CanTakeDeliver()) {
				foreach (var i in delivery.TakeDeliver()) {
					if (ingradients.Find(tmp => tmp.Name == i.Name) != null) {
						ingradients.Find(tmp => tmp.Name == i.Name).MassGr += i.MassGr;
						ingradients.Find(tmp => tmp.Name == i.Name).Quality.current = (ingradients.Find(tmp => tmp.Name == i.Name).Quality.current + i.Quality.current) / 2;
					}
					else
						ingradients.Add(i);
				}
			}
		}

		public double GetOrderPrice() {
			return delivery.GetOrderPrice() * SellMod;
		}
	}
}
