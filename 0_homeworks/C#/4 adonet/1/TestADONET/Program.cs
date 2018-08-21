using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

using System.Data;
using System.Data.SqlClient;

namespace TestADONET {
	class Program {
		static Random random = new Random();

		static void Main(string[] args) {
			CreateUserDB();
			ReadSchoolDB("School", "NVK666Pupil");
		}

		static void CreateUserDB(){
			SqlConnection con = new SqlConnection(@"Server=(localdb)\mssqllocaldb; Database=master; Integrated Security=True");

			try {
				Console.WriteLine("Opening");
				con.Open();
				Console.WriteLine("Opened\n");


				SqlCommand com = new SqlCommand(
					"IF NOT EXISTS(select * from sys.databases where name='Users') " +
					"CREATE DATABASE Users ",
					con
				);
				Console.WriteLine("Creating");
				com.ExecuteNonQuery();
				Console.WriteLine("Created\n");

				Console.WriteLine("Reopen START");
				con.ChangeDatabase("Users");
				Console.WriteLine("Reopen END\n");

				com.CommandText = "IF NOT EXISTS(select * from sys.tables where name='_User') " +
					"CREATE TABLE _User ( " +
					"IdUser TINYINT IDENTITY PRIMARY KEY, " +
					"FirstName NVARCHAR(32), " +
					"SecondtName NVARCHAR(32), " +
					"ThirdName NVARCHAR(32), " +
					"Login NVARCHAR(16) NOT NULL, " +
					"Password NVARCHAR(32) NOT NULL " +
					")";
				Console.WriteLine("Creating table");
				com.ExecuteNonQuery();
				Console.WriteLine("Created table\n");

				
				Console.WriteLine("Inserting values");
				string[] passToCreate = new string[] {
					"qwerty",
					"123456",
					"<juZjqSQjuj{fpz]y",
					"UfknhfyPFD:LBPkbdf'Nfynjce",
					"Lf<eltnNfr!1",
				};
				for(byte i = 0; i < passToCreate.Length; ++i)
					InsertValue($"Dude{i}", $"Dude{i}", $"Dude{i}", $"Dude{i}", passToCreate[i]);
				Console.WriteLine("Values inserted!\n");

				ReadSchoolDB("Users", "_User");

				//
				void InsertValue(string fname, string sname, string tname, string login, string pass){
					string key = "YtrhjvfynDsl<j;tymrb";
					StringBuilder encryptPass = new StringBuilder(pass.Length + 3, pass.Length + 3);
					//StringBuilder backTest = new StringBuilder(pass.Length, pass.Length);

					//Шифрування через XOR
					// Додаю 1 випадковий символ на початок і 2 в кінець
					encryptPass.Append((char) random.Next(2, 130));
					for(byte i = 0; i < pass.Length; i++) {
						encryptPass.Append((char) (pass[i] ^ key[i % key.Length]));
						//backTest.Append((char) (encryptPass[i + 1] ^ key[i % key.Length]));
					}
					encryptPass.Append((char)random.Next(0, 255));
					encryptPass.Append((char) random.Next(130, 200));

					//Console.WriteLine($"{pass:20}\n{encryptPass:20}\n{backTest:20}\n\n");

					com.CommandText = "INSERT INTO _User " +
						"(FirstName, SecondtName, ThirdName, Login, Password)" +
						"VALUES " +
						$"(N'{fname}', N'{sname}', N'{tname}', N'{login}', N'{encryptPass}') ";
					com.ExecuteNonQuery();
				}
			}
			catch(System.Exception ex) {
				Console.WriteLine($"ERROR: {ex}");
			}
			finally {
				Console.WriteLine("\nClosing");
				if(con.State == ConnectionState.Open) {
					con.Close();
					Console.WriteLine("Closed\n");
				}
				else
					Console.WriteLine("Warning: Already closed\n");
			}
		}

		static void ReadSchoolDB(string database, string table) {
			Console.WindowWidth = 150;
			SqlConnection connection = new SqlConnection($@"Server=(localdb)\mssqllocaldb; Database={database}; Integrated Security=True");
			try {
				Console.WriteLine("Opening");
				connection.Open();
				Console.WriteLine("Opened\n------------------------------------------------------\n");

				Console.WriteLine("\t\t\tServer info");
				foreach (var i in connection.GetType().GetProperties())
					Console.WriteLine($"{i.Name,-32}: {i.GetValue(connection)}");
				Console.WriteLine('\n');

				SqlCommand command = new SqlCommand($"select count(*) from {table}", connection);
				Console.WriteLine($"Count (*): {command.ExecuteScalar()}");

				command.CommandText = $"select * from {table}";
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
									curr = reader.GetValue(i).ToString().Replace('і', 'i');
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
