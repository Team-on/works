using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Common {
	public class Coord : ICloneable{
		public int x, y;

		public Coord() : this(0, 0) { }

		public Coord(int x, int y) {
			this.x = x;
			this.y = y;
		}

		public void Set(Coord c) {
			x = c.x;
			y = c.y;
		}

		public object Clone() {
			return MemberwiseClone();
		}
	}
}
