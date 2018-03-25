using System;
using System.Collections;

namespace ClientN {
	interface ILoginable{
		string Login { get; }
		int PassHash { get; }
	}

	class LoginPass : ILoginable{
		string login;
		public string Login {
			get { return login; }
			private set {
				login = value;
				if (login.Length >= 15)
					login = login.Substring(0, 14);
			}
		}
		public int PassHash { get; private set; }

		public static int Hasher(string pass){
			return pass.GetHashCode();
		}

		//newPass - в виді char
		public LoginPass(string newLogin, int newPass){
			login = newLogin;
			PassHash = newPass;
		}
	}

	class Person {
		string name;
		string surname;
		string phoneNumber;

		public Person() {
			name = null;
			surname = null;
			phoneNumber = null;
		}
		public Person(string Name, string Surname, string PhoneNumber) {
			name = Name;
			surname = Surname;
			phoneNumber = PhoneNumber;
		}
		public Person(Person prs) {
			name = prs.name;
			surname = prs.surname;
			phoneNumber = prs.phoneNumber;
		}
	}

	class TrashObj {
		public object stored;
		public byte cnt;

		public TrashObj(object Stored, byte Cnt) {
			stored = Stored;
			cnt = Cnt;
		}
	}

	class Trash : IEnumerable {
		//TrashObj
		ArrayList toBuy;
		uint booksBuyed;

		public void Add(TrashObj toAdd) {
			toBuy.Add(toAdd);
		}

		//Перегрузка ітератора
		IEnumerator IEnumerable.GetEnumerator() {
			for (int i = 0; i < toBuy.Count; i++) {
				yield return toBuy[i];
			}
		}

		public void Clear() {
			for (int i = 0; i < toBuy.Count; ++i) {
				booksBuyed += ((TrashObj)toBuy[i]).cnt;
			}
			toBuy.Clear();
		}

		public void Delete(object toDel) {
			for (int i = 0; i < toBuy.Count; ++i) {
				TrashObj ob = toBuy[i] as TrashObj;
				if (ob == null)
					continue;
				if (toDel == ob.stored) {
					toBuy.RemoveAt(i);
					return;
				}
			}
		}
	}

	class Client : Person {
		//Свойства до всього
		Trash trash;
		LoginPass login;
		public byte DiscountPersent { get; private set; }
		public string Email { get; private set; }

		public Trash sTrash {
			get {
				return trash;
			}
		}
		public LoginPass sLogin {
			get {
				return login;
			}
		}

		public Client(Person prs, string Login, int Pass, string email) : base(prs) {
			trash = new Trash();
			login = new LoginPass(Login, Pass);
			DiscountPersent = 0;
			Email = email;
		}
	}
}
