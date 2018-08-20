using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

using System.Data;
using System.Data.SqlClient;

namespace TestADONET {
	class Program {
		static void Main(string[] args) {

			SqlConnection con = new SqlConnection(@"Server=(localdb)\mssqllocaldb; Database=master; Integrated Security=True");

			try {
				Console.WriteLine("Opening");
				con.Open();
				Console.WriteLine("Opened\n");


				SqlCommand com = new SqlCommand(
					"IF EXISTS(select * from sys.databases where name='Users') " +
					"DROP DATABASE Users " + 
					"CREATE DATABASE Users ",
					con
				);
				Console.WriteLine("Creating");
				com.ExecuteNonQuery();
				Console.WriteLine("Created\n");

				Console.WriteLine("Reopen START");
				con.Close();
				con = new SqlConnection(@"Server=(localdb)\mssqllocaldb; Database=Users; Integrated Security=True");
				con.Open();
				com.Connection = con;
				Console.WriteLine("Reopen END\n");

				com.CommandText = "CREATE TABLE User( " +
					"IdUser TINYINT IDENTITY PRIMARY KEY, " +
					"Login NVARCHAR(16) NOT NULL, " +
					"Password NVARCHAR(32) NOT NULL" +
					")";
				Console.WriteLine("Creating table");
				com.ExecuteNonQuery();
				Console.WriteLine("Created table\n");
			}
			catch (System.Exception ex) {
				Console.WriteLine($"ERROR: {ex}");
			}
			finally {
				Console.WriteLine("Closing");
				if (con.State == ConnectionState.Open) {
					con.Close();
					Console.WriteLine("Closed\n");
				}
				else
					Console.WriteLine("Warning: Already closed\n");
			}

			//ReadSchoolDB();
		}

		static void ReadSchoolDB() {
			Console.WindowWidth = 150;
			SqlConnection connection = new SqlConnection(@"Server=(localdb)\mssqllocaldb; Database=School; Integrated Security=True");
			try {
				Console.WriteLine("Opening");
				connection.Open();
				Console.WriteLine("Opened\n------------------------------------------------------\n");

				Console.WriteLine("\t\t\tServer info");
				foreach (var i in connection.GetType().GetProperties())
					Console.WriteLine($"{i.Name,-32}: {i.GetValue(connection)}");
				Console.WriteLine('\n');

				SqlCommand command = new SqlCommand("select count(*) from NVK666Pupil", connection);
				Console.WriteLine($"Count (*): {command.ExecuteScalar()}");

				command.CommandText = "select * from NVK666Pupil";
				using (SqlDataReader reader = command.ExecuteReader()) {
					if (reader.HasRows) {
						Console.WriteLine($"FieldCount: {reader.FieldCount}");
						byte[] padSizes = new byte[reader.FieldCount];
						for (byte i = 0; i < reader.FieldCount; ++i)
							padSizes[i] = (byte)(reader.GetName(i).Length + 3);

						string header = "", curr;
						for (byte i = 0; i < reader.FieldCount; ++i)
							header += reader.GetName(i).PadRight(padSizes[i]);
						Console.WriteLine(header);

						while (reader.Read()) {
							header = "";
							for (byte i = 0; i < reader.FieldCount; ++i) {
								if (reader.GetValue(i) is DateTime dt)
									curr = dt.ToShortDateString();
								else if (reader.GetValue(i) is bool b)
									curr = (b ? "Man" : "Woman");
								else
									//Replace UA 'i' with ENG 'i'
									curr = reader.GetValue(i).ToString().Replace('³', 'i');
								if (curr.Length >= padSizes[i] - 1)
									curr = curr.Substring(0, padSizes[i] - 1);
								header += curr.PadRight(padSizes[i]);
							}
							Console.WriteLine(header);
						}
					}
				}

			}
			catch (SqlException ex) {
				Console.WriteLine(ex.Message);
			}
			finally {
				Console.WriteLine("\n------------------------------------------------------\nClosing");
				if (connection.State == ConnectionState.Open)
					connection.Close();
				Console.WriteLine("Closed");
			}

		}
	}
}
