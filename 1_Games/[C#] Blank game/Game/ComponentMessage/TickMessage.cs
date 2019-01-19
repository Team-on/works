using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Game.ComponentMessage {
	class TickMessage : BaseComponentMessage{
		public TickMessage() : base(ComponentMessageType.TickElapsed) {
		}
	}
}
