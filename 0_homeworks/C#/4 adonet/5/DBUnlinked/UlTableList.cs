using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DBUnlinked {
	public class UlTableList<T> : IEnumerable<T> {
		List<T> list;
		List<UlChanges> changes;

		public int Count => throw new NotImplementedException();

		public void Add(T item) {
			throw new NotImplementedException();
		}

		public T Find(Func<bool> predicate) {
			throw new NotImplementedException();
		}

		public bool Remove(T item) {
			throw new NotImplementedException();
		}

		public void Clear() {
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
