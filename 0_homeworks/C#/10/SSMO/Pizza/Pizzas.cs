using System;

namespace SSMO {
	[Serializable]
	class Pizza {
		public Ingradient[] Ingradients { get; private set; }
		public string Name { get; private set; }
		public string Description { get; private set; }
		public ushort MakeTime { get; private set; }
		public ushort MassGr { get {
				ushort mass = 0;
				foreach (var i in Ingradients)
					mass += (ushort) i.MassGr;
				return mass;
			} }
		public ushort Quality {
			get {
				ushort quality = 0;
				foreach (var i in Ingradients)
					quality += (ushort)i.Quality.current;
				quality /= (ushort)Ingradients.Length;
				return (ushort)(quality * QualityMod);
			}
		}

		double _QualityMod;
		public double QualityMod { get { return _QualityMod; } set { _QualityMod = value<0.30?0.30: value > 4.00 ? 4.00 :value; } }

		public Pizza(string _Name, string _Desctiproin, Ingradient[] _Ingradients, double _qualityMod, ushort _MakeTime) {
			MakeTime = _MakeTime;
			Name = _Name;
			Description = _Desctiproin;
			Ingradients = _Ingradients;
			QualityMod = _qualityMod;
		}

		public override bool Equals(object obj) {
			return Name.Equals(obj);
		}

		public override int GetHashCode() {
			return Name.GetHashCode();
		}
	}
}
