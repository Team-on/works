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
			for(int i = 0; i < list.Count; ++i)
				if(predicate.Invoke(list[i])) {
					var listItem = changes.FirstOrDefault(a => a.row == i);
					if(listItem == null) 
						changes.Add(new UlChanges(i, UlRowChangedType.Updated));
					return list[i];
				}
			return null;
		}

		internal void Remove(T item) {
			for(int i = 0; i < list.Count; ++i) {
				if(list[i] == item) {
					changes.RemoveAll((a) => a.row == i);
					changes.Add(new UlChanges(i, UlRowChangedType.Deleted));
					break;
				}
			}
			list.Remove(item);
		}

		internal void RemoveAt(int id) {
			list.RemoveAt(id);
			changes.RemoveAll((a) => a.row == id);
			changes.Add(new UlChanges(id, UlRowChangedType.Deleted));
		}

		internal void Clear() {
			list.Clear();
			ClearChanges();
		}

		internal void ClearChanges() {
			changes.Clear();
		}

		public T this[int index] {
			get{
				//if(changes.Find((a) => a.row == index) == null)
				//	changes.Add(new UlChanges(index, UlRowChangedType.Updated));
				return ((IList<T>) list)[index];
			}
			set {
				//if(changes.Find((a) => a.row == index) == null)
				//	changes.Add(new UlChanges(index, UlRowChangedType.Updated));
				((IList<T>) list)[index] = value;
			}
		}

		public IEnumerator<T> GetEnumerator() {
			return ((IEnumerable<T>) list).GetEnumerator();
		}

		IEnumerator IEnumerable.GetEnumerator() {
			return ((IEnumerable<T>) list).GetEnumerator();
		}
	}
}
