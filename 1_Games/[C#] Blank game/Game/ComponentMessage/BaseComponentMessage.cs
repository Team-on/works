using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.ComponentMessage {
	class BaseComponentMessage {
		public ComponentMessageType ComponentMessageType { get; private set; }

		public BaseComponentMessage(ComponentMessageType type) {
			ComponentMessageType = type;
		}
	}
}
