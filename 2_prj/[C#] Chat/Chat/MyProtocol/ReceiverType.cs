using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyProtocol {
	//FROM_TO
	public enum ReceiverType : byte {
		None,
		Client_Server,
		Client_Everyone,
		Client_GroupById,
		Server_User,
		Server_Everyone,
		Server_GroupById
	}
}
