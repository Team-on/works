using System;
using System.Collections;
using System.Collections.Generic;

namespace DBUnlinked {
	/// <summary>
	/// Таблиця яка створюватиметься на основі класу
	/// </summary>
	/// <typeparam name="T"></typeparam>
	public class UlTable<T> : IEnumerable<T> {
		internal UlDb ownerDb;
		UlTableList<T> table;

		/// <summary>
		/// Зчитує всю таблицю з бд
		/// </summary>
		public void Fill() {

		}

		/// <summary>
		/// Пропускає n рядків. Продовжеє пропускати з місця на якому зупинився TakeN() останній раз, або з місця де закінчився SkipN()
		/// Працює лише коли в таблиці є Primary key
		/// </summary>
		/// <param name="n"></param>
		//public void SkipN(int n) {

		//}

		/// <summary>
		/// Заповнює лише n перший рядків. Починає з місця на якому зупинився TakeN() останній раз, або з місця де закінчився SkipN().
		/// Працює лише коли в таблиці є Primary key
		/// </summary>
		/// <param name="n"></param>
		//public void TakeN(int n) {

		//}

		/// <summary>
		/// Очищує локальну копію таблиці і скидає позиції TakeN і SkipN
		/// </summary>
		public void Clear() {

		}

		/// <summary>
		/// Вносить зміни з локальної копії у таблицю з БД.
		/// </summary>
		public void Update() {

		}

		public void Add(T item) {
			throw new NotImplementedException();
		}

		public T Find(Func<bool> predicate) {
			throw new NotImplementedException();
		}

		public bool Remove(T item) {
			throw new NotImplementedException();
		}

		public IEnumerator<T> GetEnumerator() {
			return ((IEnumerable<T>) table).GetEnumerator();
		}

		IEnumerator IEnumerable.GetEnumerator() {
			return ((IEnumerable<T>) table).GetEnumerator();
		}
	}
}
