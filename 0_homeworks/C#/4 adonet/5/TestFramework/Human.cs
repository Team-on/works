using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using DBUnlinked;

namespace TestFramework {
	[UlTable(Name:"testtablenames")]
	class Human {
		/*
		Підтримувані типи для автоматичного визначення: 
		System.Byte
		System.Int16
		System.Int32
		System.Int64
		System.Float
		System.Double
		System.Decimal
		System.DateTime
		System.String (буде nvarchar(100))

		Для всіх інших буде nvarchar(100) а зберігатися  .ToString()
		*/

		[UlTableColumn(IsPrimaryKey:true)]
		public int Id { get; set; }

		[UlTableColumn(DBType:"nvarchar(100)", Name:"FirstName")]
		public string Name { get; set; }
		
		[UlTableColumn(NotNull:false, DBType:"nvarchar(100)", Name:"LastName")]
		public string Surname { get; set; }

		public Human() {}

		public Human(string name, string surname) {
			Name = name;
			Surname = surname;
		}
	}
}
