using System;

using BookN;
using CargoN;
using ClientN;
using ActiveElements;

namespace BookShopN {
	namespace UI {
		static class Validator {
			static public bool IsEmail(string str) {
				bool sob = false;
				foreach (char i in str) {
					if (i == '@')
						sob = true;
					if (sob && i == '.')
						return true;
				}
				return false;
			}

			static public bool IsPhone(string str) {
				foreach (char i in str)
					if (!char.IsNumber(i))
						return false;
				return true;
			}

			static public string ValidStr(string str, byte len) {
				if (str.Length < len)
					str += new string(' ', len - str.Length);
				else if (str.Length > len)
					str = str.Substring(0, len - 3) + "...";
				return str;
			}
		}


		class UiConsoleBookShop {
			BookShop shop;

			Coord downRightCorner = new Coord(150, 45);
			ActiveElementDraw head;

			delegate bool NextWindow();

			public UiConsoleBookShop() : this(null) {
			}

			public UiConsoleBookShop(ICargo Cargo) {

				string verticalLine = "|\n";
				for (byte i = 0; i < 44; ++i)
					verticalLine += "|\n";
				shop = new BookShop(Cargo);
				head = new ActiveElementDraw(
					new ActiveStaticElement("Main", new Coord(2, 1)),
					new ActiveInputElement("Find: " + new string(' ', 75), new Coord(21, 1), new Coord(6, 0), 74),
					new ActiveDoubleElement("Login/Register", new Coord(134, 1), "Logout", new Coord(134, 1)),
					new StaticElement(new string('_', downRightCorner.x), new Coord(0, 0)),
					new StaticElement(new string('_', downRightCorner.x), new Coord(0, downRightCorner.y)),
					new StaticElement(new string('-', downRightCorner.x - 2), new Coord(1, 2)),
					new StaticElement(verticalLine, new Coord(0, 1)),
					new StaticElement(verticalLine, new Coord(downRightCorner.x, 1)),
					new StaticElement("|", new Coord(7, 1)),

					new StaticElement("|", new Coord(20, 1)),
					new StaticElement("|", new Coord(102, 1)),

					new StaticElement("|", new Coord(133, 1)),
					new StaticElement("|", new Coord(148, 1))
					);
			}

			public void Launch() {
				Console.SetWindowSize(Console.LargestWindowWidth, Console.LargestWindowHeight);
				PrintHelloScreen();
				//System.Threading.Thread.Sleep(1500);
				Console.Clear();
				MainScreen();
				Console.Clear();
			}

			ConsoleKeyInfo InbisibleInput() {
				Console.SetCursorPosition(103, 1);
				ConsoleColor prev = Console.ForegroundColor;
				Console.ForegroundColor = Console.BackgroundColor;
				ConsoleKeyInfo rez = Console.ReadKey();
				Console.ForegroundColor = prev;
				return rez;
			}

