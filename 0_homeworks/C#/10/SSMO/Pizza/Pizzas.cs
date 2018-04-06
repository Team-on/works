using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SSMO {
	[Serializable]
	class Pizza {
		public Ingradient[] Ingradients { get; private set; }
		public string Name { get; private set; }
		public string Description { get; private set; }
		public ushort MassGr { get {
				ushort mass = 0;
				foreach (var i in Ingradients)
					mass += (ushort) i.MassGr;
				return mass;
			} }
		public ushort Quality { get; set; }

		public Pizza(string _Name, string _Desctiproin, Ingradient[] _Ingradients, ushort _Quality) {
			Name = _Name;
			Description = _Desctiproin;
			Ingradients = _Ingradients;
			Quality = _Quality;
		}
	}
}
