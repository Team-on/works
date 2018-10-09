using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyProtocol {
	public class RecieveResult {
		public ReceiverType receiverType;
		public CommandType commandType;

		public RecieveResult() : this(ReceiverType.None, CommandType.None) {
				
		}

		public RecieveResult(ReceiverType receiverType, CommandType commandType) {
			this.receiverType = receiverType;
			this.commandType = commandType;
		}
	}
}
