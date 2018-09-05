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
		//Трохи костиль =(
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
						if(value is DBNull)
							value = null;

						for(byte j = 0; j < columnAttributes.Count; ++j) {
							if(columnAttributes[j].name == name) {
								type.GetProperties()[j].SetValue(curr, value);
								break;
							}
						}
					}
					table.Add(curr, true);
				}
			}

			if(table.Count != 0) {	
				//UlTableColumnAttribute indexer = columnAttributes.FirstOrDefault((a) => a.isPrimaryKey);

				//Console.WriteLine(type.
				//			GetProperties().
				//			FirstOrDefault((a) => {
				//				if(a.GetCustomAttributes(false).Length == 1) {
				//					var b = a.GetCustomAttributes(false)[0] as UlTableColumnAttribute;
				//					Console.WriteLine("{0} {1}", indexer.name, b.name);
				//					Console.WriteLine("{0} {1}", indexer.dbType, b.dbType);
				//					Console.WriteLine("{0} {1}", indexer.isPrimaryKey, b.isPrimaryKey);
				//					Console.WriteLine("{0} {1}", indexer.notNull, b.notNull);
				//					Console.WriteLine();
				//				}
				//				return false;
				//			})
				//			);

				if(table.Count != 0) {
					for(byte j = 0; j < columnAttributes.Count; ++j) {
						if(columnAttributes[j].isPrimaryKey) {
							lastId = (int) type.GetProperties()[j].GetValue(table[table.Count - 1]);
							break;
						}
					}
				}
				else
					lastId = 0;
			}

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
		/// 
		/// </summary>
		/// <returns>Повертає масив атрибутів стовбців</returns>
		public UlTableColumnAttribute[] GetColumnAttributes() => columnAttributes.ToArray();

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
			table.Clear();
		}

		/// <summary>
		/// Вносить зміни з локальної копії у таблицю з БД.
		/// </summary>
		public void Update() {
			List<T> changedElemAdd = new List<T>();
			List<T> changedElemDelete = new List<T>();
			List<T> changedElemUpdate = new List<T>();

			table.Changes.Sort((a, b)=>a.CompareTo(b.row));

			foreach(var i in table.Changes) {
				if(i.changedType == UlRowChangedType.Added)
					changedElemAdd.Add(table[i.row]);
				else if(i.changedType == UlRowChangedType.Deleted)
					changedElemDelete.Add(table[i.row]);
				else if(i.changedType == UlRowChangedType.Updated)
					changedElemUpdate.Add(table[i.row]);
			}

			if(changedElemAdd.Count != 0) {
				command.Parameters.Clear();
				command.CommandType = CommandType.Text;
				command.CommandText = $"INSERT INTO {tableAttribute.name} (";

				for(byte i = 0; i < columnAttributes.Count; ++i) {
					if(!columnAttributes[i].isPrimaryKey)
						command.CommandText += columnAttributes[i].name + (i == columnAttributes.Count - 1 ? " " : ", ");
				}
				command.CommandText += ") VALUES";

				var props = type.GetProperties();
				for(byte j = 0; j < changedElemAdd.Count; ++j) {
					command.CommandText += "(";
					for(byte i = 0; i < columnAttributes.Count; ++i) {
						if(!columnAttributes[i].isPrimaryKey) {
							var value = props[i].GetValue(changedElemAdd[j]);
							if(value == null) {
								command.CommandText += $"NULL";
							}
							else {
								SqlParameter param = new SqlParameter($"@p{j}{i}", value);
								command.Parameters.Add(param);
								command.CommandText += $"{param.ParameterName}";
							}
							command.CommandText += i == columnAttributes.Count - 1 ? "" : ", ";
						}
					}
					command.CommandText += "), ";
				}

				command.CommandText = command.CommandText.Substring(0, command.CommandText.Length - 2);
				//Console.WriteLine(command.CommandText);

				ownerDb.connection.Open();
				command.ExecuteNonQuery();
				ownerDb.connection.Close();
			}

			if(changedElemDelete.Count != 0) {
				command.CommandType = CommandType.Text;
				command.CommandText = $"DELETE FROM {tableAttribute.name} WHERE ";

				System.Reflection.PropertyInfo idProp = null;
				UlTableColumnAttribute idAttrib = null;
				for(byte i = 0; i < columnAttributes.Count; ++i) {
					if(columnAttributes[i].isPrimaryKey) {
						idProp = type.GetProperties()[i];
						idAttrib = columnAttributes[i];
					}
				}

				for(byte i = 0; i < changedElemDelete.Count; ++i) {
					command.CommandText += $"{idAttrib.name}={(int)(idProp.GetValue(changedElemDelete[i]))-1}";
					
					if(i != changedElemDelete.Count - 1)
						command.CommandText += " or ";
				}

				ownerDb.connection.Open();
				command.ExecuteNonQuery();
				ownerDb.connection.Close();
			}

			if(changedElemUpdate.Count != 0) {
				command.Parameters.Clear();
				command.CommandType = CommandType.Text;

				System.Reflection.PropertyInfo idProp = null;
				UlTableColumnAttribute idAttrib = null;
				for(byte i = 0; i < columnAttributes.Count; ++i) {
					if(columnAttributes[i].isPrimaryKey) {
						idProp = type.GetProperties()[i];
						idAttrib = columnAttributes[i];
					}
				}

				var props = type.GetProperties();
				ownerDb.connection.Open();
				for(byte i = 0; i < changedElemUpdate.Count; ++i) {
					command.CommandText = $"UPDATE {tableAttribute.name} SET ";

					for(byte j = 0; j < columnAttributes.Count; ++j) {
						if(!columnAttributes[j].isPrimaryKey) {
							SqlParameter param = new SqlParameter($"@p{j}{i}", props[j].GetValue(changedElemUpdate[i]));
							command.Parameters.Add(param);
							command.CommandText += $"{columnAttributes[j].name}=@p{j}{i}";
							if(j != columnAttributes.Count - 1)
								command.CommandText += ", ";
						}
					}

					command.CommandText += $" WHERE {idAttrib.name}={(int) (idProp.GetValue(changedElemUpdate[i])) - 1};";
					command.ExecuteNonQuery();
				}

				ownerDb.connection.Close();
			}
			
			table.ClearChanges();
		}

		public void Add(T item) {
			//var indexer = columnAttributes.FirstOrDefault((a) => a.isPrimaryKey);
			//type.GetProperties().FirstOrDefault((a) => a.GetCustomAttributes(false).Contains(indexer))?.SetValue(item, ++lastId);

			for(byte j = 0; j < columnAttributes.Count; ++j) {
				if(columnAttributes[j].isPrimaryKey) {
					type.GetProperties()[j].SetValue(item, ++lastId);
					break;
				}
			}

			table.Add(item);
		}

		public T Find(Func<T, bool> predicate) {
			return table.Find(predicate);
		}

		public void Remove(T item) {
			table.Remove(item);
		}

		public IEnumerator<T> GetEnumerator() {
			return ((IEnumerable<T>) table).GetEnumerator();
		}

		IEnumerator IEnumerable.GetEnumerator() {
			return ((IEnumerable<T>) table).GetEnumerator();
		}
	}
}
