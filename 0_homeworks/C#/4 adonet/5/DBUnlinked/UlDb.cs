﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Data;
using System.Data.Sql;
using System.Data.SqlClient;

namespace DBUnlinked {
	/// <summary>
	/// Працює лише з MS SQL Server
	/// </summary>
	public class UlDb {
		internal SqlConnection connection;
		SqlCommand command;

		public UlDb() {
			connection = new SqlConnection();
			command = new SqlCommand {
				Connection = connection
			};
		}

		/// <summary>
		/// Викликає CreateOrLinkToDB всередині
		/// </summary>
		public UlDb(string connectionString, string initialCatalog) : base() {
			CreateOrLinkToDB(connectionString, initialCatalog);
		}

		/// <summary>
		/// Створює чи привязуються до БД.
		/// </summary>
		/// <param name="connectionString">Стандартна connectionString, але без Initial Catalog</param>
		/// <param name="dbName"> Імя БД. 
		/// <param name="alwaysRecreate"> Чи треба перестворити БД, якщо вона вже існує
		/// </param>
		/// <returns>true якщо була створена нова БД</returns>
		public bool CreateOrLinkToDB(string connectionString, string dbName, bool alwaysRecreate = false) {
			bool rez;
			connectionString += "; Initial Catalog = master";
			connection.ConnectionString = connectionString;
			connection.Open();

			command.CommandType = CommandType.Text;
			if(alwaysRecreate) {
				command.CommandText = $"IF EXISTS(select * from sys.databases where name='{dbName}') " +
				$"DROP DATABASE {dbName} " +
				$"CREATE DATABASE {dbName}";
				rez = true;
				command.ExecuteNonQuery();
			}
			else {
				command.CommandText = $"IF NOT EXISTS(select * from sys.databases where name='{dbName}') select 1 else select 0";
				rez = (int) (command.ExecuteScalar()) == 1;
				if(rez) {
					command.CommandText = $"CREATE DATABASE {dbName}";
					command.ExecuteNonQuery();
				}
			}

			connection.Close();
			connection.ConnectionString = connection.ConnectionString.Replace("master", dbName);
			connection.Open();
			connection.Close();

			return rez;
		}

		/// <summary>
		/// Створює чи привязуються до таблиці. Всі дані беруться з атрибутів класу T
		/// </summary>
		/// <typeparam name="T">Клас-шаблон для таблиці</typeparam>
		/// <returns>Таблиця, яка відповідатиме класу T</returns>
		public UlTable<T> CreateOrLinkToTable<T>() where T : class, new() {
			string tableName;
			Type type = typeof(T);
			UlTable<T> rez;
			List<UlTableColumnAttribute> columnAttributes = new List<UlTableColumnAttribute>();

			UlTableAttribute ulTableAttribute = (UlTableAttribute) type.GetCustomAttributes(false).FirstOrDefault((a) => a is UlTableAttribute);
			if(ulTableAttribute?.name?.Equals("") ?? true) {
				tableName = type.Name;
				rez = new UlTable<T>(this, new UlTableAttribute(tableName), columnAttributes);
			}
			else {
				tableName = ulTableAttribute.name;
				rez = new UlTable<T>(this, ulTableAttribute, columnAttributes);
			}

			command.CommandType = CommandType.Text;
			command.CommandText = $"IF NOT EXISTS(select * from sys.tables where name='{tableName}') " +
						$"CREATE TABLE {tableName} ( ";
			foreach(var prop in type.GetProperties()) {
				if(prop.GetGetMethod().IsPrivate || prop.GetSetMethod().IsPrivate)
					continue;

				if(prop.GetCustomAttributes(false).FirstOrDefault((a) => a is UlTableColumnAttribute) is UlTableColumnAttribute columnAttribute) {
					if(columnAttribute.name?.Equals("") ?? true)
						columnAttribute.name = prop.Name;

					command.CommandText += columnAttribute.name + ' ';

					//for(int i = 0; i < table.Columns.Count; i++) {
					//	sqlsc += ",";
					//}
					//return sqlsc.Substring(0, sqlsc.Length - 1) + "\n)";

					if(columnAttribute.dbType?.Equals("") ?? true)
						switch(prop.PropertyType.FullName) {
						case "System.Byte":
						columnAttribute.dbType = "tinyint";
						break;
						case "System.Int16":
						columnAttribute.dbType = "smallint";
						break;
						case "System.Int32":
						columnAttribute.dbType = "int";
						break;
						case "System.Int64":
						columnAttribute.dbType = "bigint";
						break;
						case "System.Float":
						columnAttribute.dbType = "real";
						break;
						case "System.Double":
						columnAttribute.dbType = "float";
						break;
						case "System.Decimal":
						columnAttribute.dbType = "decimal";
						break;
						case "System.DateTime":
						columnAttribute.dbType = "datetime";
						break;

						case "System.String":
						default:
						columnAttribute.dbType = "nvarchar(100)";
						break;
						}

					command.CommandText += columnAttribute.dbType + ' ';

					if(columnAttribute.isPrimaryKey)
						command.CommandText += "IDENTITY PRIMARY KEY ";
					if(columnAttribute.notNull && !columnAttribute.isPrimaryKey)
						command.CommandText += "NOT NULL ";

					command.CommandText += ", ";
					columnAttributes.Add(columnAttribute);
				}
			}

			command.CommandText = command.CommandText.Substring(0, command.CommandText.Length - 2);
			command.CommandText += ")";

			connection.Open();
			command.ExecuteNonQuery();
			connection.Close();

			return rez;
		}
	}
}
