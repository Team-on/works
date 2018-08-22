using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Phonebook {
	class PhoneBook {
		public int Id {get; set;}
		public string Phone {get; set;}
		public string AdressCity {get; set;}
		public string AdressStreet { get; set;}
		public string AdressStreetNum { get; set;}
		public string AdressHome { get; set;}

		public PhoneBook() {}

		public PhoneBook(string phone, string adressCity, string adressStreet, string adressStreetNum, string adressHome) {
			Phone = phone;
			AdressCity = adressCity;
			AdressStreet = adressStreet;
			AdressStreetNum = adressStreetNum;
			AdressHome = adressHome;
		}
	}
}
