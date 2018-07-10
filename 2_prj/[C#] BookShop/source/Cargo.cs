using System;
using System.Collections;
using System.Collections.Generic;
using BookN;

namespace CargoN {

	interface ICargo : IEnumerable {
		void Add(object toAdd);
		object Find(object toFind);
		object Remove(object toRemove);
		Book[] FindBook();
	}

	class Cargo : ICargo {
		ArrayList cargoData;

		//Перегрузка ітератора
		IEnumerator IEnumerable.GetEnumerator() {
			for (int i = 0; i < cargoData.Count; i++) {
				yield return cargoData[i];
			}
		}

		public Cargo() {
			cargoData = new ArrayList();
		}

		public void Add(object toAdd) {
			cargoData.Add(toAdd);
		}

		public object Find(object toFind) {
			foreach (object iterator in cargoData) {
				if (iterator.Equals(toFind)) {
					return iterator;
				}
			}
			return null;
		}

		public Book[] FindBook() {
			List<Book> arrBook = new List<Book>();
			foreach (object iterator in cargoData) {
				if (iterator is Book) {
					arrBook.Add((Book)iterator);
				}
			}
			Book[] res = new Book[arrBook.Count];
			return res;
		}

		public object Remove(object toRemove) {
			object tmp = Find(toRemove);
			if (tmp == null)
				return null;
			cargoData.Remove(tmp);
			return tmp;
		}

	}
}
