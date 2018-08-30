using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;

namespace ConsoleApp22
{
	class Program
	{
		static void PrintDataSet(DataSet ds)
		{
			
			Console.WriteLine("DataSet is named: {0}", ds.DataSetName);
			
			
			foreach (DataTable dt in ds.Tables)
			{
				Console.WriteLine("=> {0} Table:", dt.TableName);
				
				for (int curCol = 0; curCol < dt.Columns.Count; curCol++)
				{
					Console.Write(dt.Columns[curCol].ColumnName + "\t");
				}
				Console.WriteLine("\n	");
				
				for (int curRow = 0; curRow < dt.Rows.Count; curRow++)
				{
					for (int curCol = 0; curCol < dt.Columns.Count; curCol++)
					{
						Console.Write(dt.Rows[curRow][curCol].ToString() + "\t");
					}
					Console.WriteLine();
				}
			}
		}




		static void Main(string[] args)
		{

			DataColumn carIDColumn = new DataColumn();
			carIDColumn.ColumnName = "CarID";
			carIDColumn.DataType = typeof(int);

			carIDColumn.Caption = "Car ID";
			carIDColumn.ReadOnly = true;
			carIDColumn.AllowDBNull = false;
			carIDColumn.Unique = true;

			carIDColumn.AutoIncrement = true;
			carIDColumn.AutoIncrementSeed = 0;
			carIDColumn.AutoIncrementStep = 1;
/////////////////////////////////////////////////////////////////////////////////////////
			DataColumn carMakeColumn = new DataColumn("Make", typeof(string));
//////////////////////////////////////////////////////////////////////////////////////////			
            DataColumn carColorColumn = new DataColumn("Color", typeof(string));
//////////////////////////////////////////////////////////////////////////////////////////			
			DataColumn carPetNameColumn = new DataColumn("PetName", typeof(string));
			carPetNameColumn.Caption = "Pet Name";
//////////////////////////////////////////////////////////////////////////////////////////			

			DataTable inventoryTable = new DataTable("Inventory");

			inventoryTable.Columns.AddRange(new DataColumn[]{ carIDColumn, carMakeColumn, carColorColumn, carPetNameColumn });

			inventoryTable.PrimaryKey = new DataColumn[] { inventoryTable.Columns[0] };
			//inventoryTable.er
//////////////////////////////////////////////////////////////////////////////////////////			

			DataRow carRow = inventoryTable.NewRow();
			carRow["Make"] = "BMW";
			carRow["Color"] = "Black";
			carRow["PetName"] = "Hamlet";
			inventoryTable.Rows.Add(carRow);
//////////////////////////////////////////////////////////////////////////////////////////
			carRow = inventoryTable.NewRow();
			carRow[1] = "Saab";
			carRow[2] = "Red";
			carRow[3] = "Sea Breeze";
			inventoryTable.Rows.Add(carRow);
//////////////////////////////////////////////////////////////////////////////////////////
			DataSet ds = new DataSet("BD");
			ds.Tables.Add(inventoryTable);
			// var k=ds.Tables[0];
//////////////////////////////////////////////////////////////////////////////////////////
			PrintDataSet(ds);

		}
	}
}
