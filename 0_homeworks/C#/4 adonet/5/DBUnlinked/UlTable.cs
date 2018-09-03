using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Data;
using System.Data.Sql;
using System.Data.SqlClient;

namespace DBUnlinked {
	/// <summary>
	/// Таблиця яка створюватиметься на основі класу
	/// </summary>
	/// <typeparam name="T"></typeparam>
	public class UlTable<T> : IEnumerable<T> where T : class, new() {
		Type type = typeof(T);
		UlTableAttribute tableAttribute;
		List<UlTableColumnAttribute> columnAttributes;

		UlDb ownerDb;
		SqlCommand command;
		//Трохи костиль(
		int lastId;
		UlTableList<T> table;

		public UlTable(UlDb OwnerDB, UlTableAttribute attribute, List<UlTableColumnAttribute> ColumnAttributes) {
			tableAttribute = attribute;
			columnAttributes = ColumnAttributes;

			ownerDb = OwnerDB;
			command = new SqlCommand() {
				Connection = ownerDb.connection,
			};

			table = new UlTableList<T>();
		}

		/// <summary>
		/// Зчитує всю таблицю з бд
		/// </summary>
		public void Fill() {
			command.CommandType = CommandType.Text;
			command.CommandText = $"select * from {tableAttribute.name}";

			ownerDb.connection.Open();
			SqlDataReader reader = command.ExecuteReader();

			if(reader.HasRows) {
				T curr;
				while(reader.Read()) {

					curr = new T();
					for(byte i = 0; i < reader.FieldCount; ++i) {
						var name = reader.GetName(i);
						var value = reader.GetValue(i);

						for(byte j = 0; j < columnAttributes.Count; ++j) {
							if(columnAttributes[j].name == name) {
								type.GetProperties()[i].SetValue(curr, value);
								break;
							}
						}
					}
					table.Add(curr);
				}
			}

			if(table.Count != 0)
				lastId = (int) type.GetProperty("Id").GetValue(table[table.Count - 1]);
			else
				lastId = 0;

			reader.Close();
			ownerDb.connection.Close();
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns>Повертає масив імен стовбців</returns>
		public string[] GetColumnNames() {
			List<string> rez = new List<string>();
			foreach(var attr in columnAttributes) {
				rez.Add(attr.name);
			}
			return rez.ToArray();
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
