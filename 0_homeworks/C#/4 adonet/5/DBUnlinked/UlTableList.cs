using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DBUnlinked {
	internal class UlTableList<T> : IEnumerable<T> {
		List<T> list;
		List<UlChanges> changes;

		internal UlTableList() {
			list = new List<T>();
			changes = new List<UlChanges>();
		}

		internal int Count => throw new NotImplementedException();

		internal void Add(T item) {
			throw new NotImplementedException();
		}

		internal T Find(Func<bool> predicate) {
			throw new NotImplementedException();
		}

		internal bool Remove(T item) {
			throw new NotImplementedException();
		}

		internal void Clear() {
			throw new NotImplementedException();
		}

		public IEnumerator<T> GetEnumerator() {
			return ((IEnumerable<T>) list).GetEnumerator();
		}

		IEnumerator IEnumerable.GetEnumerator() {
			return ((IEnumerable<T>) list).GetEnumerator();
		}
	}
}
