using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

//SQL using
using System.Data;
using System.Data.Common;
using System.Data.SQLite;
using System.Data.Entity;
using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace SQLite_test {
	public class Student {
		public int Id { get; set; }
		public string FirstName { get; set; }
		public string SecondName { get; set; }
		public byte Course { get; set; }

		public Student() : this("", "", 1) {

		}

		public Student(string firstName, string secondName, byte course) {
			FirstName = firstName;
			SecondName = secondName;
			Course = course;
		}
	}
}
