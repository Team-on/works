using System;

//Не хоче він називатися просто Book
namespace BookN {
	class Book {
		public enum BookTypes : byte { NONE, Psychology, SciFi, Detective, END_OF_TYPES }

		//Мож на свойства(лише get) переписати? А встановлювати в конструкторах.
		public BookTypes type;
		public string autherName;
		public string shortTitle;
		public double price;
		public ushort pages;

		public Book() : this(BookTypes.NONE, "Team", "NONE", 99999.99, 1) {
		}

		public Book(BookTypes Type, string AutherName, string ShortTitle, double Price, ushort Pages) {
			type = Type;
			autherName = AutherName;
			shortTitle = ShortTitle;
			price = Price;
			pages = Pages;
		}

		public Book(Book bk) {
			type = bk.type;
			autherName = bk.autherName;
			shortTitle = bk.shortTitle;
			price = bk.price;
			pages = bk.pages;
		}
		public void Print() {
			Console.WriteLine("Type of book: " + type);
			Console.WriteLine("Autor name: " + autherName);
			Console.WriteLine("Short title: " + shortTitle);
			Console.WriteLine("price: " + price);
			Console.WriteLine("quantity pages: " + pages);
		}

		public override int GetHashCode() {
			var hash = 5;
			hash = hash * 11 + autherName.GetHashCode();
			hash = hash * 11 + shortTitle.GetHashCode();
			return hash;
		}

		public override bool Equals(object obj) {
			Book book = obj as Book;
			if (book == null)
				return false;
			return book.autherName == autherName && book.shortTitle == shortTitle;
		}

		public bool EqualsByTitle(Book book) {
			return book.shortTitle == shortTitle;
		}

		public bool ContainInTitle(string title) {
			int cnt = 0;
			for (int i = 0, j = 0; i < shortTitle.Length; ++i) {
				if(char.ToLower(shortTitle[i]) == char.ToLower(title[j])) {
					++cnt;
					++j;
					if (cnt == title.Length)
						return true;
				}
				else {
					cnt = j = 0;
				}
			}
			return false;
		}

	}
}
