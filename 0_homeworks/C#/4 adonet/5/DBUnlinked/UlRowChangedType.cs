using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DBUnlinked {
	/// <summary>
	/// Використовується всередині UlTableList. 
	/// </summary>
	enum UlRowChangedType : byte {
		Nothing,
		Added,
		Updated,
		Deleted
	}
}
