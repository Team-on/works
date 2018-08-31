using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DBUnlinked {
	/// <summary>
	/// Використовується всередині UlTableList для синхронізації з БД.
	/// </summary>
	class UlChanges {
		public int row;
		public UlRowChangedType changedType;
	}
}
