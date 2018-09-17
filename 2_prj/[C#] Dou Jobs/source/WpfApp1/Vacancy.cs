using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1 {
	public class Vacancy {
		public int Id { get; set; }
		public int IdDou { get; set; }

		public string Title { get; set; }
		public string Company { get; set; }
		public string Link { get; set; }

		public string Salary { get; set; }
		public string City { get; set; }
		public string Date { get; set; }

		public string ShortDescription { get; set; }
	}
}
