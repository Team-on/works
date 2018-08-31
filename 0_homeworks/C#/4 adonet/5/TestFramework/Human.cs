using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using DBUnlinked;

namespace TestFramework {
	[UlTable]
	class Human {
		[UlTableColumn(IsPrimaryKey:true)]
		public int Id { get; set; }

		[UlTableColumn(DBType:"nvarchar(100)")]
		public string Name { get; set; }
		
		[UlTableColumn(CanBeNull:true, DBType:"nvarchar(100)")]
		public string Surname { get; set; }

		public Human() {}

		public Human(string name, string surname) {
			Name = name;
			Surname = surname;
		}
	}
}
