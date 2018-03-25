using System;

using CargoN;
using BookN;
using ClientN;

namespace BookShopN {
	class BookShop {
		ushort usedClients;
		Client[] clients;
		ILoginable[] logData;
		ICargo cargo;
		Client currUser;

		public BookShop() : this(null) {

		}

		public BookShop(ICargo Cargo) {
			cargo = Cargo;
			currUser = null;
			clients = new Client[10];
			logData = new ILoginable[10];
			usedClients = 0;
		}

		public bool CreateUser(Person prs, string login, int passHash, string Email) {
			for (ushort i = 0; i < usedClients; ++i)
				if (login == logData[i].Login)
					return false;
			clients[usedClients] = new Client(prs, login, passHash, Email);
			logData[usedClients] = new LoginPass(login, passHash);
			++usedClients;
			return true;
		}
		public Client Login(string login, int passHash) {
			for (ushort i = 0; i < usedClients; ++i)
				if (login == logData[i].Login && passHash == logData[i].PassHash) {
					currUser = clients[i];
					break;
				}
			return currUser;
		}
		public void Logoff() {
			currUser = null;
		}

		public void AddToTrash(Book toAdd) {
			if (currUser != null)
				currUser.sTrash.Add(new TrashObj(toAdd, 1));
		}
		public void DelFromTrash(Book toDel) {
			if (currUser != null)
				currUser.sTrash.Delete(toDel);
		}
		public Trash GetClientTrash() {
			if (currUser != null)
				return currUser.sTrash;
			return null;
		}

		public void Buy() {
			if (currUser == null)
				return;
			currUser.sTrash.Clear();
		}

		public System.Collections.Generic.List<Book> FindBookByTitle(string title) {
			System.Collections.Generic.List<Book> arr = new System.Collections.Generic.List<Book>(10);
			foreach(var i in cargo) {
				Book book = i as Book;
				if (i == null)
					continue;
				if (book.ContainInTitle(title))
					arr.Add(book);
			}
			return arr;
		}

		public string[] GetBookTypes() {
			string[] rez = new string[(int)Book.BookTypes.END_OF_TYPES - 1];
			for (var i = Book.BookTypes.NONE; i < Book.BookTypes.END_OF_TYPES - 1; ++i)
				rez[(int)i] = (i + 1).ToString();
			return rez;
		}

		//public Book[] GetBooksInfo(short cnt, Book.BookTypes type) {
		//
		//	return null;
		//}
	}
}
