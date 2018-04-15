using System;

namespace SSMO {
	[Serializable]
	class Stat {
		public int basic;
		public int current;

		public Stat() : this(0, 0) { }

		public Stat(int Base, int curr) {
			basic = Base;
			current = curr;
		}

		public Stat(Stat rhs) : this(rhs.basic, rhs.current) { }
	}

	[Serializable]
	class Ingradient {
		public DELIVERY_TYPE DeliveredBy { get; protected set; }
		public string Name { get; protected set; }
		public string Description { get; protected set; }
		public uint MassGr { get; set; }
		public Stat Quality { get; protected set; }

		public Ingradient() { }

		public Ingradient(Ingradient rhs) : this(rhs.DeliveredBy, rhs.Name, rhs.Description, rhs.MassGr, 0) {
			Quality = new Stat(rhs.Quality);
		}

		public Ingradient(DELIVERY_TYPE _DeliveredBy, string _Name, string _Description, uint _MassGr, int BasicQuality) {
			DeliveredBy = _DeliveredBy;
			Name = _Name;
			Description = _Description;
			MassGr = _MassGr;
			Quality = new Stat(BasicQuality, BasicQuality);
		}

		public override int GetHashCode() {
			return Name.GetHashCode();
		}

		public override bool Equals(object obj) {
			return Name.Equals(obj);
		}
	}

	class IngradientWithPrice : Ingradient {
		public double PriceBuy { get; set; }
		public double PriceSell { get; set; }

		public IngradientWithPrice(IngradientWithPrice rhs) : base(rhs.DeliveredBy, rhs.Name, rhs.Description, rhs.MassGr, 0) {
			Quality = new Stat(rhs.Quality);
			PriceBuy = rhs.PriceBuy;
			PriceSell = rhs.PriceSell;
		}

		public IngradientWithPrice(Ingradient basic, double _PriceBuy, double _PriceSell) : base(basic) {
			PriceBuy = _PriceBuy;
			PriceSell = _PriceSell;
		}
	}

	class IngradientOnCargo : IngradientWithPrice {
		public DateTime PlacedOn { get; set; }

		public IngradientWithPrice GetFinalIngradient() {
			return null;
		}

		public IngradientOnCargo(IngradientWithPrice basic, DateTime _PlacedOn) : base(basic) {
			PlacedOn = _PlacedOn;
		}
	}
}
