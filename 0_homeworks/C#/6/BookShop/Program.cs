using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BookShop{
	interface ILoginable{
		string Login { get; }
		string PassHash { get; }
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
		public string PassHash { get; private set; }

		public static int Hasher(string pass){
			return pass.GetHashCode();
		}

		//newPass - в виді char
		public LoginPass(string newLogin, string newPass){
			login = newLogin;
			PassHash = newPass;
		}
	}

	class Person
	{
		string name;
		string surname;
		string phoneNumber;

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
		byte discountPersent;

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

		public Client(Person prs, string Login, string Pass) : base(prs)
		{
			trash = new Trash();
			login = new LoginPass(Login, Pass);
			discountPersent = 0;
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

		public BookShop()
		{
			currUser = null;
			cargo = null;
			logData = null;
			clients = null;
		}

		public BookShop(ICargo Cargo)
		{
			cargo = Cargo;
			currUser = null;
			clients = new Client[10];
			logData = new ILoginable[10];
			usedClients = 0;
		}

		public bool CreateUser(Person prs, string login, string passHash)
		{
			for (ushort i = 0; i < usedClients; ++i)
				if (login == logData[i].Login)
					return false;
			clients[usedClients - 1] = new Client(prs, login, passHash);
			logData[usedClients - 1] = new LoginPass(login, passHash);
			return true;
		}
		public Client Login(string login, string passHash)
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

	struct Coord
	{
		public short x, y;
		public Coord(short X, short Y) { x = X; y = Y; }
	}

	interface Element
	{
		Coord pos { set; get; }
		void Print();
	}

	interface ActiveElement : Element
	{
	}

	class StaticElement : Element
	{
		public Coord pos { set; get; }
		string str;

		public StaticElement(string elem, Coord printPos)
		{
			pos = printPos;
			str = elem;
		}

		public void Print()
		{
			Coord currPos = pos;
			Console.SetCursorPosition(currPos.x, currPos.y);
			foreach (char j in str)
				if (j != '\n')
					Console.Write(j);
				else
					Console.SetCursorPosition(currPos.x, ++currPos.y);
		}
	}

	class ActiveStaticElement : StaticElement, ActiveElement
	{
		public Coord pos { set; get; }
		string str;

		public ActiveStaticElement(string elem, Coord printPos) : base(elem, printPos)
		{
		}

	}

	class ActiveInputElement : ActiveElement
	{
		byte maxLen;
		string str, input;
		public Coord pos { set; get; }
		Coord inputPos;

		public ActiveInputElement(string elem, Coord printPos, Coord InputPos, byte MaxLen)
		{
			pos = printPos;
			str = elem;
			input = "";
			inputPos = InputPos;
			maxLen = MaxLen;
		}

		public void AddToValue(char c)
		{
			if(input.Length < maxLen)
				input += c;
		}

		public void DelLastSymbol()
		{
			if(input.Length != 0)
				input = input.Substring(0, input.Length - 1);
		}

		public string GetValue()
		{
			return str;
		}

		public void Print(){
			Coord currPos = pos;
			Console.SetCursorPosition(currPos.x, currPos.y);
			foreach (char j in str)
				if (j != '\n')
					Console.Write(j);
				else
					Console.SetCursorPosition(currPos.x, ++currPos.y);
			Console.SetCursorPosition(inputPos.x + pos.x, inputPos.y + pos.y);
			Console.Write(input);
		}
	}

	class ActiveElementDraw
	{
		Element[] elements;

		byte currElement;

		public ActiveElementDraw(params Element[] arr)
		{
			elements = arr;
		}

		public void InitStatic()
		{
			for (byte i = 0; i < elements.Length; ++i)
				if (elements[i] is ActiveElement == false)
					elements[i].Print();
		}

		public void Print()
		{
			Coord currPos;
			for (byte i = 0; i < elements.Length; ++i)
			{
				if (i == currElement)
					Console.BackgroundColor = ConsoleColor.DarkYellow;
				currPos = elements[i].pos;
				if(elements[i] is ActiveElement)
					elements[i].Print();
				if (i == currElement)
					Console.BackgroundColor = ConsoleColor.Black;
			}

		}

		public byte Input(ConsoleKeyInfo read)
		{
			do {
				switch (read.Key)
				{
					case ConsoleKey.PageUp:
						if (currElement != 0)
							--currElement;
						else
							currElement = (byte)(elements.Length - 1);
						break;
					case ConsoleKey.PageDown:
						++currElement;
						if (currElement == elements.Length)
							currElement = 0;
						break;
					case ConsoleKey.Enter:
						return currElement;
				}
			} while (elements[currElement] is ActiveElement == false);

			if (elements[currElement] is ActiveInputElement)
			{
				if (char.IsLetterOrDigit(read.KeyChar))
					((ActiveInputElement)(elements[currElement])).AddToValue(read.KeyChar);

				else if (read.Key == ConsoleKey.Backspace)
					((ActiveInputElement)(elements[currElement])).DelLastSymbol();
			}

			return 255;
		}
	}

	class UiConsoleBookShop
	{
		BookShop shop;

		ActiveElementDraw head;

		public UiConsoleBookShop()
		{
			string verticalLine = "|\n";
			for (byte i = 0; i < 44; ++i)
				verticalLine += "|\n";
			shop = new BookShop();
			head = new ActiveElementDraw(
				new ActiveStaticElement("Main", new Coord(2, 1)),
				new ActiveInputElement("Find: " + new string(' ', 75), new Coord(21, 1), new Coord(6,0), 74),
				new ActiveStaticElement("Login/Register", new Coord(134, 1)),
				new StaticElement(new string('_', 150), new Coord(0, 0)),
				new StaticElement(new string('_', 150), new Coord(0, 45)),
				new StaticElement(new string('-', 148), new Coord(1, 2)),
				new StaticElement(verticalLine, new Coord(0, 1)),
				new StaticElement(verticalLine, new Coord(150, 1)),
				new StaticElement("|", new Coord(7, 1)),

				new StaticElement("|", new Coord(20, 1)),
				new StaticElement("|", new Coord(102, 1)),

				new StaticElement("|", new Coord(133, 1)),
				new StaticElement("|", new Coord(148, 1))
				);
		}

		public void Launch()
		{
			Console.SetWindowSize(Console.LargestWindowWidth, Console.LargestWindowHeight);
			PrintHelloScreen();
			System.Threading.Thread.Sleep(1500);
			Console.Clear();
			MainScreen();
		}

		void PrintHelloScreen()
		{
			Console.Write("\n\n\n\n\n\n\n\n\n" + @"
          .-. .-')                     ^,,^   .-. .-')         .-')      ('-. .-.                   _ (`-.  
          \  ( OO )                   ( oO )  \  ( OO )       ( OO ).   ( OO )  /                  ( (OO  ) 
           ;-----.\    .-'),-----.    ,-----.  ,--. ,--.      (_)---\_)  ,--. ,--.   .-'),-----.   _.`     \ 
           | .-.  |   ( OO'  .-.  '  '  .-.  ' |  .'   /      /    _ |   |  | |  |  ( OO'  .-.  ' (__...--'' 
           | '-' /_)  /   |  | |  |  |  | |  | |      /,      \  :` `.   |   .|  |  /   |  | |  |  |  /  | | 
           | .-. `.   \_) |  |\|  |  |  | |  | |     ' _)      '..`''.)  |       |  \_) |  |\|  |  |  |_.' | 
           | |  \  |    \ |  | |  |  |  | |  | |  .   \       .-._)   \  |  .-.  |    \ |  | |  |  |  .___.' 
           | '--'  /     `'  '-'  '  '  '-'  ' |  |\   \      \       /  |  | |  |     `'  '-'  '  |  |      
           `------'       `-------'  `-------' `--' '--'       `-----'    `--' `-'       `------'   `-'     



											 ____  ____  ____ 
											||H ||||i ||||! ||
											||__||||__||||__||
											|/__\||/__\||/__\|");
		}

		ConsoleKeyInfo InbisibleInput()
		{
			Console.SetCursorPosition(103, 1);
			ConsoleColor prev = Console.ForegroundColor;
			Console.ForegroundColor = Console.BackgroundColor;
			ConsoleKeyInfo rez = Console.ReadKey();
			Console.ForegroundColor = prev;
			return rez;
		}

		void MainScreen()
		{
			byte choose;
			head.InitStatic();
			while (true)
			{
				head.Print();
				choose = head.Input(InbisibleInput());
				if (choose == 255)
					continue;
			}
		}

		void BooksListScreen()
		{

		}

		void BookInfoScreen()
		{

		}

	}

	class Program
	{
		static void Main(string[] args)
		{

			UiConsoleBookShop shop = new UiConsoleBookShop();

			shop.Launch();

			Console.SetCursorPosition(100, 50);

			//ActiveElementDraw draw = new ActiveElementDraw(
			//	new ActiveStaticElement("#####\n#####\n#####", new Coord(0,0)),
			//	new ActiveStaticElement("#####\n#####\n#####", new Coord(45, 0)),
			//	new ActiveInputElement("-----\n|   |\n-----", new Coord(45, 15), new Coord(1,1), 3)
			//	);
			//while (true)
			//{
			//	draw.Print();
			//	draw.Input(Console.ReadKey());
			//}
			//Console.WriteLine(Book.BookTypes.Detective.ToString());
			//BookShop s = new BookShop();
			//foreach(var i in s.GetBookTypes())
			//{
			//	Console.WriteLine(i);
			//}
			//Console.WriteLine(s.GetBookTypes().Length);
		}
	}
}
