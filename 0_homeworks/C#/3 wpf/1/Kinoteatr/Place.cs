using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1 {
	class Place {
		public PlaceTypes type;
		public bool isFree;

		public Place() {
			type = PlaceTypes.Standatd;
			isFree = true;
		}
	}
}
