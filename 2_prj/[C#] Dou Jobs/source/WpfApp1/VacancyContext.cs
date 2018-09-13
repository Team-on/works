using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Data;
using System.Data.Entity;

namespace WpfApp1 {
	class VacancyContext : DbContext {
		public DbSet<Vacancy> Vacancies { get; set; }

		public VacancyContext() : base("Default") { }

		public static VacancyContext db = new VacancyContext();
	}
}
