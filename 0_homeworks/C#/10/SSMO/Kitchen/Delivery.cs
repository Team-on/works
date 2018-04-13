using System;
using System.Collections.Generic;

namespace SSMO {
	enum DELIVERY_TYPE : byte { NONE, All, SeeFood, Grocery, Flour, Sauces, MeatShop, Cheese, Spice, END_OF_DELIVERY_TYPE };

	interface IDelivery {
		DELIVERY_TYPE DeliveryType { get; }
		double EarnedMoney { get; }
		double QualityModifier { get; }
		short SecondsToDeliver { get; }
		double CostMod { get; }

		bool CanOrder(Ingradient ingradiente);
		void AddToOrder(Ingradient ingradiente);
		double GetOrderPrice();
		double Order();
		bool CanTakeDeliver();
		IngradientOnCargo[] TakeDeliver();
	}

	class DeliveryBasic : IDelivery {
		DateTime orderTime;
		protected List<IngradientWithPrice> toOrder;
		protected List<IngradientOnCargo> toDeliver;

		public DELIVERY_TYPE DeliveryType { get; private set; }
		public double EarnedMoney { get; private set; }
		public double QualityModifier { get; private set; }
		public short SecondsToDeliver { get; private set; }
		public double CostMod { get; private set; }

		public DeliveryBasic() : this(DELIVERY_TYPE.All, 1.00, 5, 1.00) {
		}

		public DeliveryBasic(DELIVERY_TYPE DeliveryType, double QualityModifier, short SecondsToDeliver, double CostMod) {
			this.DeliveryType = DeliveryType;
			this.QualityModifier = QualityModifier;
			this.SecondsToDeliver = SecondsToDeliver;
			this.CostMod = CostMod;
			this.EarnedMoney = 0;
			this.toOrder = new List<IngradientWithPrice>();
			this.toDeliver = new List<IngradientOnCargo>();
		}

		IngradientWithPrice CreateIngradienteWithPrice(Ingradient ingradiente) {
			//if (ingradiente.Equals(IngradientLoader.Tomato()))
			return new IngradientWithPrice(ingradiente, 100, 100 * CostMod);
			return null;
		}

		IngradientOnCargo CreateIngradienteDeliver(IngradientWithPrice ingradiente) {
			return new IngradientOnCargo(ingradiente, DateTime.Now);
			return null;
		}

		public bool CanOrder(Ingradient ingradiente) {
			if (this.DeliveryType == DELIVERY_TYPE.All)
				return true;
			return ingradiente.DeliveredBy == this.DeliveryType;
		}
		public void AddToOrder(Ingradient ingradiente) {
			toOrder.Add(CreateIngradienteWithPrice(ingradiente));
		}
		public double GetOrderPrice() {
			double orderPrice = 0;
			foreach (var i in toOrder)
				orderPrice += i.PriceSell * i.MassGr / 1000;
			return orderPrice;
		}

		public bool IsInOrder(Ingradient what) {
			foreach (var i in toOrder)
				if(i.Name == what.Name)
					return true;
			foreach (var i in toDeliver)
				if (i.Name == what.Name)
					return true;
			return false;
		}

		public double Order() {
			double orderPrice = GetOrderPrice();
			foreach (var i in toOrder) {
				EarnedMoney += i.PriceSell * i.MassGr / 1000 - i.PriceBuy * i.MassGr / 1000;
				toDeliver.Add(CreateIngradienteDeliver(i));
			}
			toOrder.Clear();
			orderTime = DateTime.Now;
			return orderPrice;
		}
		public bool CanTakeDeliver() {
			return DateTime.Now >= orderTime.AddSeconds(SecondsToDeliver);
		}
		public IngradientOnCargo[] TakeDeliver() {
			var res = toDeliver.ToArray();
			foreach (var i in res)
				i.Quality.current = (int)(i.Quality.current * QualityModifier);
			toDeliver.Clear();
			return res;
		}
	}
}
