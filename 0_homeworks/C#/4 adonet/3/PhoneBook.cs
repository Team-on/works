using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Phonebook {
	class PhoneBook : ICloneable{
		public int Id {get; set;}
		public string FirstName {get; set;}
		public string LastName {get; set;}
		public string Phone {get; set; }
		public string AdressCity {get; set;}
		public string AdressStreet { get; set;}
		public int AdressStreetNum { get; set;}
		public int AdressHome { get; set;}

		public PhoneBook() {}

		public PhoneBook(string firstName, string lastName, string phone, string adressCity, string adressStreet, int adressStreetNum, int adressHome) {
			FirstName = firstName;
			LastName = lastName;
			Phone = phone;
			AdressCity = adressCity;
			AdressStreet = adressStreet;
			AdressStreetNum = adressStreetNum;
			AdressHome = adressHome;
		}

		public object Clone() => MemberwiseClone();
	}
}
