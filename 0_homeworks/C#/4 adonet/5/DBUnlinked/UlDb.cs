﻿using System;
using System.Linq;
using System.Data;
using System.Data.Sql;
using System.Data.SqlClient;

namespace DBUnlinked {
	/// <summary>
	/// Працює лише з MS SQL Server
	/// </summary>
	public class UlDb {
		SqlConnection connection;
		SqlCommand command;

		public UlDb() {
			connection = new SqlConnection();
			command = new SqlCommand();
			command.Connection = connection;
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
				connection.ChangeDatabase(dbName);
			}
			else {
				command.CommandText = $"IF NOT EXISTS(select * from sys.databases where name='{dbName}') select 1 else select 0";
				rez = (int) (command.ExecuteScalar()) == 1;
				if(rez) {
					command.CommandText = $"CREATE DATABASE {dbName}";
					command.ExecuteNonQuery();
					connection.ChangeDatabase(dbName);
				}
			}

			connection.Close();
			return rez;
		}

		public UlTable<T> CreateOrLinkToTable<T>() {
			return null;
		}
	}
}
