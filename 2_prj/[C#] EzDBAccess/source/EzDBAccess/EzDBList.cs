using System;
using System.Collections;
using System.Collections.Generic;

using System.Data;
using System.Data.Common;

namespace EzDBAccess {

	//Працює лише з повністю публічними свойствами
	//Має бути свойсто Id
	public class EzDBList<T> : IEnumerable<T> where T : class, new() {
		//string debugStr = "EMPTY";

		Type type;
		string dbName;
		string tableName;
		int lastId;
		List<T> list;
		DbProviderFactory factory;
		DbConnection connection;
		DbCommand command;

		public EzDBList(string providerName, string connectionStr, bool ForceRecreate = false) {
			list = new List<T>();
			type = typeof(T);
			dbName = type.ToString().Substring(type.ToString().LastIndexOf('.') + 1) + 's';
			tableName = dbName.Substring(0, dbName.Length - 1);

			factory = DbProviderFactories.GetFactory(providerName);

			connection = factory.CreateConnection();
			connection.ConnectionString = connectionStr;
			connection.Open();

			command = factory.CreateCommand();
			command.Connection = connection;
			
			CreateDBIfNeed(ForceRecreate);
			CreateTableIfNeed();
			ReadTable();
		}

		//public string GetDebugStr() {
		//	return debugStr;
		//}

		public void Add(T obj) {
			command.Parameters.Clear();
			command.CommandText = $"INSERT INTO {tableName} (";
			var props = type.GetProperties();
			for(byte i = 0; i < props.Length; ++i) {
				if(props[i].GetGetMethod().IsPublic && props[i].GetSetMethod().IsPublic && props[i].Name != "Id")
					command.CommandText += props[i].Name + (i == props.Length - 1 ? " " : ", ");
			}
			command.CommandText += ") VALUES (";
			for(byte i = 0; i < props.Length; ++i) {
				if(props[i].GetGetMethod().IsPublic && props[i].GetSetMethod().IsPublic && props[i].Name != "Id") {
					var param = factory.CreateParameter();
					param.ParameterName = $"@p{i}";
					param.Value = props[i].GetValue(obj);
					command.Parameters.Add(param);

					command.CommandText += $"{param.ParameterName}";

					command.CommandText += i == props.Length - 1 ? " " : ", ";
				}
			}
			command.CommandText += ")";
			command.ExecuteNonQuery();

			type.GetProperty("Id").SetValue(obj, ++lastId);
			list.Add(obj);
		}

		public void AddRange(IEnumerable<T> obj) {
			foreach(var i in obj)
				Add(i);
		}

		public void Remove(T obj) {
			command.Parameters.Clear();
			var param = factory.CreateParameter();
			param.ParameterName = $"@idDel";
			param.Value = type.GetProperty("Id").GetValue(obj);
			command.Parameters.Add(param);

			command.CommandText = $"DELETE FROM {tableName} where Id=@idDel";
			command.ExecuteNonQuery();
			list.Remove(obj);
		}

		public T Find(Predicate<T> predicate) {
			foreach(T i in list)
				if(predicate.Invoke(i))
					return i;
			return null;
		}

		public int Count() => list.Count;

		public T this[int id]{
			get => list[id];
			set => list[id] = value;
		}

		public IEnumerator<T> GetEnumerator() => ((IEnumerable<T>) list).GetEnumerator();
		IEnumerator IEnumerable.GetEnumerator() => ((IEnumerable<T>) list).GetEnumerator();

		void CreateDBIfNeed(bool isForsed){
			command.CommandType = CommandType.Text;
			if(isForsed){
				command.CommandText = $"IF EXISTS(select * from sys.databases where name='{dbName}') " +
				$"DROP DATABASE {dbName} " + 
				$"CREATE DATABASE {dbName} ";
			}
			else{
				command.CommandText = $"IF NOT EXISTS(select * from sys.databases where name='{dbName}') " +
				$"CREATE DATABASE {dbName} ";
			}
			command.ExecuteNonQuery();
			connection.ChangeDatabase(dbName);
		}

		void CreateTableIfNeed(){
			command.CommandType = CommandType.Text;
			command.CommandText = $"IF NOT EXISTS(select * from sys.tables where name='{tableName}') " +
						$"CREATE TABLE {tableName} ( ";
			foreach(var prop in type.GetProperties()) {
				if(prop.GetGetMethod().IsPublic && prop.GetSetMethod().IsPublic) {
					command.CommandText += prop.Name + ' ';
					if(prop.PropertyType.Name.ToLower() == "bool")
						command.CommandText += "BIT ";
					else if(prop.PropertyType.Name.ToLower() == "string")
						command.CommandText += "NVARCHAR(100) ";
					else
						command.CommandText += "INT ";

					if(prop.Name == "Id")
						command.CommandText += "IDENTITY PRIMARY KEY ";

					command.CommandText += ", ";
				}
			}
			command.CommandText = command.CommandText.Substring(0, command.CommandText.Length - 2);
			command.CommandText += ")";
			command.ExecuteNonQuery();
		}
		
		void ReadTable() {
			command.CommandType = CommandType.Text;
			command.CommandText = $"select * from {tableName}";
			DbDataReader reader = command.ExecuteReader();
			if(reader.HasRows) {
				T curr;
				while(reader.Read()) {
					curr = new T();
					for(byte i = 0; i < reader.FieldCount; ++i) {
						var name = reader.GetName(i);
						var value = reader.GetValue(i);

						foreach(var prop in type.GetProperties()) {
							if(prop.Name == name) {
								prop.SetValue(curr, value);
								break;
							}
						}
					}
					list.Add(curr);
				}
			}
			if(list.Count != 0)
				lastId = (int) type.GetProperty("Id").GetValue(list[list.Count - 1]);
			else
				lastId = 0;
			reader.Close();
		}
	}
}