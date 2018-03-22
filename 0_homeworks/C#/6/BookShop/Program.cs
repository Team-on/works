using System;
using System.Collections;

namespace BookShop{
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

	class Person
	{
		string name;
		string surname;
		string phoneNumber;

		public Person(string Name,string Surname, string PhoneNumber) {
			name = Name;
			surname = Surname;
			phoneNumber = PhoneNumber;
		}

		public Person(Person prs)
		{
			name = prs.name;
			surname = prs.surname;
			phoneNumber = prs.phoneNumber;
		}
	}

	class TrashObj
	{
		public object stored;
		public byte cnt;

	}

	class Trash : IEnumerable
	{
		//TrashObj
		ArrayList toBuy;
		int booksBuyed;

		public void Add(object toAdd)
		{
			toBuy.Add(new TrashObj() { stored = toAdd, cnt = 1 });
		}

		//Перегрузка ітератора
		IEnumerator IEnumerable.GetEnumerator()
		{
			for (int i = 0; i < toBuy.Count; i++)
			{
				yield return toBuy[i];
			}
		}

		public void Clear()
		{
			for (int i = 0; i < toBuy.Count; ++i)
			{
				booksBuyed += ((TrashObj)toBuy[i]).cnt;
			}
			toBuy.Clear();
		}

		public void Delete(object toDel)
		{
			toBuy.RemoveAt(toBuy.IndexOf(toDel));
		}
	}

	class Client : Person
	{
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

		public Client(Person prs, string Login, int Pass, string email) : base(prs)
		{
			trash = new Trash();
			login = new LoginPass(Login, Pass);
			DiscountPersent = 0;
			Email = email;
		}
	}

	//----------------------------------------------


	class Book
	{
		public enum BookTypes : byte { NONE, SciFi, Detective, END_OF_TYPES }

		BookTypes type;
		string autherName;
		string shortTitle;
		double price;
		ushort pages;
	}

	interface ICargo
	{
		void Add(object toAdd);
		object Find(object toFind);
		object Remove(object toRemove);
	}

	// class Cargo : ICargo
	//{
	//     System.Collections.Hashtable cargoData;
	//        //Перегрузити ітератор
	//}

	//------------------------------------------------------

	class BookShop
	{
		ushort usedClients;
		Client[] clients;
		ILoginable[] logData;
		ICargo cargo;
		Client currUser;

		public BookShop() : this(null)
		{
			
		}

		public BookShop(ICargo Cargo)
		{
			cargo = Cargo;
			currUser = null;
			clients = new Client[10];
			logData = new ILoginable[10];
			usedClients = 0;
		}

		public bool CreateUser(Person prs, string login, int passHash, string Email)
		{
			for (ushort i = 0; i < usedClients; ++i)
				if (login == logData[i].Login)
					return false;
			clients[usedClients] = new Client(prs, login, passHash, Email);
			logData[usedClients] = new LoginPass(login, passHash);
			++usedClients;
			return true;
		}
		public Client Login(string login, int passHash)
		{
			for (ushort i = 0; i < usedClients; ++i)
				if (login == logData[i].Login && passHash == logData[i].PassHash)
				{
					currUser = clients[i];
					break;
				}
			return currUser;
		}
		public void Logoff()
		{
			currUser = null;
		}

		public void AddToTrash(Book toAdd)
		{
			if (currUser != null)
				currUser.sTrash.Add(toAdd);
		}
		public void DelFromTrash(Book toDel)
		{
			if (currUser != null)
				currUser.sTrash.Delete(toDel);
		}
		public Trash GetClientTrash()
		{
			if (currUser != null)
				return currUser.sTrash;
			return null;
		}

		public void Buy()
		{
			if (currUser == null)
				return;
			currUser.sTrash.Clear();
		}


		public string[] GetBookTypes()
		{
			string[] rez = new string[(int)Book.BookTypes.END_OF_TYPES - 1];
			for (var i = Book.BookTypes.NONE; i < Book.BookTypes.END_OF_TYPES - 1; ++i)
				rez[(int)i] = (i + 1).ToString();
			return rez;
		}

		public Book[] GetBooksInfo(short cnt, Book.BookTypes type)
		{

			return null;
		}
	}

	//---------------------------------

	//MAX login length 15
	//max pass length 32
	//max email length 32
	

	class Program{
		static void Main(string[] args){

			UiConsoleBookShop shop = new UiConsoleBookShop();

			shop.Launch();

			Console.SetCursorPosition(100, 50);
		}
	}
}
