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

		internal List<UlChanges> Changes => changes;

		internal void Add(T item, bool isLoadFromDB = false) {
			if(!isLoadFromDB)
				changes.Add(new UlChanges(list.Count, UlRowChangedType.Added));
			list.Add(item);
		}

		internal T Find(Func<T, bool> predicate) {
			foreach(var i in list)
				if(predicate.Invoke(i))
					return i;
			return null;
		}

		internal void Remove(T item) {
			for(int i = 0; i < list.Count; ++i) {
				if(list[i] == item) {
					changes.Add(new UlChanges(i, UlRowChangedType.Deleted));
					break;
				}
			}
			list.Remove(item);
		}

		internal void RemoveAt(int id) {
			list.RemoveAt(id);
			changes.Add(new UlChanges(id, UlRowChangedType.Deleted));
		}

		internal void Clear() {
			list.Clear();
			ClearChanges();
		}

		internal void ClearChanges() {
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
