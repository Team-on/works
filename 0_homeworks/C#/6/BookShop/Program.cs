using System;
using System.Collections;

using BookN;
using CargoN;
using BookShopN.UI;

namespace Programm{
	//MAX login length 15
	//max pass length 32
	//max email length 32


	class Program {
		static void Main(string[] args){
			Cargo cargo = new Cargo();

			cargo.Add(new Book(Book.BookTypes.Detective, "autN", "bookName", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Psychology, "autN", "bookName1", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Detective, "autN", "bookName2", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.SciFi, "autN", "bookName3", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Detective, "autN1", "bookName13", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.SciFi, "autN2", "bookName13", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Psychology, "autN3", "bookName13", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.SciFi, "autN4", "bookName13", 9.99, 42));

			//Console.WriteLine(cargo.Find(new Book(Book.BookTypes.Detective, "autN", "bookName1", 0, 0)) == null);
			//(cargo.Find(new Book(Book.BookTypes.Detective, "autN", "bookName1", 0, 0)) as Book).Print();
			//System.Threading.Thread.Sleep(10000);

			UiConsoleBookShop shop = new UiConsoleBookShop(cargo);

			shop.Launch();

			Console.SetCursorPosition(100, 50);
		}
	}
}
