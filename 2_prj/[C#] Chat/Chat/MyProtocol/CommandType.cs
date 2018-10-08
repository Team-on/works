using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MyProtocol {
	public enum CommandType : byte {
		None,
		Connect,
		Exit,
		String,
		RawData
	}
}
