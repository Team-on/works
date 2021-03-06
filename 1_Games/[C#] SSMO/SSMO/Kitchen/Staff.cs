﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SSMO {
	class Staff : Human {
		public string Clicuxa { get; private set; }
		public string Posada { get; private set; }

		public Staff(string _Clicuxa, string _Posada, string _name, string _surname) {
			Posada = _Posada;
			Clicuxa = _Clicuxa;
			Name = _name;
			Surname = _surname;
		}
	}

	class KitchenStaff : Staff {
		public double QualityMod { get; private set; }
		public bool IsReady;
		public double Salary { get; private set; }

		public KitchenStaff(Staff st, double qmod, double _Salary) : base(st.Clicuxa, st.Posada, st.Name, st.Surname) {
			IsReady = true;
			QualityMod = qmod;
			Salary = _Salary;
		}
	}
}
