using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SSMO {
	class Staff : Human {
		public string Clicuxa { get; private set; }
		public string Posada { get; private set; }

		public Staff(string _Clicuxa, string _Posada) {
			Posada = _Posada;
			_Clicuxa = Clicuxa;
		}
	}

	class KitchenStaff : Staff {
		public double QualityMod { get; private set; }
		public bool IsReady;

		public KitchenStaff(Staff st, double qmod) : base(st.Clicuxa, st.Posada) {
			IsReady = true;
			QualityMod = qmod;
		}
	}
}