			void PrintHelloScreen() {
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

			void MainScreen() {
				string[] bookTypes = shop.GetBookTypes();
				Element[] mainScreenElements = new Element[bookTypes.Length + 3];
				mainScreenElements[0] = new ActiveStaticElement("__________\n| Trash  |\n----------", new Coord((short)(downRightCorner.x - 10),4));

					mainScreenElements[1] = mainScreenElements[2] = null;

				for (byte i = 0; i < bookTypes.Length; ++i)
					mainScreenElements[i + 3] = new ActiveStaticElement(bookTypes[i], new Coord(5, (short)(i + 4)));

				byte choose;
				ActiveElementDraw mainWindow = new ActiveElementDraw(head, mainScreenElements);

				mainWindow.InitStatic();
				while (true) {
					mainWindow.Print();
					choose = mainWindow.Input(InbisibleInput());
					if (choose == 255)
						continue;

					switch (choose) {
					//Main
					case 0:
					break;
					//Find
					case 1:
					mainWindow.ClearScreen();
					BooksListByName();
					mainWindow.InitStatic();
					break;
					//Register/Login    Logout
					case 2:
					mainWindow.ClearScreen();
					ClickOnLoginBtn();
					if (shop.IsLogOn())
						mainScreenElements[1] = new ActiveStaticElement("__________\n|UserInfo|\n----------", new Coord((short)(downRightCorner.x - 10), 7));
					else
						mainScreenElements[1] = null;

					if (shop.IsSuperUserLogOn())
						mainScreenElements[2] = new ActiveStaticElement("____________\n|AdminPanel|\n------------", new Coord((short)(downRightCorner.x - 12), 10));
					else
						mainScreenElements[2] = null;
					mainWindow = new ActiveElementDraw(head, mainScreenElements);
					mainWindow.InitStatic();
					break;
					//Trash manager
					case 13:
					mainWindow.ClearScreen();
					TrashScreen(shop.GetClientTrash());
					mainWindow.InitStatic();
					break;
					//User profile
					case 14:
					mainWindow.ClearScreen();
					UserScreen(shop.GetClient());
					mainWindow.InitStatic();
					break;
					//Admin terminal
					case 15:
					mainWindow.ClearScreen();
					AdminPanel();
					mainWindow.InitStatic();
					break;
					default:
					if (choose >= 16) {
						mainWindow.ClearScreen();
						BooksListByType((Book.BookTypes)(choose - 15));
						mainWindow.InitStatic();
					}
					break;
					}
				}

			}

			void UserScreen(Client user) {
				Console.SetCursorPosition(100, 40);
				Console.Write("UserScreen");
			}

			bool TrashScreen(Trash trash) {
				Element[] trashToPrint = new Element[trash.Length * 3 + 1];
				Book currBook;
				string str;
				for (int i = 0; i < trash.Length; ++i) {
					if (trash[i].stored is Book) {
						currBook = trash[i].stored as Book;
						str = Validator.ValidStr(currBook.shortTitle, 16) + " | ";
						str += Validator.ValidStr(currBook.autherName, 16) + " | ";
						str += Validator.ValidStr(currBook.price.ToString(), 7);
						trashToPrint[i * 3] = new ActiveStaticElement(str, new Coord(5,(short)(i + 5)));
						trashToPrint[i * 3 + 1] = new ActiveCounter("-----", new Coord(53, (short)(i + 5)), new Coord(1, 0), ref trash[i].cnt, 1, 255, "   ");
						trashToPrint[i * 3 + 2] = new ActiveStaticElement("X", new Coord(62, (short)(i + 5)));
					}

				}
				str = Validator.ValidStr("Title", 16) + " | ";
				str += Validator.ValidStr("Auther name", 16) + " | ";
				str += Validator.ValidStr("Price", 7) + " | ";
				str += Validator.ValidStr("Cnt", 5) + " | ";
				str += Validator.ValidStr("Del", 5);
				trashToPrint[trash.Length * 3] = new StaticElement(str, new Coord(5, 4));

				byte choose;
				ActiveElementDraw trashWindow = new ActiveElementDraw(head, trashToPrint);
				NextWindow nextWindow = null;

				trashWindow.InitStatic();
				while (true) {
					trashWindow.Print();
					choose = trashWindow.Input(InbisibleInput());
					if (choose == 255)
						continue;

					switch (choose) {
					//Main
					case 0:
					goto TRASH_SCREEN_RETURN;
					//Find
					case 1:
					nextWindow = new NextWindow(BooksListByName);
					goto TRASH_SCREEN_RETURN;
					//Register/Login    Logout
					case 2:
					nextWindow = new NextWindow(ClickOnLoginBtn);
					goto TRASH_SCREEN_RETURN;
					default:
					choose -= 13;
					if (choose % 3 == 0) {
						trashWindow.ClearScreen();
						BookInfoScreen(((Book)trash[choose / 3].stored), false);
						trashWindow.InitStatic();
					}
					else if (choose % 3 == 2) {
						trash.Delete(((Book)trash[choose / 3].stored));
						trashWindow.ClearScreen();
						TrashScreen(trash);
						goto TRASH_SCREEN_RETURN;
					}
					break;
					}
				}

			TRASH_SCREEN_RETURN:
				trashWindow.ClearScreen();
				if (nextWindow != null)
					nextWindow.Invoke();
				return true;
			}

			void AdminPanel() {
				bool isRunning = true;
				string str;
				Console.SetCursorPosition(0, 0);
				while (isRunning) {
					Console.Write("> ");
					str = Console.ReadLine();
					str = str.Trim();
					if (str == "?") {
						Console.Write('\t'); Console.WriteLine("exit");
						Console.Write('\t'); Console.WriteLine("add [bookTitle] | [author] | [price] | [pages]");
						Console.Write('\t'); Console.WriteLine("del [bookTitle] | [author]");
					}
					else if (str == "exit")
						isRunning = false;
					else if (str.Substring(0, 3) == "del") {
						str = str.Substring(3, str.Length - 3);
						string[] info = new string[2];
						char[] sep = new char[] { '|' };
						info = str.Split(sep, info.Length);
						for (int i = 0; i < info.Length; ++i) 
							info[i] = info[i].Trim();
						if (shop.GetCargo().Remove(new Book(Book.BookTypes.NONE, info[1], info[0], 0, 0)) != null) 
							Console.WriteLine("del succes");
						else 
							Console.WriteLine("book not exist");
						
					}
					else if (str.Substring(0, 3) == "add") {
						str = str.Substring(3, str.Length - 3);
						string[] info = new string[4];
						double price;
						int pages;
						char[] sep = new char[] { '|' };
						info = str.Split(sep, info.Length);
						for (int i = 0; i < info.Length; ++i) 
							info[i] = info[i].Trim();
						if (!double.TryParse(info[2], out price) || !int.TryParse(info[3], out pages)) 
							Console.WriteLine("add error");
						else {
							shop.GetCargo().Add(new Book(Book.BookTypes.NONE, info[1], info[0], double.Parse(info[2]), (ushort) int.Parse(info[3])));
							Console.WriteLine("add succes");
						}
					}
				}
				Console.Clear();
			}

			bool BooksListByType(Book.BookTypes type) {
				System.Collections.Generic.List<Book> find = shop.FindBookByType(type);
				if (find.Count == 0)
					return false;
				return BooksListScreen(find);
			}

			bool BooksListByName() {
				string toFind = head.GetInputValue(1);
				if (toFind.Length < 3)
					return false;
				System.Collections.Generic.List<Book> find = shop.FindBookByTitle(toFind);
				if (find.Count == 0)
					return false;
				return BooksListScreen(find);
			}
			
			bool BooksListScreen(System.Collections.Generic.List<Book> find) {
				bool toReturn = false;

				Element[] booksToPrint = new Element[find.Count + 2];
				Book currBook = null;
				string str = null;
				int len = find.Count > downRightCorner.y - 7 ? downRightCorner.y - 7 : find.Count;
				for (int i = 0; i < len; ++i) {
					currBook = find[i];
					str = Validator.ValidStr(currBook.shortTitle, 16) + " | ";
					str += Validator.ValidStr(currBook.autherName, 16) + " | ";
					str += Validator.ValidStr(currBook.price.ToString(), 7);
					if(i % 2 == 0)
						booksToPrint[i] = new ActiveStaticElement(str, new Coord(5, (short)(i / 2 + 5)));
					else
						booksToPrint[i] = new ActiveStaticElement(str, new Coord((short)(downRightCorner.x / 2 + 3), (short)(i / 2 + 5)));
				}

				str = Validator.ValidStr("Title", 16) + " | ";
				str += Validator.ValidStr("Auther name", 16) + " | ";
				str += Validator.ValidStr("Price", 7);
				booksToPrint[find.Count] = new StaticElement(str, new Coord(5, 4));
				if (find.Count != 1)
					booksToPrint[find.Count + 1] = new StaticElement(str, new Coord((short)(downRightCorner.x / 2 + 3), 4));
				else
					booksToPrint[find.Count + 1] = new StaticElement("",new Coord(0,0));

				byte choose;
				ActiveElementDraw findWindow = new ActiveElementDraw(head, booksToPrint);
				NextWindow nextWindow = null;

				findWindow.InitStatic();
				while (true) {
					findWindow.Print();
					choose = findWindow.Input(InbisibleInput());
					if (choose == 255)
						continue;

					switch (choose) {
					//Main
					case 0:
					goto BOOK_LIST_SCREEN_RETURN;
					//Find
					case 1:
					nextWindow = new NextWindow(BooksListByName);
					goto BOOK_LIST_SCREEN_RETURN;
					//Register/Login    Logout
					case 2:
					nextWindow = new NextWindow(ClickOnLoginBtn);
					goto BOOK_LIST_SCREEN_RETURN;
					default:
					if (choose >= 13) {
						findWindow.ClearScreen();
						if(BookInfoScreen(find[choose - 13]))
							goto BOOK_LIST_SCREEN_RETURN;
						findWindow.InitStatic();
					}
					break;
					}
				}

			BOOK_LIST_SCREEN_RETURN:
				findWindow.ClearScreen();
				head.InitStatic();
				if (nextWindow != null)
					nextWindow.Invoke();
				return toReturn;
			}

			bool BookInfoScreen(Book book, bool withTrashBtn = true) {
				if(book == null)
					return false;

				byte choose;
				ActiveElementDraw bookWindow;
				if (withTrashBtn) {
					bookWindow = new ActiveElementDraw(head,
						new StaticElement('[' + book.type.ToString() + "] " + book.shortTitle, new Coord((short)(downRightCorner.x / 2 + 3), 5)),
						new StaticElement(book.autherName, new Coord((short)(downRightCorner.x / 2 + 3), 6)),
						new StaticElement("Price:" + book.price.ToString(), new Coord((short)(downRightCorner.x / 2 + 3), 7)),
						new StaticElement("Pages:" + book.pages.ToString(), new Coord((short)(downRightCorner.x / 2 + 3), 8)),

						new ActiveStaticElement("______________\n|Add to trash|\n--------------", new Coord((short)(downRightCorner.x / 2 + downRightCorner.x / 6), 15))
					);
				}
				else {
					bookWindow = new ActiveElementDraw(head,
						new StaticElement('[' + book.type.ToString() + "] " + book.shortTitle, new Coord((short)(downRightCorner.x / 2 + 3), 5)),
						new StaticElement(book.autherName, new Coord((short)(downRightCorner.x / 2 + 3), 6)),
						new StaticElement("Price:" + book.price.ToString(), new Coord((short)(downRightCorner.x / 2 + 3), 7)),
						new StaticElement("Pages:" + book.pages.ToString(), new Coord((short)(downRightCorner.x / 2 + 3), 8))
					);
				}
				NextWindow nextWindow = null;

				bookWindow.InitStatic();
				while (true) {
					bookWindow.Print();
					choose = bookWindow.Input(InbisibleInput());
					if (choose == 255)
						continue;

					switch (choose) {
					//Main
					case 0:
					goto BOOK_INFO_SCREEN_RETURN;
					//Find
					case 1:
					nextWindow = new NextWindow(BooksListByName);
					goto BOOK_INFO_SCREEN_RETURN;
					//Register/Login    Logout
					case 2:
					nextWindow = new NextWindow(ClickOnLoginBtn);
					goto BOOK_INFO_SCREEN_RETURN;
					case 17:
					shop.AddToTrash(book);
					goto BOOK_INFO_SCREEN_RETURN;
					default:
					break;
					}
				}

			BOOK_INFO_SCREEN_RETURN:
				bookWindow.ClearScreen();
				head.InitStatic();
				if (nextWindow != null) {
					nextWindow.Invoke();
					return true;
				}
				return false;
			}

			bool ClickOnLoginBtn() {
				if (head.GetDoubleElementContrain(2)) {
					shop.Logoff();
					head.ChangeDoubleElementContrain(2);
					return false;
				}
				RegisterAndLoginScreen();
				return true;
			}

			void RegisterAndLoginScreen() {
				byte choose;
				ActiveElementDraw loginWindow;
				NextWindow nextWindow = null;
				{
					loginWindow = new ActiveElementDraw(head,

						new StaticElement(" ::Login::", new Coord(10, 5)),
						new ActiveInputElement("Login:" + new string(' ', 16), new Coord(10, 7), new Coord(7, 0), 15),
						new ActiveInputElement("Pass:" + new string(' ', 34), new Coord(10, 8), new Coord(7, 0), 32),
						new ActiveStaticElement("-------\n|Login|\n-------", new Coord(10, 10)),


						new StaticElement("╔══╗╔═══╗\n║╔╗║║╔═╗║\n║║║║║╚═╝║\n║║║║║╔╗╔╝\n║╚╝║║║║║\n╚══╝╚╝╚╝", new Coord((short)(downRightCorner.x / 2 - 10), (short)(downRightCorner.y / 2 - 5))),

						new StaticElement(" ::Register::", new Coord((short)(downRightCorner.x / 2 + 10), 5)),
						new ActiveInputElementAllSymbols("E-mail: " + new string(' ', 31), new Coord((short)(downRightCorner.x / 2 + 10), 7), new Coord(8, 0), 32),
						new ActiveInputElement("Login: " + new string(' ', 17), new Coord((short)(downRightCorner.x / 2 + 10), 8), new Coord(8, 0), 16),
						new ActiveInputElement("Pass: " + new string(' ', 34), new Coord((short)(downRightCorner.x / 2 + 10), 9), new Coord(8, 0), 32),

						new ActiveInputElement("Name:    " + new string(' ', 16), new Coord((short)(downRightCorner.x / 2 + 10), 11), new Coord((short)"Name:    ".Length, 0), 16),
						new ActiveInputElement("Surname: " + new string(' ', 16), new Coord((short)(downRightCorner.x / 2 + 10), 12), new Coord((short)"Surname: ".Length, 0), 16),
						new ActiveInputElement("Phone:   " + new string(' ', 13), new Coord((short)(downRightCorner.x / 2 + 10), 13), new Coord((short)"Phone:   ".Length, 0), 10),

						new ActiveStaticElement("----------\n|Register|\n----------", new Coord((short)(downRightCorner.x / 2 + 10), 15))
						);
				}

				loginWindow.InitStatic();
				while (true) {
					loginWindow.Print();
					choose = loginWindow.Input(InbisibleInput());
					if (choose == 255)
						continue;

					switch (choose) {
					//Main
					case 0:
					goto REGISTER_AND_LOGIN_RETURN;
					//Find
					case 1:
					nextWindow = new NextWindow(BooksListByName);
					goto REGISTER_AND_LOGIN_RETURN;
					//Register/Login    Logout
					case 2:
					break;
					//Login
					case 16:
					if (shop.Login(loginWindow.GetInputValue(14), LoginPass.Hasher(loginWindow.GetInputValue(15))) != null) {
						head.ChangeDoubleElementContrain(2);
						goto REGISTER_AND_LOGIN_RETURN;
					}
					break;
					//Register
					case 25:
					if (loginWindow.GetInputValue(22).Length == 0 || loginWindow.GetInputValue(23).Length == 0
						|| loginWindow.GetInputValue(24).Length == 0 || loginWindow.GetInputValue(21).Length == 0
						|| loginWindow.GetInputValue(20).Length == 0 || loginWindow.GetInputValue(19).Length == 0
						)
						break;
					if (! (Validator.IsEmail(loginWindow.GetInputValue(19)) && Validator.IsPhone(loginWindow.GetInputValue(24)) ))
						break;
					if (shop.CreateUser(new Person(loginWindow.GetInputValue(22), loginWindow.GetInputValue(23), loginWindow.GetInputValue(24)),
						loginWindow.GetInputValue(20), LoginPass.Hasher(loginWindow.GetInputValue(21)), loginWindow.GetInputValue(19))) {
						shop.Login(loginWindow.GetInputValue(20), LoginPass.Hasher(loginWindow.GetInputValue(21)));
						head.ChangeDoubleElementContrain(2);
						goto REGISTER_AND_LOGIN_RETURN;
					}

					break;
					default:
					//Console.Write(choose);
					break;
					}
				}

			REGISTER_AND_LOGIN_RETURN:
				loginWindow.ClearScreen();
				head.InitStatic();
				if (nextWindow != null)
					nextWindow.Invoke();
			}
		}
	}
}