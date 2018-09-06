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
		public UlRowChangedType changedType;
		public object changedItem;

		public UlChanges(object changedItem) {
			changedType = UlRowChangedType.Nothing;
			this.changedItem = changedItem;
		}

		public UlChanges(object changedItem, UlRowChangedType ChangedType) {
			changedType = ChangedType;
			this.changedItem = changedItem;
		}
	}
}
