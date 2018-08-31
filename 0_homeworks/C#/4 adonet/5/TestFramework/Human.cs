using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using DBUnlinked;

namespace TestFramework {
	class Human {
		[UlTableColumn(IsPrimaryKey : true)]
		int Id { get; set; }
		[UlTableColumn(DBType: "nvarchar(100)")]
		string Name { get; set; }
		[UlTableColumn(CanBeNull:true, DBType:"nvarchar(100)")]
		string Surname { get; set; }
	}
}
