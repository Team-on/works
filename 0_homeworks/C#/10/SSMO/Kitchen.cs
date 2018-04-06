using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SSMO {
	class Kitchen {
		Cargo cargo;
		List<Staff> staff;
		System.Collections.Generic.Queue<int> orders;

		public Kitchen(Cargo _cargo) {
			cargo = _cargo;
		}

	}
}
