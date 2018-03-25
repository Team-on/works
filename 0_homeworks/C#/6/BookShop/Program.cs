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

			cargo.Add(new Book(Book.BookTypes.Art, "autN", "bookName", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.ActionAndAdventure, "autN", "bookName1", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Art, "autN", "bookName2", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.ActionAndAdventure, "autN", "bookName3", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Anthology, "autN1", "bookName13", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.ActionAndAdventure, "autN2", "bookName13", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Anthology, "autN3", "bookName13", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Anthology, "autN4", "bookName13", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Trilogy, "Team", "OneBook", 9.99, 42));
			cargo.Add(new Book(Book.BookTypes.Trilogy, "Team", "TwoBook", 9.99, 42));

			cargo.Remove(new Book(Book.BookTypes.NONE, "Team", "OneBook", 0, 0));

			UiConsoleBookShop shop = new UiConsoleBookShop(cargo);

			shop.Launch();

			Console.SetCursorPosition(100, 50);
		}
	}
}
