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
				byte choose;
				head.InitStatic();
				while (true) {
					head.Print();
					choose = head.Input(InbisibleInput());
					if (choose == 255)
						continue;

					switch (choose) {
					//Main
					case 0:
					break;
					//Find
					case 1:
							BooksListScreen();
					break;
					//Register/Login    Logout
					case 2:
					ClickOnLoginBtn();
					break;
					}
				}

			}
			
			bool BooksListScreen() {
				bool toReturn = false;
				string toFind = head.GetInputValue(1);
				if (toFind.Length < 3)
					return false;

				System.Collections.Generic.List<Book> find = shop.FindBookByTitle(toFind);
				if (find.Count == 0)
					return false;

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
				booksToPrint[find.Count + 1] = new StaticElement(str, new Coord((short)(downRightCorner.x / 2 + 3), 4));

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
					nextWindow = new NextWindow(BooksListScreen);
					goto BOOK_LIST_SCREEN_RETURN;
					//Register/Login    Logout
					case 2:
					nextWindow = new NextWindow(ClickOnLoginBtn);
					goto BOOK_LIST_SCREEN_RETURN;
					default:
					//Console.Write(choose);
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

			void BookInfoScreen(Book info) {

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
					nextWindow = new NextWindow(BooksListScreen);
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