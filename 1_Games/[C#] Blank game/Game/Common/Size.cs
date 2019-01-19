using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.Common {
	public class Size : ICloneable {
		public int width, height;

		public Size() : this(0, 0) { }

		public Size(int width, int height) {
			this.width = width;
			this.height = height;
		}

		public object Clone() {
			return MemberwiseClone();
		}
	}
}
