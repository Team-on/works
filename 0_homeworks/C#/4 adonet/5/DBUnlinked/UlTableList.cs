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

		internal int Count => list.Count;

		internal void Add(T item) {
			changes.Add(new UlChanges(list.Count));
			list.Add(item);
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

		public T this[int index] { get => ((IList<T>) list)[index]; set => ((IList<T>) list)[index] = value; }

		public IEnumerator<T> GetEnumerator() {
			return ((IEnumerable<T>) list).GetEnumerator();
		}

		IEnumerator IEnumerable.GetEnumerator() {
			return ((IEnumerable<T>) list).GetEnumerator();
		}
	}
}
