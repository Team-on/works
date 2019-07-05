using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Web;
using System.Data;
using System.Data.OleDb;
using System.Xml;
using System.IO;

namespace Converter {
	class Program {
		static void Main(string[] args) {

			var fileNameXls = @"D:\work\Converter\Runefall_translation.xlsx";
			var fileNameXml = @"D:\work\Converter\English.xml";
			var szConnectionString = @"Provider=Microsoft.Jet.OLEDB.4.0;" +
									"Data Source = '" + fileNameXls + "';" +
									"Extended Properties=\"Excel 8.0;HDR=YES;\"";
			szConnectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=" + fileNameXls + ";Extended Properties='Excel 12.0 Xml; HDR=YES; IMEX=1 '";

			//szConnectionString = @"Provider = Microsoft.ACE.OLEDB.12.0;" +
			//						"Data Source = " + fileNameXls + ";" +
			//						"Extended Properties=\"Excel 8.0;HDR=YES;\"";


			Dictionary<string, string> dict = new Dictionary<string, string>();

			//Read .xls file
			using (OleDbConnection conn = new OleDbConnection(szConnectionString)) {
				conn.Open();

				var dtSchema = conn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, new object[] { null, null, null, "TABLE" });
				var Sheet1Name = dtSchema.Rows[0].Field<string>("TABLE_NAME");

				OleDbDataAdapter objDA = new System.Data.OleDb.OleDbDataAdapter
				("select * from [" + Sheet1Name + "]", conn);
				DataSet excelDataSet = new DataSet();
				objDA.Fill(excelDataSet);
				var table = excelDataSet.Tables[0];

				OleDbCommand command = new OleDbCommand();
				command.CommandType = CommandType.Text;
				command.CommandText = $"select * from [{Sheet1Name}]";
				command.Connection = conn;
				OleDbDataReader reader = command.ExecuteReader();
				if (reader.HasRows) {
					while (reader.Read()) {
						//for (byte i = 0; i < reader.FieldCount; ++i) {
						//	var name = reader.GetName(i);
						//	var value = reader.GetValue(i);
						//	Console.Write($"/*{name}*/ {value}  ");
						//}
						//Console.WriteLine();
						dict[reader.GetValue(1).ToString()] = reader.GetValue(2).ToString();
					}
				}
				
				reader.Close();
			}

			//write to xml file
			XmlDocument xDoc = new XmlDocument();
			xDoc.PreserveWhitespace = true;
			xDoc.Load(fileNameXml);
			XmlElement xRoot = xDoc.DocumentElement;

			foreach (XmlNode node in xRoot.ChildNodes) {
				if(node.Attributes?[0]?.InnerText != null){
					string id = node.Attributes[0].InnerText;
					if (dict.ContainsKey(id)) {
						node.InnerText = dict[id].Replace("\n", "&#13;");
						if(dict[id].Length >= 255)
						{

						}
					}
					else {
						Console.WriteLine("No match for " + id + " in .xls");
						node.InnerText = "No match for " + id + " in .xls";
					}

					if (node.InnerText.Length == 0) {
						Console.WriteLine("Untranslated " + id);
						node.InnerText = "Untranslated " + id;
					}
				}
			}
			xDoc.Save(fileNameXml);


			string text;
			StreamReader sr = new StreamReader(fileNameXml);
			text = sr.ReadToEnd();
			text = text.Replace("&amp;#13;", "&#13;");
			sr.Close();

			StreamWriter ws = new StreamWriter(fileNameXml, false);
			ws.Write(text);
			ws.Close();
		}
		
	}
}
