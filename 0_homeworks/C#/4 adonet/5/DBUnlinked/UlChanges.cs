using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DBUnlinked {
	/// <summary>
	/// Використовується всередині UlTableList для синхронізації з БД.
	/// </summary>
	class UlChanges : IComparable {
		public int row;
		public UlRowChangedType changedType;

		public UlChanges(int Row) {
			row = Row;
			changedType = UlRowChangedType.Nothing;
		}

		public UlChanges(int Row, UlRowChangedType ChangedType) {
			row = Row;
			changedType = ChangedType;
		}

		public int CompareTo(object obj) {
			return -row.CompareTo(obj);
		}
	}
}
