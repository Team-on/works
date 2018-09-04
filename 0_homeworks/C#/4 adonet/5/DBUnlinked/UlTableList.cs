using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DBUnlinked {
	internal class UlTableList<T> : IEnumerable<T> where T : class {
		List<T> list;
		List<UlChanges> changes;

		internal UlTableList() {
			list = new List<T>();
			changes = new List<UlChanges>();
		}

		internal int Count => list.Count;

		internal void Add(T item, bool isLoadFromDB = false) {
			changes.Add(new UlChanges(list.Count, isLoadFromDB?UlRowChangedType.Nothing:UlRowChangedType.Added));
			list.Add(item);
		}

		internal T Find(Func<T, bool> predicate) {
			foreach(var i in list)
				if(predicate.Invoke(i))
					return i;
			return null;
		}

		internal void Remove(T item) {
			changes.RemoveAt(list.IndexOf(item));
			list.Remove(item);
		}

		internal void RemoveAt(int id) {
			list.RemoveAt(id);
			changes.RemoveAt(id);
		}

		internal void Clear() {
			list.Clear();
			changes.Clear();
		}

		public T this[int index] { get => ((IList<T>) list)[index]; set => ((IList<T>) list)[index] = value; }
		public UlChanges this[int index, int nothing] { get => changes[index]; set => changes[index] = value; }

		public IEnumerator<T> GetEnumerator() {
			return ((IEnumerable<T>) list).GetEnumerator();
		}

		IEnumerator IEnumerable.GetEnumerator() {
			return ((IEnumerable<T>) list).GetEnumerator();
		}
	}
}
